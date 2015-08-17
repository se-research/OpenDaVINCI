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

#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/WIN32/WIN32UDPSender.h"

namespace core {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32UDPSender::WIN32UDPSender(const string &address, const uint32_t &port) :
                m_address(),
                m_fd(),
                m_socketMutex(NULL) {
                m_socketMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_socketMutex.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::WIN32UDPSender] Error while creating mutex.";
                    throw s.str();
                }

				// Load Winsock 2.2 DLL.
				WSADATA wsaData;
				if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
					stringstream s;
					const int retcode = WSAGetLastError();
					s << "[core::wrapper::WIN32UDPSender] Error while calling WSAStartUp: " << retcode;
					throw s.str();
				}

                // Create socket for sending.
                m_fd = ::socket(PF_INET, SOCK_DGRAM, 0);
                if (m_fd < 0) {
                    stringstream s;
					const int retcode = WSAGetLastError();
					s << "[core::wrapper::WIN32UDPSender] Error while creating file descriptor: " << retcode;

					// Decrement Winsock 2.2 DLL access counter.
					WSACleanup();

                    throw s.str();
                }

                // Setup address and port.
                memset(&m_address, 0, sizeof(m_address));
                m_address.sin_family = AF_INET;
                m_address.sin_addr.s_addr = inet_addr(address.c_str());
                m_address.sin_port = htons(port);
            }

            WIN32UDPSender::~WIN32UDPSender() {
                // Interrupt socket.
                ::shutdown(m_fd, SD_BOTH); // On POSIX: SHUT_RDWR

                // Close socket.
                ::closesocket(m_fd);

				// Decrement Winsock 2.2 DLL access counter.
				WSACleanup();
            }

            void WIN32UDPSender::send(const string &data) const {
                if (data.length() > WIN32UDPSender::MAX_UDP_PACKET_SIZE) {
                    stringstream s;
                    s << "[core::wrapper::WIN32UDPSender] Data to be sent is too large.";
                    throw s.str();
                }

                m_socketMutex->lock();
                {
					::sendto(m_fd, data.c_str(), data.length(), 0, (struct sockaddr *) &m_address, sizeof(m_address));
                }
                m_socketMutex->unlock();
            }

        }
    }
} // core::wrapper::WIN32Impl
