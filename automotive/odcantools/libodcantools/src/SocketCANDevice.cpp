/**
 * libodcantools - Library to wrap a CAN interface.
 * Copyright (C) 2017 Christian Berger
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

#include <sys/ioctl.h>
#include <sys/socket.h>

#ifdef __linux__
    #include <linux/if.h>
#endif

#include <cerrno>
#include <cstring>

#include <iostream>
#include <sstream>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/base/module/AbstractCIDModule.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include "automotivedata/generated/automotive/GenericCANMessage.h"

#include "SocketCANDevice.h"
#include "GenericCANMessageListener.h"

namespace automotive {
    namespace odcantools {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;

        SocketCANDevice::SocketCANDevice(const string &deviceNode, GenericCANMessageListener &listener) :
            CANDevice(),
            m_deviceNode(deviceNode),
            m_address(),
            m_socketCANMutex(),
            m_socketCAN(-1),
            m_listener(listener) {
            cerr << "[SocketCANDevice] Opening " << m_deviceNode << "... ";
#ifdef __linux__
            // Create socket for SocketCAN.
            m_socketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW);
            if (m_socketCAN < 0) {
                cerr << "failed." << endl;

                stringstream s;
                s << "[SocketCANDevice] Error while creating socket: " << strerror(errno);
                throw s.str();
            }

            // Try opening the given CAN device node.
            struct ifreq ifr;
            memset(&ifr, 0, sizeof(ifr));
            strcpy(ifr.ifr_name, m_deviceNode.c_str());
            if (0 != ioctl(m_socketCAN, SIOCGIFINDEX, &ifr)) {
                cerr << "failed." << endl;

                stringstream s;
                s << "[SocketCANDevice] Error while getting index for " << m_deviceNode << ": " << strerror(errno);
                throw s.str();
            }

            // Setup address and port.
            memset(&m_address, 0, sizeof(m_address));
            m_address.can_family = AF_CAN;
            m_address.can_ifindex = ifr.ifr_ifindex;

#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic push
#endif
#if (__GNUC__ == 4 && 3 <= __GNUC_MINOR__) || 4 < __GNUC__
#    pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
            if (bind(m_socketCAN, reinterpret_cast<struct sockaddr *>(&m_address), sizeof(m_address)) < 0) {
                cerr << "failed." << endl;

                stringstream s;
                s << "[SocketCANDevice] Error while binding socket: " << strerror(errno);
                throw s.str();
            }
            cerr << "done." << endl;
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic pop
#endif

#else
            cerr << "failed (SocketCAN not available on this platform). ";
#endif
        }

        SocketCANDevice::~SocketCANDevice() {
            CLOG << "[SocketCANDevice] Closing " << m_deviceNode << "... ";

            // Close file descriptor.
            if (m_socketCAN > -1) {
                close(m_socketCAN);
            }

            CLOG << "done." << endl;
        }

        bool SocketCANDevice::isOpen() const {
            return (m_socketCAN > -1);
        }

        int SocketCANDevice::write(const GenericCANMessage &gcm) {
            int errorCode = 0;
            Lock l(m_socketCANMutex);

#ifndef __linux__
            // Avoid compilation error.
            (void)gcm;
#endif

            if (m_socketCAN > -1) {
#ifdef __linux__
                struct can_frame frame;

                const uint8_t LENGTH = gcm.getLength();
                frame.can_id = gcm.getIdentifier();
                frame.can_dlc = LENGTH;
                uint64_t data = gcm.getData();
                for (uint8_t i = 0; i < LENGTH; i++) {
                    frame.data[LENGTH-1-i] = (data & 0xFF);
                    data = data >> 8;
                }
                int32_t nbytes = ::write(m_socketCAN, &frame, sizeof(struct can_frame));
                if (0 < nbytes) {
                    CLOG1 << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", nbytes = " << nbytes << endl;
                }
                else {
                    CLOG1 << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", errorCode = " << errorCode << ", strerror(" << errno << "): '" << strerror(errno) << "'" << endl;
                    errorCode = errno;
                }
#endif
            }
            return errorCode;
        }

        void SocketCANDevice::beforeStop() {}

        void SocketCANDevice::run() {
#ifdef __linux__
            struct can_frame frame;
            fd_set rfds;
            struct timeval timeout;
            struct timeval socketTimeStamp;
            int32_t nbytes = 0;
#endif

            // serviceReady must be called in any case to avoid blocking of caller.
            serviceReady();

#ifdef __linux__
            while ( (m_socketCAN > -1) && 
                    isRunning() ) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_socketCAN, &rfds);

                    select(m_socketCAN + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_socketCAN, &rfds)) {
                        nbytes = read(m_socketCAN, &frame, sizeof(struct can_frame));
                        if ( (nbytes > 0) && (nbytes == sizeof(struct can_frame)) ) {
                            // Get receiving time stamp.
                            if (0 != ioctl(m_socketCAN, SIOCGSTAMP, &socketTimeStamp)) {
                                // In case the ioctl failed, use traditional vsariant.
                                const odcore::data::TimeStamp now;
                                socketTimeStamp.tv_sec = now.getSeconds();
                                socketTimeStamp.tv_usec = now.getMicroseconds();
                            }
                            odcore::data::TimeStamp received(socketTimeStamp.tv_sec, socketTimeStamp.tv_usec);

                            // Create generic CAN message representation.
                            GenericCANMessage gcm;
                            gcm.setDriverTimeStamp(received);
                            gcm.setIdentifier(frame.can_id);
                            gcm.setLength(frame.can_dlc);
                            uint64_t data = 0;
                            for (uint8_t i = 0; i < frame.can_dlc; i++) {
                                CLOG1 << static_cast<uint32_t>(frame.data[i]) << " ";
                                data |= (static_cast<uint64_t>(frame.data[i]) << ((frame.can_dlc-1-i)*8));
                            }
                            CLOG1 << endl;
                            gcm.setData(data);

                            // Propagate GenericCANMessage.
                            m_listener.nextGenericCANMessage(gcm);
                        }
                    }
            }
#endif
        }

    } // odcantools
} // automotive

