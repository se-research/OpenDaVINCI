/**
 * odmjpegstreamer - Tool to stream a given SharedImage as HTTP encapsulated MJPEG stream
 * Copyright (C) 2017 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <cstdlib>
#include <iostream>

#include <opendavinci/odcore/base/CommandLineArgument.h>
#include <opendavinci/odcore/base/CommandLineParser.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/wrapper/jpg/JPG.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>
#include <opendavinci/generated/odcore/data/image/SharedImage.h>

#include "MJPEGStreamer.h"

namespace odmjpegstreamer {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;

    MJPEGStreamer::MJPEGStreamer(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv, "odmjpegstreamer"),
        m_tcpAcceptor(),
        m_listOfConnections(),
        m_listOfClientHandlers(),
        m_port(8080),
        m_jpegQuality(15),
        m_bgr2rgb(false),
        m_sharedimagename(""),
        m_buffer(NULL) {
        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);
    }

    MJPEGStreamer::~MJPEGStreamer() {
        // Free pointer to compressed data.
        OPENDAVINCI_CORE_FREE_POINTER(m_buffer);
    }

    void MJPEGStreamer::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("port");
        cmdParser.addCommandLineArgument("jpegquality");
        cmdParser.addCommandLineArgument("sharedimagename");
        cmdParser.addCommandLineArgument("bgr2rgb");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentPORT = cmdParser.getCommandLineArgument("port");
        CommandLineArgument cmdArgumentJPEGQUALITY = cmdParser.getCommandLineArgument("jpegquality");
        CommandLineArgument cmdArgumentSHAREDIMAGENAME = cmdParser.getCommandLineArgument("sharedimagename");
        CommandLineArgument cmdArgumentBGR2RGB = cmdParser.getCommandLineArgument("bgr2rgb");

        if (cmdArgumentPORT.isSet()) {
            m_port = cmdArgumentPORT.getValue<uint32_t>();

            if (m_port < 1024 || m_port > 65000) {
                clog << "Value for parameter --port must be between 1024 and 65000; using default value 8080." << endl;
                m_port = 8080;
            }
        }

        if (cmdArgumentJPEGQUALITY.isSet()) {
            m_jpegQuality = cmdArgumentJPEGQUALITY.getValue<int32_t>();

            if (m_jpegQuality < 1 || m_jpegQuality > 100) {
                clog << "Value for parameter --jpegquality must be between 1 and 100; using default value 15." << endl;
                m_jpegQuality = 15;
            }
        }

        if (cmdArgumentSHAREDIMAGENAME.isSet()) {
            m_sharedimagename = cmdArgumentSHAREDIMAGENAME.getValue<string>();
        }

        if (cmdArgumentBGR2RGB.isSet()) {
            m_bgr2rgb = cmdArgumentBGR2RGB.getValue<int32_t>() == 1;
        }
    }

    void MJPEGStreamer::setUp() {
        try {
            m_tcpAcceptor = std::shared_ptr<odcore::io::tcp::TCPAcceptor>(odcore::io::tcp::TCPFactory::createTCPAcceptor(m_port));
            m_tcpAcceptor->setAcceptorListener(this);
            m_tcpAcceptor->start();
        }
        catch(string &exception) {
            cerr << "Error while creating TCP receiver: " << exception << endl;
        }
    }

    void MJPEGStreamer::tearDown() {
        if (NULL != m_tcpAcceptor.get()) {
            // Stop accepting new connections and unregister our handler.
            m_tcpAcceptor->stop();
            m_tcpAcceptor->setAcceptorListener(NULL);
        }

        for(auto it = m_listOfConnections.begin(); it != m_listOfConnections.end(); it++) {
            (*it)->stop();
            (*it)->setStringListener(NULL);
            (*it)->setConnectionListener(NULL);
        }

        m_listOfConnections.clear();
        m_listOfClientHandlers.clear();
    }

    void MJPEGStreamer::onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection) {
        if (connection.get()) {
            shared_ptr<MJPEGClientHandler> tmp = shared_ptr<MJPEGClientHandler>(new MJPEGClientHandler(connection));
            if (NULL != tmp.get()) {
                m_listOfClientHandlers.push_back(tmp);
                connection->setStringListener(tmp.get());
                connection->setConnectionListener(tmp.get());

                // Do not impose netstrings-like protocol.
                connection->setRaw(true);

                // Start receiving data from this connection.
                connection->start();

                m_listOfConnections.push_back(connection);
            }
        }
    }

    void MJPEGStreamer::nextContainer(odcore::data::Container &c) {
        // SharedImages are transformed into compressed images using JPEG compression.
        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

            if ( (1 == si.getBytesPerPixel()) || 
                 (3 == si.getBytesPerPixel()) ) {
                // No shared image set via console. Select the first one.
                if (m_sharedimagename == "") {
                    clog << "[odmjpegstreamer]: No shared image selected; using " << si.getName() << "." << std::endl;
                    m_sharedimagename = si.getName();
                }

                if (m_sharedimagename == si.getName()) {
                    bool retVal = false;
                    int compressedSize = si.getWidth() * si.getHeight() * si.getBytesPerPixel();
                    if (NULL == m_buffer) {
                        m_buffer = ::malloc(compressedSize);
                    }
                    if (NULL != m_buffer) {
                        std::shared_ptr<odcore::wrapper::SharedMemory> memory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                        if (memory->isValid()) {
                            Lock l(memory);

                            unsigned char *input = (unsigned char*)memory->getSharedMemory();
                            if (m_bgr2rgb && (3 == si.getBytesPerPixel())) {
                                for(int32_t i = 0; i < compressedSize; i += 3) {
                                    std::swap(input[i + 0], input[i + 2]);
                                }
                            }

                            retVal = odcore::wrapper::jpg::JPG::compress(m_buffer, compressedSize, si.getWidth(), si.getHeight(), si.getBytesPerPixel(), static_cast<unsigned char*>(input), m_jpegQuality);
                        }

                        if (retVal) {
                            for(auto it = m_listOfClientHandlers.begin(); it != m_listOfClientHandlers.end(); it++) {
                                (*it)->sendImage(static_cast<char*>(m_buffer), compressedSize);
                            }
                        }
                        if (!retVal) {
                            cerr << "[odmjpegstreamer]: Warning! Failed to compress image. Image skipped." << std::endl;
                        }
                    }
                }
            }
            else {
                cerr << "[odmjpegstreamer]: Warning! Color space not supported. Image skipped." << std::endl;
            }
        }
    }

} // odmjpegstreamer

