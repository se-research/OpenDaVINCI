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

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "opendavinci/core/base/FIFOQueue.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendavinci/core/base/Service.h"
#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/exceptions/Exceptions.h"

#include "opendavinci/core/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/core/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/core/dmcp/discoverer/Server.h"
#include "opendavinci/core/dmcp/connection/Server.h"
#include "opendavinci/core/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/core/dmcp/connection/ModuleConnection.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "../include/GlobalConfigurationProvider.h"
#include "../include/SuperComponent.h"

using namespace std;
using namespace core::base;
using namespace core::base::module;
using namespace core::data;
using namespace core::exceptions;
using namespace core::dmcp;
using namespace core::io;
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
        core::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor &md) {
            return m_globaleConfigurationProvider.getConfiguration(md);
        }

        virtual void onNewModule(core::SharedPointer<core::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testServerInformation() {
            ServerInformation s1("127.0.0.1", 19000, ServerInformation::ML_NONE);
            ServerInformation s2;

            stringstream sstr;
            sstr << s1;
            sstr >> s2;

            cerr << s1.toString() << endl;

            TS_ASSERT(s1.toString() == s2.toString());

            ServerInformation s3("127.0.0.1", 19000, ServerInformation::ML_PULSE);
            ServerInformation s4;

            stringstream sstr2;
            sstr2 << s3;
            sstr2 >> s4;

            cerr << s4.toString() << endl;

            TS_ASSERT(s3.toString() == s4.toString());
        }

};

#endif /*SUPERCOMPONENTCLIENTMODULETESTSUITE_H_*/
