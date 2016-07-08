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

#include <string>
#include <iostream>
#include <fstream>
#include <opendavinci/odcore/base/Thread.h>

#include "PcapReplay.h"
#include <opendavinci/odcore/io/udp/UDPSender.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>

namespace automotive {

        using namespace std;
        using namespace odcore::io::udp;

        PcapReplay::PcapReplay(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "PcapReplay"),
            lidarStream(),
            udpsender(UDPFactory::createUDPSender(RECEIVER, PORT)),
            stop(false){}

        PcapReplay::~PcapReplay() {}

        void PcapReplay::setUp() {
            //lidarStream.open("../../velodyne/build/imeangowest.pcap", ios::binary|ios::in);
            lidarStream.open("../../velodyne/build/atwall.pcap", ios::binary|ios::in);
        }

        void PcapReplay::tearDown() {
            lidarStream.close();
        }

        // This method will do the main data processing job.
        //Running this module with a frequency of 60Hz gives a data rate 3*10⁶Bps
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode PcapReplay::body() {
            char *buffer = new char[BUFFER_SIZE+1];
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                if (lidarStream.good()) {
                    lidarStream.read(buffer, BUFFER_SIZE * sizeof(char));
                    string s(buffer,BUFFER_SIZE);
                    udpsender->send(s);
                }
                if(!lidarStream.good() && !stop){
                    lidarStream.close();
                    cout<<"File read complete."<<endl;
                    delete [] buffer;
                    stop=true;
                }
            } 
            
            
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

