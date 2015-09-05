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
#include "core/data/TimeStamp.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "CanProxy.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    CanProxy::CanProxy(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "canproxy"),
        m_recorder(),
        m_deviceNode(),
        m_handle(NULL) {}

    CanProxy::~CanProxy() {}

    void CanProxy::setUp() {
        m_deviceNode = getKeyValueConfiguration().getValue<string>("canproxy.devicenode");

        CLOG << "[CanProxy] Opening " << m_deviceNode << "... ";
		m_handle = LINUX_CAN_Open(m_deviceNode.c_str(), O_RDWR);
		if (!m_handle) {
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

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CanProxy::body() {
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            TPCANRdMsg message;
            int32_t errorCode = LINUX_CAN_Read(m_handle, &message);

            if (errorCode == 0) {
                cout << "[CanProxy] ID = " << message.Msg.ID << ", LEN = " << message.Msg.LEN << ", DATA = ";

                // Set time stamp from driver.
                TimeStamp driverTimeStamp(message.dwTime, message.wUsec);

                // Create generic CAN message representation.
                GenericCANMessage gcm;
                gcm.setDriverTimeStamp(driverTimeStamp);
                gcm.setIdentifier(message.Msg.ID);
                gcm.setLength(message.Msg.LEN);
                uint64_t data = 0;
                for (uint8_t i = 0; i < message.Msg.LEN; i++) {
                    cout << static_cast<uint32_t>(message.Msg.DATA[i]) << " ";
                    data |= (message.Msg.DATA[i] << (i*8));
                }
                cout << endl;
                gcm.setData(data);

                Container c(Container::GENERIC_CAN_MESSAGE, gcm);

                // Store container to dump file.
                if (m_recorder.get() != NULL) {
                    m_recorder->store(c);
                }

                // Send container with GenericCANMessage.
                getConference().send(c);
            }
            else {
                cerr << "[CanProxy] Error receiving data, error code " << errno << ", " << strerror(errno) << endl;
                break;
            }
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // automotive
