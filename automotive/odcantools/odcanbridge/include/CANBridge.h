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

#include <core/SharedPointer.h>
#include "core/base/FIFOQueue.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "tools/recorder/Recorder.h"

#include "GenericCANMessageListener.h"
#include "CANDevice.h"
#include "CANMessageReplicator.h"
#include "DataMapper.h"

namespace automotive {

    using namespace std;

    /**
     * This class bridges between two CAN devices and maps GenericCANMessages to high-level C++ messages.
     */
    class CANBridge : public core::base::module::TimeTriggeredConferenceClientModule,
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

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            virtual void nextGenericCANMessage(const GenericCANMessage &gcm);

        private:
            virtual void setUp();

            virtual void tearDown();

        private:
            core::base::FIFOQueue m_fifo;
            auto_ptr<tools::recorder::Recorder> m_recorder;
            core::SharedPointer<CANDevice> m_deviceA;
            string m_deviceNodeA;
            core::SharedPointer<CANDevice> m_deviceB;
            string m_deviceNodeB;
            CANMessageReplicator m_replicatorFromAtoB;
            CANMessageReplicator m_replicatorFromBtoA;
            DataMapper m_dataMapper;
    };

} // automotive

#endif /*CANBRIDGE_H_*/
