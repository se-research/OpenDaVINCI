/**
 * velodyne is an example application to demonstrate how to 
 *              decode Velodyne data realized
 *              with OpenDaVINCI
 * Copyright (C) 2015 Christian Berger and Hang Yin
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

#include <cstdio>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>
#include <memory>

//#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include <opendavinci/odcore/base/Thread.h>
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "Velodyne.h"
#include "velodyneListener.h"

const std::string NAME = "pointCloud";
const uint32_t MAX_POINT_SIZE=125000;
const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
const uint32_t SIZE_PER_COMPONENT = sizeof(float);
const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory? 

namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::wrapper;
        using namespace automotive;
        using namespace odcore::base::module;

        VelodyneDecoder::VelodyneDecoder(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "VelodyneDecoder"),
            m_pcap(),
            lidarStream(),
            VelodyneSharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE)),
            m_vListener(VelodyneSharedMemory,getConference()),
            fileClosed(false),
            frameSent(false),
            counter(0){}

        VelodyneDecoder::~VelodyneDecoder() {}

        void VelodyneDecoder::setUp() {
        // setup share memory.
        // create instance of velodyneListener and pass shared_ptr from shared memory to velodynelister in its constructor
            //cout<<"Start decoding"<<endl;
            //m_pcap.setContainerListener(this);
            //m_vListener.setContainerListener(this);
            m_pcap.setContainerListener(&m_vListener);
            lidarStream.open("atwall.pcap", ios::binary|ios::in);
        }

        void VelodyneDecoder::tearDown() {
            //cout<<"Stop decoding"<<endl;
            lidarStream.close();
        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode VelodyneDecoder::body() {
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                //cout<<"Decoding ongoing"<<endl;
                //counter--;

                while (lidarStream.good() && !m_vListener.getStatus()) {
                //while (lidarStream.good()) {
                    char cc;
                    lidarStream.read(&cc, sizeof(uint8_t));
                    stringstream sstr;
                    sstr << cc;
                    string s = sstr.str();
                    m_pcap.nextString(s);
                }
                if(!fileClosed){
                    lidarStream.close();
                    cout<<"File read complete."<<endl;
                    fileClosed=true;
                }
                /*if(!frameSent){
                    for(int iii=0;iii<m_vListener.getFrameIndex();iii++){
                        m_vListener.sendSPC(iii);
                        cout<<"Send frame "<<iii<<endl;
                        const uint32_t TEN_MSECOND = 1000 * 1000;
                        Thread::usleepFor(TEN_MSECOND);
                    }
                    frameSent=true;
                }*/
                if(counter<=m_vListener.getFrameIndex()){
                    m_vListener.sendSPC(counter);
                    cout<<"Send frame "<<counter<<endl;
                    counter++;
                }
                else{
                    counter=0;
                    cout<<"Replay"<<endl;
                }

                /*if(!frameSent){
                    m_vListener.sendSPC(1);
                    cout<<"Send frame 1"<<endl;
                    frameSent=true;
                }*/
            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

