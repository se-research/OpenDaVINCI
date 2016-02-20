/**
 * odplayer - Tool for playing back recorded data
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

#ifndef PLAYERTESTSUITE_H_
#define PLAYERTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/StreamFactory.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/discoverer/Server.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "../include/PlayerModule.h"

using namespace std;
using namespace odplayer;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::dmcp;
using namespace odcore::io;
using namespace odcore::io::conference;
using namespace odcore::data::dmcp;

class PlayerModuleTestService : public Service {
    public:
        PlayerModuleTestService(const int32_t &argc, char **argv) :
            myPlayerModule(argc, argv) {}

        virtual void beforeStop() {
            // Stop player.
            myPlayerModule.setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myPlayerModule.runModule();
        }

    private:
        PlayerModule myPlayerModule;
};

class PlayerModuleTestContainerListener : public ContainerListener {
    public:
        PlayerModuleTestContainerListener() :
            fifo(NULL) {
            fifo = new FIFOQueue();
        }

        FIFOQueue& getQueue() {
            return *fifo;
        }

        virtual void nextContainer(Container &c) {
            if ( (c.getDataType() == TimeStamp::ID()) ) {
                fifo->enter(c);
            }
        }

    private:
        PlayerModuleTestContainerListener(const PlayerModuleTestContainerListener& );
        PlayerModuleTestContainerListener& operator=(const PlayerModuleTestContainerListener& );
        FIFOQueue *fifo;
};

class PlayerModuleTest : public CxxTest::TestSuite,
            public connection::ConnectionHandler,
            public ModuleConfigurationProvider {
    public:
        PlayerModuleTest() :
            m_configuration(),
            m_connection() {}

        KeyValueConfiguration m_configuration;
        odcore::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testRealtimeReplayNoRewindRemoteControl() {
#if !defined(__FreeBSD__) && !defined(__NetBSD__)
            // Prepare record file.
            fstream fout("PlayerModuleTest.rec", ios::out | ios::binary | ios::trunc);

            // Write data.
            TimeStamp ts1(0, 1);
            Container c1(ts1);
            c1.setReceivedTimeStamp(ts1);
            fout << c1;

            TimeStamp ts2(1, 2);
            Container c2(ts2);
            c2.setReceivedTimeStamp(ts2);
            fout << c2;

            TimeStamp ts3(2, 3);
            Container c3(ts3);
            c3.setReceivedTimeStamp(ts3);
            fout << c3;

            TimeStamp ts4(3, 4);
            Container c4(ts4);
            c4.setReceivedTimeStamp(ts4);
            fout << c4;

            TimeStamp ts5(4, 5);
            Container c5(ts5);
            c5.setReceivedTimeStamp(ts5);
            fout << c5;

            fout.flush();
            fout.close();

            // Setup ContainerConference.
            PlayerModuleTestContainerListener ptcl;
            odcore::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");
            conference->setContainerListener(&ptcl);

            // Setup DMCP.
            stringstream sstr;
            sstr << "odplayer.input = file://PlayerModuleTest.rec" << endl
            << "odplayer.autoRewind = 0" << endl
            << "odplayer.remoteControl = 1" << endl
            << "odplayer.timeScale = 1.0" << endl
            << "global.buffer.memorySegmentSize = 1000" << endl
            << "global.buffer.numberOfMemorySegments = 3" << endl;

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

            // Setup player.
            string argv0("odplayer");
            string argv1("--cid=100");
            int32_t argc = 2;
            char **argv;
            argv = new char*[2];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            PlayerModuleTestService pts(argc, argv);

            pts.start();

            // Wait shortly.
            Thread::usleepFor(10*1000*1000);

            ////////////////////////////////////////////////////////////////////
            // Start player.
            ////////////////////////////////////////////////////////////////////

            // Start playing.
            odcore::data::player::PlayerCommand playerCommand;
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PLAY);
            Container cPC1(playerCommand);
            conference->send(cPC1);

            uint32_t numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            // Pause playing.
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PAUSE);
            Container cPC2(playerCommand);
            conference->send(cPC2);

            ////////////////////////////////////////////////////////////////////
            // Pause player (first token of recorded file has to be replayed).
            ////////////////////////////////////////////////////////////////////

            TS_ASSERT(ptcl.getQueue().getSize() == 1);

            // Check replayed data:
            Container c;
            TimeStamp ts;

            c = ptcl.getQueue().leave();
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts1.toMicroseconds());

            ////////////////////////////////////////////////////////////////////
            // Rewind player.
            ////////////////////////////////////////////////////////////////////

            // Rewind.
            playerCommand.setCommand(odcore::data::player::PlayerCommand::REWIND);
            Container cPC3(playerCommand);
            conference->send(cPC3);

            Thread::usleepFor(1000);

            ////////////////////////////////////////////////////////////////////
            // Start player.
            ////////////////////////////////////////////////////////////////////

            // Start playing.
            // Clear queue.
            ptcl.getQueue().clear();
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PLAY);
            Container cPC4(playerCommand);
            conference->send(cPC4);

            numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            ////////////////////////////////////////////////////////////////////
            // Pause player (first token of recorded file has to be replayed again).
            ////////////////////////////////////////////////////////////////////

            // Pause playing.
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PAUSE);
            Container cPC5(playerCommand);
            conference->send(cPC5);

            TS_ASSERT(ptcl.getQueue().getSize() == 1);

            // Check replayed data:
            c = ptcl.getQueue().leave();
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts1.toMicroseconds());

            Thread::usleepFor(1000);

            ////////////////////////////////////////////////////////////////////
            // Start player.
            ////////////////////////////////////////////////////////////////////

            // Start playing.
            // Clear queue.
            ptcl.getQueue().clear();
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PLAY);
            Container cPC6(playerCommand);
            conference->send(cPC6);

            numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            ////////////////////////////////////////////////////////////////////
            // Pause player (second token of recorded file has to be replayed).
            ////////////////////////////////////////////////////////////////////

            // Pause playing.
            playerCommand.setCommand(odcore::data::player::PlayerCommand::PAUSE);
            Container cPC7(playerCommand);
            conference->send(cPC7);

            TS_ASSERT(ptcl.getQueue().getSize() == 1);

            // Check replayed data:
            c = ptcl.getQueue().leave();
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts2.toMicroseconds());

            Thread::usleepFor(1000);

            ////////////////////////////////////////////////////////////////////
            // Stepwise playing.
            ////////////////////////////////////////////////////////////////////

            // Clear queue.
            ptcl.getQueue().clear();
            playerCommand.setCommand(odcore::data::player::PlayerCommand::STEP_FORWARD);
            Container cPC8(playerCommand);
            conference->send(cPC8);

            numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            TS_ASSERT(ptcl.getQueue().getSize() == 1);

            // Check replayed data:
            c = ptcl.getQueue().leave();
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts3.toMicroseconds());

            // Clear queue.
            ptcl.getQueue().clear();
            playerCommand.setCommand(odcore::data::player::PlayerCommand::STEP_FORWARD);
            Container cPC9(playerCommand);
            conference->send(cPC9);

            numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            TS_ASSERT(ptcl.getQueue().getSize() == 1);

            // Check replayed data:
            c = ptcl.getQueue().leave();
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts4.toMicroseconds());

            pts.stop();

            delete &(StreamFactory::getInstance());

            UNLINK("PlayerModuleTest.rec");

            // "Ugly" cleaning up conference.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
#endif /* !FreeBSD and !NetBSD */
        }
};

#endif /*PLAYERTESTSUITE_H_*/
