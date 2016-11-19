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

#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>

// Include headers to query IP addresses from local devices.
#ifdef __linux__
    #include <netdb.h>
    #include <ifaddrs.h>
#endif

#include <cerrno>
#include <cstring>
#include <sstream>

#include "opendavinci/odcore/io/Packet.h"
#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/POSIX/POSIXUDPReceiver.h"
#include "opendavinci/odcore/wrapper/Thread.h"

namespace odcore {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXUDPReceiver::POSIXUDPReceiver(const string &address, const uint32_t &port, const bool &isMulticast) :
                m_mapOfIPAddresses(),
                m_portToIgnore(0),
                m_isMulticast(isMulticast),
                m_address(),
                m_mreq(),
                m_fd(),
                m_buffer(NULL),
                m_thread() {
                m_buffer = new char[BUFFER_SIZE];
                if (m_buffer == NULL) {
                    stringstream s;
                    s << "[POSIXUDPReceiver] Error while allocating memory for buffer: " << strerror(errno);
                    throw s.str();
                }

                // Create socket for sending.
                m_fd = socket(PF_INET, SOCK_DGRAM, 0);
                if (m_fd < 0) {
                    stringstream s;
                    s << "[POSIXUDPReceiver] Error while creating socket: " << strerror(errno);
                    throw s.str();
                }

                // Allow reusing of ports by multiple sockets.
                uint32_t yes = 1;
                if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0) {
                    stringstream s;
                    s << "[POSIXUDPReceiver] Error while setting socket options: " << strerror(errno);
                    throw s.str();
                }


                // Setup address and port.
                memset(&m_address, 0, sizeof(m_address));
                m_address.sin_family = AF_INET;
                // Bind to given address.
                m_address.sin_addr.s_addr = inet_addr(address.c_str());
                m_address.sin_port = htons(port);

                // Bind to receive address/port.
                // Fixing -Werror=strict-aliasing
                struct sockaddr addr;
                memcpy(&addr, &m_address, sizeof(m_address));
                if (::bind(m_fd, &addr, sizeof(m_address)) < 0) {
                    stringstream s;
                    s << "[POSIXUDPReceiver] Error while binding socket: " << strerror(errno);
                    throw s.str();
                }

                if (m_isMulticast) {
                    // Join the multicast group.
                    m_mreq.imr_multiaddr.s_addr = inet_addr(address.c_str());
                    m_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
                    if (setsockopt(m_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &m_mreq, sizeof(m_mreq)) < 0) {
                        stringstream s;
                        s << "[POSIXUDPReceiver] Error while joining multicast group: " << strerror(errno);
                        throw s.str();
                    }
                }

                // Create thread for encapsulating waiting for receiving data.
                m_thread = unique_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    stringstream s;
                    s << "[POSIXUDPReceiver] Error creating thread: " << strerror(errno);
                    throw s.str();
                }

                // Fill map of IP addresses from local devices to avoid
                // circular data sending.
                getIPAddresses();
            }

            POSIXUDPReceiver::~POSIXUDPReceiver() {
                // Stop receiving.
                stop();

                // Close file descriptor.
                close(m_fd);

                if (m_buffer != NULL) {
                    delete [] m_buffer;
                }
                m_buffer = NULL;
            }

            void POSIXUDPReceiver::getIPAddresses() {
#ifdef __linux__
                struct ifaddrs *ifaddr;
                if (0 == ::getifaddrs(&ifaddr)) {
                    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
                        if ( (ifa->ifa_addr != NULL) && (ifa->ifa_addr->sa_family == AF_INET) ) {
                            if (0 == ::getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), NULL, 0, NULL, 0, NI_NUMERICHOST)) {
                                // Fix compile warning -Wcast-align.
                                struct sockaddr_in tmpAddr;
                                memcpy(&tmpAddr, ifa->ifa_addr, sizeof(tmpAddr));
                                // Get numerical representation of IP address...
                                const unsigned long IP_ADDRESS = tmpAddr.sin_addr.s_addr;
                                // ...and store it as key in map for access in logarithmic time.
                                m_mapOfIPAddresses[IP_ADDRESS] = true;
                            }
                        }
                    }
                    ::freeifaddrs(ifaddr);
                }
#endif
            }

            void POSIXUDPReceiver::setSenderPortToIgnore(const uint16_t &portToIgnore) {
                m_portToIgnore = portToIgnore;
            }

            void POSIXUDPReceiver::run() {
                fd_set rfds;
                struct timeval timeout;
                int32_t nbytes = 0;

                struct sockaddr_storage remote;

                while (isRunning()) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fd, &rfds);

                    select(m_fd + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fd, &rfds)) {
                        // Get data and sender address.
                        socklen_t addrLength= sizeof(remote);

// Fix -Werror=strict-aliasing (ignoring it is okay for the following call).
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic push
#endif
#if (__GNUC__ == 4 && 3 <= __GNUC_MINOR__) || 4 < __GNUC__
#    pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
                        nbytes = recvfrom(m_fd, m_buffer, BUFFER_SIZE, 0, reinterpret_cast<struct sockaddr *>(&remote), reinterpret_cast<socklen_t*>(&addrLength));
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic pop
#endif

                        if (nbytes > 0) {
// Fix -Werror=strict-aliasing (ignoring it is okay for the following calls).
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic push
#endif
#if (__GNUC__ == 4 && 3 <= __GNUC_MINOR__) || 4 < __GNUC__
#    pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
                            // Get IP address and port from sender.
                            const unsigned long RECVFROM_IP_ADDRESS = (reinterpret_cast<struct sockaddr_in*>(&remote))->sin_addr.s_addr;
                            const uint16_t RECVFROM_PORT = ntohs(reinterpret_cast<struct sockaddr_in*>(&remote)->sin_port);
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic pop
#endif

                            // Forward packet if (a) it is NOT sent from the same machine that is receiving (i.e. over network),
                            // or, if sent from the same machine as the one used for receiving, if the data was not sent from a
                            // port that shall be ignored.
                            const bool ACCEPT_PACKET = (0 == m_mapOfIPAddresses.count(RECVFROM_IP_ADDRESS))
                                                    || ((m_mapOfIPAddresses.count(RECVFROM_IP_ADDRESS) > 0) && (m_portToIgnore != RECVFROM_PORT));
                            if (ACCEPT_PACKET) {
                                // Get sender address.
                                const uint32_t MAX_ADDR_SIZE = 1024;
                                char remoteAddr[MAX_ADDR_SIZE];
// Fix -Werror=strict-aliasing (ignoring it is okay for the following call).
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic push
#endif
#if (__GNUC__ == 4 && 3 <= __GNUC_MINOR__) || 4 < __GNUC__
#    pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif
                                inet_ntop(remote.ss_family, &((reinterpret_cast<struct sockaddr_in*>(&remote))->sin_addr), remoteAddr, sizeof(remoteAddr));
#if !defined(__OpenBSD__) && !defined(__NetBSD__)
#    pragma GCC diagnostic pop
#endif
                                // -----     -----------------v (remote address)--v (data)
                                nextPacket(odcore::io::Packet(string(remoteAddr), string(m_buffer, nbytes)));
                            }
                        }
                    }
                }
            }

            void POSIXUDPReceiver::start() {
                m_thread->start();
            }

            void POSIXUDPReceiver::stop() {
                if (m_isMulticast) {
                    // Remove ourselves from membership.
                    setsockopt(m_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, &m_mreq, sizeof(m_mreq));
                }

                // Interrupt socket.
                shutdown(m_fd, SHUT_RDWR);

                m_thread->stop();
            }

            bool POSIXUDPReceiver::isRunning() {
                return m_thread->isRunning();
            }
        }
    }
} // odcore::wrapper::POSIX
