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

#ifndef OPENDAVINCI_CORE_WRAPPER_WRAPPEDKEYVALUEDATABASEFACTORY_H_
#define OPENDAVINCI_CORE_WRAPPER_WRAPPEDKEYVALUEDATABASEFACTORY_H_

#include "opendavinci/odcore/opendavinci.h"
#include <memory>

namespace odcore {
    namespace wrapper {

class KeyValueDatabase;

        /**
         * Abstract factory for creating wrapped key/value databases:
         *
         * It can be used as follows:
         *
         * @code
         * std::shared_ptr<KeyValueDatabase> kvdb;
         *
         * try {
         *     kvdb = KeyValueDatabaseFactory::createKeyValueDatabase();
         * }
         * catch(string &s) {
         *    clog << "Failed: " << s << endl;
         * }
         *
         * if (kvdb != NULL) {
         *     const string value = "ABCD";
         *     const int32_t key = 123;
         *     kvdb->put(key, value);
         *
         *     string retrievedValue = kvdb->get(key);
         * }
         *
         * @endcode
         */
        struct OPENDAVINCI_API KeyValueDatabaseFactory {
            static std::shared_ptr<KeyValueDatabase> createKeyValueDatabase();
        };
    }
} // odcore::wrapper

#endif /*OPENDAVINCI_CORE_WRAPPER_KEYVALUEDATABASEFACTORY_H_*/
