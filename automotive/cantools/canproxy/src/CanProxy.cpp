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

#include "CanProxy.h"
#include "ReadCanMessageService.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    CanProxy::CanProxy(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "canproxy"),
        GenericCANMessageListener(),
        m_fifo(),
        m_recorder(),
        m_deviceNode(),
        m_handle(NULL) {}

    CanProxy::~CanProxy() {}

    void CanProxy::setUp() {
        m_deviceNode = getKeyValueConfiguration().getValue<string>("canproxy.devicenode");

        CLOG << "[CanProxy] Opening " << m_deviceNode << "... ";
        m_handle = LINUX_CAN_Open(m_deviceNode.c_str(), O_RDWR);
        if (m_handle == NULL) {
            CLOG << "failed." << endl;
        }
        else {
            CLOG << "done." << endl;

            // URL for storing containers.
            stringstream recordingURL;
            recordingURL << "file://" << "canproxy_" << TimeStamp().getYYYYMMDD_HHMMSS() << ".rec";
            // Size of memory segments.
            const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");
            // Number of memory segments.
            const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");
            // Run recorder in asynchronous mode to allow real-time recording in background.
            const bool THREADING = true;
            // Dump shared images and shared data?
            const bool DUMP_SHARED_DATA = false;

            // Create a recorder instance.
            m_recorder = auto_ptr<tools::recorder::Recorder>(new tools::recorder::Recorder(recordingURL.str(), MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, DUMP_SHARED_DATA));
        }
    }

    void CanProxy::tearDown() {
        CLOG << "[CanProxy] Closing " << m_deviceNode << "... ";
        if (m_handle != NULL) {
            CAN_Close(m_handle);
        }
        CLOG << "done." << endl;
    }

    void CanProxy::nextGenericCANMessage(const GenericCANMessage &gcm) {
        Container c(Container::GENERIC_CAN_MESSAGE, gcm);
        m_fifo.add(c);
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CanProxy::body() {
        // Start a thread to receive CAN messages concurrently.
        ReadCanMessageService reader(m_handle, *this);
        reader.start();

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

        reader.stop();

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // automotive
