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

#ifndef CANMESSAGEREPLICATOR_H_
#define CANMESSAGEREPLICATOR_H_

#include <core/SharedPointer.h>

#include "GenericCANMessageListener.h"

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

class CANDevice;

        using namespace std;

        /**
         * This class replicates a GenericCANMessage to another CAN device.
         */
        class CANMessageReplicator : public GenericCANMessageListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                CANMessageReplicator(const CANMessageReplicator &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                CANMessageReplicator& operator=(const CANMessageReplicator &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param conference Reference to the gateway to the OpenDaVINCI conference where the received messages shall be mapped into high-level C++ messages.
                 */
                CANMessageReplicator(GenericCANMessageListener &conference);

                /**
                 * This method sets the CAN device to replicate the data to.
                 *
                 * @param CANDeviceToReplicateTo SharedPointer to the CAN device where GenericCANMessages received from this listener shall be replicated.
                 */
                void setCANDevice(core::SharedPointer<CANDevice> CANDeviceToReplicateTo);

                virtual ~CANMessageReplicator();

                virtual void nextGenericCANMessage(const GenericCANMessage &gcm);

            private:
                core::SharedPointer<CANDevice> m_CANDeviceToReplicateTo;
                GenericCANMessageListener &m_conference;
        };

    } // odcantools
} // automotive

#endif /*CANMESSAGEREPLICATOR_H_*/
