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

#ifndef CORE_WRAPPER_TCPACCEPTORTESTSUITE_H_
#define CORE_WRAPPER_TCPACCEPTORTESTSUITE_H_

#include <string>                       // for string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/SharedPointer.h"         // for SharedPointer
#include "core/wrapper/NetworkLibraryProducts.h"
#include "mocks/ConnectionListenerMock.h"
#include "mocks/StringListenerMock.h"
#include "mocks/TCPAcceptorListenerMock.h"

#ifndef WIN32
    #include "core/wrapper/POSIX/POSIXTCPFactoryWorker.h"
#endif
#ifdef WIN32
    #include "core/wrapper/WIN32/WIN32TCPFactoryWorker.h"
#endif

#include "core/io/tcp/TCPAcceptor.h"    // for TCPAcceptor
#include "core/io/tcp/TCPConnection.h"  // for TCPConnection

using namespace std;
using namespace core;
using namespace core::base;

template <typename worker> struct TCPAcceptorTests
{
        static void acceptTest()
        {
            mocks::TCPAcceptorListenerMock ah;

            SharedPointer<core::io::tcp::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&ah);
            acceptor->start();

            SharedPointer<core::io::tcp::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah.CALLWAITER_onNewConnection.wait());
        }

        static void multipleAcceptTest()
        {
            mocks::TCPAcceptorListenerMock ah1;
            mocks::TCPAcceptorListenerMock ah2;

            SharedPointer<core::io::tcp::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&ah1);
            acceptor->start();

            SharedPointer<core::io::tcp::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah1.CALLWAITER_onNewConnection.wait());

            acceptor->setAcceptorListener(&ah2);

            SharedPointer<core::io::tcp::TCPConnection> connection2(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(ah2.CALLWAITER_onNewConnection.wait());
        }

        static void noAcceptTest() {
            mocks::TCPAcceptorListenerMock am1;
            mocks::TCPAcceptorListenerMock am2;

            SharedPointer<core::io::tcp::TCPAcceptor> acceptor(worker::createTCPAcceptor(20000));
            acceptor->setAcceptorListener(&am1);
            acceptor->start();

            SharedPointer<core::io::tcp::TCPConnection> connection(worker::createTCPConnectionTo("127.0.0.1", 20000));
            connection->start();

            TS_ASSERT(am1.CALLWAITER_onNewConnection.wait());

            acceptor->setAcceptorListener(&am2);
            acceptor->stop();
            bool exceptionCaught = false;
            clog << "Test:" << endl;
            core::io::tcp::TCPConnection* connection2 = NULL;
            try {
                connection2 = worker::createTCPConnectionTo("127.0.0.1", 20000);
                connection2->start();
            } catch (string &/*s*/) {
                exceptionCaught = true;
                delete connection2;
            }

            TS_ASSERT(exceptionCaught);
            TS_ASSERT(!am2.CALLWAITER_onNewConnection.wasCalled());
        }

};

class TCPAcceptorTestsuite : public CxxTest::TestSuite
{
    public:
        void testAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::acceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::acceptTest();
            #endif
        }

        void testMultipleAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testMultipleAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::multipleAcceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testMultipleAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::multipleAcceptTest();
            #endif
        }

        void testNoAccept()
        {
            #ifdef WIN32
                clog << endl << "TCPAcceptorTestsuite::testNoAccept using NetworkLibraryWin32" << endl;
                TCPAcceptorTests
                <
                     core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryWin32>
                >::noAcceptTest();
            #endif

            #ifndef WIN32
                clog << endl << "TCPAcceptorTestsuite::testNoAccept using NetworkLibraryPosix" << endl;
                TCPAcceptorTests
                <
                    core::wrapper::TCPFactoryWorker<core::wrapper::NetworkLibraryPosix>
                >::noAcceptTest();
            #endif
        }
};

#endif /*CORE_WRAPPER_TCPACCEPTORTESTSUITE_H_*/
