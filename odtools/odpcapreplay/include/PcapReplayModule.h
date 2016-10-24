 /**
 * PcapReplay - Tool for reading a Velodyne recording file in pcap format
 * and send Velodyne packets via UDP.
 * Copyright (C) 2016 Hang Yin
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

#ifndef PCAPREPLAYMODULE_H_
#define PCAPREPLAYMODULE_H_

#include <fstream>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include <opendavinci/odcore/io/udp/UDPSender.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>

namespace odpcapreplay {

        using namespace std;

        class PcapReplayModule : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                PcapReplayModule(const PcapReplayModule &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                PcapReplayModule& operator=(const PcapReplayModule &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                PcapReplayModule(const int32_t &argc, char **argv);

                virtual ~PcapReplayModule();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();
                
                virtual void nextContainer(odcore::data::Container &c);

            private:
                virtual void setUp();

                virtual void tearDown();
                
                const string RECEIVER = "127.0.0.1";
                const uint32_t PORT = 2368;
                uint32_t BUFFER_SIZE;
                fstream lidarStream;   
                odcore::io::protocol::PCAPProtocol m_pcap;
                std::shared_ptr<odcore::io::udp::UDPSender> udpsender;
                bool stop;
        };

} // odpcapreplay

#endif /*PCAPREPLAYMODULE_H_*/
