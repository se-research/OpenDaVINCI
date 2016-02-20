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

#ifndef CORE_CONNECTIONTESTSUITE_H_
#define CORE_CONNECTIONTESTSUITE_H_

#include <iostream>                     // for operator<<, basic_ostream, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/SharedPointer.h"         // for SharedPointer
#include "opendavinci/core/base/Thread.h"           // for Thread
#include "opendavinci/core/data/Container.h"        // for Container, etc
#include "opendavinci/core/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendavinci/core/io/Connection.h"         // for Connection
#include "opendavinci/core/io/ConnectionAcceptor.h"  // for ConnectionAcceptor
#include "mocks/ConnectionAcceptorListenerMock.h"
#include "mocks/ConnectionErrorListenerMock.h"
#include "mocks/ContainerListenerMock.h"

namespace core { namespace exceptions { class ConnectException; } }

using namespace std;
using namespace core::base;
using namespace core::io;
using namespace core::data;
using namespace core::exceptions;

class ConnectionTestsuite : public CxxTest::TestSuite {
    public:
        void testAcceptAndConnect() {
#ifndef WIN32
            ConnectionAcceptor acceptor(12345);
            acceptor.start();

            // Connection test 1
            mocks::ConnectionAcceptorListenerMock cam1;
            acceptor.setConnectionAcceptorListener(&cam1);

            Connection connection1("127.0.0.1", 12345);
            connection1.start();

            Thread::usleepFor(2000);
            cam1.waitForConnection();
            TS_ASSERT( cam1.hasConnection() );

            // Connection test 2
            mocks::ConnectionAcceptorListenerMock cam2;
            acceptor.setConnectionAcceptorListener(&cam2);

            Connection connection2("127.0.0.1", 12345);
            connection2.start();

            Thread::usleepFor(2000);
            cam2.waitForConnection();
            TS_ASSERT( cam2.hasConnection() );

            // Connection test 3 with disabled acceptor
            acceptor.stop();
            mocks::ConnectionAcceptorListenerMock cam3;
            acceptor.setConnectionAcceptorListener(&cam3);

            bool exceptionCaught = false;
            try {
                Connection connection3("127.0.0.1", 12345);
                connection3.start();
            } catch (ConnectException &/*s*/) {
                exceptionCaught = true;
            }

            TS_ASSERT( exceptionCaught == true);
            TS_ASSERT( !cam3.hasConnection() );

            connection1.stop();
            connection2.stop();
            acceptor.stop();
#endif
        }

        void testErrorHandler() {
#ifndef WIN32
            clog << "testErrorHandler" << endl;
            mocks::ConnectionAcceptorListenerMock cam;

            ConnectionAcceptor acceptor(12346);
            acceptor.setConnectionAcceptorListener(&cam);
            acceptor.start();

            Connection  connection1("127.0.0.1", 12346);

            mocks::ConnectionErrorListenerMock cem;
            connection1.setErrorListener(&cem);
            connection1.start();
            Thread::usleepFor(10000);
            cam.waitForConnection();
            TS_ASSERT( cam.hasConnection() );
            core::SharedPointer<core::io::Connection> connection2 = cam.getConnection();
            cam.dontDeleteConnection();

            // Provoke an error by deleting connection
            clog << "Starting test." << endl;
            connection2.release();

            TS_ASSERT( cem.CALLWAITER_handleConnectionError.wait() );

            connection1.stop();
            acceptor.stop();
#endif
        }

        void testTransfer() {
            ConnectionAcceptor acceptor(12345);
            acceptor.start();

            // Connecting
            mocks::ConnectionAcceptorListenerMock cam;
            acceptor.setConnectionAcceptorListener(&cam);

            Connection connection("127.0.0.1", 12345);
            connection.start();

            Thread::usleepFor(2000);
            cam.waitForConnection();
            TS_ASSERT( cam.hasConnection() );
            cam.getConnection()->start();

            mocks::ContainerListenerMock clm1;

            TimeStamp ts;
            Container container(ts);
            clm1.VALUES_nextContainer.addItem(container);
            clm1.VALUES_nextContainer.prepare();

            cam.getConnection()->setContainerListener(&clm1);

            connection.send(container);

            TS_ASSERT( clm1.CALLWAITER_nextContainer.wait());
            TimeStamp rec = clm1.currentValue.getData<TimeStamp>();

            TS_ASSERT( rec.getFractionalMicroseconds() == ts.getFractionalMicroseconds())
            TS_ASSERT( rec.getSeconds() == ts.getSeconds());
        }
};

#endif /*CORE_CONNECTIONTESTSUITE_H_*/
