/**
 * odplayerh264 - Tool for replaying video streams encoded with h264.
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

#include <cstring>
#include <iostream>
#include <string>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odtools/player/Player.h>

#include "opendavinci/generated/odcore/data/image/H264Frame.h"

#include "PlayerH264.h"
#include "PlayerH264Decoder.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::player;

    uint32_t basePortForChildProcesses = 1234;

    __attribute__((noreturn))
    void handleInChild(int id) {
        PlayerH264Decoder decoder(basePortForChildProcesses + id);

        const uint32_t ONE_SECOND = 1000 * 1000;
        while (decoder.hasConnection()) {
            odcore::base::Thread::usleepFor(ONE_SECOND);
        }

        cout << "[odplayerh264] Goodbye from " << id << endl;
        exit(EXIT_SUCCESS);
    }

    ///////////////////////////////////////////////////////////////////////////

    PlayerH264::PlayerH264(const odcore::io::URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading, const uint32_t &basePort) :
        Player(url, autoRewind, memorySegmentSize, numberOfMemorySegments, threading),
        m_basePort(basePort),
        m_mapOfDecodersMutex(),
        m_mapOfDecoders() {
        basePortForChildProcesses = basePort;

        // Register all codecs from FFMPEG.
        avcodec_register_all();

        // Register us as delegate to handle odcore::data::image::H264Frame messages.
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), this);
    }

    PlayerH264::~PlayerH264() {
        // Unregister us as delegate to handle odcore::data::image::H264Frame messages.
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), NULL);

        // Close connection to child.
        for(auto entry : m_mapOfDecoders) {
            entry.second->getConnection()->stop();
        }

        // Terminate child processes.
        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(ONE_SECOND);
        for(auto entry : m_mapOfDecoders) {
            kill(entry.second->getPID(), SIGKILL);
        }

        m_mapOfDecoders.clear();
    }

    Container PlayerH264::process(Container &c) {
        static uint32_t id = 0;
        Lock l(m_mapOfDecodersMutex);

        Container replacementContainer;

        if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
            odcore::data::image::H264Frame h264frame = c.getData<odcore::data::image::H264Frame>();

            // Find existing or create new encoder.
            auto delegateEntry = m_mapOfDecoders.find(h264frame.getH264Filename());
            if (delegateEntry == m_mapOfDecoders.end()) {
                shared_ptr<PlayerH264ChildHandler> handler(new PlayerH264ChildHandler(m_basePort + id));

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

                    m_mapOfDecoders[h264frame.getH264Filename()] = handler;

                    cout << "[odplayerh264] Created decoding child process " << handler->getPID() << " to handle '" << h264frame.getH264Filename() << "'." << endl;
                    id++;

                    replacementContainer = m_mapOfDecoders[h264frame.getH264Filename()]->process(c);
                }
            }
            else {
                // Reuse existing decoder.
                replacementContainer = m_mapOfDecoders[h264frame.getH264Filename()]->process(c);
            }
        }

        return replacementContainer;
    }

} // odplayerh264
