/**
 * odredirector - Tool for dumping data to stdout or reading back from stdin
 * Copyright (C) 2015 Christian Berger
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
#include <cstring>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/CommandLineArgument.h"
#include "opendavinci/odcore/base/CommandLineParser.h"
#include "opendavinci/odcore/base/QueryableNetstringsDeserializerABCF.h"
#include "opendavinci/odcore/wrapper/jpg/JPG.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/odcore/data/image/CompressedImage.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include "Redirector.h"
#include "StdoutPump.h"

namespace odredirector {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;

    Redirector::Redirector(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odredirector"),
        m_fromstdin(false),
        m_tostdout(false),
        m_jpegQuality(15),
        m_mapOfSharedMemories() {
        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);
    }

    Redirector::~Redirector() {
        m_mapOfSharedMemories.clear();
    }

    void Redirector::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("fromstdin");
        cmdParser.addCommandLineArgument("tostdout");
        cmdParser.addCommandLineArgument("jpegquality");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentFROMSTDIN = cmdParser.getCommandLineArgument("fromstdin");
        CommandLineArgument cmdArgumentTOSTDOUT = cmdParser.getCommandLineArgument("tostdout");
        CommandLineArgument cmdArgumentJPEGQUALITY = cmdParser.getCommandLineArgument("jpegquality");

        if (cmdArgumentFROMSTDIN.isSet()) {
            m_fromstdin = cmdArgumentFROMSTDIN.getValue<int>() == 1;
        }

        if (cmdArgumentTOSTDOUT.isSet()) {
            m_tostdout = cmdArgumentTOSTDOUT.getValue<int>() == 1;
        }

        if (cmdArgumentJPEGQUALITY.isSet()) {
            m_jpegQuality = cmdArgumentJPEGQUALITY.getValue<int32_t>();

            if (m_jpegQuality < 1 || m_jpegQuality > 100) {
                clog << "Value for parameter --jpegquality must be between 1 and 100; using default value 15." << endl;
                m_jpegQuality = 15;
            }
        }
    }

    void Redirector::setUp() {}

    void Redirector::tearDown() {}

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Redirector::body() {
        // Enforce synchronized behavior with C STDIN and STDOUT.
        cin.sync_with_stdio(true);
        cout.sync_with_stdio(true);

        // Create a stdout pump.
        StdoutPump stdoutPump(m_jpegQuality);

        if (m_tostdout) {
            // ...that is called automagically whenever we receive data from the UDP multicast session.
            addDataStoreFor(stdoutPump);
        }

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            if (m_fromstdin) {
                // Please note that reading from stdin does not evaluate sending latencies.
                while (cin.good()) {
                    // Buffer from cin.
                    stringstream containerBuffer;
                    // Fill buffer.
                    QueryableNetstringsDeserializerABCF::fillBuffer(cin, containerBuffer);

                    // Decode container from buffer.
                    Container c;
                    containerBuffer >> c;

                    // Compressed images are transformed into regular shared images again.
                    if (c.getDataType() == odcore::data::image::CompressedImage::ID()) {
                        odcore::data::image::CompressedImage ci = c.getData<odcore::data::image::CompressedImage>();

                        // Check, whether a shared memory was already created for this SharedImage; otherwise, create it and save it for later.
                        map<string, std::shared_ptr<odcore::wrapper::SharedMemory> >::iterator it = m_mapOfSharedMemories.find(ci.getName());
                        if (it == m_mapOfSharedMemories.end()) {
                            std::shared_ptr<odcore::wrapper::SharedMemory> sp = odcore::wrapper::SharedMemoryFactory::createSharedMemory(ci.getName(), ci.getSize());
                            m_mapOfSharedMemories[ci.getName()] = sp;
                        }

                        // Get the shared memory to put the uncompressed image into.
                        std::shared_ptr<odcore::wrapper::SharedMemory> sp = m_mapOfSharedMemories[ci.getName()];

                        int width = 0;
                        int height = 0;
                        int bpp = 0;

                        // Decompress image data.
                        unsigned char *imageData = odcore::wrapper::jpg::JPG::decompress(ci.getRawData(), ci.getCompressedSize(), &width, &height, &bpp, ci.getBytesPerPixel());

                        if ( (imageData != NULL) &&
                             (width > 0) &&
                             (height > 0) &&
                             (bpp > 0) ) {
                            // Lock shared memory to store the uncompressed data.
                            if (sp->isValid()) {
                                Lock l(sp);
                                ::memcpy(sp->getSharedMemory(), imageData, width * height * bpp);
                            }

                            // As we have now the decompressed image data in memory, create a SharedMemory data structure to describe it.
                            odcore::data::image::SharedImage si;
                            si.setName(ci.getName());
                            si.setWidth(ci.getWidth());
                            si.setHeight(ci.getHeight());
                            si.setBytesPerPixel(ci.getBytesPerPixel());
                            si.setSize(ci.getWidth() * ci.getHeight() * ci.getBytesPerPixel());

                            // Distribute the SharedImage information in the UDP multicast session.
                            Container c2(si);
                            getConference().send(c2);
                        }

                        OPENDAVINCI_CORE_FREE_POINTER(imageData);
                    }
                    else {
                        getConference().send(c);
                    }
                }
            }
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odredirector

