/**
 * odcanbridge - Tool for bridging between two CAN devices and for
 *               mapping the low-level CAN messages to high-level
 *               C++ data structures and vice-versa.
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

#include <vector>

#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "tools/recorder/Recorder.h"
#include "generated/automotive/GenericCANMessage.h"

#include "CANBridge.h"
#include "CANDevice.h"
#include "MessageToCANDataStore.h"

namespace automotive {
    namespace odcantools {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::data;

        CANBridge::CANBridge(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "odcanbridge"),
            m_fifo(),
            m_recorder(),
            m_deviceA(),
            m_deviceNodeA(),
            m_deviceB(),
            m_deviceNodeB(),
            m_replicatorFromAtoB(*this),
            m_replicatorFromBtoA(*this),
            m_canMapping() {}

        CANBridge::~CANBridge() {}

        void CANBridge::setUp() {
            // Get CAN device node A from configuration.
            m_deviceNodeA = getKeyValueConfiguration().getValue<string>("odcanbridge.devicenodeA");
            // Get CAN device node B from configuration.
            m_deviceNodeB = getKeyValueConfiguration().getValue<string>("odcanbridge.devicenodeB");

            // Try to open CAN device A and register this instance as receiver for GenericCANMessages.
            m_deviceA = SharedPointer<CANDevice>(new CANDevice(m_deviceNodeA, m_replicatorFromAtoB));
            // Try to open CAN device B and register this instance as receiver for GenericCANMessages.
            m_deviceB = SharedPointer<CANDevice>(new CANDevice(m_deviceNodeB, m_replicatorFromBtoA));

            // If the device could be successfully opened, create a recording file with a dump of the data.
            if (m_deviceA->isOpen() &&
                m_deviceB->isOpen()) {
                // Set the CAN devices to the replicators.
                m_replicatorFromAtoB.setCANDevice(m_deviceB);
                m_replicatorFromBtoA.setCANDevice(m_deviceA);

                // Set receivers for OpenDaVINCI Containers to be translated as CAN messages.
                if (getKeyValueConfiguration().getValue<int>("odcanbridge.devicenodeA.receivesContainers") == 1) {
                    addDataStoreFor(m_deviceA->getMessageToCANDataStore());
                }
                if (getKeyValueConfiguration().getValue<int>("odcanbridge.devicenodeB.receivesContainers") == 1) {
                    addDataStoreFor(m_deviceB->getMessageToCANDataStore());
                }

                // URL for storing containers.
                stringstream recordingURL;
                recordingURL << "file://" << "odcanbridge_" << TimeStamp().getYYYYMMDD_HHMMSS() << ".rec";
                // Size of memory segments.
                const uint32_t MEMORY_SEGMENT_SIZE = 0;
                // Number of memory segments.
                const uint32_t NUMBER_OF_SEGMENTS = 0;
                // Run recorder in asynchronous mode to allow real-time recording in background.
                const bool THREADING = true;
                // Dump shared images and shared data?
                const bool DUMP_SHARED_DATA = false;

                // Create a recorder instance.
                m_recorder = auto_ptr<tools::recorder::Recorder>(new tools::recorder::Recorder(recordingURL.str(), MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, DUMP_SHARED_DATA));
            }
        }

        void CANBridge::tearDown() {}

        void CANBridge::nextGenericCANMessage(const GenericCANMessage &gcm) {
            // Pass the received GenericCANMessage to the recorder.
            Container c(gcm, Container::GENERIC_CAN_MESSAGE);
            m_fifo.add(c);

            vector<Container> listOfContainers = m_canMapping.mapNext(gcm);
            if (listOfContainers.size() > 0) {
                vector<Container>::iterator it = listOfContainers.begin();
                while (it != listOfContainers.end()) {
                    Container container = (*it++);
                    getConference().send(container);
                    Thread::usleepFor(100);
                }
            }
        }

        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CANBridge::body() {
            // Start the wrapped CAN devices to receive CAN messages concurrently.
            m_deviceA->start();
            m_deviceB->start();

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                const uint32_t ENTRIES = m_fifo.getSize();
                for (uint32_t i = 0; i < ENTRIES; i++) {
                    Container c = m_fifo.leave();

                    // Store container to dump file.
                    if (m_recorder.get() != NULL) {
                        m_recorder->store(c);
                    }

                    // Send container with GenericCANMessage.
                    getConference().send(c);
                }
            }

            m_deviceA->stop();
            m_deviceB->stop();

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    } // namespace odcantools
} // automotive
