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

#include "CANDevice.h"
#include "CANMessageReplicator.h"
#include "opendavinci/odcore/SharedPointer.h"

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

class CANDevice;

        using namespace std;

        CANMessageReplicator::CANMessageReplicator(GenericCANMessageListener &conference) :
            m_CANDeviceToReplicateTo(),
            m_conference(conference) {}

        CANMessageReplicator::~CANMessageReplicator() {}

        void CANMessageReplicator::setCANDevice(odcore::SharedPointer<CANDevice> CANDeviceToReplicateTo) {
            m_CANDeviceToReplicateTo = CANDeviceToReplicateTo;
        }

        void CANMessageReplicator::nextGenericCANMessage(const GenericCANMessage &gcm) {
            // Replicate the received GenericCANMessage on the specified device.
            if (m_CANDeviceToReplicateTo.isValid()) {
                m_CANDeviceToReplicateTo->write(gcm);
            }

            // Replicate the received GenericCANMessage to OpenDaVINCI for mapping to the high-level C++ structure.
            m_conference.nextGenericCANMessage(gcm);
        }

    } // odcantools
} // automotive

