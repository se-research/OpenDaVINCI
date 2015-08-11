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

#include "cxxtest/TestSuite.h"

#include <sstream>
#include <string>
#include <memory>
#include <vector>

#include "core/dmcp/discoverer/Client.h"
#include "core/dmcp/discoverer/Server.h"

#include "mocks/FunctionCallWaiter.h"

#include "GeneratedHeaders_CoreData.h"

using namespace std;

using namespace core::dmcp;
using namespace core::data;
using namespace coredata::dmcp;

class TestClient : public core::dmcp::discoverer::Client
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

class TestServer : public core::dmcp::discoverer::Server
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
            TestServer server(myServerInfo, coredata::dmcp::TestConstants::DMCPCONFIG_TEST_GROUP, coredata::dmcp::TestConstants::DMCPCONFIG_TEST_SERVERPORT, coredata::dmcp::TestConstants::DMCPCONFIG_TEST_CLIENTPORT, noModulesToIgnore);

            TestClient client(coredata::dmcp::TestConstants::DMCPCONFIG_TEST_GROUP, coredata::dmcp::TestConstants::DMCPCONFIG_TEST_SERVERPORT, coredata::dmcp::TestConstants::DMCPCONFIG_TEST_CLIENTPORT, "myName");
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
