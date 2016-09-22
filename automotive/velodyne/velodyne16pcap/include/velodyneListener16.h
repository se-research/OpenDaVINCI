/**
 * velodyneListener16 is used to decode VLP-16 data realized with OpenDaVINCI
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

#ifndef VELODYNELISTENER16_H_
#define VELODYNELISTENER16_H_

#include <memory>

#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/conference/ContainerObserver.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"
#include "automotivedata/generated/cartesian/Constants.h"

namespace automotive {

        using namespace std;
        using namespace odcore::wrapper;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class VelodyneListener16 : public odcore::io::conference::ContainerListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                VelodyneListener16(const VelodyneListener16&);
                
                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                VelodyneListener16& operator=(const VelodyneListener16&);
                
        
            public:
                VelodyneListener16(std::shared_ptr<SharedMemory>,odcore::io::conference::ContainerConference&);
                
                virtual ~VelodyneListener16();

                // This method is called by ControlledContainerConferenceFactory to send c to the registered ContainerListener from an app.
                virtual void nextContainer(odcore::data::Container &c);
                
                bool getStatus();
                
            private:
                const uint32_t MAX_POINT_SIZE=30000;  // The maximum number of points per frame is set based on the observation of the first 100 frames of a sample pcap file. This upper bound should be set as low as possible, as it affects the shared memory size and thus the frame updating speed.
                const uint32_t SIZE_PER_COMPONENT = sizeof(float);
                const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
                const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory?    
                const int32_t LOAD_FRAME_NO=100;
                const uint8_t NO_OF_CHANNELS=16; 
                
                long pointIndex;
                long startID;
                long frameIndex;
                float previousAzimuth;
                float deltaAzimuth;
                float distance;
                std::shared_ptr<SharedMemory> VelodyneSharedMemory;//shared memory for the shared point cloud
                float* segment;//temporary memory for transferring data of each frame to the shared memory
                odcore::io::conference::ContainerConference& velodyneFrame;
                odcore::data::SharedPointCloud spc;//shared point cloud
                bool stopReading;//a flag to determine when to stop reading a pcap file
                float vertCorrection[16];  //Vertal angle of each sensor beam    
        };

} // automotive

#endif /*VELODYNELISTENER16_H_*/
