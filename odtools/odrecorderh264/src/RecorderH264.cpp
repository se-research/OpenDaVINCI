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

#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include <iostream>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/io/URL.h>

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


    string filenameBaseForChildProcesses = "";
    bool losslessForChildProcesses = true;
    uint32_t basePortForChildProcesses = 1234;

    __attribute__((noreturn))
    void handleInChild(int id) {
        RecorderH264Encoder encoder(filenameBaseForChildProcesses, losslessForChildProcesses, basePortForChildProcesses + id);

        const uint32_t ONE_SECOND = 1000 * 1000;
        while (encoder.hasConnection()) {
            odcore::base::Thread::usleepFor(ONE_SECOND);
        }

        cout << "[odrecorderh264] Goodbye from " << id << endl;
        exit(EXIT_SUCCESS);
    }

    ///////////////////////////////////////////////////////////////////////////

    RecorderH264::RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData, const bool &lossless, const uint32_t &basePort) :
        Recorder(url, memorySegmentSize, numberOfSegments, threading, dumpSharedData),
        m_filenameBase(""),
        m_lossless(lossless),
        m_basePort(basePort),
        m_mapOfEncodersMutex(),
        m_mapOfEncoders() {
        odcore::io::URL u(url);
        m_filenameBase = u.getResource();
        filenameBaseForChildProcesses = m_filenameBase;
        losslessForChildProcesses = m_lossless;
        basePortForChildProcesses = m_basePort;

        // This instance is handling all SharedImages by delegating to the corresponding entry in the map.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), this);

        // Register all codecs from FFMPEG.
        avcodec_register_all();
    }

    RecorderH264::~RecorderH264() {
        // Unregister us.
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), NULL);

        // Close connection to child.
        for(auto entry : m_mapOfEncoders) {
            entry.second->getConnection()->stop();
        }

        // Terminate child processes.
        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(ONE_SECOND);
        for(auto entry : m_mapOfEncoders) {
            kill(entry.second->getPID(), SIGKILL);
        }
        m_mapOfEncoders.clear();
    }

    Container RecorderH264::process(Container &c) {
        static uint32_t id = 0;
        Lock l(m_mapOfEncodersMutex);

        Container retVal;

        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();

            // Find existing or create new encoder.
            auto delegateEntry = m_mapOfEncoders.find(si.getName());
            if (delegateEntry == m_mapOfEncoders.end()) {
                shared_ptr<RecorderH264ChildHandler> handler(new RecorderH264ChildHandler(m_basePort + id));

                // Duplicate the current process.
                pid_t cpid = fork();
                if (cpid == 0) {
                    // Here, we are in the child process.
                    handleInChild(id);
                }
                else {
                    // Here, we are in the parent process.
                    handler->setPID(cpid);
                    handler->waitForClientToConnect();

                    m_mapOfEncoders[si.getName()] = handler;

                    cout << "[odrecorderh264] Created encoding child process " << handler->getPID() << endl;
                    id++;

                    retVal = m_mapOfEncoders[si.getName()]->process(c);
                }
            }
            else {
                // Reuse existing encoder.
                retVal = m_mapOfEncoders[si.getName()]->process(c);
            }
        }

        return retVal;
    }

} // odrecorderh264
