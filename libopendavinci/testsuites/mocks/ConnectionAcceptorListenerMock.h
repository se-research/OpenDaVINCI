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

#ifndef MOCKS__CONNECTIONACCEPTORLISTENERMOCK_H
#define MOCKS__CONNECTIONACCEPTORLISTENERMOCK_H

#include <iostream>
#include <memory>
#include <string>

#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Mutex.h"

#include "opendavinci/odcore/io/ConnectionAcceptorListener.h"
#include "opendavinci/odcore/io/Connection.h"

namespace mocks {
    using namespace odcore;

    class ConnectionAcceptorListenerMock : public odcore::io::ConnectionAcceptorListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            ConnectionAcceptorListenerMock(const ConnectionAcceptorListenerMock& );

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            ConnectionAcceptorListenerMock& operator=(const ConnectionAcceptorListenerMock&);

        private:
            std::shared_ptr<odcore::io::Connection> m_connection;
            bool m_connected;
            base::Condition m_condition;

        public:
            ConnectionAcceptorListenerMock() :
                    m_connection(NULL),
                    m_connected(false),
                    m_condition() {};

            ~ConnectionAcceptorListenerMock() {};

            std::shared_ptr<io::Connection> getConnection() {
                return m_connection;
            }

            void dontDeleteConnection() {
                m_connection.reset();
            }

            void waitForConnection() {
                base::Lock l(m_condition);
                if (!hasConnection() ) {
                    m_condition.waitOnSignal();
                }
            }

            bool hasConnection() {
                return m_connected;
            }

            virtual void onNewConnection(std::shared_ptr<odcore::io::Connection> connection) {
                base::Lock l(m_condition);
                m_connection = connection;
                m_connected = true;
                m_condition.wakeAll();
            }
    };
}
#endif
