/**
 * canproxy - Tool wrapping a CAN interface.
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

#include <iostream>

#include "core/data/Container.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "CANProxy.h"
#include "CANDevice.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    CANProxy::CANProxy(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "canproxy"),
        GenericCANMessageListener(),
        m_fifo(),
        m_recorder(),
        m_device(),
        m_deviceNode() {}

    CANProxy::~CANProxy() {}

    void CANProxy::setUp() {
        // Get CAN device node from configuration.
        m_deviceNode = getKeyValueConfiguration().getValue<string>("canproxy.devicenode");

        // Try to open CAN device and register this instance as receiver for GenericCANMessages.
        m_device = auto_ptr<CANDevice>(new CANDevice(m_deviceNode, *this));

        // If the device could be successfully opened, create a recording file with a dump of the data.
        if (m_device->isOpen()) {
            // URL for storing containers.
            stringstream recordingURL;
            recordingURL << "file://" << "canproxy_" << TimeStamp().getYYYYMMDD_HHMMSS() << ".rec";
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

    void CANProxy::tearDown() {}

    void CANProxy::nextGenericCANMessage(const GenericCANMessage &gcm) {
        Container c(Container::GENERIC_CAN_MESSAGE, gcm);
        m_fifo.add(c);
    }

    void CANProxy::writeGenericCANMessage(const GenericCANMessage &gcm) {
        m_device->write(gcm);
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CANProxy::body() {
        // Register the CAN device as receiver for all Containers to be
        // potentially written to the CAN bus.
        addDataStoreFor(m_device->getMessageToCANDataStore());

        // Start the wrapped CAN device to receive CAN messages concurrently.
        m_device->start();

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

        m_device->stop();

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // automotive
