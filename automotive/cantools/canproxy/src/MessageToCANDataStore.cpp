/**
 * canproxy - Tool wrapping a CAN interface.
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

#include "MessageToCANDataStore.h"

namespace automotive {

    using namespace core::data;

    MessageToCANDataStore::MessageToCANDataStore(CANDevice &canDevice) :
        m_canDevice(canDevice) {}

    MessageToCANDataStore::~MessageToCANDataStore() {}

    void MessageToCANDataStore::add(const core::data::Container &container) {
        // TODO: Here, we need to check for which Containers we have specified a mapping to CAN messages.
        if (container.getDataType() == Container::VEHICLECONTROL) {
            // TODO: Use the Visitor-pattern to transform a Container into the CAN message.
            // The visitor would have to transform the container into a set of GenericCANMessages
            // that are subsequently written via the CAN device.
            GenericCANMessage gcm;
            m_canDevice.write(gcm);
        }
    }

    void MessageToCANDataStore::clear() {}

    uint32_t MessageToCANDataStore::getSize() const {
        return 0;
    }

    bool MessageToCANDataStore::isEmpty() const {
        return true;
    }

} // automotive

