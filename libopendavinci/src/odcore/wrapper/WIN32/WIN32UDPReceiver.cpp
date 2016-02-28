/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include <memory>
#include <iostream>
#include <sstream>
#include <string>

#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/io/Packet.h"
#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/WIN32/WIN32UDPReceiver.h"

namespace odcore {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32UDPReceiver::WIN32UDPReceiver(const string &address, const uint32_t &port, const bool &isMulticast) :
                m_isMulticast(isMulticast),
                m_address(),
                m_mreq(),
                m_fd(),
                m_buffer(NULL),
                m_thread() {
                m_buffer = new char[BUFFER_SIZE];
                if (m_buffer == NULL) {
                    stringstream s;
                    s << "[core::wrapper::WIN32UDPReceiver] Error while allocating memory for buffer.";
                    throw s.str();
                }

                // Load Winsock 2.2 DLL.
                WSADATA wsaData;
                if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32UDPReceiver] Error while calling WSAStartUp: " << retcode;
                    throw s.str();
                }
                
                // Create socket for receiving.
                m_fd = ::socket(PF_INET, SOCK_DGRAM, 0);
                if (m_fd < 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32UDPReceiver] Error while creating file descriptor: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }

                // Allow reusing of ports by multiple sockets.
                uint32_t yes = 1;
                if (::setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes)) < 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32UDPReceiver] Error while setting socket options: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }

                // Setup address and port.
                memset(&m_address, 0, sizeof(m_address));
                m_address.sin_family = AF_INET;
                // The binding is different from POSIX as Windows would return the WSA error 10049 if we would use address here. See explanation http://www.sockets.com/err_lst1.htm for error 10049.
                m_address.sin_addr.s_addr = (m_isMulticast ? htonl(INADDR_ANY) : inet_addr(address.c_str()));
                m_address.sin_port = htons(port);

                // Bind to receive address/port.
                if (::bind(m_fd, (struct sockaddr *) &m_address, sizeof(m_address)) < 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32UDPReceiver] Error while binding: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();
                    
                    throw s.str();
                }

                if (m_isMulticast) {
                    // Join the multicast group.
                    m_mreq.imr_multiaddr.s_addr = inet_addr(address.c_str());
                    m_mreq.imr_interface.s_addr = htonl(INADDR_ANY);
                    if (::setsockopt(m_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&m_mreq, sizeof(m_mreq)) < 0) {
                        stringstream s;
                        const int retcode = WSAGetLastError();
                        s << "[core::wrapper::WIN32UDPReceiver] Error while joining multicast group: " << retcode;

                        // Decrement Winsock 2.2 DLL access counter.
                        WSACleanup();

                        throw s.str();
                    }
                }

                // Create thread for encapsulating waiting for receiving data.
                m_thread = unique_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::WIN32UDPReceiver] Error while creating thread.";

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();
                    
                    throw s.str();
                }
            }

            WIN32UDPReceiver::~WIN32UDPReceiver() {
                // Stop receiving.
                stop();

                // Close file descriptor.
                ::closesocket(m_fd);

                if (m_buffer != NULL) {
                    delete [] m_buffer;
                }
                m_buffer = NULL;

                // Decrement Winsock 2.2 DLL access counter.
                WSACleanup();
            }

            const char* WIN32UDPReceiver::inet_ntop(int af, const void* src, char* dst, int cnt) {
                struct sockaddr_in srcaddr;

                memset(&srcaddr, 0, sizeof(struct sockaddr_in));
                memcpy(&(srcaddr.sin_addr), src, sizeof(srcaddr.sin_addr));

                srcaddr.sin_family = af;
                if (WSAAddressToString((struct sockaddr*) &srcaddr, sizeof(struct sockaddr_in), 0, dst, (LPDWORD)&cnt) != 0) {
                    const int retcode = WSAGetLastError();
                    CLOG3 << "[core::wrapper::WIN32UDPReceiver] Error while calling WSAAddressToString: " << retcode;
                    return NULL;
                }
                return dst;
            }

            void WIN32UDPReceiver::run() {
                fd_set rfds;
                struct timeval timeout;
                int32_t nbytes = 0;

                struct sockaddr_storage remote;

                while (isRunning()) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fd, &rfds);

                    ::select(m_fd + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fd, &rfds)) {
                        // Get data and sender address.
                        size_t addrLength = sizeof(remote);
                        nbytes = ::recvfrom(m_fd, m_buffer, BUFFER_SIZE, 0, (struct sockaddr *)&remote, (socklen_t*)&addrLength);

                        if (nbytes > 0) {
                            // Get sender address.
                            const uint32_t MAX_ADDR_SIZE = 1024;
                            char remoteAddr[MAX_ADDR_SIZE];
                            inet_ntop(remote.ss_family, &(((struct sockaddr_in*)&remote)->sin_addr), remoteAddr, sizeof(remoteAddr));

                            // ------------------------v (remote address)-----v (data)
                            nextPacket(odcore::io::Packet(string(remoteAddr), string(m_buffer, nbytes)));
                        }
                    }
                }
            }

            void WIN32UDPReceiver::start() {
                m_thread->start();
            }

            void WIN32UDPReceiver::stop() {
                if (m_isMulticast) {
                    // Remove ourselves from membership.
                    ::setsockopt(m_fd, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&m_mreq, sizeof(m_mreq));
                }

                // Interrupt socket.
                ::shutdown(m_fd, SD_BOTH); // On POSIX: SHUT_RDWR

                m_thread->stop();
            }

            bool WIN32UDPReceiver::isRunning() {
                return m_thread->isRunning();
            }
        }
    }
} // odcore::wrapper::WIN32
