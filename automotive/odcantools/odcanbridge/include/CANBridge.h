/**
 * odcanbridge - Tool for bridging between two CAN devices and for
 *               mapping the low-level CAN messages to high-level
 *               C++ data structures and vice-versa.
 * Copyright (C) 2015 Christian Berger
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

#ifndef CANBRIDGE_H_
#define CANBRIDGE_H_

#include <opendavinci/odcore/SharedPointer.h>
#include <stdint.h>
#include <memory>
#include <string>

#include "CANMessageReplicator.h"
#include "canmessagemapping/GeneratedHeaders_CANMessageMapping.h"
#include "GenericCANMessageListener.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"

namespace automotive { class GenericCANMessage; }
namespace odtools { namespace recorder { class Recorder; } }

namespace automotive {
    namespace odcantools {

class CANDevice;

        using namespace std;

        /**
         * This class bridges between two CAN devices and maps GenericCANMessages to high-level C++ messages.
         */
        class CANBridge : public odcore::base::module::TimeTriggeredConferenceClientModule,
                          public GenericCANMessageListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                CANBridge(const CANBridge &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                CANBridge& operator=(const CANBridge &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                CANBridge(const int32_t &argc, char **argv);

                virtual ~CANBridge();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

                virtual void nextGenericCANMessage(const GenericCANMessage &gcm);

            private:
                virtual void setUp();

                virtual void tearDown();

            private:
                odcore::base::FIFOQueue m_fifo;
                unique_ptr<odtools::recorder::Recorder> m_recorder;
                odcore::SharedPointer<CANDevice> m_deviceA;
                string m_deviceNodeA;
                odcore::SharedPointer<CANDevice> m_deviceB;
                string m_deviceNodeB;
                CANMessageReplicator m_replicatorFromAtoB;
                CANMessageReplicator m_replicatorFromBtoA;
                canmapping::CanMapping m_canMapping;
        };

    } // odcantools
} // automotive

#endif /*CANBRIDGE_H_*/
