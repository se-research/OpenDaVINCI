/**
 * odsupercomponent - Configuration and monitoring component for
 *                    distributed software systems
 * Copyright (C) 2016 Christian Berger
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

#ifndef LOGGINGTESTSUITE_H_
#define LOGGINGTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "../include/SuperComponent.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcore::exceptions;

class ExampleApp : public TimeTriggeredConferenceClientModule {
    public:
        bool &m_tearDownCalled;
        uint32_t m_counter;

    public:
        ExampleApp(const int32_t &argc, char **argv, bool &tearDownCalled) :
            TimeTriggeredConferenceClientModule(argc, argv, "exampleapp"),
            m_tearDownCalled(tearDownCalled),
            m_counter(0) {}

        void setUp() {
            clog << getName() << "/" << getIdentifier() << " setUp called..." << endl;
        }

        void tearDown() {
            m_tearDownCalled = true;
            clog << getName() << "/" << getIdentifier() << " tearDown called..." << endl;
        }

        uint32_t getCounter() const {
            return m_counter;
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            clog << getName() << "/" << getIdentifier() << " before while-body..." << endl;
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                m_counter++;
            }
            clog << getName() << "/" << getIdentifier() << " after while-body..." << endl;

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
};

class ModuleRunnerTestService : public Service {
    public:
        ModuleRunnerTestService(TimeTriggeredConferenceClientModule *app) :
            myApp(app),
            m_isRunModuleCompletedMutex(),
            m_isRunModuleCompleted(false) {}

    private:
        ModuleRunnerTestService(const ModuleRunnerTestService &/*obj*/);
        ModuleRunnerTestService& operator=(const ModuleRunnerTestService &/*obj*/);

    public:
        virtual void beforeStop() {
            // Stop app.
            myApp->setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
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
            mySC.setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
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

class ShutdownTest : public CxxTest::TestSuite {
    public:

        void testClosingOneModule() {
            // Create a configuration.
            stringstream configuration;
            configuration << "global.buffer.memorySegmentSize = 2800000 # Size of a memory segment for a shared data stream in bytes." << endl
                 << "global.buffer.numberOfMemorySegments = 20 # Number of memory segments used for buffering." << endl
                 << "odsupercomponent.pulseshift.shift = 10000 # (in microseconds) If the managed level is pulse_shift, all connected modules will be informed about the supercomponent's real time by this increment per module. Thus, the execution times per modules are better aligned with supercomponent and the data exchange is somewhat more predictable." << endl
                 << "odsupercomponent.pulsetimeack.timeout = 5000 # (in milliseconds) If the managed level is pulse_time_ack, this is the timeout for waiting for an ACK message from the dependent client." << endl
                 << "odsupercomponent.pulsetimeack.yield = 5000 # (in microseconds) If the managed level is pulse_time_ack, the modules are triggered sequentially by sending pulses and waiting for acknowledgment messages. To allow the modules to deliver their respective containers, this yielding time is used to sleep before supercomponent sends the pulse messages the next module in this execution cycle. This value needs to be adjusted for networked simulations to ensure deterministic execution. " << endl
                 << "odsupercomponent.pulsetimeack.exclude = cockpit,monitor # List of modules that will not get a pulse message from supercomponent." << endl;
            // Create configuration file.
            fstream fout("configuration", ios::out);
            TS_ASSERT(fout.good());
            fout << configuration.str();
            fout.close();

            // Start the encapsulated supercomponent.
            string sc_argv0("odsupercomponent");
            string sc_argv1("--cid=73");
            int32_t sc_argc = 2;
            char **sc_argv;
            sc_argv = new char*[sc_argc];
            sc_argv[0] = const_cast<char*>(sc_argv0.c_str());
            sc_argv[1] = const_cast<char*>(sc_argv1.c_str());

            SupercomponentService scs(sc_argc, sc_argv);

            clog << "Starting odsupercomponent..." << endl;
            scs.start();

            const uint32_t ONE_SECOND = 1*1000*1000;
            Thread::usleepFor(ONE_SECOND * 0.5);

            clog << "odsupercomponent started." << endl;

            string c0_argv0("ClientModuleTestService");
            string c0_argv1("--cid=73");
            int32_t c0_argc = 2;
            char **c0_argv;
            c0_argv = new char*[c0_argc];
            c0_argv[0] = const_cast<char*>(c0_argv0.c_str());
            c0_argv[1] = const_cast<char*>(c0_argv1.c_str());

            bool app1TearDownCalled = false;
            ExampleApp app1(c0_argc, c0_argv, app1TearDownCalled);
            ModuleRunnerTestService mrts1(&app1);

            Thread::usleepFor(ONE_SECOND * 0.5);

            mrts1.start();
            Thread::usleepFor(ONE_SECOND * 0.5);

            uint32_t cycles = 0;
            const uint32_t MAX_CYCLES = 5;
            while (cycles < MAX_CYCLES) {
                Thread::usleepFor(ONE_SECOND);
                cycles++;
            }

            // Close module.
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts1.stop();

            // Close supercomponent.
            Thread::usleepFor(ONE_SECOND);
            scs.stop();

            Thread::usleepFor(ONE_SECOND);

            // Expected result: ExampleApp should be closed.
            TS_ASSERT(app1TearDownCalled);
            TS_ASSERT(app1.getCounter() > 0);

            UNLINK("configuration");
        }

        void testStartingTwoModulesWithSameNameButDifferentIDsClosingOneWithShuttingDownTCPLinkLetsOtherModuleRunning() {
            // Create a configuration.
            stringstream configuration;
            configuration << "global.buffer.memorySegmentSize = 2800000 # Size of a memory segment for a shared data stream in bytes." << endl
                 << "global.buffer.numberOfMemorySegments = 20 # Number of memory segments used for buffering." << endl
                 << "odsupercomponent.pulseshift.shift = 10000 # (in microseconds) If the managed level is pulse_shift, all connected modules will be informed about the supercomponent's real time by this increment per module. Thus, the execution times per modules are better aligned with supercomponent and the data exchange is somewhat more predictable." << endl
                 << "odsupercomponent.pulsetimeack.timeout = 5000 # (in milliseconds) If the managed level is pulse_time_ack, this is the timeout for waiting for an ACK message from the dependent client." << endl
                 << "odsupercomponent.pulsetimeack.yield = 5000 # (in microseconds) If the managed level is pulse_time_ack, the modules are triggered sequentially by sending pulses and waiting for acknowledgment messages. To allow the modules to deliver their respective containers, this yielding time is used to sleep before supercomponent sends the pulse messages the next module in this execution cycle. This value needs to be adjusted for networked simulations to ensure deterministic execution. " << endl
                 << "odsupercomponent.pulsetimeack.exclude = cockpit,monitor # List of modules that will not get a pulse message from supercomponent." << endl;
            // Create configuration file.
            fstream fout("configuration", ios::out);
            TS_ASSERT(fout.good());
            fout << configuration.str();
            fout.close();

            // Start the encapsulated supercomponent.
            string sc_argv0("odsupercomponent");
            string sc_argv1("--cid=71");
            int32_t sc_argc = 2;
            char **sc_argv;
            sc_argv = new char*[sc_argc];
            sc_argv[0] = const_cast<char*>(sc_argv0.c_str());
            sc_argv[1] = const_cast<char*>(sc_argv1.c_str());

            SupercomponentService scs(sc_argc, sc_argv);

            clog << "Starting odsupercomponent..." << endl;
            scs.start();

            const uint32_t ONE_SECOND = 1*1000*1000;
            Thread::usleepFor(ONE_SECOND * 0.5);

            clog << "odsupercomponent started." << endl;

            // Create first component.
            string c0_argv0("ClientModuleTestService");
            string c0_argv1("--cid=71");
            string c0_argv2("--id=1");
            int32_t c0_argc = 3;
            char **c0_argv;
            c0_argv = new char*[c0_argc];
            c0_argv[0] = const_cast<char*>(c0_argv0.c_str());
            c0_argv[1] = const_cast<char*>(c0_argv1.c_str());
            c0_argv[2] = const_cast<char*>(c0_argv2.c_str());

            bool app1TearDownCalled = false;
            ExampleApp app1(c0_argc, c0_argv, app1TearDownCalled);
            ModuleRunnerTestService mrts1(&app1);

            Thread::usleepFor(ONE_SECOND * 0.5);

            mrts1.start();
            Thread::usleepFor(ONE_SECOND * 0.5);

            uint32_t cycles = 0;
            const uint32_t MAX_CYCLES = 5;
            bool app2TearDownCalled = false;
            uint32_t counterModule1 = 0;
            {
                // Create second component with different ID.
                string c1_argv0("ClientModuleTestService");
                string c1_argv1("--cid=71");
                string c1_argv2("--id=2");
                int32_t c1_argc = 3;
                char **c1_argv;
                c1_argv = new char*[c1_argc];
                c1_argv[0] = const_cast<char*>(c1_argv0.c_str());
                c1_argv[1] = const_cast<char*>(c1_argv1.c_str());
                c1_argv[2] = const_cast<char*>(c1_argv2.c_str());

                ExampleApp app2(c1_argc, c1_argv, app2TearDownCalled);
                ModuleRunnerTestService mrts2(&app2);

                Thread::usleepFor(ONE_SECOND * 0.5);

                mrts2.start();
                Thread::usleepFor(ONE_SECOND * 0.5);

                while (cycles < MAX_CYCLES) {
                    Thread::usleepFor(ONE_SECOND);
                    cycles++;
                }

                // Close module 2.
                Thread::usleepFor(ONE_SECOND * 0.5);
                clog << "Closing module 2...";
                mrts2.stop();
                clog << "done." << endl;

                // Expected result: app2 should be closed.
                TS_ASSERT(app2TearDownCalled);
                TS_ASSERT(app2.getCounter() > 0);

                // Expected result: app1 should still be running.
                TS_ASSERT(!app1TearDownCalled);
                counterModule1 = app1.getCounter();
                TS_ASSERT(counterModule1 > 0);
            }
            clog << "Module 2 destroyed." << endl;

            cycles = 0;
            while (cycles < MAX_CYCLES) {
                Thread::usleepFor(ONE_SECOND);
                cycles++;
            }

            TS_ASSERT(!app1TearDownCalled);
            TS_ASSERT(app1.getCounter() > counterModule1);

            // Close module 1
            Thread::usleepFor(ONE_SECOND * 0.5);
            clog << "Closing module 1...";
            mrts1.stop();
            clog << "done." << endl;

            Thread::usleepFor(ONE_SECOND);

            // Expected result: app1 should be closed by now.
            TS_ASSERT(app1TearDownCalled);
            TS_ASSERT(app1.getCounter() > 0);

            // Close supercomponent.
            Thread::usleepFor(ONE_SECOND);
            scs.stop();

            Thread::usleepFor(ONE_SECOND);

            // Expected result: Both apps should be closed.
            TS_ASSERT(app1TearDownCalled);
            TS_ASSERT(app1.getCounter() > 0);

            TS_ASSERT(app2TearDownCalled);

            UNLINK("configuration");
        }
};

#endif /*LOGGINGTESTSUITE_H_*/
