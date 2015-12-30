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

#include "core/io/udp/UDPFactory.h"
#include "core/io/udp/UDPReceiver.h"
#include "core/io/udp/UDPSender.h"
#include "core/wrapper/ConfigurationTraits.h"
#include "core/wrapper/Libraries.h"
#include "core/wrapper/NetworkLibraryProducts.h"

#ifdef WIN32
    #include "core/wrapper/WIN32/WIN32UDPFactoryWorker.h"
#endif
#ifndef WIN32
    #include "core/wrapper/POSIX/POSIXUDPFactoryWorker.h"
#endif

namespace core {
    namespace io {
        namespace udp {

            SharedPointer<UDPSender> UDPFactory::createUDPSender(const string &address, const uint32_t &port) {
                typedef core::wrapper::ConfigurationTraits<core::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<UDPSender>(core::wrapper::UDPFactoryWorker<configuration::value>::createUDPSender(address, port));
            }

            SharedPointer<UDPReceiver> UDPFactory::createUDPReceiver(const string &address, const uint32_t &port) {
                typedef core::wrapper::ConfigurationTraits<core::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<UDPReceiver>(core::wrapper::UDPFactoryWorker<configuration::value>::createUDPReceiver(address, port));
            }

        }
    }
} // core::io::udp
