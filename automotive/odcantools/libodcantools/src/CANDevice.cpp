/**
 * libodcantools - Library to wrap a CAN interface.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <fcntl.h>

#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"

#include "automotivedata/generated/automotive/GenericCANMessage.h"

#include "CANDevice.h"
#include "GenericCANMessageListener.h"

namespace automotive {
    namespace odcantools {

        using namespace std;
        using namespace odcore::base::module;
        using namespace odcore::data;

        CANDevice::CANDevice(const string &deviceNode, GenericCANMessageListener &listener) :
            m_deviceNode(deviceNode),
            m_handle(NULL),
            m_listener(listener) {
            CLOG << "[CANDevice] Opening " << m_deviceNode << "... ";
            m_handle = LINUX_CAN_Open(m_deviceNode.c_str(), O_RDWR);
            if (m_handle == NULL) {
                CLOG << "failed." << endl;
            }
            else {
                CLOG << "done." << endl;
            }
        }

        CANDevice::~CANDevice() {
            CLOG << "[CANDevice] Closing " << m_deviceNode << "... ";
            if (m_handle != NULL) {
                CAN_Close(m_handle);
            }
            CLOG << "done." << endl;
        }

        bool CANDevice::isOpen() const {
            return (m_handle != NULL);
        }

        void CANDevice::write(const GenericCANMessage &gcm) {
            if (m_handle != NULL) {
                TPCANMsg msg;
                const uint8_t LENGTH = gcm.getLength();
                msg.ID = gcm.getIdentifier();
                msg.MSGTYPE = MSGTYPE_STANDARD;
                msg.LEN = LENGTH;
                uint64_t data = gcm.getData();
                for (uint8_t i = 0; i < LENGTH; i++) {
                    msg.DATA[i] = (data & 0xFF);
                    data = data >> 8;
                }
                int32_t errorCode = CAN_Write(m_handle, &msg);

                CLOG1 << "[CANDevice] Writing ID = " << msg.ID << ", LEN = " << msg.LEN << ", errorCode = " << errorCode << endl;
            }
        }

        void CANDevice::beforeStop() {}

        void CANDevice::run() {
            serviceReady();

            while ( (m_handle != NULL) && 
                    isRunning() ) {
                TPCANRdMsg message;
                const int32_t TIMEOUT_IN_MICROSECONDS = 1000*1000;
                int32_t errorCode = LINUX_CAN_Read_Timeout(m_handle, &message, TIMEOUT_IN_MICROSECONDS);

                if ( !(errorCode < 0) && (errorCode != CAN_ERR_QRCVEMPTY) ) {
                    CLOG1 << "[CANDevice] ID = " << message.Msg.ID << ", LEN = " << message.Msg.LEN << ", DATA = ";

                    // Set time stamp from driver.
                    TimeStamp driverTimeStamp(message.dwTime, message.wUsec);

                    // Create generic CAN message representation.
                    GenericCANMessage gcm;
                    gcm.setDriverTimeStamp(driverTimeStamp);
                    gcm.setIdentifier(message.Msg.ID);
                    gcm.setLength(message.Msg.LEN);
                    uint64_t data = 0;
                    for (uint8_t i = 0; i < message.Msg.LEN; i++) {
                        CLOG1 << static_cast<uint32_t>(message.Msg.DATA[i]) << " ";
                        data |= (message.Msg.DATA[i] << (i*8));
                    }
                    CLOG1 << endl;
                    gcm.setData(data);

                    // Propagate GenericCANMessage.
                    m_listener.nextGenericCANMessage(gcm);
                }
            }
        }

    } // odcantools
} // automotive

