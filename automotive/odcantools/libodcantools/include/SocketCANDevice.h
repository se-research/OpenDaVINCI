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

#ifndef SOCKETCANDEVICE_H_
#define SOCKETCANDEVICE_H_

#ifdef __linux__
    #include <linux/can.h>
#endif

#include <memory>
#include <string>

#include <opendavinci/odcore/base/Mutex.h>

#include "CANDevice.h"

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

class GenericCANMessageListener;

        using namespace std;

        /**
         * This class encapsulates the service for reading low-level CAN message to be
         * wrapped into a GenericCANMessage and for writing a GenericCANDevice to the
         * socket represented by this class.
         */
        class SocketCANDevice : public CANDevice {
           private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                SocketCANDevice(const SocketCANDevice &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                SocketCANDevice& operator=(const SocketCANDevice &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param deviceNode CAN device node.
                 * @param listener Listener that will receive wrapped GenericCANMessages.
                 */
                SocketCANDevice(const string &deviceNode, GenericCANMessageListener &listener);

                virtual ~SocketCANDevice();

                virtual bool isOpen() const;

                virtual int write(const GenericCANMessage &gcm);

                virtual void beforeStop();

                virtual void run();

            private:
                string m_deviceNode;
#ifdef __linux__
                struct sockaddr_can m_address;
#endif
                odcore::base::Mutex m_socketCANMutex;
                int m_socketCAN;
                GenericCANMessageListener &m_listener;
        };

    } // odcantools
} // automotive

#endif /*SOCKETCANDEVICE_H_*/
