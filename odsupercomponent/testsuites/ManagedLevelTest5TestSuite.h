/**
 * odsupercomponent - Configuration and monitoring component for
 *                    distributed software systems
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef MANAGEDLEVELTESTSUITE_H_
#define MANAGEDLEVELTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#ifndef WIN32
    #include <sys/wait.h>
#endif

#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "GeneratedHeaders_CoreData.h"
#include "core/base/Mutex.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"
#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"

#include "core/data/TimeStamp.h"

#include "../include/SuperComponent.h"

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace core::exceptions;

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

        static int32_t ID() {
            return 33;
        }

        virtual int32_t getID() const {
            return 33;
        }

        virtual const string getShortName() const {
            return "TestSuiteExample7Data";
        }

        virtual const string getLongName() const {
            return getShortName();
        }

		virtual const string toString() const {
		    stringstream s;
		    s << m_numericalValue;
		    return s.str();
	    }

	private:
		uint32_t m_numericalValue;
};

class Example7SenderApp : public TimeTriggeredConferenceClientModule {
    public:
        bool tearDownCalled;
        bool m_withRandomSleep;

    public:
        Example7SenderApp(const int32_t &argc, char **argv, bool withRandomSleep) :
            TimeTriggeredConferenceClientModule(argc, argv, "example7sender"),
            tearDownCalled(false),
            m_withRandomSleep(withRandomSleep) {}

        void setUp() {}

        void tearDown() {
            tearDownCalled = true;
        }

        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            uint32_t seed = 24;
        	uint32_t counter = 0;

            srand(seed);

        	while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
        		// Create user data.
        		TestSuiteExample7Data data;
        		data.setNumericalValue(counter++);

        		// Create container.
        		Container c(data);

        		// Send container.
        		getConference().send(c);

        		// Restrict counter.
        		if (counter > 10000) counter = 0;

                if (m_withRandomSleep) {
                    // Provoke unexpected delays to demonstrate the need for --pulse in supercomponent.
                    double r = ((rand() / (double)RAND_MAX)) * 1000 * 1000 * 1.1;
                    cerr << "Sleep for " << r << " ms." << endl;
                    Thread::usleepFor((long)r);
                }
            }

        	return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }
};

class Example7ReceiverApp : public TimeTriggeredConferenceClientModule {
    public:
        bool tearDownCalled;
        mutable Mutex m_diffMutex;
        uint32_t m_diff;

    public:
        Example7ReceiverApp(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "example7receiver"),
            tearDownCalled(false),
            m_diffMutex(),
            m_diff(0) {}

        void setUp() {}

        void tearDown() {
            tearDownCalled = true;
        }

        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            uint32_t sum = 0;
            uint32_t expected_sum = 0;
            uint32_t counter = 0;

        	while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
			    Container c = getKeyValueDataStore().get(TestSuiteExample7Data::ID());
			    TestSuiteExample7Data data = c.getData<TestSuiteExample7Data>();
                sum += data.getNumericalValue();
			    cout << "Latest container from data type " << (uint32_t)c.getDataType() << ", content: " << data.toString() << ", sum = " << sum << endl;

                if (sum > 0) {
                    counter++;
                    expected_sum += counter;
                    {
                        Lock l(m_diffMutex);
                        m_diff = (expected_sum - sum);
                        cout << "Diff: " << m_diff << endl;
                    }
                }
        	}

        	return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

        uint32_t getDiff() {
            Lock l(m_diffMutex);
            return m_diff;
        }
};


class ConnectedClientModuleApp : public TimeTriggeredConferenceClientModule {
    public:
        ConnectedClientModuleApp(const int32_t &argc, char **argv, const string &name) :
            TimeTriggeredConferenceClientModule(argc, argv, name),
            tearDownCalled(false) {}

        const KeyValueConfiguration getKVC() const {
            return getKeyValueConfiguration();
        }

        void setUp() {}

        void tearDown() {
            tearDownCalled = true;
        }

        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                // Do nothing.
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

        bool tearDownCalled;
};

class ConnectedClientModuleTestService : public Service {
    public:
        ConnectedClientModuleTestService(TimeTriggeredConferenceClientModule *app) :
            myApp(app),
            m_isRunModuleCompletedMutex(),
            m_isRunModuleCompleted(false) {}

        ConnectedClientModuleTestService(const ConnectedClientModuleTestService &/*obj*/);
        ConnectedClientModuleTestService& operator=(const ConnectedClientModuleTestService &/*obj*/);

        virtual void beforeStop() {
            // Stop app.
            myApp->setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myApp->runModule();

            Lock l(m_isRunModuleCompletedMutex);
            m_isRunModuleCompleted = true;
        }

        bool isRunModuleCompleted() const {
            bool retVal = false;
            {
                Lock l(m_isRunModuleCompletedMutex);
                retVal = m_isRunModuleCompleted;
            }
            return retVal;
        }

        const TimeStamp getStartOfCurrentCycle() const {
            return myApp->getStartOfCurrentCycle();
        }

    private:
        TimeTriggeredConferenceClientModule *myApp;
        mutable Mutex m_isRunModuleCompletedMutex;
        bool m_isRunModuleCompleted;
};

class SupercomponentService : public Service {
    public:
        SupercomponentService(const int32_t &argc, char **argv) :
            mySC(argc, argv) {}

        virtual void beforeStop() {
            // Stop app.
            mySC.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            mySC.runModule();
        }

        const TimeStamp getStartOfCurrentCycle() const {
            return mySC.getStartOfCurrentCycle();
        }

    private:
        odsupercomponent::SuperComponent mySC;
};

class ManagedLevelTest : public CxxTest::TestSuite {
    public:

        void testManagedLevelPulseTime() {
// This test suite does not run properly on Win32 and MacOS and on qemu-arm-static. Thus, skip it for the time being...
#if !defined(WIN32) && !defined(__APPLE__) && !defined(__arm__)

// The following test case design pattern (singleton of system service & fork/waitpid) is only available on Linux, OpenBSD, and FreeBSD.
#if defined(__linux__) || (__OpenBSD__) || (__FreeBSD__)
            const uint32_t ONE_SECOND = 1*1000*1000;

            // As the dependent modules replace the time factory, we need a separate process context for them by using the syscall fork.

            pid_t child;
            child = fork();

            if (child == 0) {
                // In child process.

                // Create a component.
                string c0_argv0("ClientModuleTestService");
                string c0_argv1("--cid=99");
                int32_t c0_argc = 2;
                char **c0_argv;
                c0_argv = new char*[c0_argc];
                c0_argv[0] = const_cast<char*>(c0_argv0.c_str());
                c0_argv[1] = const_cast<char*>(c0_argv1.c_str());

                ConnectedClientModuleApp app1(c0_argc, c0_argv, "ConnectedClientModuleTestService1");
                ConnectedClientModuleTestService ccms1(&app1);

                ccms1.start();
                uint32_t cycles = 0;
                const uint32_t MAX_CYCLES = 5;
                while (cycles < MAX_CYCLES) {
                    Thread::usleepFor(ONE_SECOND);
                    cycles++;
                }
                TS_ASSERT(app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 0 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 100000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 200000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 300000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 400000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 500000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 600000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 700000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 800000 ||
                          app1.getStartOfCurrentCycle().getFractionalMicroseconds() == 900000 );

                ccms1.stop();

                TS_ASSERT(ccms1.isRunModuleCompleted());
                TS_ASSERT(app1.tearDownCalled);

                uint32_t retVal = (!ccms1.isRunModuleCompleted() ? 1<<1 : 0) |
                                  (!app1.tearDownCalled ? 1<<2 : 0);

                // Leave child's process context.
                exit(retVal);
            }
            else if (child > 0) {
                // In parent process.

                // Create a configuration.
                stringstream configuration;
                configuration << "global.buffer.memorySegmentSize = 2800000 # Size of a memory segment for a shared data stream in bytes." << endl
                     << "global.buffer.numberOfMemorySegments = 20 # Number of memory segments used for buffering." << endl
                     << "odsupercomponent.pulseshift.shift = 10000 # (in microseconds) If the managed level is pulse_shift, all connected modules will be informed about the supercomponent's real time by this increment per module. Thus, the execution times per modules are better aligned with supercomponent and the data exchange is somewhat more predictable." << endl
                     << "odsupercomponent.pulsetimeack.timeout = 5000 # (in milliseconds) If the managed level is pulse_time_ack, this is the timeout for waiting for an ACK message from the dependent client." << endl
                     << "odsupercomponent.pulsetimeack.yield = 5000 # (in microseconds) If the managed level is pulse_time_ack, the modules are triggered sequentially by sending pulses and waiting for acknowledgment messages. To allow the modules to deliver their respective containers, this yielding time is used to sleep before supercomponent sends the pulse messages the next module in this execution cycle. This value needs to be adjusted for networked simulations to ensure deterministic execution. " << endl
                     << "odsupercomponent.pulsetimeack.exclude = cockpit,monitor # List of modules that will not get a pulse message from supercomponent." << endl;

                fstream fout("configuration", ios::out);
                TS_ASSERT(fout.good());
                fout << configuration.str();
                fout.close();

                // Start the encapsulated supercomponent.
                string sc_argv0("odsupercomponent");
                string sc_argv1("--cid=99");
                string sc_argv2("--freq=10");
                string sc_argv3("--managed=pulse_time");
                int32_t sc_argc = 4;
                char **sc_argv;
                sc_argv = new char*[sc_argc];
                sc_argv[0] = const_cast<char*>(sc_argv0.c_str());
                sc_argv[1] = const_cast<char*>(sc_argv1.c_str());
                sc_argv[2] = const_cast<char*>(sc_argv2.c_str());
                sc_argv[3] = const_cast<char*>(sc_argv3.c_str());

                SupercomponentService scs(sc_argc, sc_argv);
                scs.start();

                // Monitor the child's process and wait for its exit.
                int status = 0;
                do {
                    pid_t w = waitpid(child, &status, WUNTRACED | WCONTINUED);
                    TS_ASSERT(w > -1);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
                TS_ASSERT(WIFEXITED(status));
                if (WIFEXITED(status)) {
                    TS_ASSERT(WEXITSTATUS(status) == 0);
                }

                scs.stop();

                UNLINK("configuration");
            }
#endif /*defined(__linux__) || (__OpenBSD__) || (__FreeBSD__) || (__arm__)*/

#endif /*!defined(WIN32) && !defined(__APPLE__)*/
        }
};

#endif /*MANAGEDLEVELTESTSUITE_H_*/
