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

#ifndef CONTEXT_CONTROLFLOWTESTSUITE_H_
#define CONTEXT_CONTROLFLOWTESTSUITE_H_

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <memory>
#include <string>                       // for string, char_traits
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcontext/base/BlockableContainerReceiver.h"
#include "opendavinci/odcontext/base/ControlledContainerConferenceFactory.h"
#include "opendavinci/odcontext/base/ControlledContainerConferenceForSystemUnderTest.h"
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/FIFOQueue.h"        // for FIFOQueue
#include "opendavinci/odcore/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/odcore/base/Lock.h"             // for Lock
#include "opendavinci/odcore/base/Mutex.h"            // for Mutex
#include "opendavinci/odcore/serialization/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/serialization/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Service.h"          // for Service
#include "opendavinci/odcore/base/Thread.h"           // for Thread
#include "opendavinci/odcore/base/module/Breakpoint.h"  // for Breakpoint
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/odcore/data/TimeStamp.h"        // for TimeStamp
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"  // for Server
#include "opendavinci/odcore/dmcp/discoverer/Server.h"  // for Server
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/generated/odcore/data/dmcp/Constants.h"  // for Constants, etc
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcontext { namespace base { class BlockableContainerReceiver; } }
namespace odcore { namespace data { namespace dmcp { class ModuleDescriptor; } } }
namespace odcore { namespace dmcp { namespace connection { class ModuleConnection; } } }

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcore::dmcp;
using namespace odcore::io;
using namespace odcore::io::conference;
using namespace odcontext::base;
using namespace odcore::serialization;

using namespace odcore::data::dmcp;

////////////////////////////////////////////////////////////////////////////////
//
// Breakpoint for interrupting the inner thread of the application.
//
////////////////////////////////////////////////////////////////////////////////

class ControlFlowTestBreakpoint : public odcore::base::module::Breakpoint {
    public:
        ControlFlowTestBreakpoint() :
            m_reachedMutex(),
            m_reached(false),
            m_continueMutex(),
            m_continue(false) {}

        virtual void reached() {
            // Indicate the outer thread that the inner thread has reached its breakpoint.
            {
                Lock l1(m_reachedMutex);
                m_reached = true;
            }

            while (!hasContinue()) {
                Thread::usleepFor(1000);
            }

            {
                Lock l3(m_continueMutex);
                m_continue = false;
            }
        }

        bool hasReached() {
            bool retVal = false;
            {
                Lock l(m_reachedMutex);
                retVal = m_reached;
            }
            return retVal;
        }

        bool hasContinue() {
            bool retVal = false;
            {
                Lock l1(m_continueMutex);
                retVal = m_continue;
            }
            return retVal;
        }

        void continueExecution() {
            {
                Lock l1(m_continueMutex);
                m_continue = true;
            }
            {
                Lock l2(m_reachedMutex);
                m_reached = false;
            }
        }

    private:
        Mutex m_reachedMutex;
        bool m_reached;

        Mutex m_continueMutex;
        bool m_continue;
};

////////////////////////////////////////////////////////////////////////////////
//
// ControlFlow Test Application.
//
////////////////////////////////////////////////////////////////////////////////

class ControlFlowTestSampleData : public odcore::data::SerializableData {
    public:
        ControlFlowTestSampleData() :
                m_int(0) {}

        uint32_t m_int;

        const string toString() const {
            stringstream sstr;
            sstr << m_int;
            return sstr.str();
        }

        int32_t getID() const {
            return 0;
        }

        const string getLongName() const {
            return "ControlFlowTestSampleData";
        }

        const string getShortName() const {
            return getLongName();
        }

        ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Serializer> s = sf.getSerializer(out);

            s->write(1, m_int);

            return out;
        }

        istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();

            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

            d->read(1, m_int);

            return in;
        }
};

class ControlFlowTestApp : public TimeTriggeredConferenceClientModule {
    public:
        ControlFlowTestApp(const int32_t &argc, char **argv, const string &name) :
            TimeTriggeredConferenceClientModule(argc, argv, name),
            m_counter(0) {}

        void setUp() {}

        void tearDown() {}

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            FIFOQueue myFIFO;
            addDataStoreFor(myFIFO);
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                const uint32_t SIZE = myFIFO.getSize();
                for(uint32_t i = 0; i < SIZE; i++) {
                    Container c = myFIFO.leave();
                    if (c.getDataType() == TimeStamp::ID()) {
                        TimeStamp ts = c.getData<TimeStamp>();
                        clog << "ControlFlowTestApp received '" << ts.toString() << "'" << endl;

                        // Compute some data.
                        m_counter++;

                        // Send some data.
                        ControlFlowTestSampleData cftsd;
                        cftsd.m_int = m_counter;
                        Container c2(cftsd, Container::UNDEFINEDDATA);
                        getConference().send(c2);
                    }
                }

            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    private:
        uint32_t m_counter;
};

class ControlFlowTestService : public Service {
    public:
        ControlFlowTestService(const int32_t &argc, char **argv, const string &name, odcore::base::module::Breakpoint *bp) :
            myApp(argc, argv, name) {
            myApp.setBreakpoint(bp);
        }

        virtual void beforeStop() {
            // Stop app.
            myApp.setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myApp.runModule();
        }

        BlockableContainerReceiver& getBlockableContainerReceiver() {
            return dynamic_cast<ControlledContainerConferenceForSystemUnderTest&>(myApp.getConference()).getBlockableContainerReceiver();
        }

    private:
        ControlFlowTestApp myApp;
};

class ControlFlowTestContainerReceiverFromSystemUnderTest : public odcore::io::conference::ContainerListener {
    public:
        ControlFlowTestContainerReceiverFromSystemUnderTest() :
            queueContainingContainersSentToConferenceBySystemUnderTest() {}

        virtual void nextContainer(odcore::data::Container &c) {
            queueContainingContainersSentToConferenceBySystemUnderTest.add(c);
        }

        FIFOQueue& getFIFO() {
            return queueContainingContainersSentToConferenceBySystemUnderTest;
        }

    private:
        FIFOQueue queueContainingContainersSentToConferenceBySystemUnderTest;
};

////////////////////////////////////////////////////////////////////////////////

class ControlFlowTest : public CxxTest::TestSuite,
                        public connection::ConnectionHandler,
                        public ModuleConfigurationProvider{
    public:
        ControlFlowTest() :
            m_configuration(),
            m_connection() {}

        KeyValueConfiguration m_configuration;
        std::shared_ptr<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(std::shared_ptr<odcore::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testControlledContainerFactoryTestSuite() {
            // Destroy any existing ContainerConferenceFactory.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);

            // Create controlled ContainerConferenceFactory.
            ControlledContainerConferenceFactory *controlledCF = new ControlledContainerConferenceFactory();
            ContainerConferenceFactory &controlledccf = ContainerConferenceFactory::getInstance();
            ccf2 = &controlledccf;
            TS_ASSERT(ccf2 == controlledCF);

            // Get ControlledContainerConference.
            std::shared_ptr<ContainerConference> cf = controlledccf.getContainerConference("testControlledContainerFactoryTestSuite");
            ControlledContainerConferenceForSystemUnderTest *controlledConferenceForSystemUnderTest = NULL;
            TS_ASSERT(cf.get());
            bool castIntoCCFSuccessful = false;
            try {
                controlledConferenceForSystemUnderTest = dynamic_cast<ControlledContainerConferenceForSystemUnderTest*>(cf.operator->());
                if (controlledConferenceForSystemUnderTest != NULL) {
                    castIntoCCFSuccessful = true;
                }
            }
            catch(...) {}
            TS_ASSERT(castIntoCCFSuccessful);
            TS_ASSERT(controlledConferenceForSystemUnderTest != NULL);

            // Register a ContainerListener at ControlledContainerConferenceFactory to get Containers sent by System Under Test.
            ControlFlowTestContainerReceiverFromSystemUnderTest cftcrfcut;
            controlledCF->add(&cftcrfcut);

            // Create application to test.
            // Setup DMCP.
            stringstream sstr;
            sstr << "ControlFlowTestApp.key = value" << endl;
            m_configuration = KeyValueConfiguration();
            m_configuration.readFrom(sstr);

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000, ServerInformation::ML_NONE);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.100",
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            // Setup recorder.
            string argv0("ControlFlowTestApp");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());

            ControlFlowTestBreakpoint controlflowBreakpoint;
            ControlFlowTestService cfts(argc, argv, argv0, &controlflowBreakpoint);
            cfts.start();

            for(uint32_t i = 0; i < 5; i++) {
                while (!controlflowBreakpoint.hasReached()) {
                    Thread::usleepFor(1000);
                }
                cfts.getBlockableContainerReceiver().setNextContainerAllowed(false);

                clog << "Do some computation." << endl;

                // Send to application.
                TimeStamp tsSendFromSimulatorToContainerConference(i, i+1);
                Container c = Container(tsSendFromSimulatorToContainerConference);
                controlledCF->sendToSystemsUnderTest(c);

                cfts.getBlockableContainerReceiver().setNextContainerAllowed(true);
                controlflowBreakpoint.continueExecution();
            }

            {
                cfts.getBlockableContainerReceiver().setNextContainerAllowed(true);
                // Break last waiting.
                controlflowBreakpoint.continueExecution();
                cfts.getBlockableContainerReceiver().setNextContainerAllowed(false);
            }

            cfts.stop();

            Thread::usleepFor(10 * 1000);

            // Check received data from application.
            FIFOQueue &queueContainingContainersSentToConference = cftcrfcut.getFIFO();
            clog << "Received: " << queueContainingContainersSentToConference.getSize() << " container." << endl;
            TS_ASSERT(queueContainingContainersSentToConference.getSize() > 3);

            uint32_t undefDataCnt = 0;
            for(uint32_t i = 0; i < queueContainingContainersSentToConference.getSize(); i++) {
                Container c = queueContainingContainersSentToConference.leave();
                if (c.getDataType() == Container::UNDEFINEDDATA) {
                    undefDataCnt++;
                    ControlFlowTestSampleData data = c.getData<ControlFlowTestSampleData>();
                    TS_ASSERT(data.m_int == undefDataCnt);
                }
            }
        }
};

#endif /*CONTEXT_CONTROLFLOWTESTSUITE_H_*/
