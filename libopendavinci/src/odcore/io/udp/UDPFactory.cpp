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

#include "opendavinci/odcore/io/udp/UDPFactory.h"
#include "opendavinci/odcore/io/udp/UDPReceiver.h"
#include "opendavinci/odcore/io/udp/UDPSender.h"
#include "opendavinci/odcore/wrapper/ConfigurationTraits.h"
#include "opendavinci/odcore/wrapper/Libraries.h"
#include "opendavinci/odcore/wrapper/NetworkLibraryProducts.h"

#ifdef WIN32
    #include "opendavinci/odcore/wrapper/WIN32/WIN32UDPFactoryWorker.h"
#endif
#ifndef WIN32
    #include "opendavinci/odcore/wrapper/POSIX/POSIXUDPFactoryWorker.h"
#endif

namespace odcore {
    namespace io {
        namespace udp {

            SharedPointer<UDPSender> UDPFactory::createUDPSender(const string &address, const uint32_t &port) {
                typedef odcore::wrapper::ConfigurationTraits<odcore::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<UDPSender>(odcore::wrapper::UDPFactoryWorker<configuration::value>::createUDPSender(address, port));
            }

            SharedPointer<UDPReceiver> UDPFactory::createUDPReceiver(const string &address, const uint32_t &port) {
                typedef odcore::wrapper::ConfigurationTraits<odcore::wrapper::NetworkLibraryProducts>::configuration configuration;
                return SharedPointer<UDPReceiver>(odcore::wrapper::UDPFactoryWorker<configuration::value>::createUDPReceiver(address, port));
            }

        }
    }
} // odcore::io::udp
