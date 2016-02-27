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

#ifndef CORE_WRAPPER_TCPCONNECTIONTESTSUITE_H_
#define CORE_WRAPPER_TCPCONNECTIONTESTSUITE_H_

#include <memory>                       // for unique_ptr, etc
#include <string>                       // for string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include <memory>
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/io/tcp/TCPAcceptor.h"
#include "opendavinci/odcore/wrapper/NetworkLibraryProducts.h"
#include "mocks/ConnectionListenerMock.h"
#include "mocks/StringListenerMock.h"
#include "mocks/TCPAcceptorListenerMock.h"

#ifndef WIN32
    #include "opendavinci/odcore/wrapper/POSIX/POSIXTCPFactoryWorker.h"
#endif
#ifdef WIN32
    #include "opendavinci/odcore/wrapper/WIN32/WIN32TCPFactoryWorker.h"
#endif
#include "opendavinci/odcore/io/tcp/TCPConnection.h"  // for TCPConnection

namespace odcore { namespace io { class Connection; } }
namespace odcore { namespace io { namespace tcp { class TCPAcceptor; } } }

using namespace std;
using namespace odcore;
using namespace odcore::base;

template <typename worker> struct TCPConnectionTests
{
    static void transferTest()
    {
        mocks::TCPAcceptorListenerMock am;

        unique_ptr<odcore::io::tcp::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
        acceptor->setAcceptorListener(&am);
        acceptor->start();

        unique_ptr<odcore::io::tcp::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
        connection->start();

        TS_ASSERT(am.CALLWAITER_onNewConnection.wait());
        am.getConnection()->start();

        //Prepare StringListenerMock for connected TCPConnection
        mocks::StringListenerMock stmConnection;
        stmConnection.VALUES_nextString.addItem("TRANSFER ACCEPTED->CONNECTED");
        stmConnection.VALUES_nextString.prepare();
        connection->setStringListener(&stmConnection);

        //Prepare StringListenerMock for accepted TCPConnection
        mocks::StringListenerMock stmAcceptedConnection;
        stmAcceptedConnection.VALUES_nextString.addItem("TRANSFER CONNECTED->ACCEPTED");
        stmAcceptedConnection.VALUES_nextString.prepare();
        am.getConnection()->setStringListener(&stmAcceptedConnection);

        clog << "Sending from connected to accepted TCPConnection..." << endl;
        connection->send("TRANSFER CONNECTED->ACCEPTED");

        TS_ASSERT( stmAcceptedConnection.CALLWAITER_nextString.wait() );
        TS_ASSERT( stmAcceptedConnection.correctCalled() );
        TS_ASSERT( !stmConnection.CALLWAITER_nextString.wasCalled() );
        stmAcceptedConnection.CALLWAITER_nextString.reset();

        clog << "Sending from accepted to connected TCPConnection..." << endl;
        am.getConnection()->send("TRANSFER ACCEPTED->CONNECTED");

        TS_ASSERT( stmConnection.CALLWAITER_nextString.wait() );
        TS_ASSERT( stmConnection.correctCalled() );
        TS_ASSERT( !stmAcceptedConnection.CALLWAITER_nextString.wasCalled() );
        stmAcceptedConnection.CALLWAITER_nextString.reset();
    }

    static void errorTest() {
        bool failed = true;
        try {
            mocks::TCPAcceptorListenerMock acceptorListenerMock1;

            unique_ptr<odcore::io::tcp::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&acceptorListenerMock1);
            acceptor->start();

            // 1. Case: Remove accepted part of connection.
            unique_ptr<odcore::io::tcp::TCPConnection> connection1(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection1->start();

            TS_ASSERT(acceptorListenerMock1.CALLWAITER_onNewConnection.wait());
            acceptorListenerMock1.getConnection()->start();

            mocks::ConnectionListenerMock connectionListenerMock1;
            connection1->setConnectionListener(&connectionListenerMock1);
            std::shared_ptr<odcore::io::tcp::TCPConnection> conn = acceptorListenerMock1.getConnection();
            conn.reset();
            acceptorListenerMock1.dontDeleteConnection();

            TS_ASSERT(connectionListenerMock1.CALLWAITER_handleConnectionError.wait());

            // 2. Case: Remove connecting part of connection.
            mocks::TCPAcceptorListenerMock acceptorListenerMock2;
            acceptor->setAcceptorListener(&acceptorListenerMock2);
            odcore::io::tcp::TCPConnection* connection2(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection2->start();

            TS_ASSERT(acceptorListenerMock2.CALLWAITER_onNewConnection.wait());
            acceptorListenerMock2.getConnection()->start();

            mocks::ConnectionListenerMock connectionListenerMock2;
            acceptorListenerMock2.getConnection()->setConnectionListener(&connectionListenerMock2);
            delete connection2;

            TS_ASSERT(connectionListenerMock2.CALLWAITER_handleConnectionError.wait());
            failed = false;
        } catch (string &s) {
            TS_WARN(s);
            failed = true;
        } catch (...) {
            TS_WARN("Undefined error.");
            failed = true;
        }
        TS_ASSERT(!failed);
    }
};

class TCPConnectionTestSuite  : public CxxTest::TestSuite
{
    public:
        void testTransfer()
        {
            #ifdef WIN32
                clog << endl << "TCPConnectionTestSuite::testTransfer using NetworkLibraryWin32" << endl;
                TCPConnectionTests
                <
                     odcore::wrapper::TCPFactoryWorker<odcore::wrapper::NetworkLibraryWin32>
                >::transferTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPConnectionTestSuite::testTransfer using NetworkLibraryPosix" << endl;
                TCPConnectionTests
                <
                     odcore::wrapper::TCPFactoryWorker<odcore::wrapper::NetworkLibraryPosix>
                >::transferTest();
            #endif
        }

        void testError()
        {
            #ifdef WIN32
                clog << endl << "TCPConnectionTestSuite::testError using NetworkLibraryWin32" << endl;
                TCPConnectionTests
                <
                     odcore::wrapper::TCPFactoryWorker<odcore::wrapper::NetworkLibraryWin32>
                >::errorTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPConnectionTestSuite::testError using NetworkLibraryPosix" << endl;
                TCPConnectionTests
                <
                     odcore::wrapper::TCPFactoryWorker<odcore::wrapper::NetworkLibraryPosix>
                >::errorTest();
            #endif
        }
};

#endif /*CORE_WRAPPER_TCPCONNECTIONTESTSUITE_H_*/
