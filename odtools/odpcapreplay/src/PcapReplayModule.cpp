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

#include <string>
#include <iostream>
#include <fstream>

#include "PcapReplayModule.h"
#include "opendavinci/odcore/data/Container.h"
#include <opendavinci/odcore/io/udp/UDPSender.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>
#include "opendavinci/generated/odcore/data/pcap/Packet.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"

namespace odpcapreplay {

        using namespace std;
        using namespace odcore::data;
        using namespace odcore::io::udp;

        PcapReplayModule::PcapReplayModule(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "PcapReplay"),
            BUFFER_SIZE(),
            lidarStream(),
            m_pcap(),
            udpsender(UDPFactory::createUDPSender(RECEIVER, PORT)),
            stop(false){}

        PcapReplayModule::~PcapReplayModule() {}

        void PcapReplayModule::setUp() {
            lidarStream.open(getKeyValueConfiguration().getValue<string>("PcapReplay.readpcap"), ios::binary|ios::in);
            BUFFER_SIZE=getKeyValueConfiguration().getValue<uint32_t>("PcapReplay.bufferSize");
            
            //Setup PCAPDecoder and register PcapReplay as ContainerListener
            m_pcap.setContainerListener(this);
        }

        void PcapReplayModule::tearDown() {
            // Unregister PcapReplay as ContainerListener from PCAPDecoder
            lidarStream.close();
            m_pcap.setContainerListener(NULL);
        }
        
        void PcapReplayModule::nextContainer(Container &c) {
            // Check if container is of type PCAPPacket. If true, send the payload of each Velodyne packet (1206 bytes)
            if (c.getDataType() == odcore::data::pcap::Packet::ID()) {
                pcap::Packet packet = c.getData<pcap::Packet>();
                pcap::PacketHeader packetHeader = packet.getHeader();
                if(packetHeader.getIncl_len()==1248)
                {
                    string payload = packet.getPayload();
                    payload = payload.substr(42,1206); //Remove the 42-byte Ethernet header
                    udpsender->send(payload);
                }
            }
        }

        // This method will do the main data processing job.
        //In the configuration file for odsupercomponent, adjust buffer size and the frequency of this module to tune the byte sending rate. 
        //For VLP-16, the data rate is roughly 1MB/s. So 4000 for buffer size and 250 for frequency of PcapReplay is a good combination.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode PcapReplayModule::body() {
            char *buffer = new char[BUFFER_SIZE+1];
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                if (lidarStream.good()) {
                    lidarStream.read(buffer, BUFFER_SIZE * sizeof(char));
                    string s(buffer,BUFFER_SIZE);
                    m_pcap.nextString(s);// feed s to PCAPDecoder
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
} // odpcapreplay

