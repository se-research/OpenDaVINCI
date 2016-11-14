/**
 * velodyne16pcap is a program that reads VLP-16 data in .pcap format and 
 * sends out the decoded data as 3D shared point cloud, including x, y, z, and intensity (all float)
 * Copyright (C) 2016 Hang Yin and Christian Berger
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
#include <memory>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "Velodyne16pcap.h"


namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::wrapper;
        using namespace automotive;
        using namespace odcore::base::module;

        VelodyneDecoder16pcap::VelodyneDecoder16pcap(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "VelodyneDecoder16pcap"),
            m_pcap(),
            lidarStream(),
            VelodyneSharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE)),
            m_vListener(VelodyneSharedMemory,getConference()),
            fileClosed(false),
            counter(0){}

        VelodyneDecoder16pcap::~VelodyneDecoder16pcap() {}

        void VelodyneDecoder16pcap::setUp() {
        // setup share memory.
        // create instance of velodyneListener and pass shared_ptr from shared memory to velodynelister in its constructor
            m_pcap.setContainerListener(&m_vListener);
            lidarStream.open(getKeyValueConfiguration().getValue<string>("VelodyneDecoder16pcap.readpcap"), ios::binary|ios::in);
            
        }

        void VelodyneDecoder16pcap::tearDown() {
            lidarStream.close();
        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode VelodyneDecoder16pcap::body() {
            char *buffer = new char[BUFFER_SIZE+1];
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                counter=0;
                while (lidarStream.good() && !m_vListener.getStatus() && counter<100) {
                        lidarStream.read(buffer, BUFFER_SIZE * sizeof(char));
                        string s(buffer,BUFFER_SIZE);
                        m_pcap.nextString(s);
                        counter++;
                } 
            }
            if(!fileClosed){
                lidarStream.close();
                cout<<"File read complete."<<endl;
                fileClosed=true;
            }
            delete [] buffer;
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

