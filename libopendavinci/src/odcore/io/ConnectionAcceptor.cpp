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

#include <iostream>
#include <sstream>
#include <string>

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/io/ConnectionAcceptor.h"
#include "opendavinci/odcore/io/ConnectionAcceptorListener.h"
#include "opendavinci/odcore/io/tcp/TCPConnection.h"
#include "opendavinci/odcore/io/tcp/TCPFactory.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace io {

        using namespace std;
        using namespace odcore::base;

        ConnectionAcceptor::ConnectionAcceptor(const uint32_t &port) :
            m_listenerMutex(),
            m_listener(NULL),
            m_acceptor(NULL) {
            try {
                m_acceptor = odcore::io::tcp::TCPFactory::createTCPAcceptor(port);
            }
            catch (std::string &s) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ConnectionAcceptorException , s);
            }

            m_acceptor->setAcceptorListener(this);
        }

        ConnectionAcceptor::~ConnectionAcceptor() {
            m_acceptor->stop();
            m_acceptor->setAcceptorListener(NULL);
        }

        void ConnectionAcceptor::setConnectionAcceptorListener(ConnectionAcceptorListener* listener) {
            Lock l(m_listenerMutex);
            m_listener = listener;
        }

        void ConnectionAcceptor::onNewConnection(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection) {
            Lock l(m_listenerMutex);
            if (m_listener != NULL) {
                m_listener->onNewConnection(odcore::SharedPointer<odcore::io::Connection>(new odcore::io::Connection(connection)));
            }
            else {
                CLOG3 << "[core::io::ConnectionAcceptor] no listener to call" << endl;
            }
        }

        void ConnectionAcceptor::start() {
            m_acceptor->start();
        }

        void ConnectionAcceptor::stop() {
            m_acceptor->stop();
        }
    }
}
