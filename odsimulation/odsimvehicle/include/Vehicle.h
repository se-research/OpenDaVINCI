/**
 * vehicle - Vehicle dynamics (part of simulation environment)
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

#ifndef VEHICLE_H_
#define VEHICLE_H_

#include "core/base/module/TimeTriggeredConferenceClientModule.h"

namespace vehicle {

    using namespace std;

    /**
     * This class encapsulates the vehicle.
     */
    class Vehicle : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Vehicle(const Vehicle &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Vehicle& operator=(const Vehicle &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Vehicle(const int32_t &argc, char **argv);

            virtual ~Vehicle();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runLinearBicycleModel();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runLinearBicycleModelNew(const bool &withSpeedController);
    };

} // vehicle

#endif /*VEHICLE_H_*/
