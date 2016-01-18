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

#include <string>
#include <iostream>

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Condition.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/Mutex.h"

#include "opendavinci/core/io/ConnectionAcceptorListener.h"
#include "opendavinci/core/io/Connection.h"

namespace mocks {
    using namespace core;

    class ConnectionAcceptorListenerMock : public core::io::ConnectionAcceptorListener {
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
            core::SharedPointer<core::io::Connection> m_connection;
            bool m_connected;
            base::Condition m_condition;

        public:
            ConnectionAcceptorListenerMock() :
                    m_connection(NULL),
                    m_connected(false),
                    m_condition() {};

            ~ConnectionAcceptorListenerMock() {};

            core::SharedPointer<io::Connection> getConnection() {
                return m_connection;
            }

            void dontDeleteConnection() {
                m_connection.release();
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

            virtual void onNewConnection(core::SharedPointer<core::io::Connection> connection) {
                base::Lock l(m_condition);
                m_connection = connection;
                m_connected = true;
                m_condition.wakeAll();
            }
    };
}
#endif
