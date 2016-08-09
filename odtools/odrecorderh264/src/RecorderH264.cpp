/**
 * odrecorderh264 - Tool for recording data and encoding video streams with h264.
 * Copyright (C) 2016 Christian Berger
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

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
}

#include <unistd.h>
#include <sys/wait.h>

#include <iostream>

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include <opendavinci/odcore/io/tcp/TCPFactory.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>

#include "RecorderH264.h"

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io::tcp;
    using namespace odtools::recorder;


    string filenameBase;
    __attribute__((noreturn))
    void handleInChild(int id) {
        const bool LOSSLESS = true;
        RecorderH264Encoder encoder(filenameBase, LOSSLESS, 1234 + id);

        const uint32_t ONE_SECOND = 1000 * 1000;
        while (encoder.hasConnection()) {
            odcore::base::Thread::usleepFor(ONE_SECOND);
        }

        cout << "Goodbye from " << id << endl;
        exit(EXIT_SUCCESS);
    }

    RecorderH264ChildHandler::RecorderH264ChildHandler() :
        m_childPID(0),
        m_tcpacceptor(),
        m_connection(),
        m_condition(),
        m_response() {}

    RecorderH264ChildHandler::RecorderH264ChildHandler(const uint32_t &port) :
        m_childPID(0),
        m_tcpacceptor(),
        m_connection(),
        m_condition(),
        m_response() {

        try {
            m_tcpacceptor = odcore::io::tcp::TCPFactory::createTCPAcceptor(port);
            m_tcpacceptor->setAcceptorListener(this);
            // Start accepting new connections to receive data.
            m_tcpacceptor->start();
        }
        catch(string &exception) {
            cerr << "Error while creating TCP receiver: " << exception << endl;
        }
    }

    RecorderH264ChildHandler::~RecorderH264ChildHandler() {
        try {
            // Stop accepting new connections and unregister our handler.
            m_tcpacceptor->stop();
            m_tcpacceptor->setAcceptorListener(NULL);
        }
        catch(string &exception) {
            cerr << "Error while creating TCP receiver: " << exception << endl;
        }
    }

    void RecorderH264ChildHandler::waitForClientToConnect() {
        // Wait for the connecting client.
        cout << "Waiting for client to connect...";
        Lock l(m_condition);
        m_condition.waitOnSignal();
        cout << " Client connected." << endl;
    }

    void RecorderH264ChildHandler::handleConnectionError() {
        cout << "Connection terminated." << endl;

        // Stop this connection.
        m_connection->stop();

        // Unregister the listeners.
        m_connection->setStringListener(NULL);
        m_connection->setConnectionListener(NULL);
    }

    void RecorderH264ChildHandler::nextString(const std::string &s) {
        Lock l(m_condition);
        m_condition.wakeAll();

        stringstream sstr(s);
        sstr >> m_response;
    }

    void RecorderH264ChildHandler::onNewConnection(shared_ptr<TCPConnection> connection) {
        if (connection.get()) {
            cout << "Handle a new connection." << endl;

            m_connection = connection;

            // Set this class as StringListener to receive
            // data from this connection.
            m_connection->setStringListener(this);

            // Set this class also as ConnectionListener to
            // handle errors originating from this connection.
            m_connection->setConnectionListener(this);

            // Start receiving data from this connection.
            m_connection->start();

            // Indicate that we have a valid connection.
            Lock l(m_condition);
            m_condition.wakeAll();
        }
    }

    Container RecorderH264ChildHandler::process(Container &c) {
        // First, send the container to the child process.
        stringstream sstr;
        sstr << c;
        m_connection->send(sstr.str());

        // Wait for the child's response.
        Lock l(m_condition);
        m_condition.waitOnSignal();

        // The child's response is in m_response.
        return m_response;
    }


    RecorderH264::RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData, const bool &lossless) :
        Recorder(url, memorySegmentSize, numberOfSegments, threading, dumpSharedData),
        m_filenameBase(""),
        m_lossless(lossless),
        m_mapOfEncodersPerSharedImageSourceMutex(),
        m_mapOfEncodersPerSharedImageSource(),
        m_mapOfEncoders() {
        odcore::io::URL u(url);
        m_filenameBase = u.getResource();
        filenameBase = m_filenameBase;

        // Register all codecs from FFMPEG.
        avcodec_register_all();

        // This instance is handling all SharedImages by delegating to the corresponding entry in the map.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), this);
    }

    RecorderH264::~RecorderH264() {
        // Unregister us.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), NULL);

        // Close connection to child.
        for(auto entry : m_mapOfEncoders) {
            entry.second->m_connection->stop();
        }

        // Terminate child processes.
        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(ONE_SECOND * 5);
        for(auto entry : m_mapOfEncoders) {
            ::kill(entry.second->m_childPID, SIGKILL);
        }
        m_mapOfEncoders.clear();

        // Clean up map.
        m_mapOfEncodersPerSharedImageSource.clear();
    }

    Container RecorderH264::process(Container &c) {
        static uint32_t id = 0;
        Lock l(m_mapOfEncodersPerSharedImageSourceMutex);

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

            // Find existing or create new encoder.
            auto delegateEntry = m_mapOfEncoders.find(si.getName());
            if (delegateEntry == m_mapOfEncoders.end()) {
                const uint32_t PORT = 1234 + id;

                shared_ptr<RecorderH264ChildHandler> handler(new RecorderH264ChildHandler(PORT));

                // Duplicate the current process.
                pid_t cpid = fork();
                if (cpid == 0) {
                    // Child process.
                    handleInChild(id);
                }
                else {
                    // Parent process.
                    handler->m_childPID = cpid;
                    m_mapOfEncoders[si.getName()] = handler;

                    handler->waitForClientToConnect();

                    cout << "Created child " << handler->m_childPID << endl;
                    id++;

                    retVal = m_mapOfEncoders[si.getName()]->process(c);
                }
            }
            else {
//                cout << "To handle in child " << m_mapOfEncoders[si.getName()]->m_childPID << endl;
                retVal = m_mapOfEncoders[si.getName()]->process(c);
            }
        }

        return retVal;
    }


    Container RecorderH264::processOld(Container &c) {
        Lock l(m_mapOfEncodersPerSharedImageSourceMutex);

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
//            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

//            // Find existing or create new encoder.
//            shared_ptr<RecorderH264Encoder> encoder;
//            auto delegateEntry = m_mapOfEncodersPerSharedImageSource.find(si.getName());
//            if (delegateEntry != m_mapOfEncodersPerSharedImageSource.end()) {
//                encoder = m_mapOfEncodersPerSharedImageSource[si.getName()];
//            }
//            else {
//                if (m_mapOfEncodersPerSharedImageSource.size() == 0) {
//                    // Create a new encoder for this SharedImage.
//                    const string FILENAME = m_filenameBase + "-" + odcore::strings::StringToolbox::replaceAll(si.getName(), ' ', '_') + ".mp4";
//                    encoder = shared_ptr<RecorderH264Encoder>(new RecorderH264Encoder(FILENAME, m_lossless));
//                    m_mapOfEncodersPerSharedImageSource[si.getName()] = encoder;
//                }
//                else {
//                    // TODO: Fix multi-source handling.
//                    cerr << "[odrecorderh264] Multi-source processing not fully supported yet; discarding " << si.getName() << endl;
//                }
//            }

//            if (encoder.get() != NULL) {
//                // Use encoder for this SharedImage to encode next frame.
//                retVal = encoder->process(c);
//            }
        }

        return retVal;
    }

} // odrecorderh264
