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

#include <sstream>
#include <string>

#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/odcore/wrapper/WIN32/WIN32TCPAcceptor.h"
#include "opendavinci/odcore/wrapper/WIN32/WIN32TCPConnection.h"

namespace odcore {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32TCPAcceptor::WIN32TCPAcceptor(const uint32_t &port) :
                m_thread(),
                m_listenerMutex(),
                m_listener(NULL),
                m_fileDescriptor(0),
                m_port(port) {
                m_thread = unique_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    throw std::string("[core::wrapper::WIN32TCPAcceptor] Error creating thread");
                }

                m_listenerMutex = unique_ptr<Mutex>(MutexFactory::createMutex());
                if (m_listenerMutex.get() == NULL) {
                    throw std::string("[core::wrapper::WIN32TCPAcceptor] Error creating mutex");
                }

                // Load Winsock 2.2 DLL.
                WSADATA wsaData;
                if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32TCPAcceptor] Error while calling WSAStartUp: " << retcode;
                    throw s.str();
                }
                
                // Create socket.
                m_fileDescriptor = ::socket(AF_INET, SOCK_STREAM, 0);
                if (m_fileDescriptor < 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32TCPAcceptor] Error while creating file descriptor: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }

                // Allow reusing of ports by multiple sockets.
                int32_t yes = 1;
                int32_t retval = ::setsockopt (m_fileDescriptor,
                                               SOL_SOCKET,
                                               SO_REUSEADDR,
                                               (char*)&yes,
                                               sizeof(yes));
                if (retval < 0) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32TCPAcceptor] Error while setting socket options: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }

                // Setup address and port.
                sockaddr_in address;
                memset(&address, 0, sizeof(address));
                address.sin_family = AF_INET;
                address.sin_addr.s_addr = htonl(INADDR_ANY);
                address.sin_port = htons(port);

                // Bind handle.
                if (::bind(m_fileDescriptor, (struct sockaddr *) &address, sizeof(address)) == -1) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32TCPAcceptor] Error while binding: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }

                if (::listen(m_fileDescriptor, WIN32TCPAcceptor::BACKLOG) == -1) {
                    stringstream s;
                    const int retcode = WSAGetLastError();
                    s << "[core::wrapper::WIN32TCPAcceptor] Error while listening: " << retcode;

                    // Decrement Winsock 2.2 DLL access counter.
                    WSACleanup();

                    throw s.str();
                }
            }

            WIN32TCPAcceptor::~WIN32TCPAcceptor() {
                setAcceptorListener(NULL);
                ::closesocket(m_fileDescriptor);

                // Decrement Winsock 2.2 DLL access counter.
                WSACleanup();
            }

            void WIN32TCPAcceptor::setAcceptorListener(odcore::io::tcp::TCPAcceptorListener* listener) {
                m_listenerMutex->lock();
                    m_listener = listener;
                m_listenerMutex->unlock();
            }

            void WIN32TCPAcceptor::invokeAcceptorListener(std::shared_ptr<odcore::io::tcp::TCPConnection> connection) {
                m_listenerMutex->lock();
                if (m_listener != NULL) {
                    m_listener->onNewConnection(connection);
                }
                else {
                    // No listener available. The std::shared_ptr will delete the connection automatically to prevent memory leakage.
                }
                m_listenerMutex->unlock();
            }

            void WIN32TCPAcceptor::start() {
                m_thread->start();
            }

            void WIN32TCPAcceptor::stop() {
                m_thread->stop();
            }

            bool WIN32TCPAcceptor::isRunning() {
                return m_thread->isRunning();
            }

            void WIN32TCPAcceptor::run() {
                fd_set rfds;
                struct timeval timeout;

                while (isRunning() ) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fileDescriptor, &rfds);

                    ::select(m_fileDescriptor + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fileDescriptor, &rfds)) {
                        sockaddr clientsock;
                        socklen_t csize = sizeof(clientsock);

                        int32_t client = ::accept(m_fileDescriptor, &clientsock, &csize);

                        if (client >= 0) {
                            invokeAcceptorListener(std::shared_ptr<odcore::io::tcp::TCPConnection>(new WIN32TCPConnection(client)));
                        }
                    }
                }
                ::closesocket(m_fileDescriptor);
            }

        }
    }
}
