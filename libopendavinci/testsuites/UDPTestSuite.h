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

#ifndef CORE_WRAPPER_UDPTESTSUITE_H_
#define CORE_WRAPPER_UDPTESTSUITE_H_

#include <iostream>                     // for endl, operator<<, etc
#include <string>                       // for string

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "mocks/StringListenerMock.h"

namespace odcore { namespace io { namespace udp { class UDPReceiver; } } }
namespace odcore { namespace io { namespace udp { class UDPSender; } } }

using namespace std;

#ifndef WIN32
    #include "opendavinci/odcore/wrapper/POSIX/POSIXUDPFactoryWorker.h"
    #include "opendavinci/odcore/wrapper/POSIX/POSIXUDPReceiver.h"
    #include "opendavinci/odcore/wrapper/POSIX/POSIXUDPSender.h"

    struct UDPTestPOSIX
    {
        static void test(mocks::StringListenerMock &mock)
        {
            clog << endl << "UDPTestPOSIX" << endl;
            const string group = "225.0.0.13";
            const uint32_t port = 4567;

            std::shared_ptr<odcore::io::udp::UDPReceiver> receiver(
                    odcore::wrapper::UDPFactoryWorker<odcore::wrapper::NetworkLibraryPosix>::createUDPReceiver(group, port));

            std::shared_ptr<odcore::io::udp::UDPSender> sender(
                                odcore::wrapper::UDPFactoryWorker<odcore::wrapper::NetworkLibraryPosix>::createUDPSender(group, port));

            receiver->start();

            mock.VALUES_nextString.addItem("Hello UDPMulticast");
            mock.VALUES_nextString.prepare();
            receiver->setStringListener(&mock);

            mock.CALLWAITER_nextString.wait();

            sender->send("Hello UDPMulticast");

            mock.CALLWAITER_nextString.wait();

            receiver->setStringListener(NULL);
            receiver->stop();
        }
    };

#endif

#ifdef WIN32
    #include "opendavinci/odcore/wrapper/WIN32/WIN32UDPFactoryWorker.h"
    #include "opendavinci/odcore/wrapper/WIN32/WIN32UDPReceiver.h"
    #include "opendavinci/odcore/wrapper/WIN32/WIN32UDPSender.h"

    struct UDPTestWin32
    {
        static void test(mocks::StringListenerMock &mock)
        {
            clog << endl << "UDPTestWin32" << endl;
            const string group = "225.0.0.13";
            const uint32_t port = 4567;

            std::shared_ptr<odcore::io::udp::UDPReceiver> receiver(
                    odcore::wrapper::UDPFactoryWorker<odcore::wrapper::NetworkLibraryWin32>::createUDPReceiver(group, port));

            std::shared_ptr<odcore::io::udp::UDPSender> sender(
                                odcore::wrapper::UDPFactoryWorker<odcore::wrapper::NetworkLibraryWin32>::createUDPSender(group, port));

            receiver->start();

            mock.VALUES_nextString.addItem("Hello UDPMulticast");
            mock.VALUES_nextString.prepare();
            receiver->setStringListener(&mock);

            mock.CALLWAITER_nextString.wait();

            sender->send("Hello UDPMulticast");

            mock.CALLWAITER_nextString.wait();

            receiver->setStringListener(NULL);
            receiver->stop();
        }
    };
#endif


    class UDPTestsuite : public CxxTest::TestSuite
    {
        public:
            void testDataExchange()
            {
                mocks::StringListenerMock mock;

                #ifndef WIN32
                UDPTestPOSIX::test(mock);
                #endif

                #ifdef WIN32
                UDPTestWin32::test(mock);
                #endif

                TS_ASSERT( mock.CALLWAITER_nextString.wasCalled() );
                TS_ASSERT( mock.correctCalled() );
            }
    };


#endif /*CORE_WRAPPER_UDPTESTSUITE_H_*/
