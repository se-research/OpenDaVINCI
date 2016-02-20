/**
 * odrecorder - Tool for recording data
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

#ifndef RECORDERMODULETESTSUITE_H_
#define RECORDERMODULETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/core/base/Service.h"
#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/data/TimeStamp.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/io/conference/ContainerConference.h"
#include "opendavinci/core/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/core/io/StreamFactory.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/core/dmcp/discoverer/Server.h"
#include "opendavinci/core/dmcp/connection/Server.h"
#include "opendavinci/core/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/core/dmcp/connection/ModuleConnection.h"

#include "../include/RecorderModule.h"

using namespace std;
using namespace odrecorder;
using namespace core::base;
using namespace core::data;
using namespace core::dmcp;
using namespace core::io;
using namespace core::io::conference;
using namespace coredata::dmcp;

class RecorderTestService : public Service {
    public:
        RecorderTestService(const int32_t &argc, char **argv) :
            myRecorder(argc, argv) {}

        virtual void beforeStop() {
            // Stop recorder.
            myRecorder.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myRecorder.runModule();
        }

    private:
        RecorderModule myRecorder;
};

class RecorderTest : public CxxTest::TestSuite,
                     public connection::ConnectionHandler,
                     public ModuleConfigurationProvider {
    public:
        RecorderTest() :
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

        void testRecorder() {
            // Setup ContainerConference.
            core::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");

            // Setup DMCP.
            stringstream sstr;
            sstr << "odrecorder.output = file://RecorderTest.rec" << endl
            << "global.buffer.memorySegmentSize = 1000" << endl
            << "global.buffer.numberOfMemorySegments = 5" << endl
            << "odrecorder.dumpSharedData = 1" << endl
            << "odrecorder.remoteControl = 0" << endl;

            m_configuration = KeyValueConfiguration();
            m_configuration.readFrom(sstr);

            vector<string> noModulesToIgnore;
            ServerInformation serverInformation("127.0.0.1", 19000, ServerInformation::ML_NONE);
            discoverer::Server dmcpDiscovererServer(serverInformation,
                                                    "225.0.0.100",
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                    noModulesToIgnore);
            dmcpDiscovererServer.startResponding();

            connection::Server dmcpConnectionServer(serverInformation, *this);
            dmcpConnectionServer.setConnectionHandler(this);

            // Setup recorder.
            string argv0("odrecorder");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());

            RecorderTestService rts(argc, argv);

            rts.start();

            Thread::usleepFor(10000000);
            // Send data.
            TimeStamp ts1(0, 1);
            Container c1(ts1);
            conference->send(c1);

            Thread::usleepFor(100000);

            TimeStamp ts2(1, 2);
            Container c2(ts2);
            conference->send(c2);

            Thread::usleepFor(100000);

            TimeStamp ts3(2, 3);
            Container c3(ts3);
            conference->send(c3);

            Thread::usleepFor(100000);

            TimeStamp ts4(3, 4);
            Container c4(ts4);
            conference->send(c4);

            Thread::usleepFor(100000);

            TimeStamp ts5(4, 5);
            Container c5(ts5);
            conference->send(c5);

            Thread::usleepFor(100000);

            rts.stop();

            Thread::usleepFor(100000);

            delete &(StreamFactory::getInstance());

            fstream fin("RecorderTest.rec", ios::binary | ios::in);
            TS_ASSERT(fin.good());
            Container c;
            TimeStamp ts;

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts1.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts2.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts3.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts4.toMicroseconds());
            TS_ASSERT(fin.good());

            fin >> c;
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts5.toMicroseconds());
            TS_ASSERT(fin.good());
            fin.close();
            UNLINK("RecorderTest.rec");

            // "Ugly" cleaning up conference.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }
};

#endif /*RECORDERTESTSUITE_H_*/
