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

#include <sys/socket.h>

#include <cerrno>
#include <cstring>
#include <sstream>

#include "opendavinci/odcore/wrapper/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/odcore/wrapper/POSIX/POSIXUDPSender.h"

namespace odcore {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXUDPSender::POSIXUDPSender(const string &address, const uint32_t &port) :
                m_address(),
                m_fd(),
                m_socketMutex() {
                m_socketMutex = unique_ptr<Mutex>(MutexFactory::createMutex());
                if (m_socketMutex.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::POSIXUDPSender] Error creating mutex: " << strerror(errno);
                    throw s.str();
                }

                // Create socket for sending.
                m_fd = socket(PF_INET, SOCK_DGRAM, 0);
                if (m_fd < 0) {
                    stringstream s;
                    s << "[core::wrapper::POSIXUDPSender] Error while creating socket: " << strerror(errno);
                    throw s.str();
                }

                // Setup address and port.
                memset(&m_address, 0, sizeof(m_address));
                m_address.sin_family = AF_INET;
                m_address.sin_addr.s_addr = inet_addr(address.c_str());
                m_address.sin_port = htons(port);
            }

            POSIXUDPSender::~POSIXUDPSender() {
                // Interrupt socket.
                shutdown(m_fd, SHUT_RDWR);

                // Close socket.
                close(m_fd);
            }

            void POSIXUDPSender::send(const string &data) const {
                if (data.length() > POSIXUDPSender::MAX_UDP_PACKET_SIZE) {
                    stringstream s;
                    s << "[core::wrapper::POSIXUDPSender] Data to be sent is too large (" << data.length() << " > " << POSIXUDPSender::MAX_UDP_PACKET_SIZE << ").";
                    throw s.str();
                }

                m_socketMutex->lock();
                {
// Fix -Werror=strict-aliasing (ignoring it is okay for the following call.
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic push
#endif
#if (__GNUC__ == 4 && 3 <= __GNUC_MINOR__) || 4 < __GNUC__
#    pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
                    sendto(m_fd, data.c_str(), data.length(), 0, reinterpret_cast<const struct sockaddr *>(&m_address), sizeof(m_address));
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic pop
#endif
                }
                m_socketMutex->unlock();
            }

        }
    }
} // odcore::wrapper::POSIX
