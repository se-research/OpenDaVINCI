/**
 * odrecorder - Tool for recording data
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
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

#ifndef RECORDERMODULE_H_
#define RECORDERMODULE_H_

#include "core/opendavinci.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace odrecorder {

    using namespace std;

    /**
     * This class can be used to record data distributed
     * using a conference.
     */
    class RecorderModule : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecorderModule(const RecorderModule &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecorderModule& operator=(const RecorderModule &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            RecorderModule(const int32_t &argc, char **argv);

            virtual ~RecorderModule();

            virtual void wait();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

} // odrecorder

#endif /*RECORDERMODULE_H_*/
