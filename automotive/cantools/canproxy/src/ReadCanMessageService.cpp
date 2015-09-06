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

#include "core/data/TimeStamp.h"

#include "ReadCanMessageService.h"

namespace automotive {

    using namespace std;
    using namespace core::data;

    ReadCanMessageService::ReadCanMessageService(HANDLE handle, GenericCANMessageListener &listener) :
        m_handle(handle),
        m_listener(listener) {}

    ReadCanMessageService::~ReadCanMessageService() {}

    void ReadCanMessageService::beforeStop() {}

    void ReadCanMessageService::run() {
        serviceReady();

        while ( (m_handle != NULL) && 
                isRunning() ) {
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

                // Propagate GenericCANMessage.
                m_listener.nextGenericCANMessage(gcm);
            }
        }
    }

} // automotive

