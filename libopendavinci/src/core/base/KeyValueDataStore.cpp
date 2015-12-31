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

#include <iosfwd>
#include <string>

#include "core/base/KeyValueDataStore.h"
#include "core/base/Serializable.h"
#include "core/macros.h"

namespace core {
    namespace base {

        using namespace data;
        using namespace exceptions;

        KeyValueDataStore::KeyValueDataStore(SharedPointer<wrapper::KeyValueDatabase> keyValueDatabase) throw (NoDatabaseAvailableException) :
                m_keyValueDatabase(keyValueDatabase) {
            if (!m_keyValueDatabase.isValid()) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(NoDatabaseAvailableException, "Given database is NULL.");
            }
        }

        KeyValueDataStore::~KeyValueDataStore() {}

        void KeyValueDataStore::put(const int32_t &key, const Container &value) {
            // Transform the given Container to a plain string...
            stringstream stringStreamValue;
            stringStreamValue << value;
            string stringValue = stringStreamValue.str();

            // ...and use the datastore backend for storing the content.
            m_keyValueDatabase->put(key, stringValue);
        }

        Container KeyValueDataStore::get(const int32_t &key) const {
            Container value;

            // Try to get the value from the database backend and try to parse a Container.
            string stringValue(m_keyValueDatabase->get(key));
            if (stringValue != "") {
                stringstream stringStreamValue;
                stringStreamValue.str(stringValue);
                stringStreamValue >> value;
            }

            return value;
        }

    }
} // core::base
