/**
 * odredirector - Tool for dumping data to stdout or reading back from stdin
 * Copyright (C) 2015 Christian Berger
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

#ifndef REDIRECTORTESTSUITE_H_
#define REDIRECTORTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <memory>
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/io/StreamFactory.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/discoverer/Server.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"

// Include local header files.
#include "../include/Redirector.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::data;
using namespace odcore::dmcp;
using namespace odcore::io;
using namespace odcore::io::conference;
using namespace odcore::data::dmcp;
using namespace odredirector;

/**
 * This class derives from Redirector to allow parallel execution.
 */
class RedirectorTestService : public Service {
    public:
        RedirectorTestService(const int32_t &argc, char **argv) :
                myRedirector(argc, argv) {}

        virtual void beforeStop() {
            // Stop redirector.
            myRedirector.setModuleState(odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING);
        }

        virtual void run() {
            serviceReady();
            myRedirector.runModule();
        }

    private:
        Redirector myRedirector;
};
/**
 * The actual testsuite starts here.
 */
class RedirectorTest : public CxxTest::TestSuite,
                       public connection::ConnectionHandler,
                       public ModuleConfigurationProvider,
                       public ContainerListener {
    public:
        RedirectorTest() :
            m_configuration(),
            m_connection(),
            m_listOfContainers() {
            // Enforce synchronized behavior with C STDIN and STDOUT.
            cin.sync_with_stdio(true);
            cout.sync_with_stdio(true);
        }

        KeyValueConfiguration m_configuration;
        std::shared_ptr<connection::ModuleConnection> m_connection;
        vector<Container> m_listOfContainers;

        virtual KeyValueConfiguration getConfiguration(const ModuleDescriptor& /*md*/) {
            return m_configuration;
        }

        virtual void onNewModule(std::shared_ptr<odcore::dmcp::connection::ModuleConnection> mc) {
            m_connection = mc;
        }

        virtual void nextContainer(Container &c) {
            m_listOfContainers.push_back(c);
        }

        void testRedirectorPumpFromStdin() {
#if defined(WIN32) || defined(__OpenBSD__)
            TS_ASSERT(true);
#else
            // Setup ContainerConference.
            std::shared_ptr<ContainerConference> conference = ContainerConferenceFactory::getInstance().getContainerConference("225.0.0.100");

            // Setup DMCP.
            stringstream sstr_;
            sstr_ << "global.buffer.memorySegmentSize = 1000" << endl
                  << "global.buffer.numberOfMemorySegments = 5" << endl;

            m_configuration = KeyValueConfiguration();
            m_configuration.readFrom(sstr_);

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


            // Prepare the data that would be available from commandline.
            string argv0("odredirector");
            string argv1("--cid=100");
            string argv2("--fromstdin=1");
            int32_t argc = 3;
            char **argv;
            argv = new char*[3];
            argv[0] = const_cast<char*>(argv0.c_str());
            argv[1] = const_cast<char*>(argv1.c_str());
            argv[2] = const_cast<char*>(argv2.c_str());

            // Write data to file.
            fstream fout("testRedirectorPumpFromStdin.in", ios::binary | ios::out);
            TS_ASSERT(fout.good());

            TimeStamp ts1(0, 1);
            Container c1(ts1);
            fout << c1;
            fout.flush();

            TimeStamp ts2(1, 2);
            Container c2(ts2);
            fout << c2;
            fout.flush();

            TimeStamp ts3(2, 3);
            Container c3(ts3);
            fout << c3;
            fout.flush();

            TimeStamp ts4(3, 4);
            Container c4(ts4);
            fout << c4;
            fout.flush();

            TimeStamp ts5(4, 5);
            Container c5(ts5);
            fout << c5;

            fout.flush();

            fout.close();

            // Add container listener to validate containers read from STDIN and replayed to ContainerConference.
            m_listOfContainers.clear();
            conference->setContainerListener(this);

            // Redirect STDIN to file.
            ifstream in("testRedirectorPumpFromStdin.in");
            streambuf *cinbuf = cin.rdbuf(); // Save old rdbuf.
            cin.rdbuf(in.rdbuf()); // Redirect std::cin to testRedirectorPumpFromStdin.in.

            RedirectorTestService rts(argc, argv);

            rts.start();

            Thread::usleepFor(10 * 1000 * 1000);

            rts.stop();

            Thread::usleepFor(100 * 1000);

            delete &(StreamFactory::getInstance());

            // Reset to standard int.
            cin.rdbuf(cinbuf);
            in.close();
            UNLINK("testRedirectorPumpFromStdin.in");

            Container c;
            TimeStamp ts;

            TS_ASSERT(m_listOfContainers.size() >= 5);

            c = m_listOfContainers.at(0);
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts1.toMicroseconds());

            c = m_listOfContainers.at(1);
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts2.toMicroseconds());

            c = m_listOfContainers.at(2);
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts3.toMicroseconds());

            c = m_listOfContainers.at(3);
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts4.toMicroseconds());

            c = m_listOfContainers.at(4);
            ts = c.getData<TimeStamp>();
            TS_ASSERT(ts.toMicroseconds() == ts5.toMicroseconds());

            // Reset container listener.
            m_listOfContainers.clear();
            conference->setContainerListener(NULL);

            // "Ugly" cleaning up conference.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);        
#endif     
        }
};

#endif /*REDIRECTORTESTSUITE_H_*/

