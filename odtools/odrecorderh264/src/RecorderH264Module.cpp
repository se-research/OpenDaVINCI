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

#include <iostream>
#include <string>

#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odtools/recorder/SharedDataListener.h"
#include "opendavinci/generated/odcore/data/recorder/RecorderCommand.h"

#include "RecorderH264.h"
#include "RecorderH264Module.h"

namespace odcore { namespace base { class KeyValueDataStore; } }

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::io;
    using namespace odtools::recorder;

    RecorderH264Module::RecorderH264Module(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odrecorderh264") {}

    RecorderH264Module::~RecorderH264Module() {}

    void RecorderH264Module::setUp() {}

    void RecorderH264Module::tearDown() {}

    void RecorderH264Module::wait() {
        AbstractModule::wait();
    }

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode RecorderH264Module::body() {
        // Check if the recorder is remotely controlled.
        bool remoteControl = (getKeyValueConfiguration().getValue<bool>("odrecorderh264.remoteControl") != 0);

        // URL for storing containers.
        const string recorderOutputURL = getKeyValueConfiguration().getValue<string>("odrecorderh264.output");
        // Size of memory segments.
        const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");
        // Number of memory segments.
        const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");
        // Run recorder in asynchronous mode to allow real-time recording in background.
        const bool THREADING = true;
        // Dump shared images and shared data?
        const bool DUMP_SHARED_DATA = getKeyValueConfiguration().getValue<uint32_t>("odrecorderh264.dumpshareddata") == 1;

        // Actual "recording" interface.
        RecorderH264 rh264(recorderOutputURL, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, DUMP_SHARED_DATA);

        // Connect recorder's FIFOQueue to record all containers except for shared images/shared data.
        addDataStoreFor(rh264.getFIFO());

        // Connect recorder's data store that can handle shared data except for SharedImages.
        addDataStoreFor(odcore::data::SharedData::ID(), rh264.getDataStoreForSharedData());
        addDataStoreFor(odcore::data::SharedPointCloud::ID(), rh264.getDataStoreForSharedData());

        // SharedImages will be encoded as h264 data. RecorderH264's constructor
        // will take care of that automatically.

        // Get key/value-datastore for controlling the odrecorder.
        KeyValueDataStore &kvds = getKeyValueDataStore();

        // If remote control is disabled, simply start recording immediately.
        bool recording = (!remoteControl);
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            // Recording queued entries.
            if (recording) {
                if (!rh264.getFIFO().isEmpty()) {
                    rh264.recordQueueEntries();
                }
                else {
                    Thread::usleepFor(500);
                }
            }

            // Check for remote control.
            if (remoteControl) {
                Container container = kvds.get(odcore::data::recorder::RecorderCommand::ID());
                if (container.getDataType() == odcore::data::recorder::RecorderCommand::ID()) {
                    odcore::data::recorder::RecorderCommand rc;
                    rc = container.getData<odcore::data::recorder::RecorderCommand>();

                    recording = (rc.getCommand() == odcore::data::recorder::RecorderCommand::RECORD);
                }

                // Discard existing entries.
                if (!recording) {
                    rh264.getFIFO().clear();
                }
            }
        }

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odrecorderh264
