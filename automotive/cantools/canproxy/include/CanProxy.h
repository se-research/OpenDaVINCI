/**
 * canproxy - Tool wrapping a CAN interface.
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

#ifndef CANPROXY_H_
#define CANPROXY_H_

#include <libpcan.h>

#include "core/base/FIFOQueue.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "tools/recorder/Recorder.h"

#include "GenericCANMessageListener.h"

namespace automotive {

    using namespace std;

    /**
     * This class wraps a CAN device node to wrap low-level CAN messages into GenericCANMessages.
     */
    class CanProxy : public core::base::module::TimeTriggeredConferenceClientModule,
                     public GenericCANMessageListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            CanProxy(const CanProxy &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            CanProxy& operator=(const CanProxy &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            CanProxy(const int32_t &argc, char **argv);

            virtual ~CanProxy();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            virtual void nextGenericCANMessage(const GenericCANMessage &gcm);

        private:
            virtual void setUp();

            virtual void tearDown();

        private:
            core::base::FIFOQueue m_fifo;
            auto_ptr<tools::recorder::Recorder> m_recorder;
            string m_deviceNode;
            HANDLE m_handle;
    };

} // automotive

#endif /*CANPROXY_H_*/
