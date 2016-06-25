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

#ifndef VELODYNE_H_
#define VELODYNE_H_

#include <fstream>
#include <memory>

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
//#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include "PCAPProtocol.h"
#include "velodyneListener.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
//#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"

namespace automotive {

        using namespace std;
        using namespace odcore::wrapper;
        using namespace odcore::base::module;
        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class VelodyneDecoder : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                VelodyneDecoder(const VelodyneDecoder &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                VelodyneDecoder& operator=(const VelodyneDecoder &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                VelodyneDecoder(const int32_t &argc, char **argv);

                virtual ~VelodyneDecoder();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();
                const std::string NAME = "pointCloud";
                //const uint32_t MAX_POINT_SIZE=125000;
                const uint32_t MAX_POINT_SIZE=101000;  //The maximum number of points per frame is set based on the observation of the first 100 frames of the pcap file imeangowest.pcap. This upper bound should be set as low as possible, as it affects the shared memory size and thus the frame updating speed.
                const uint8_t NUMBER_OF_COMPONENTS_PER_POINT = 4; // How many components do we have per vector?
                const uint32_t SIZE_PER_COMPONENT = sizeof(float);
                const uint32_t SIZE = MAX_POINT_SIZE * NUMBER_OF_COMPONENTS_PER_POINT * SIZE_PER_COMPONENT; // What is the total size of the shared memory? 
                const uint32_t BUFFER_SIZE=4000;
                
                odcore::io::protocol::PCAPProtocol m_pcap;
                fstream lidarStream;
                std::shared_ptr<SharedMemory> VelodyneSharedMemory;
                VelodyneListener m_vListener;
                bool fileClosed;
                //bool frameSent;
                //int counter;      
        };

} // automotive

#endif /*VELODYNE_H_*/
