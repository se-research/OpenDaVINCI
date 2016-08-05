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
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "../include/SuperComponent.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcore::exceptions;
using namespace odcore::serialization;

class ExampleLoggerApp : public TimeTriggeredConferenceClientModule {
    public:
        bool tearDownCalled;
        uint32_t m_loggingLevel;

    public:
        ExampleLoggerApp(const int32_t &argc, char **argv, const uint32_t &loggingLevel) :
            TimeTriggeredConferenceClientModule(argc, argv, "examplelogger"),
            tearDownCalled(false),
            m_loggingLevel(loggingLevel) {}

        void setUp() {}

        void tearDown() {
            tearDownCalled = true;
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            uint32_t cnt = 0;
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                stringstream msg;
                msg << "Log message: " << cnt++;
                toLogger(static_cast<odcore::data::LogMessage::LogLevel>(m_loggingLevel), msg.str());
            }

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

class LoggerTest : public CxxTest::TestSuite {
    public:

        void testLogLevelInfo() {
            // Delete any existing log file.
            UNLINK("test2.log");

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
            string sc_argv1("--cid=82");
            string sc_argv2("--freq=10");
            string sc_argv3("--loglevel=info");
            string sc_argv4("--logfile=test2.log");
            int32_t sc_argc = 5;
            char **sc_argv;
            sc_argv = new char*[sc_argc];
            sc_argv[0] = const_cast<char*>(sc_argv0.c_str());
            sc_argv[1] = const_cast<char*>(sc_argv1.c_str());
            sc_argv[2] = const_cast<char*>(sc_argv2.c_str());
            sc_argv[3] = const_cast<char*>(sc_argv3.c_str());
            sc_argv[4] = const_cast<char*>(sc_argv4.c_str());

            SupercomponentService scs(sc_argc, sc_argv);

            clog << "Starting odsupercomponent..." << endl;
            scs.start();

            const uint32_t ONE_SECOND = 1*1000*1000;
            Thread::usleepFor(ONE_SECOND * 0.5);

            clog << "odsupercomponent started." << endl;

            // Create first component sending at level NONE.
            string c0_argv0("ClientModuleTestService");
            string c0_argv1("--cid=82");
            string c0_argv2("--id=1");
            string c0_argv3("--freq=10");
            int32_t c0_argc = 4;
            char **c0_argv;
            c0_argv = new char*[c0_argc];
            c0_argv[0] = const_cast<char*>(c0_argv0.c_str());
            c0_argv[1] = const_cast<char*>(c0_argv1.c_str());
            c0_argv[2] = const_cast<char*>(c0_argv2.c_str());
            c0_argv[3] = const_cast<char*>(c0_argv3.c_str());

            ExampleLoggerApp app1(c0_argc, c0_argv, odcore::data::LogMessage::NONE);
            ModuleRunnerTestService mrts1(&app1);

            // Create second component sending at level INFO.
            string c1_argv0("ClientModuleTestService");
            string c1_argv1("--cid=82");
            string c1_argv2("--id=2");
            string c1_argv3("--freq=10");
            int32_t c1_argc = 4;
            char **c1_argv;
            c1_argv = new char*[c1_argc];
            c1_argv[0] = const_cast<char*>(c1_argv0.c_str());
            c1_argv[1] = const_cast<char*>(c1_argv1.c_str());
            c1_argv[2] = const_cast<char*>(c1_argv2.c_str());
            c1_argv[3] = const_cast<char*>(c1_argv3.c_str());

            ExampleLoggerApp app2(c1_argc, c1_argv, odcore::data::LogMessage::INFO);
            ModuleRunnerTestService mrts2(&app2);

            // Create third component sending at level WARN.
            string c2_argv0("ClientModuleTestService");
            string c2_argv1("--cid=82");
            string c2_argv2("--id=3");
            string c2_argv3("--freq=10");
            int32_t c2_argc = 4;
            char **c2_argv;
            c2_argv = new char*[c2_argc];
            c2_argv[0] = const_cast<char*>(c2_argv0.c_str());
            c2_argv[1] = const_cast<char*>(c2_argv1.c_str());
            c2_argv[2] = const_cast<char*>(c2_argv2.c_str());
            c2_argv[3] = const_cast<char*>(c2_argv3.c_str());

            ExampleLoggerApp app3(c2_argc, c2_argv, odcore::data::LogMessage::WARN);
            ModuleRunnerTestService mrts3(&app3);

            // Create fourth component sending at level DEBUG.
            string c3_argv0("ClientModuleTestService");
            string c3_argv1("--cid=82");
            string c3_argv2("--id=4");
            string c3_argv3("--freq=10");
            int32_t c3_argc = 4;
            char **c3_argv;
            c3_argv = new char*[c3_argc];
            c3_argv[0] = const_cast<char*>(c3_argv0.c_str());
            c3_argv[1] = const_cast<char*>(c3_argv1.c_str());
            c3_argv[2] = const_cast<char*>(c3_argv2.c_str());
            c3_argv[3] = const_cast<char*>(c3_argv3.c_str());

            ExampleLoggerApp app4(c3_argc, c3_argv, odcore::data::LogMessage::DEBUG);
            ModuleRunnerTestService mrts4(&app4);


            Thread::usleepFor(ONE_SECOND * 0.5);

            mrts1.start();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts2.start();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts3.start();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts4.start();
            Thread::usleepFor(ONE_SECOND * 0.5);

            uint32_t cycles = 0;
            const uint32_t MAX_CYCLES = 5;
            while (cycles < MAX_CYCLES) {
                Thread::usleepFor(ONE_SECOND);
                cycles++;
            }

            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts1.stop();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts2.stop();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts3.stop();
            Thread::usleepFor(ONE_SECOND * 0.5);
            mrts4.stop();
            Thread::usleepFor(ONE_SECOND * 0.5);
            scs.stop();
            Thread::usleepFor(ONE_SECOND * 0.5);

            fstream fin("test2.log", ios::in);
            TS_ASSERT(fin.good());

            uint32_t lines = 0;
            const uint32_t MAX_LINES = 80;
            bool foundLogLevelNone = false;
            bool foundLogLevelInfo = false;
            bool foundLogLevelWarn = false;
            bool foundLogLevelDebug = false;
            while ( (!fin.eof()) && (lines < MAX_LINES) ) {
                lines++;
                string line;
                getline(fin, line);
                vector<string> tokens = odcore::strings::StringToolbox::split(line, ';');

                // Ensure we have correct entries.
                TS_ASSERT(tokens.size() > 3);

                // Check for log levels.
                foundLogLevelNone |= odcore::strings::StringToolbox::equalsIgnoreCase(tokens.at(2), "0");
                foundLogLevelInfo |= odcore::strings::StringToolbox::equalsIgnoreCase(tokens.at(2), "1");
                foundLogLevelWarn |= odcore::strings::StringToolbox::equalsIgnoreCase(tokens.at(2), "2");
                foundLogLevelDebug |= odcore::strings::StringToolbox::equalsIgnoreCase(tokens.at(2), "3");
            }

            fin.close();

            UNLINK("test2.log");
            UNLINK("configuration");

            TS_ASSERT(foundLogLevelNone);
            TS_ASSERT(foundLogLevelInfo);
            TS_ASSERT(!foundLogLevelWarn);
            TS_ASSERT(!foundLogLevelDebug);
        }

};

#endif /*LOGGINGTESTSUITE_H_*/
