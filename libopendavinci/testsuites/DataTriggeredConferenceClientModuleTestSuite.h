/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
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

#ifndef OPENDAVINCI_DATATRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_
#define OPENDAVINCI_DATATRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "core/base/Lock.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/io/conference/ContainerConference.h"
#include "core/io/conference/ContainerConferenceFactory.h"
#include "core/io/URL.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "core/base/module/AbstractConferenceClientModule.h"
#include "core/base/module/DataTriggeredConferenceClientModule.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/dmcp/ModuleConfigurationProvider.h"
#include "core/dmcp/discoverer/Server.h"
#include "core/dmcp/connection/Server.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"

#include "GeneratedHeaders_CoreData.h"

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace core::io;
using namespace core::io::conference;
using namespace core::dmcp;
using namespace coredata::dmcp;

class TestSuiteExample7Data : public core::data::SerializableData {
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
		    core::SharedPointer<Serializer> s = sf.getSerializer(out);
		    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('n', 'u', 'm') >::RESULT,
				    m_numericalValue);
		    return out;
	    }

		virtual istream& operator>>(istream &in) {
            SerializationFactory& sf=SerializationFactory::getInstance();
		    core::SharedPointer<Deserializer> d = sf.getDeserializer(in);
		    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('n', 'u', 'm') >::RESULT,
			       m_numericalValue);
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

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            bodyCalled = true;
            correctOrder &= (setUpCalled && bodyCalled && !tearDownCalled);

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
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

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
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
        DataTriggeredConferenceClientModuleTestModule(int argc, char** argv, Condition& condition, const int &stopCounter) :
                DataTriggeredConferenceClientModule(argc, argv, "DataTriggeredConferenceClientModuleTestModule"),
                m_condition(condition),
                m_stopCounter(stopCounter),
                counter(0),
                correctOrder(true),
                setUpCalled(false),
                tearDownCalled(false),
                nextContainerCalled(false) {}

        Condition &m_condition;
        int m_stopCounter;
        int counter;
        bool correctOrder;
        bool setUpCalled;
        bool tearDownCalled;
        bool nextContainerCalled;

        virtual void setUp() {
            setUpCalled = true;
            correctOrder &= (setUpCalled && !nextContainerCalled && !tearDownCalled);
        }

        virtual void nextContainer(Container &c) {
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
            myACCM.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myACCM.runModule();
        }

        AbstractConferenceClientModule &myACCM;
};

class DataTriggeredConferenceClientModuleTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        DataTriggeredConferenceClientModuleTest() :
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
                                                    "225.0.0.101",
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            Thread::usleepFor(1000 * 1);

            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=101");
            string argv3("--freq=1");
            int argc = 4;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            int counter = 2;
            Condition c;
            TimeTriggeredConferenceClientModuleTestModule ttccmtm(argc, argv, c, counter);

            ConferenceClientModuleTestService ccmts(ttccmtm);
            ccmts.start();

            Lock l(c);
            c.waitOnSignal();

            Thread::usleepFor(1000 * 1);

            ccmts.stop();

            TS_ASSERT(ttccmtm.correctOrder);
            TS_ASSERT(ttccmtm.setUpCalled);
            TS_ASSERT(ttccmtm.bodyCalled);
            TS_ASSERT(ttccmtm.tearDownCalled);
#endif

            // Ugly cleanup.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);

            Thread::usleepFor(1000 * 1);
        }

        void testDataTriggeredTimeTriggeredConferenceClientModules() {
            // Setup ContainerConference.
            core::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.102");

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
                                                    "225.0.0.102",
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            Thread::usleepFor(1000 * 1);

            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=102");
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
            string argv2_2("--cid=102");
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

            DataTriggeredConferenceClientModuleTestModule dtccmtm(argc_2, argv_2, dataTriggeredCondition, stopCounter);

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

        void testDataTriggeredTimeTriggeredConferenceClientModulesFreq10() {
            // Setup ContainerConference.
            core::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.103");

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
                                                    "225.0.0.103",
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            Thread::usleepFor(1000 * 1);

            string argv0("TimeTriggeredConferenceClientModuleTestModule");
            string argv1("--id=ABC");
            string argv2("--cid=103");
            string argv3("--freq=10");
            int argc = 4;
            char **argv;
            argv = new char*[argc];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());
            argv[3] = const_cast<char*>(argv3.c_str());

            int counter = 100;
            Condition module1;
            TimeTriggeredConferenceClientModuleTestModule ttccmtm(argc, argv, module1, counter);


            string argv0_2("DataTriggeredConferenceClientModuleTestModule");
            string argv1_2("--id=ABC");
            string argv2_2("--cid=103");
            string argv3_2("--freq=1");
            int argc_2 = 4;
            char **argv_2;
            argv_2 = new char*[argc_2];
            argv_2[0] = const_cast<char*>(argv0_2.c_str());
            argv_2[1] = const_cast<char*>(argv1_2.c_str());
            argv_2[2] = const_cast<char*>(argv2_2.c_str());
            argv_2[3] = const_cast<char*>(argv3_2.c_str());

            Condition dataTriggeredCondition;
            int stopCounter = 30;

            DataTriggeredConferenceClientModuleTestModule dtccmtm(argc_2, argv_2, dataTriggeredCondition, stopCounter);

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
            TS_ASSERT(dtccmtm.counter >= 20);
#ifndef _WIN32
            TS_ASSERT(dtccmtm.counter < 50);
#endif
            TS_ASSERT(dtccmtm.tearDownCalled);
#if !defined(__FreeBSD__)
            TS_ASSERT(dtccmtm.correctOrder);
#endif
#endif

            // Ugly cleanup.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);

            Thread::usleepFor(1000 * 1);
        }
};

#endif /*CORE_DATATRIGGEREDCONFERENCECLIENTMODULETESTSUITE_H_*/
