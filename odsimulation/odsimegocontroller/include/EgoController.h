/**
 * egocontroller - Manual control of the vehicle (part of simulation environment)
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

#ifndef EGOCONTROLLER_H_
#define EGOCONTROLLER_H_

#include <string>

#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace egocontroller {

class ForceControlBehaviour;
class ForceControlBehaviourBicycleModel;
class ForceControlBehaviourSimplifiedBicycleModel;
class LinearBicycleModelBehaviour;

    using namespace std;

    /**
     * This class is the camera server providing new camera images.
     */
    class EgoController : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            EgoController(const EgoController &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            EgoController& operator=(const EgoController &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            EgoController(const int &argc, char **argv);

            virtual ~EgoController();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            string m_device;

            ForceControlBehaviour* createForceControlBehaviour();

            ForceControlBehaviourBicycleModel* createForceControlBehaviourBicycleModel();

            ForceControlBehaviourSimplifiedBicycleModel* createForceControlBehaviourSimplifiedBicycleModel();

            LinearBicycleModelBehaviour* createLinearBicycleModelBehaviour();

            virtual void setUp();

            virtual void tearDown();
    };

} // egocontroller

#endif /*EGOCONTROLLER_H_*/
