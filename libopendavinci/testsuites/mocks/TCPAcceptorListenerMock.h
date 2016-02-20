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

#ifndef MOCKS__TCPACCEPTORLISTENERMOCK_H
#define MOCKS__TCPACCEPTORLISTENERMOCK_H

#include "FunctionCallWaiter.h"

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/io/tcp/TCPAcceptorListener.h"
#include "opendavinci/odcore/io/tcp/TCPConnection.h"

namespace mocks {
    class TCPAcceptorListenerMock : public odcore::io::tcp::TCPAcceptorListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            TCPAcceptorListenerMock(const TCPAcceptorListenerMock& );

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            TCPAcceptorListenerMock& operator=(const TCPAcceptorListenerMock&);

            odcore::SharedPointer<odcore::io::tcp::TCPConnection> m_connection;

        public:
            TCPAcceptorListenerMock() :
                m_connection(NULL),
                CALLWAITER_onNewConnection()
            {};

            ~TCPAcceptorListenerMock() {};

            odcore::SharedPointer<odcore::io::tcp::TCPConnection> getConnection() {
                return m_connection;
            }

            void dontDeleteConnection() {
                m_connection.release();
            }

             virtual void onNewConnection(odcore::SharedPointer<odcore::io::tcp::TCPConnection> connection) {
                m_connection = connection;
                CALLWAITER_onNewConnection.called();
            }

            FunctionCallWaiter CALLWAITER_onNewConnection;
    };
}
#endif
