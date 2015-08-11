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

#include "core/SharedPointer.h"
#include "core/base/FIFOQueue.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/io/conference/ContainerConference.h"
#include "core/io/conference/ContainerConferenceFactory.h"
#include "core/io/conference/ContainerListener.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"
#include "core/dmcp/ModuleConfigurationProvider.h"
#include "core/dmcp/discoverer/Server.h"
#include "core/dmcp/connection/Server.h"
#include "core/dmcp/connection/ConnectionHandler.h"
#include "core/dmcp/connection/ModuleConnection.h"

#include "GeneratedHeaders_CoreData.h"

#include "../include/PlayerModule.h"

using namespace std;
using namespace odplayer;
using namespace core::base;
using namespace core::data;
using namespace core::dmcp;
using namespace core::io;
using namespace core::io::conference;
using namespace coredata::dmcp;

class PlayerModuleTestService : public Service {
    public:
        PlayerModuleTestService(const int32_t &argc, char **argv) :
            myPlayerModule(argc, argv) {}

        virtual void beforeStop() {
            // Stop player.
            myPlayerModule.setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
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
            if ( (c.getDataType() == Container::TIMESTAMP) ) {
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
        core::SharedPointer<connection::ModuleConnection> m_connection;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(core::SharedPointer<core::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        void testRealtimeReplayNoRewindRemoteControl() {
#if !defined(__FreeBSD__) && !defined(__NetBSD__)
            // Prepare record file.
            fstream fout("PlayerModuleTest.rec", ios::out | ios::binary | ios::trunc);

            // Write data.
            TimeStamp ts1(0, 1);
            Container c1(Container::TIMESTAMP, ts1);
            c1.setReceivedTimeStamp(ts1);
            fout << c1;

            TimeStamp ts2(1, 2);
            Container c2(Container::TIMESTAMP, ts2);
            c2.setReceivedTimeStamp(ts2);
            fout << c2;

            TimeStamp ts3(2, 3);
            Container c3(Container::TIMESTAMP, ts3);
            c3.setReceivedTimeStamp(ts3);
            fout << c3;

            TimeStamp ts4(3, 4);
            Container c4(Container::TIMESTAMP, ts4);
            c4.setReceivedTimeStamp(ts4);
            fout << c4;

            TimeStamp ts5(4, 5);
            Container c5(Container::TIMESTAMP, ts5);
            c5.setReceivedTimeStamp(ts5);
            fout << c5;

            fout.flush();
            fout.close();

            // Setup ContainerConference.
            PlayerModuleTestContainerListener ptcl;
            core::SharedPointer<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");
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
                                                    coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                    coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
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
            coredata::player::PlayerCommand playerCommand;
            playerCommand.setCommand(coredata::player::PlayerCommand::PLAY);
            Container cPC1(Container::PLAYER_COMMAND, playerCommand);
            conference->send(cPC1);

            uint32_t numberOfElements = 0;
            while (!(numberOfElements > 0)) {
                numberOfElements = ptcl.getQueue().getSize();
                Thread::usleepFor(50);
            }

            // Pause playing.
            playerCommand.setCommand(coredata::player::PlayerCommand::PAUSE);
            Container cPC2(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::REWIND);
            Container cPC3(Container::PLAYER_COMMAND, playerCommand);
            conference->send(cPC3);

            Thread::usleepFor(1000);

            ////////////////////////////////////////////////////////////////////
            // Start player.
            ////////////////////////////////////////////////////////////////////

            // Start playing.
            // Clear queue.
            ptcl.getQueue().clear();
            playerCommand.setCommand(coredata::player::PlayerCommand::PLAY);
            Container cPC4(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::PAUSE);
            Container cPC5(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::PLAY);
            Container cPC6(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::PAUSE);
            Container cPC7(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::STEP_FORWARD);
            Container cPC8(Container::PLAYER_COMMAND, playerCommand);
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
            playerCommand.setCommand(coredata::player::PlayerCommand::STEP_FORWARD);
            Container cPC9(Container::PLAYER_COMMAND, playerCommand);
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
