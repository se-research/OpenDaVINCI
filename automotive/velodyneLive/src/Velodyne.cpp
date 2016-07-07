/**
 * velodyne is an example application to demonstrate how to 
 *              decode Velodyne data realized
 *              with OpenDaVINCI
 * Copyright (C) 2016 Christian Berger and Hang Yin
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

#include "Velodyne.h"


namespace automotive {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::wrapper;
        using namespace automotive;
        using namespace odcore::base::module;
        using namespace odcore::io::udp;

        VelodyneDecoder::VelodyneDecoder(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "VelodyneDecoder"),
            m_pcap(),
            VelodyneSharedMemory(SharedMemoryFactory::createSharedMemory(NAME, SIZE)),
            m_vListener(VelodyneSharedMemory,getConference()),
            udpreceiver(UDPFactory::createUDPReceiver(RECEIVER, PORT)),
            handler(m_pcap),
            rfb(){}

        VelodyneDecoder::~VelodyneDecoder() {}

        void VelodyneDecoder::setUp() {
            m_pcap.setContainerListener(&m_vListener);
            udpreceiver->setStringListener(&handler);
            // Start receiving bytes.
            udpreceiver->start();
        }

        void VelodyneDecoder::tearDown() {
            udpreceiver->stop();
            udpreceiver->setStringListener(NULL);
        }

        // This method will do the main data processing job.
        //While running this module, adjust the frequency to get desired frame rate of the replay. For instance, for an input date rate 3*10⁶Bps, 30Hz gives a good frame rate
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode VelodyneDecoder::body() {
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING){
                /*while(!handler.getBuffer().empty()){
                    rfb.lock();
                    m_pcap.nextString(handler.getBuffer());
                    handler.clearBuffer();
                    rfb.unlock();
                }*/
                while(handler.getBuffer().size()>CONSUME){
                    rfb.lock();
                    m_pcap.nextString(handler.getBuffer().substr(0,CONSUME));
                    handler.consume(CONSUME);
                    rfb.unlock();
                } 
            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
} // automotive

