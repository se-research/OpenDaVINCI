/**
 * velodyne16pcap is a program that reads VLP-16 data in .pcap format and 
 * sends out the decoded data as 3D shared point cloud, including x, y, z, and intensity (all float)
 *              with OpenDaVINCI
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

#ifndef VELODYNE16PCAP_H_
#define VELODYNE16PCAP_H_

#include <fstream>
#include <memory>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include "velodyneListener16.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace automotive {

        using namespace std;
        using namespace odcore::wrapper;
        using namespace odcore::base::module;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class VelodyneDecoder16pcap : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                VelodyneDecoder16pcap(const VelodyneDecoder16pcap &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                VelodyneDecoder16pcap& operator=(const VelodyneDecoder16pcap &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                VelodyneDecoder16pcap(const int32_t &argc, char **argv);

                virtual ~VelodyneDecoder16pcap();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();
                //const std::string NAME = "pointCloud";
                //const uint32_t MAX_POINT_SIZE=30000;  // The maximum number of points per frame is set based on the observation of the first 100 frames of a sample pcap file. This upper bound should be set as low as possible, as it affects the shared memory size and thus the frame updating speed.
                //const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
                //const uint32_t SIZE_PER_COMPONENT = sizeof(float);
                //const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory? 
                const uint32_t BUFFER_SIZE=2000;
                
                odcore::io::protocol::PCAPProtocol m_pcap;
                fstream lidarStream;
                //std::shared_ptr<SharedMemory> VelodyneSharedMemory;
                //VelodyneListener16 m_vListener;
                bool fileClosed;   
                uint8_t counter; //Used to tune the pcap file reading speed
        };

} // automotive

#endif /*VELODYNE16PCAP_H_*/
