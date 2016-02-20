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

#include <cerrno>
#include <cstring>
#include <sstream>

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/io/tcp/TCPAcceptorListener.h"
#include "opendavinci/core/io/tcp/TCPConnection.h"
#include "opendavinci/core/wrapper/ConcurrencyFactory.h"
#include "opendavinci/core/wrapper/Mutex.h"
#include "opendavinci/core/wrapper/MutexFactory.h"
#include "opendavinci/core/wrapper/POSIX/POSIXTCPAcceptor.h"
#include "opendavinci/core/wrapper/POSIX/POSIXTCPConnection.h"
#include "opendavinci/core/wrapper/Thread.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXTCPAcceptor::POSIXTCPAcceptor(const uint32_t &port) :
                m_thread(NULL),
                m_listenerMutex(NULL),
                m_listener(NULL),
                m_fileDescriptor(0),
                m_port(port) {
                m_thread = auto_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPAcceptor] Error creating thread: " << strerror(errno);
                    throw s.str();
                }

                m_listenerMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_listenerMutex.get() == NULL) {
                    stringstream s;
                    s << "[POSIXTCPConnection] Error creating mutex: " << strerror(errno);
                    throw s.str();
                }

                // Create socket.
                m_fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
                if (m_fileDescriptor < 0) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPAcceptor] Error while creating socket: " << strerror(errno);
                    throw s.str();
                }

                // Allow reusing of ports by multiple sockets.
                int32_t yes = 1;
                int32_t retval = setsockopt(m_fileDescriptor,
                                            SOL_SOCKET,
                                            SO_REUSEADDR,
                                            &yes,
                                            sizeof(yes));
                if (retval < 0) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPAcceptor] Error while setting socket options: " << strerror(errno);
                    throw s.str();
                }

                // Setup address and port.
                sockaddr_in address;
                memset(&address, 0, sizeof(address));
                address.sin_family = AF_INET;
                address.sin_addr.s_addr = htonl(INADDR_ANY);
                address.sin_port = htons(port);

                // Bind handle.
                if (::bind(m_fileDescriptor, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) == -1) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPAcceptor] Error while binding socket: " << strerror(errno);
                    throw s.str();
                }

                if (listen(m_fileDescriptor, POSIXTCPAcceptor::BACKLOG) == -1) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPAcceptor] Listen failed: " << strerror(errno);
                    throw s.str();
                }
            }

            POSIXTCPAcceptor::~POSIXTCPAcceptor() {
                setAcceptorListener(NULL);
                close(m_fileDescriptor);
            }

            void POSIXTCPAcceptor::setAcceptorListener(core::io::tcp::TCPAcceptorListener* listener) {
                m_listenerMutex->lock();
                    m_listener = listener;
                m_listenerMutex->unlock();
            }

            void POSIXTCPAcceptor::invokeAcceptorListener(core::SharedPointer<core::io::tcp::TCPConnection> connection) {
                m_listenerMutex->lock();
                if (m_listener != NULL) {
                    m_listener->onNewConnection(connection);
                }
                else {
                    // No listener available. The SharedPointer will delete the connection automatically to prevent memory leakage.
                }
                m_listenerMutex->unlock();
            }

            void POSIXTCPAcceptor::start() {
                m_thread->start();
            }

            void POSIXTCPAcceptor::stop() {
                m_thread->stop();
            }

            bool POSIXTCPAcceptor::isRunning() {
                return m_thread->isRunning();
            }

            void POSIXTCPAcceptor::run() {
                fd_set rfds;
                struct timeval timeout;

                while (isRunning() ) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fileDescriptor, &rfds);

                    select(m_fileDescriptor + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fileDescriptor, &rfds)) {
                        sockaddr clientsock;
                        socklen_t csize = sizeof(clientsock);

                        int32_t client = accept(m_fileDescriptor, &clientsock, &csize);
                        if (client >= 0) {
                            invokeAcceptorListener(core::SharedPointer<core::io::tcp::TCPConnection>(new POSIXTCPConnection(client)));
                        }
                    }
                }
                close(m_fileDescriptor);
            }

        }
    }
}
