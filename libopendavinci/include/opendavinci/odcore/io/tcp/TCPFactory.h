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

#ifndef OPENDAVINCI_CORE_IO_TCP_TCPFACTORY_H_
#define OPENDAVINCI_CORE_IO_TCP_TCPFACTORY_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>

namespace odcore {
    namespace io {
        namespace tcp {

class TCPAcceptor;
class TCPConnection;

            using namespace std;

            struct OPENDAVINCI_API TCPFactory {
                /**
                 * This method creates a TCP acceptor listening on the specified port.
                 *
                 * @param port to listen on.
                 */
                static std::shared_ptr<TCPAcceptor> createTCPAcceptor(const uint32_t &port);

                /**
                 * This method creates a TCP connection to the specified IP address and port.
                 *
                 * @param ip Ip address to connect to.
                 * @param port to connect to.
                 */
                static std::shared_ptr<TCPConnection> createTCPConnectionTo(const string &ip, const uint32_t &port);
            };

        }
    }
}

#endif /* OPENDAVINCI_CORE_IO_TCP_TCPFACTORY_H_ */
