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

#include "opendavinci/core/wrapper/ConfigurationTraits.h"
#include "opendavinci/core/wrapper/Libraries.h"
#include "opendavinci/core/wrapper/MutexFactory.h"
#include "opendavinci/core/wrapper/SystemLibraryProducts.h"

namespace core { namespace wrapper { class Mutex; } }

#ifdef WIN32
    #include "opendavinci/core/wrapper/WIN32/WIN32MutexFactoryWorker.h"
#endif
#ifndef WIN32
    #include "opendavinci/core/wrapper/POSIX/POSIXMutexFactoryWorker.h"
#endif

namespace core {
    namespace wrapper {

        Mutex* MutexFactory::createMutex() {
            typedef ConfigurationTraits<SystemLibraryProducts>::configuration configuration;
            return MutexFactoryWorker<configuration::value>::createMutex();
        }

      }
} // core::wrapper

