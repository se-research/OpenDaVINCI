/**
 * velodyneListener is used to 
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

#ifndef VELODYNELISTENER_H_
#define VELODYNELISTENER_H_

//#include <fstream>
#include <memory>

//#include "opendavinci/odcore/opendavinci.h"
//#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/conference/ContainerObserver.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
//#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"


namespace automotive {

        using namespace std;
        using namespace odcore::wrapper;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class VelodyneListener : public odcore::io::conference::ContainerListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                VelodyneListener(const VelodyneListener&);
                
                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                VelodyneListener& operator=(const VelodyneListener&);
                
        
            public:
                VelodyneListener(std::shared_ptr<SharedMemory>,odcore::io::conference::ContainerConference&);
                //VelodyneListener();
                
                virtual ~VelodyneListener();

                // This method is called by ControlledContainerConferenceFactory to send c to the registered ContainerListener from an app.
                virtual void nextContainer(odcore::data::Container &c);
                
                //void sendSPC(int frame);
                bool getStatus();
                //long getFrameIndex();
                //void freeSpace();
                
            private:
                const float PI=3.1415926;
	            //const uint32_t MAX_POINT_SIZE=125000;
	            const uint32_t MAX_POINT_SIZE=101000;  //The maximum number of points per frame is set based on the observation of the first 100 frames of the pcap file imeangowest.pcap. This upper bound should be set as low as possible, as it affects the shared memory size and thus the frame updating speed.
	            const uint32_t SIZE_PER_COMPONENT = sizeof(float);
	            const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
                const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory?    
                //const int READ_FRAME_NO=150;
                const int LOAD_FRAME_NO=100;
                
                //long packetNr;
                long pointIndex;
                int startID;
                long frameIndex;
                float previousAzimuth;
                bool upperBlock;
                //float distance[32];
                float distance;
                std::shared_ptr<SharedMemory> VelodyneSharedMemory;
                //std::shared_ptr<SharedMemory> frameStore[200];
                float* segment;
                odcore::io::conference::ContainerConference& velodyneFrame;
                odcore::data::SharedPointCloud spc;
                bool stopReading;
                //int pointNumberPerFrame[READ_FRAME_NO];
                float rotCorrection[64];
	            float vertCorrection[64];
	            float distCorrection[64];
	            float vertOffsetCorrection[64];
	            float horizOffsetCorrection[64];                
        };

} // automotive

#endif /*VELODYNELISTENER_H_*/
