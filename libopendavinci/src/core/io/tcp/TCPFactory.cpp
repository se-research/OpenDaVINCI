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

#include "core/io/tcp/TCPFactory.h"

#include "core/wrapper/Libraries.h"
#include "core/wrapper/ConfigurationTraits.h"
#include "core/wrapper/TCPFactoryWorker.h"

#ifdef WIN32
    #include "core/wrapper/WIN32/WIN32TCPFactoryWorker.h"
#endif

#ifndef WIN32
    #include "core/wrapper/POSIX/POSIXTCPFactoryWorker.h"
#endif

namespace core {
    namespace io {
        namespace tcp {

            SharedPointer<TCPAcceptor> TCPFactory::createTCPAcceptor(const uint32_t &port) {
                typedef core::wrapper::ConfigurationTraits<core::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<TCPAcceptor>(core::wrapper::TCPFactoryWorker<configuration::value>::createTCPAcceptor(port));
            }

            SharedPointer<TCPConnection> TCPFactory::createTCPConnectionTo(const std::string& ip, const uint32_t& port) {
                typedef core::wrapper::ConfigurationTraits<core::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<TCPConnection>(core::wrapper::TCPFactoryWorker<configuration::value>::createTCPConnectionTo(ip, port));
            }

        }
    }
} // core::io::tcp
