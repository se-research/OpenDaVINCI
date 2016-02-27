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

#ifndef OPENDAVINCI_CORE_IO_CONNECTION_H_
#define OPENDAVINCI_CORE_IO_CONNECTION_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/ConnectionListener.h"
#include "opendavinci/odcore/io/StringListener.h"
#include "opendavinci/odcore/io/conference/ContainerObserver.h"
#include "opendavinci/odcore/io/tcp/TCPConnection.h"

namespace odcore { namespace data { class Container; } }

namespace odcore {
    namespace io {

class ConnectionErrorListener;
namespace conference { class ContainerListener; }

        using namespace std;

        class OPENDAVINCI_API Connection : public odcore::io::conference::ContainerObserver,
                                           protected StringListener,
                                           protected ConnectionListener
        {
            private:
                /**
                 * Forbidden copy constructor
                 */
                Connection(Connection& obj);

                /**
                 * Forbidden assignement operator
                 */
                Connection& operator=(Connection& obj);

            public:
                Connection(const std::string &ip, const uint32_t &port);
                virtual ~Connection();

                void send(odcore::data::Container &container);
                virtual void setContainerListener(odcore::io::conference::ContainerListener *cl);
                void setErrorListener(ConnectionErrorListener* el);

                void start();
                void stop();

                bool isConnected();

            protected:
                friend class ConnectionAcceptor;
                Connection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection);

                virtual void nextString(const std::string &s);
                virtual void handleConnectionError();

            private:
                odcore::base::Mutex m_listenerMutex;
                odcore::io::conference::ContainerListener* m_listener;

                odcore::base::Mutex m_errorHandlerMutex;
                ConnectionErrorListener* m_errorHandler;

                std::shared_ptr<odcore::io::tcp::TCPConnection> m_connection;

                odcore::base::Mutex m_connectedMutex;
                bool m_connected;
        };
    }
}

#endif /* OPENDAVINCI_CORE_IO_CONNECTION_H_ */
