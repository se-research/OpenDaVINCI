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

#include "CANDevice.h"
#include "MessageToCANDataStore.h"
#include "opendavinci/odcore/data/Container.h"
#include "automotivedata/generated/automotive/GenericCANMessage.h"
#include "automotivedata/generated/automotive/VehicleControl.h"

namespace automotive {
    namespace odcantools {

        using namespace odcore::data;

        MessageToCANDataStore::MessageToCANDataStore(shared_ptr<CANDevice> canDevice) :
            m_canDevice(canDevice) {}

        MessageToCANDataStore::~MessageToCANDataStore() {}

        void MessageToCANDataStore::add(odcore::data::Container &container) {
            if (container.getDataType() == automotive::GenericCANMessage::ID()) {
                GenericCANMessage gcm = container.getData<GenericCANMessage>();
                m_canDevice->write(gcm);
            }
        }

        void MessageToCANDataStore::clear() {}

        uint32_t MessageToCANDataStore::getSize() const {
            return 0;
        }

        bool MessageToCANDataStore::isEmpty() const {
            return true;
        }

    } // odcantools
} // automotive

