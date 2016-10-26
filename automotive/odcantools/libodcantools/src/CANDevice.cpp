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

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include <opendavinci/odcore/strings/StringToolbox.h>

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
            m_listener(listener),
            m_deviceDriverStartTime() {
            CLOG << "[CANDevice] Opening " << m_deviceNode << "... ";
            m_handle = LINUX_CAN_Open(m_deviceNode.c_str(), O_RDWR);
            if (m_handle == NULL) {
                CLOG << "failed." << endl;
            }
            else {
                CLOG << "done." << endl;

                {
                    // Read time point when device driver was loaded.
                    ifstream pcanStartTimeProcFile("/proc/pcan.starttime", ios::in);
                    if (pcanStartTimeProcFile.good()) {
                        string pcanStartTime;
                        getline(pcanStartTimeProcFile, pcanStartTime);
                        vector<string> tokens = odcore::strings::StringToolbox::split(pcanStartTime, '.');
                        if (tokens.size() == 2) {
                            stringstream sstrSeconds; uint64_t seconds = 0;
                            sstrSeconds << tokens.at(0); sstrSeconds >> seconds;

                            stringstream sstrMicroseconds; uint64_t microseconds = 0;
                            sstrMicroseconds << tokens.at(1); sstrMicroseconds >> microseconds;

                            m_deviceDriverStartTime = TimeStamp(seconds, microseconds);
                            CLOG << "[CANDevice] Kernel module start time: " << m_deviceDriverStartTime.getYYYYMMDD_HHMMSSms() << endl;
                        }
                    }
                }
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
                    msg.DATA[LENGTH-1-i] = (data & 0xFF);
                    data = data >> 8;
                }
                int32_t errorCode = CAN_Write(m_handle, &msg);

                CLOG1 << "[CANDevice] Writing ID = " << msg.ID << ", LEN = " << +msg.LEN << ", errorCode = " << errorCode << endl;
            }
        }

        void CANDevice::beforeStop() {}

        void CANDevice::run() {
            serviceReady();

            while ( (m_handle != NULL) && 
                    isRunning() ) {
                TPCANRdMsg message;
                const int32_t TIMEOUT_IN_MICROSECONDS = 1000 * 1000;
                int32_t errorCode = LINUX_CAN_Read_Timeout(m_handle, &message, TIMEOUT_IN_MICROSECONDS);

                if ( !(errorCode < 0) && (errorCode != CAN_ERR_QRCVEMPTY) ) {
                    CLOG1 << "[CANDevice] ID = " << message.Msg.ID << ", LEN = " << message.Msg.LEN << ", DATA = ";

                    // Set time stamp from driver.
                    const uint64_t TIME_IN_MICROSECONDS =
                          m_deviceDriverStartTime.toMicroseconds()
                        + (message.dwTime * 1000 + message.wUsec);
                    const TimeStamp absoluteDriverTimeStamp(TIME_IN_MICROSECONDS / 1000000L, TIME_IN_MICROSECONDS % 1000000L);
//{
//    TimeStamp now;
//    cout << "dwTime = " << message.dwTime << ", message.wUsec = " << message.wUsec << ", TIM = " << TIME_IN_MICROSECONDS << ", ABS = " << absoluteDriverTimeStamp.toString() << endl << " hr = " << absoluteDriverTimeStamp.getYYYYMMDD_HHMMSSms() << endl << " nw = " << now.getYYYYMMDD_HHMMSSms() << endl;
//}

                    // Create generic CAN message representation.
                    GenericCANMessage gcm;
                    gcm.setDriverTimeStamp(absoluteDriverTimeStamp);
                    gcm.setIdentifier(message.Msg.ID);
                    gcm.setLength(message.Msg.LEN);
                    uint64_t data = 0;
                    for (uint8_t i = 0; i < message.Msg.LEN; i++) {
                        CLOG1 << static_cast<uint32_t>(message.Msg.DATA[i]) << " ";
                        data |= (static_cast<uint64_t>(message.Msg.DATA[i]) << ((message.Msg.LEN-1-i)*8));
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

