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

#ifndef PCANDEVICE_H_
#define PCANDEVICE_H_

#include <memory>
#include <string>

#include <libpcan.h>

#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/data/TimeStamp.h>

#include "CANDevice.h"

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

class GenericCANMessageListener;

        using namespace std;

        /**
         * This class encapsulates the service for reading low-level CAN message to be
         * wrapped into a GenericCANMessage and for writing a GenericPCANDevice to the
         * device node represented by this class.
         */
        class PCANDevice : public CANDevice {
           private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                PCANDevice(const PCANDevice &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                PCANDevice& operator=(const PCANDevice &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param deviceNode CAN device node.
                 * @param listener Listener that will receive wrapped GenericCANMessages.
                 */
                PCANDevice(const string &deviceNode, GenericCANMessageListener &listener);

                virtual ~PCANDevice();

                virtual bool isOpen() const;

                virtual int write(const GenericCANMessage &gcm);

                virtual void beforeStop();

                virtual void run();

            private:
                string m_deviceNode;
                odcore::base::Mutex m_handleMutex;
                HANDLE m_handle;
                GenericCANMessageListener &m_listener;
                odcore::data::TimeStamp m_deviceDriverStartTime;
        };

    } // odcantools
} // automotive

#endif /*PCANDEVICE_H_*/
