/**
 * PcapReplay reads a pcap file and sends out strings periodically.
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

#ifndef PCAPREPLAY_H_
#define PCAPREPLAY_H_

//#include <memory>
#include <fstream>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include <opendavinci/odcore/io/udp/UDPSender.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>

namespace automotive {

        using namespace std;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class PcapReplay : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                PcapReplay(const PcapReplay &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                PcapReplay& operator=(const PcapReplay &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                PcapReplay(const int32_t &argc, char **argv);

                virtual ~PcapReplay();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();
                
                const string RECEIVER = "127.0.0.1";
                const uint32_t PORT = 2368;
                const uint32_t BUFFER_SIZE=50000; //number of bytes read from the pcap file each time
                fstream lidarStream;   
                std::shared_ptr<odcore::io::udp::UDPSender> udpsender;
                bool stop;
        };

} // automotive

#endif /*PCAPREPLAY_H_*/
