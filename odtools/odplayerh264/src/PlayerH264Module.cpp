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

#include <cmath>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odtools/player/Player2.h"

#include "PlayerH264.h"
#include "PlayerH264Module.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io;
    using namespace odtools::player;

    PlayerH264Module::PlayerH264Module(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odplayerh264") {}

    PlayerH264Module::~PlayerH264Module() {}

    void PlayerH264Module::setUp() {}

    void PlayerH264Module::tearDown() {}

    void PlayerH264Module::wait() {
        AbstractModule::wait();
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode PlayerH264Module::body() {
        // Read the URL of the file to replay.
        URL url(getKeyValueConfiguration().getValue<string>("odplayerh264.input"));

        // Size of the memory buffer.
        const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");

        // Number of memory segments.
        const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");

        // Do we have to rewind the stream on EOF?
        bool autoRewind = (getKeyValueConfiguration().getValue<int>("odplayerh264.autoRewind") != 0);

        // Base port for letting spawned children connect to parent process.
        const uint32_t BASE_PORT = getKeyValueConfiguration().getValue<uint32_t>("odplayerh264.portbaseforchildprocesses");

        // Construct player.
        PlayerH264 player(url, autoRewind, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, BASE_PORT);

        // The next container to be sent.
        Container nextContainerToBeSent;

        // Delay between two containers.
        uint32_t delay = 0;

        // The main loop.
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            // Get container to be sent.
            nextContainerToBeSent = player.getNextContainerToBeSent();

            // Get delay to wait _after_ sending the container.
            delay = player.getDelay();

            // Here, the container is sent while discarding player commands.
            if (nextContainerToBeSent.getDataType() != Container::UNDEFINEDDATA) {
                CLOG1 << "[" << getName() << "(" << getIdentifier() << ")]: Sending " << nextContainerToBeSent.toString() << " (delay was " << delay << " us): " << nextContainerToBeSent.getReceivedTimeStamp().toString() << endl;

                getConference().send(nextContainerToBeSent);
            }

            // If replaying is finished, exit.
            if (!player.hasMoreData()) {
                break;
            }
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odplayerh264
