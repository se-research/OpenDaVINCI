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

#include "core/base/Lock.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/Connection.h"
#include "core/io/tcp/TCPFactory.h"

namespace core {
    namespace io {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::data;

        Connection::Connection(const string& ip, const uint32_t &port) :
            m_listenerMutex(),
            m_listener(NULL),
            m_errorHandlerMutex(),
            m_errorHandler(NULL),
            m_connection(NULL),
            m_connectedMutex(),
            m_connected(false) {
            try {
                m_connection = core::io::tcp::TCPFactory::createTCPConnectionTo(ip, port);
            }
            catch (string& s) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ConnectException, s);
            }

            if (m_connection.isValid()) {
                m_connection->setStringListener(this);
                m_connection->setConnectionListener(this);
            }
        }

        Connection::Connection(core::SharedPointer<core::io::tcp::TCPConnection> connection) :
            m_listenerMutex(),
            m_listener(NULL),
            m_errorHandlerMutex(),
            m_errorHandler(NULL),
            m_connection(NULL),
            m_connectedMutex(),
            m_connected(false) {
            m_connection = connection;
            if (m_connection.isValid()) {
                m_connection->setStringListener(this);
                m_connection->setConnectionListener(this);
            }
        }

        Connection::~Connection() {
            if (m_connection.isValid()) {
                m_connection->setConnectionListener(NULL);
                m_connection->setStringListener(NULL);
                m_connection->stop();
            }

            Lock l(m_connectedMutex);
            m_connected = false;
        }

        bool Connection::isConnected() {
            Lock l(m_connectedMutex);
            return m_connected;
        }

        void Connection::send(Container &container) {
            container.setSentTimeStamp(TimeStamp());

            stringstream stringstreamValue;
            stringstreamValue << container;

            m_connection->send(stringstreamValue.str());
        }

        void Connection::nextString(const string &s) {
            Lock l(m_listenerMutex);

            if (m_listener != NULL) {
                Container container;

                stringstream stringstreamData(s);
                stringstreamData >> container;

                container.setReceivedTimeStamp(TimeStamp());

                // Inform the registered container listener about the new data.
                m_listener->nextContainer(container);
            }
        }

        void Connection::handleConnectionError() {
            {
                Lock l(m_errorHandlerMutex);

                if (m_errorHandler != NULL) {
                    m_errorHandler->handleConnectionError();
                }
            }

            Lock l(m_connectedMutex);
            m_connected = false;
        }

        void Connection::setErrorListener(ConnectionErrorListener *el) {
            Lock l(m_errorHandlerMutex);
            m_errorHandler = el;
        }

        void Connection::setContainerListener(core::io::conference::ContainerListener *cl) {
            Lock l(m_listenerMutex);
            m_listener = cl;
        }

        void Connection::start() {
            if (m_connection.isValid()) {
                m_connection->start();

                Lock l(m_connectedMutex);
                m_connected = true;
            }
        }

        void Connection::stop() {
            if (m_connection.isValid()) {
                m_connection->stop();

                Lock l(m_connectedMutex);
                m_connected = false;
            }
        }

    }
}
