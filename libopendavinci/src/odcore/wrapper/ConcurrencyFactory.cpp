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

#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/ConfigurationTraits.h"
#include "opendavinci/odcore/wrapper/Libraries.h"
#include "opendavinci/odcore/wrapper/SystemLibraryProducts.h"

namespace odcore { namespace wrapper { class Runnable; } }
namespace odcore { namespace wrapper { class Thread; } }

#ifdef WIN32
  #include "opendavinci/odcore/wrapper/WIN32/WIN32ConcurrencyFactoryWorker.h"
#endif
#ifndef WIN32
  #include "opendavinci/odcore/wrapper/POSIX/POSIXConcurrencyFactoryWorker.h"
#endif

namespace odcore {
    namespace wrapper {

        Thread* ConcurrencyFactory::createThread(Runnable &runnable) {
            typedef ConfigurationTraits<SystemLibraryProducts>::configuration configuration;
            return ConcurrencyFactoryWorker<configuration::value>::createThread(runnable);
        }

        void ConcurrencyFactory::usleepFor(const long &microseconds) {
            typedef ConfigurationTraits<SystemLibraryProducts>::configuration configuration;
            return ConcurrencyFactoryWorker<configuration::value>::usleepFor(microseconds);
        }

        void ConcurrencyFactory::usleepUntil(const long &seconds, const long &partialMicroseconds) {
            typedef ConfigurationTraits<SystemLibraryProducts>::configuration configuration;
            return ConcurrencyFactoryWorker<configuration::value>::usleepUntil(seconds, partialMicroseconds);
        }
    }
} // odcore::wrapper
