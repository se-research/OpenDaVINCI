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

#ifndef OPENDAVINCI_TIMETRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_
#define OPENDAVINCI_TIMETRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_

#include <fstream>                      // for operator<<, basic_ostream, etc
#include <string>                       // for string, operator==, etc
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/opendavinci.h"
#include "core/SharedPointer.h"         // for SharedPointer
#include "core/base/Condition.h"        // for Condition
#include "core/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "core/base/Lock.h"             // for Lock
#include "core/base/Service.h"          // for Service
#include "core/base/Thread.h"           // for Thread
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/dmcp/ModuleConfigurationProvider.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"
#include "core/dmcp/connection/Server.h"  // for Server
#include "core/dmcp/discoverer/Server.h"  // for Server
#include "core/io/conference/ContainerConference.h"
#include "core/io/conference/ContainerConferenceFactory.h"
#include "core/opendavinci.h"
#include "generated/coredata/dmcp/Constants.h"  // for Constants, etc
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"
#include "generated/coredata/dmcp/ModuleStateMessage.h"
#include "generated/coredata/dmcp/ServerInformation.h"

namespace coredata { namespace dmcp { class ModuleDescriptor; } }

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace core::io;
using namespace core::io::conference;
using namespace core::dmcp;
using namespace coredata::dmcp;


class TimeTriggeredConferenceClientModuleTestModule : public TimeTriggeredConferenceClientModule {
    public:
        TimeTriggeredConferenceClientModuleTestModule(int argc, char** argv, Condition& condition) :
            TimeTriggeredConferenceClientModule(argc, argv, "TimeTriggeredConferenceClientModuleTestModule"),
            correctOrder(true),
            setUpCalled(false),
            tearDownCalled(false),
            bodyCalled(false),
            configurationCorrect(true),
            m_condition(condition) {}

        bool correctOrder;
        bool setUpCalled;
        bool tearDownCalled;
        bool bodyCalled;
        bool configurationCorrect;
        Condition& m_condition;

        virtual void setUp() {
            string value1 = getKeyValueConfiguration().getValue<string>("global.config");
            configurationCorrect &= (value1 == "example");

            string value2 = getKeyValueConfiguration().getValue<string>("TimeTriggeredConferenceClientModuleTestModule.config1");
            configurationCorrect &= (value2 == "example1");

            string value3 = getKeyValueConfiguration().getValue<string>("TimeTriggeredConferenceClientModuleTestModule:ABC.config1");
            configurationCorrect &= (value3 == "example2");

            string value4NotReceived = "";
            try {
                value4NotReceived = getKeyValueConfiguration().getValue<string>("TimeTriggeredConferenceClientModuleTestModule:DEF.config1");
                configurationCorrect = false;
            } catch (...) {}

            string value5NotReceived = "";
            try {
                value5NotReceived = getKeyValueConfiguration().getValue<string>("TimeTriggeredConferenceClientModuleTestModule2.config2");
                configurationCorrect = false;
            } catch (...) {}

            setUpCalled = true;
            correctOrder &= (setUpCalled && !bodyCalled && !tearDownCalled);
        }

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            bodyCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && !tearDownCalled);
            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

        virtual void tearDown() {
            tearDownCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && tearDownCalled);
            Lock l(m_condition);
            m_condition.wakeAll();
        }
};


class TimeTriggeredConferenceClientModuleTestService : public Service {
    public:
        TimeTriggeredConferenceClientModuleTestService(const int32_t &argc, char **argv, Condition& condition) :
                myCCMTM(argc, argv, condition) {}

        virtual void beforeStop() {
            myCCMTM.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myCCMTM.runModule();
        }

        TimeTriggeredConferenceClientModuleTestModule myCCMTM;
};

class TimeTriggeredConferenceClientModuleTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        TimeTriggeredConferenceClientModuleTest() :
            m_configuration(),
            m_connection() {}

        KeyValueConfiguration m_configuration;
        core::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(core::SharedPointer<core::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testTimeTriggeredTimeTriggeredConferenceClientModule() {
            // Setup ContainerConference.
            core::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.101");

            // Setup DMCP.
            stringstream sstr;
            sstr << "global.config=example" << endl
            << "TimeTriggeredConferenceClientModuleTestModule.config1=example1" << endl
            << "TimeTriggeredConferenceClientModuleTestModule:ABC.config1=example2" << endl
            << "TimeTriggeredConferenceClientModuleTestModule:DEF.config1=example3" << endl
            << "TimeTriggeredConferenceClientModuleTestModule2.config2=example4" << endl;

            m_configuration = KeyValueConfiguration();
            m_configuration.readFrom(sstr);

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000, ServerInformation::ML_NONE);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.101",
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);



            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=101");
            int argc = 3;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            Condition c;
            TimeTriggeredConferenceClientModuleTestService ccmtms(argc, argv, c);
            TS_ASSERT(ccmtms.myCCMTM.getIdentifier() == "ABC");
            //TS_ASSERT( cmtm.runModule() == coredata::dmcp::ModuleExitCodeMessage::OKAY );

            //Lock l(c);
            //if ( cmtm.getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING ) {
            //    c.waitOnSignal();
            //}

            ccmtms.start();

            Thread::usleepFor(3*1000*1000);

            ccmtms.stop();

            TS_ASSERT(ccmtms.myCCMTM.correctOrder);
            TS_ASSERT(ccmtms.myCCMTM.setUpCalled);
            TS_ASSERT(ccmtms.myCCMTM.bodyCalled);
            TS_ASSERT(ccmtms.myCCMTM.tearDownCalled);


            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }
};

#endif /*CORE_TIMETRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_*/
