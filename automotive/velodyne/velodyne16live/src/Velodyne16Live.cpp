/**
 * velodyne16live is a program that reads VLP-16 live data and sends out
 * the decoded data as 3D shared point cloud, including x, y, z, and intensity (all float)
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
#include <memory>

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/odcore/base/Lock.h"

#include "Velodyne16Live.h"


namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::wrapper;
        using namespace automotive;
        using namespace odcore::base::module;
        using namespace odcore::io::udp;

        VelodyneDecoder16Live::VelodyneDecoder16Live(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "VelodyneDecoder16Live"),
            m_pcap(),
            VelodyneSharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE)),
            m_vListener(VelodyneSharedMemory,getConference()),
            udpreceiver(UDPFactory::createUDPReceiver(RECEIVER, PORT)),
            handler(m_pcap),
            rfb(){}

        VelodyneDecoder16Live::~VelodyneDecoder16Live() {}

        void VelodyneDecoder16Live::setUp() {
            m_pcap.setContainerListener(&m_vListener);
            udpreceiver->setStringListener(&handler);
            // Start receiving bytes.
            udpreceiver->start();
        }

        void VelodyneDecoder16Live::tearDown() {
            udpreceiver->stop();
            udpreceiver->setStringListener(NULL);
        }

        // This method will do the main data processing job.
        //While running this module, adjust the frequency to get desired frame rate of the replay. Note that too low frame rate may lead to buffer overflow!
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode VelodyneDecoder16Live::body() {
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                while(handler.getBuffer().size()>CONSUME){
                    odcore::base::Lock l(rfb);
                    m_pcap.nextString(handler.getBuffer().substr(0,CONSUME));
                    handler.consume(CONSUME);
                } 
            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

