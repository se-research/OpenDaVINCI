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

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/wrapper/ConfigurationTraits.h"
#include "opendavinci/core/wrapper/KeyValueDatabase.h"
#include "opendavinci/core/wrapper/KeyValueDatabaseFactory.h"
#include "opendavinci/core/wrapper/KeyValueDatabaseLibraryProducts.h"
#include "opendavinci/core/wrapper/Libraries.h"
#include "opendavinci/core/wrapper/SimpleDB/SimpleDBFactoryWorker.h"

namespace core {
    namespace wrapper {

        SharedPointer<KeyValueDatabase> KeyValueDatabaseFactory::createKeyValueDatabase() {
            typedef ConfigurationTraits<KeyValueDatabaseLibraryProducts>::configuration configuration;
            return KeyValueDatabaseFactoryWorker<configuration::value>::createKeyValueDatabase();
        }
    }
} // core::wrapper
