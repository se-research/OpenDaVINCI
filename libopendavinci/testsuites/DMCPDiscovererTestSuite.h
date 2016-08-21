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

#ifndef CORE_DMCPDISCOVERERTESTSUITE_H_
#define CORE_DMCPDISCOVERERTESTSUITE_H_

#include <string>                       // for string
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/dmcp/discoverer/Client.h"  // for Client
#include "opendavinci/odcore/dmcp/discoverer/Server.h"  // for Server
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"
#include "opendavincitestdata/generated/odcore/testdata/dmcp/TestConstants.h"  // for TestConstants, etc
#include "mocks/FunctionCallWaiter.h"

using namespace std;

using namespace odcore::dmcp;
using namespace odcore::data;
using namespace odcore::data::dmcp;

class TestClient : public odcore::dmcp::discoverer::Client
{
    public:
        TestClient(const string& group, const uint32_t &serverPort, const uint32_t &clientPort, const string &name) :
            Client(group, serverPort, clientPort, name),
            WAITER()
        {}

        virtual void onResponse() {
            WAITER.called();
        }

    mocks::FunctionCallWaiter WAITER;
};

class TestServer : public odcore::dmcp::discoverer::Server
{
    public:
        TestServer(const ServerInformation& serverInformation,
                   const std::string& group, const uint32_t &serverPort, const uint32_t &clientPort, const vector<string> &modulesToIgnore) :
           Server(serverInformation, group, serverPort, clientPort, modulesToIgnore),
           WAITER()
        {};

        virtual void onRequest() {
            WAITER.called();
        }

        mocks::FunctionCallWaiter WAITER;
};

class DMCPDiscovererTestsuite : public CxxTest::TestSuite
{
    public:

        void testClientAndServer() {
            //DMCPConfig::TEST_GROUP
            clog << endl << "DMCPDiscovererTestsuite::testClient" << endl;
            
            vector<string> noModulesToIgnore;
            ServerInformation myServerInfo("0.0.0.0", 12345, ServerInformation::ML_NONE);
            TestServer server(myServerInfo, odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_GROUP, odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_SERVERPORT, odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_CLIENTPORT, noModulesToIgnore);

            TestClient client(odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_GROUP, odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_SERVERPORT, odcore::testdata::dmcp::TestConstants::DMCPCONFIG_TEST_CLIENTPORT, "myName");
            TS_ASSERT( !client.existsServer() );
            TS_ASSERT( !client.WAITER.wasCalled() );
            TS_ASSERT( !server.WAITER.wasCalled() );
            TS_ASSERT( client.getServerInformation().toString() == ServerInformation().toString() );

            server.startResponding();

            TS_ASSERT( client.existsServer() );
            TS_ASSERT( client.WAITER.wasCalled() );
            TS_ASSERT( server.WAITER.wasCalled() );
            TS_WARN(client.getServerInformation().toString());
            // The server sends a message containing 0.0.0.0 and the client uses recvfrom to get the sender's IP address. Thus, the following test fails.
            // TS_ASSERT( client.getServerInformation().toString() == myServerInfo.toString() );
        }
};


#endif /*CORE_SERVERDISCOVERERTESTSUITE_H_*/
