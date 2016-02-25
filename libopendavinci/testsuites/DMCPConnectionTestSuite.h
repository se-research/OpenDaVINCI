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

#ifndef CORE_DMCPCONNECTIONTESTSUITE_H_
#define CORE_DMCPCONNECTIONTESTSUITE_H_

#include <sstream>                      // for basic_ostream, operator<<, etc
#include <string>                       // for string, operator==, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/SharedPointer.h"         // for SharedPointer
#include "opendavinci/odcore/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/odcore/dmcp/connection/Client.h"  // for Client
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"  // for Server
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"
#include "opendavinci/generated/odcore/data/dmcp/TestConstants.h"  // for TestConstants, etc
#include "mocks/ConnectionHandlerMock.h"
#include "mocks/ModuleConfigurationProviderMock.h"

namespace odcore { namespace dmcp { namespace connection { class ModuleConnection; } } }

using namespace std;

using namespace odcore::base;
using namespace odcore::exceptions;
using namespace odcore::dmcp;
using namespace odcore::data;
using namespace odcore::data::dmcp;

class DMCPConnectionTestsuite : public CxxTest::TestSuite,
                                public connection::ConnectionHandler
{
    private:
        DMCPConnectionTestsuite(const DMCPConnectionTestsuite& /*obj*/);
        DMCPConnectionTestsuite& operator=(const DMCPConnectionTestsuite& /*obj*/);

    public:
        DMCPConnectionTestsuite() :
            connection(NULL) {}

        odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> connection;

        void testClientAndServer()
        {
            clog << endl << "DMCPConnectionTestsuite::testClientAndServer" << endl;
            stringstream sstr;
            sstr << "global.exampleKey = exampleValue" << endl;
            sstr << "NAME.key=Test" << endl;

            KeyValueConfiguration kv;
            kv.readFrom(sstr);

            mocks::ModuleConfigurationProviderMock configProvider;
            mocks::ConnectionHandlerMock connectionHandler;

            ServerInformation serverInfo("127.0.0.1", odcore::data::dmcp::TestConstants::DMCPCONFIG_TEST_SERVERPORT, ServerInformation::ML_NONE);
            ModuleDescriptor descriptor("DMCPConnectionTestSuite", "NONE", "TestVersion", 1);

            configProvider.addConfig(descriptor, kv);

            connection::Server server(serverInfo, configProvider);
            server.setConnectionHandler(&connectionHandler);

            connection::Client client(descriptor, serverInfo);
            TS_ASSERT(connectionHandler.WAITER.wait());
            TS_ASSERT(connectionHandler.WAITER.wasCalled());

            client.initialize();

            TS_ASSERT(client.getConfiguration().getValue<string>("NAME.Key") == "Test");
            TS_ASSERT(client.getConfiguration().getValue<string>("global.exampleKey") == "exampleValue");
        }

        virtual void onNewModule(odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> mc)
        {
            connection = mc;
        }
};

#endif

