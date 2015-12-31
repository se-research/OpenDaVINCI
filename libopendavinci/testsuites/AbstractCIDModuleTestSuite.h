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

#ifndef CORE_ABSTRACTCIDMODULETESTSUITE_H_
#define CORE_ABSTRACTCIDMODULETESTSUITE_H_

#include <cerrno>                       // for errno
#include <iostream>                     // for basic_ostream, clog, endl, etc
#include <string>                       // for string, operator==, etc
#include <vector>                       // for vector, vector<>::iterator

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/platform.h"
#include "core/base/Service.h"          // for Service
#include "core/base/Thread.h"           // for Thread
#include "core/base/module/AbstractCIDModule.h"  // for AbstractCIDModule
#include "core/exceptions/Exceptions.h"  // for InvalidArgumentException
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace core { namespace base { namespace module { class AbstractModule; } } }

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::exceptions;

class AbstractCIDModuleTestConcreteModule : public AbstractCIDModule {
    public:
        AbstractCIDModuleTestConcreteModule(int32_t argc = 0, char **argv = NULL) :
                AbstractCIDModule(argc, argv), counter(0) {}

        int32_t counter;
        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule() {
            counter++;
            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }
};

class AbstractCIDModuleTestConcreteModule2 : public AbstractCIDModule {
    public:
        AbstractCIDModuleTestConcreteModule2(int32_t argc = 0, char **argv = NULL):
                AbstractCIDModule(argc, argv), counter(0), ready(false) {}

        int32_t counter;
        bool ready;
        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule() {
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                ready = true;
                counter++;
                Thread::usleepFor(100);
            }
            ready = false;
            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }
};

class AbstractCIDModuleTestConcreteModule3 : public AbstractCIDModule {
    public:
        AbstractCIDModuleTestConcreteModule3(int32_t argc = 0, char **argv = NULL):
                AbstractCIDModule(argc, argv) {}

        virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule() {
            errno = 0;
            throw InvalidArgumentException("Test", "Testcase", 123);
        }
};

class AbstractCIDModuleTestConcreteModule2Service : public Service {
    public:
        AbstractCIDModuleTestConcreteModule2Service(AbstractCIDModuleTestConcreteModule2 &amtcm2) :
                m_module(amtcm2) {}

        virtual void beforeStop() {}

        virtual void run() {
            serviceReady();
            m_module.setModuleState(coredata::dmcp::ModuleStateMessage::RUNNING);
            m_module.runModule();
        }

        AbstractCIDModuleTestConcreteModule2 &m_module;
};

class AbstractCIDModuleTest : public CxxTest::TestSuite {
    public:
        void testAbstractCIDModule() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=10");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            AbstractCIDModuleTestConcreteModule amtcm(argc, argv);
            TS_ASSERT(AbstractCIDModule::getListOfModules().size() == 1);

            amtcm.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
            TS_ASSERT(amtcm.getModuleStateAndWaitForRemainingTimeInTimeslice() ==  coredata::dmcp::ModuleStateMessage::NOT_RUNNING);

            amtcm.counter = 0;
            TS_ASSERT(amtcm.runModule() == coredata::dmcp::ModuleExitCodeMessage::OKAY);
            TS_ASSERT(amtcm.counter == 1);

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();
            delete[] argv;
        }

        void testAbstractCIDModuleCID() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=10");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            AbstractCIDModuleTestConcreteModule amtcm(argc, argv);
            TS_ASSERT(amtcm.getMultiCastGroup() == "225.0.0.10");

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();
            delete[] argv;
        }

        void testAbstractCIDModuleWrongCID1() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=0");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            bool failed = true;
            try {
                AbstractCIDModuleTestConcreteModule amtcm(argc, argv);
            } catch (InvalidArgumentException &iae) {
                clog << iae.getMessage() << endl;
                TS_ASSERT(iae.getMessage() == "The conference group id has to be in range [2, 254].");
                failed = false;
            }
            TS_ASSERT(!failed);

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();
            delete[] argv;
        }

        void testAbstractCIDModuleWrongCID2() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=255");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            bool failed = true;
            try {
                AbstractCIDModuleTestConcreteModule amtcm(argc, argv);
            } catch (InvalidArgumentException &iae) {
                TS_ASSERT(iae.getMessage() == "The conference group id has to be in range [2, 254].");
                failed = false;
            }
            TS_ASSERT(!failed);

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();
            delete[] argv;
        }

        void testKillAbstractCIDModule() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=200");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            AbstractCIDModuleTestConcreteModule2 amtcm2(argc, argv);
            amtcm2.ready = false;
            amtcm2.counter = 0;
            TS_ASSERT(AbstractCIDModule::getListOfModules().size() == 1);

            AbstractCIDModuleTestConcreteModule2Service service(amtcm2);
            service.start();

            Thread::usleepFor(100);
            while (!amtcm2.ready) {
                Thread::usleepFor(100);
            }

            // Kill module.
            /******* This is the same code as in AbstractCIDModule **********/
            vector<AbstractModule*>::iterator it = AbstractCIDModule::getListOfModules().begin();
            while (it != AbstractCIDModule::getListOfModules().end()) {
                AbstractModule *m = *it++;
                if (m != NULL) {
                    m->setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
                }
            }
            /******* This is the same code as in AbstractCIDModule **********/

            service.stop();

            TS_ASSERT(!amtcm2.ready);

            TS_ASSERT(amtcm2.counter > 0);

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();
            delete[] argv;
        }

        void testExceptionAbstractCIDModule() {
            string argv0("ConferenceClientModuleTestModule");
            string argv1("--id=ABD");
            string argv2("--cid=200");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            AbstractCIDModuleTestConcreteModule3 amtcm3(argc, argv);
            TS_ASSERT(AbstractCIDModule::getListOfModules().size() == 1);

            bool failed = true;
            try {
                amtcm3.runModule();
            } catch (InvalidArgumentException &iae) {
                string s = iae.toString();
                TS_ASSERT(s == "InvalidArgumentException: Test at Testcase: 123");
                failed = false;
            }

            // Clean up created modules.
            AbstractCIDModule::getListOfModules().clear();

            TS_ASSERT(!failed);
            delete[] argv;
        }
};

#endif /*CORE_ABSTRACTCIDMODULETESTSUITE_H_*/
