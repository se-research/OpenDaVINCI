/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#ifndef OPENDAVINCI_CONTAINERSENDERSTAMPTESTSUITE_H_
#define OPENDAVINCI_CONTAINERSENDERSTAMPTESTSUITE_H_

#include <fstream>                      // for operator<<, basic_ostream, etc
#include <memory>
#include <string>                       // for string, char_traits
#include <vector>                       // for vector

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Condition.h"        // for Condition
#include "opendavinci/odcore/serialization/Deserializer.h"     // for Deserializer
#include "opendavinci/odcore/base/KeyValueConfiguration.h"  // for KeyValueConfiguration
#include "opendavinci/odcore/base/Lock.h"             // for Lock
#include "opendavinci/odcore/base/Mutex.h"             // for Lock
#include "opendavinci/odcore/serialization/SerializationFactory.h"  // for SerializationFactory
#include "opendavinci/odcore/serialization/Serializer.h"       // for Serializer
#include "opendavinci/odcore/base/Service.h"          // for Service
#include "opendavinci/odcore/base/Thread.h"           // for Thread
#include "opendavinci/odcore/base/module/AbstractConferenceClientModule.h"
#include "opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"        // for Container, etc
#include "opendavinci/odcore/data/SerializableData.h"  // for SerializableData
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"  // for Server
#include "opendavinci/odcore/dmcp/discoverer/Server.h"  // for Server
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/generated/odcore/data/dmcp/Constants.h"  // for Constants, etc
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcore { namespace data { namespace dmcp { class ModuleDescriptor; } } }

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcore::io;
using namespace odcore::io::conference;
using namespace odcore::dmcp;
using namespace odcore::data::dmcp;
using namespace odcore::serialization;

class TestSuiteExample7Data : public odcore::data::SerializableData {
    public:
        TestSuiteExample7Data() : m_numericalValue(0) {}

        virtual ~TestSuiteExample7Data() {}

        TestSuiteExample7Data(const TestSuiteExample7Data &obj) :
            SerializableData(),
            m_numericalValue(obj.m_numericalValue) {}

        TestSuiteExample7Data& operator=(const TestSuiteExample7Data &obj) {
            m_numericalValue = obj.m_numericalValue;
            return (*this);
        }

        uint32_t getNumericalValue() const {
            return m_numericalValue;
        }

        void setNumericalValue(const uint32_t &nv) {
            m_numericalValue = nv;
        }

        virtual ostream& operator<<(ostream &out) const {
            SerializationFactory& sf=SerializationFactory::getInstance();
            std::shared_ptr<Serializer> s = sf.getSerializer(out);
            s->write(1, m_numericalValue);
            return out;
        }

        virtual istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();
            std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
            d->read(1, m_numericalValue);
            return in;
        }

        virtual const string toString() const {
            stringstream s;
            s << m_numericalValue;
            return s.str();
        }

        int32_t getID() const {
            return 2345;
        }

        const string getLongName() const {
            return "TestSuiteExample7Data";
        }

        const string getShortName() const {
            return getLongName();
        }

    private:
        uint32_t m_numericalValue;
};

class TimeTriggeredConferenceClientModuleTestModule : public TimeTriggeredConferenceClientModule {
    public:
        TimeTriggeredConferenceClientModuleTestModule(int argc, char** argv, Condition& condition, int cntr) :
                TimeTriggeredConferenceClientModule(argc, argv, "TimeTriggeredConferenceClientModuleTestModule"),
                counter(cntr),
                correctOrder(true),
                setUpCalled(false),
                tearDownCalled(false),
                bodyCalled(false),
                m_condition(condition) {}

        int counter;
        bool correctOrder;
        bool setUpCalled;
        bool tearDownCalled;
        bool bodyCalled;
        Condition& m_condition;

        virtual void setUp() {
            setUpCalled = true;
            correctOrder &= (setUpCalled && !bodyCalled && !tearDownCalled);
        }

        virtual odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            bodyCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && !tearDownCalled);

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                if (counter-- < 0) {
                    break;
                }

                // Create user data.
                TestSuiteExample7Data data;
                data.setNumericalValue(counter);

                // Create container with user data type ID 5.
                Container c(data);

                // Send container.
                getConference().send(c);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

        virtual void tearDown() {
            tearDownCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && tearDownCalled);
            Lock l(m_condition);
            m_condition.wakeAll();
        }
};


class DataTriggeredConferenceClientModuleTestModule : public DataTriggeredConferenceClientModule {
    public:
        DataTriggeredConferenceClientModuleTestModule(int argc, char** argv, Condition& condition, const int &stopCounter, const uint32_t &expectedSenderStamp) :
                DataTriggeredConferenceClientModule(argc, argv, "DataTriggeredConferenceClientModuleTestModule"),
                m_condition(condition),
                m_stopCounter(stopCounter),
                counter(0),
                m_expectedSenderStamp(expectedSenderStamp),
                correctOrder(true),
                setUpCalled(false),
                tearDownCalled(false),
                nextContainerCalled(false),
                correctSenderStamp(true) {}

        Condition &m_condition;
        int m_stopCounter;
        int counter;
        uint32_t m_expectedSenderStamp;
        bool correctOrder;
        bool setUpCalled;
        bool tearDownCalled;
        bool nextContainerCalled;
        bool correctSenderStamp;

        virtual void setUp() {
            setUpCalled = true;
            correctOrder &= (setUpCalled && !nextContainerCalled && !tearDownCalled);
        }

        virtual void nextContainer(Container &c) {
            correctSenderStamp &= c.getSenderStamp() == m_expectedSenderStamp;

            TestSuiteExample7Data t;
            if (c.getDataType() == t.getID()) {
                nextContainerCalled = true;
                correctOrder &= nextContainerCalled;
                counter++;
            }

            if (counter == m_stopCounter) {
                Lock l(m_condition);
                m_condition.wakeAll();
            }
        }

        virtual void tearDown() {
            tearDownCalled = true;
            correctOrder &= tearDownCalled;
        }
};


class ConferenceClientModuleTestService : public Service {
    public:
        ConferenceClientModuleTestService(AbstractConferenceClientModule &accm) :
                myACCM(accm) {}

        virtual void beforeStop() {
            myACCM.setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myACCM.runModule();
        }

        AbstractConferenceClientModule &myACCM;
};

class ContainerSenderStampTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        ContainerSenderStampTest() :
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

        void testDataTriggeredTimeTriggeredConferenceClientModules() {
            // Setup ContainerConference.
            std::shared_ptr<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.109");

#if !defined(__OpenBSD__) && !defined(__APPLE__)
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
                                                    "225.0.0.109",
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            Thread::usleepFor(1000 * 1);

            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=109");
            string argv3("--freq=1");
            int argc = 4;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            int counter = 5;
            Condition module1;
            TimeTriggeredConferenceClientModuleTestModule ttccmtm(argc, argv, module1, counter);


            string argv0_2("DataTriggeredConferenceClientModuleTestModule");
            string argv1_2("--id=ABC");
            string argv2_2("--cid=109");
            string argv3_2("--freq=1");
            int argc_2 = 4;
            char **argv_2;
            argv_2 = new char*[argc_2];
            argv_2[0] = const_cast<char*>(argv0_2.c_str());
            argv_2[1] = const_cast<char*>(argv1_2.c_str());
            argv_2[2] = const_cast<char*>(argv2_2.c_str());
            argv_2[3] = const_cast<char*>(argv3_2.c_str());

            Condition dataTriggeredCondition;
            int stopCounter = 3;
            uint32_t expectedSenderStamp = 0;

            DataTriggeredConferenceClientModuleTestModule dtccmtm(argc_2, argv_2, dataTriggeredCondition, stopCounter, expectedSenderStamp);

            ConferenceClientModuleTestService ccmts_d(dtccmtm);
            ccmts_d.start();

            Thread::usleepFor(1000 * 3);

            ConferenceClientModuleTestService ccmts(ttccmtm);
            ccmts.start();

            Lock l(dataTriggeredCondition);
            dataTriggeredCondition.waitOnSignal();

            ccmts_d.stop();
            ccmts.stop();

            Thread::usleepFor(1000 * 3);

            TS_ASSERT(ttccmtm.correctOrder);
            TS_ASSERT(ttccmtm.setUpCalled);
            TS_ASSERT(ttccmtm.bodyCalled);
            TS_ASSERT(ttccmtm.tearDownCalled);

            TS_ASSERT(dtccmtm.correctOrder);
            TS_ASSERT(dtccmtm.setUpCalled);
            TS_ASSERT(dtccmtm.nextContainerCalled);
            TS_ASSERT(dtccmtm.counter > 2);
#ifndef _WIN32
            TS_ASSERT(dtccmtm.counter < 5);
            TS_ASSERT(dtccmtm.correctSenderStamp);
#endif
            TS_ASSERT(dtccmtm.tearDownCalled);
            TS_ASSERT(dtccmtm.correctOrder);
#endif

            // Ugly cleanup.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);

            Thread::usleepFor(1000 * 1);
        }

        void testDataTriggeredTimeTriggeredConferenceClientModulesIdentifier() {
            // Setup ContainerConference.
            std::shared_ptr<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.110");

#if !defined(__OpenBSD__) && !defined(__APPLE__)
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
                                                    "225.0.0.110",
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    odcore::data::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            Thread::usleepFor(1000 * 1);

            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=345");
            string argv2("--cid=110");
            string argv3("--freq=1");
            int argc = 4;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            int counter = 5;
            Condition module1;
            TimeTriggeredConferenceClientModuleTestModule ttccmtm(argc, argv, module1, counter);


            string argv0_2("DataTriggeredConferenceClientModuleTestModule");
            string argv1_2("--id=0");
            string argv2_2("--cid=110");
            string argv3_2("--freq=1");
            int argc_2 = 4;
            char **argv_2;
            argv_2 = new char*[argc_2];
            argv_2[0] = const_cast<char*>(argv0_2.c_str());
            argv_2[1] = const_cast<char*>(argv1_2.c_str());
            argv_2[2] = const_cast<char*>(argv2_2.c_str());
            argv_2[3] = const_cast<char*>(argv3_2.c_str());

            Condition dataTriggeredCondition;
            int stopCounter = 3;
            uint32_t expectedSenderStamp = 345;

            DataTriggeredConferenceClientModuleTestModule dtccmtm(argc_2, argv_2, dataTriggeredCondition, stopCounter, expectedSenderStamp);

            ConferenceClientModuleTestService ccmts_d(dtccmtm);
            ccmts_d.start();

            Thread::usleepFor(1000 * 3);

            ConferenceClientModuleTestService ccmts(ttccmtm);
            ccmts.start();

            Lock l(dataTriggeredCondition);
            dataTriggeredCondition.waitOnSignal();

            ccmts_d.stop();
            ccmts.stop();

            Thread::usleepFor(1000 * 3);

            TS_ASSERT(ttccmtm.correctOrder);
            TS_ASSERT(ttccmtm.setUpCalled);
            TS_ASSERT(ttccmtm.bodyCalled);
            TS_ASSERT(ttccmtm.tearDownCalled);

            TS_ASSERT(dtccmtm.correctOrder);
            TS_ASSERT(dtccmtm.setUpCalled);
            TS_ASSERT(dtccmtm.nextContainerCalled);
            TS_ASSERT(dtccmtm.counter > 2);
#ifndef _WIN32
            TS_ASSERT(dtccmtm.counter < 5);
            TS_ASSERT(dtccmtm.correctSenderStamp);
#endif
            TS_ASSERT(dtccmtm.tearDownCalled);
            TS_ASSERT(dtccmtm.correctOrder);
#endif

            // Ugly cleanup.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);

            Thread::usleepFor(1000 * 1);
        }

};

#endif /*OPENDAVINCI_CONTAINERSENDERSTAMPTESTSUITE_H_*/
