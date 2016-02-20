/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "opendavinci/context/base/SystemContextComponent.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/wrapper/KeyValueDatabase.h"
#include "opendavinci/core/wrapper/KeyValueDatabaseFactory.h"

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace core::base;

        SystemContextComponent::SystemContextComponent() :
            m_fifo(),
            m_keyValueDataStore() {
            // Create an in-memory database.
            m_keyValueDataStore = core::SharedPointer<KeyValueDataStore>(new KeyValueDataStore(core::wrapper::KeyValueDatabaseFactory::createKeyValueDatabase()));
        }

        SystemContextComponent::~SystemContextComponent() {}

        void SystemContextComponent::nextContainer(core::data::Container &c) {
            m_fifo.add(c);

            // Store data using a plain map.
            m_keyValueDataStore->put(c.getDataType(), c);
        }

        core::base::FIFOQueue& SystemContextComponent::getFIFO() {
            return m_fifo;
        }

        core::base::KeyValueDataStore& SystemContextComponent::getKeyValueDataStore() {
        	return *m_keyValueDataStore;
        }

    }
} // odcontext::base
