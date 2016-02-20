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

#ifndef SUPERCOMPONENTCLIENTMODULETESTSUITE_H_
#define SUPERCOMPONENTCLIENTMODULETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/discoverer/Server.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "../include/GlobalConfigurationProvider.h"
#include "../include/SuperComponent.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::base::module;
using namespace odcore::data;
using namespace odcore::exceptions;
using namespace odcore::dmcp;
using namespace odcore::io;
using namespace coredata::dmcp;
using namespace odsupercomponent;

class SuperComponentApp : public SuperComponent {
    public:
        SuperComponentApp(const int32_t &argc, char **argv) :
            SuperComponent(argc, argv) {}
};

class ClientModuleApp : public TimeTriggeredConferenceClientModule {
    public:
        ClientModuleApp(const int32_t &argc, char **argv, const string &name) :
            TimeTriggeredConferenceClientModule(argc, argv, name) {}

        const KeyValueConfiguration getKVC() const {
            return getKeyValueConfiguration();
        }

        void setUp() {}

        void tearDown() {}

        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body() {
            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }
};

class ClientModuleTestService : public Service {
    public:
        ClientModuleTestService(const int32_t &argc, char **argv, const string &name) :
            myApp(argc, argv, name),
            m_hasConfigurationReceivedMutex(),
            m_hasConfigurationReceived(false) {}

        virtual void beforeStop() {
            // Stop app.
            myApp.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myApp.runModule();

            Lock l(m_hasConfigurationReceivedMutex);
            m_hasConfigurationReceived = true;
        }

        const KeyValueConfiguration getKVC() const {
            return myApp.getKVC();
        }

        bool hasConfigurationReceived() const {
            bool retVal = false;
            {
                Lock l(m_hasConfigurationReceivedMutex);
                retVal = m_hasConfigurationReceived;
            }
            return retVal;
        }

    private:
        ClientModuleApp myApp;
        mutable Mutex m_hasConfigurationReceivedMutex;
        bool m_hasConfigurationReceived;
};

class SupercomponentClientModuleTest : public CxxTest::TestSuite,
            public connection::ConnectionHandler,
            public ModuleConfigurationProvider {
    public:
        SupercomponentClientModuleTest() :
            m_globaleConfigurationProvider(),
            m_connection() {}

        odsupercomponent::GlobalConfigurationProvider m_globaleConfigurationProvider;
        odcore::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor &md) {
            return m_globaleConfigurationProvider.getConfiguration(md);
        }

        virtual void onNewModule(odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testServerExistingDefaultConfigurationFile() {
            UNLINK("configuration");
            stringstream configurationData;
            configurationData << "global.mydata = ABC" << endl;
            fstream fout("configuration", ios::trunc | ios::out);
            fout << configurationData.str();
            fout.flush();
            fout.close();

            bool nothingThrown = false;
            try {
                string argv0("odsupercomponent");
                string argv1("--cid=150");
                int32_t argc = 2;
                char **argv;
                argv = new char*[2];
                argv[0] = const_cast<char*>(argv0.c_str());
                argv[1] = const_cast<char*>(argv1.c_str());

                SuperComponentApp sc(argc, argv);
                nothingThrown = true;
            }
            catch (...) {
            }
            TS_ASSERT(nothingThrown);
        }

};

#endif /*SUPERCOMPONENTCLIENTMODULETESTSUITE_H_*/
