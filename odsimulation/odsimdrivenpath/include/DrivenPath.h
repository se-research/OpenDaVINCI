/**
 * drivenpath - Export driven path (part of simulation environment)
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef DRIVENPATH_H_
#define DRIVENPATH_H_

#include <stdint.h>

#include "opendavinci/core/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace measurements {

    using namespace std;

    /**
     * This class encapsulates the a measurement module to measure the driven vs. the optimal path.
     */
    class DrivenPath : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            DrivenPath(const DrivenPath &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            DrivenPath& operator=(const DrivenPath &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            DrivenPath(const int32_t &argc, char **argv);

            virtual ~DrivenPath();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
    };

} // measurements

#endif /*DRIVENPATH_H_*/
