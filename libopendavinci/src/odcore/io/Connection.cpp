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

#include <iosfwd>

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/io/ConnectionErrorListener.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/tcp/TCPFactory.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace io {

        using namespace std;
        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::data;

        Connection::Connection(const string& ip, const uint32_t &port) :
            m_listenerMutex(),
            m_listener(NULL),
            m_errorHandlerMutex(),
            m_errorHandler(NULL),
            m_connection(NULL),
            m_connectedMutex(),
            m_connected(false) {
            try {
                m_connection = odcore::io::tcp::TCPFactory::createTCPConnectionTo(ip, port);
            }
            catch (string& s) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ConnectException, s);
            }

            if (m_connection.get()) {
                m_connection->setStringListener(this);
                m_connection->setConnectionListener(this);
            }
        }

        Connection::Connection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection) :
            m_listenerMutex(),
            m_listener(NULL),
            m_errorHandlerMutex(),
            m_errorHandler(NULL),
            m_connection(NULL),
            m_connectedMutex(),
            m_connected(false) {
            m_connection = connection;
            if (m_connection.get()) {
                m_connection->setStringListener(this);
                m_connection->setConnectionListener(this);
            }
        }

        Connection::~Connection() {
            if (m_connection.get()) {
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

        void Connection::setContainerListener(odcore::io::conference::ContainerListener *cl) {
            Lock l(m_listenerMutex);
            m_listener = cl;
        }

        void Connection::start() {
            if (m_connection.get()) {
                m_connection->start();

                Lock l(m_connectedMutex);
                m_connected = true;
            }
        }

        void Connection::stop() {
            if (m_connection.get()) {
                m_connection->stop();

                Lock l(m_connectedMutex);
                m_connected = false;
            }
        }

    }
}
