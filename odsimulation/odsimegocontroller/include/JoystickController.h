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

#ifndef EGOCONTROLLER_JOYSTICKCONTROLLER_H_
#define EGOCONTROLLER_JOYSTICKCONTROLLER_H_

#include <string>

#include "Controller.h"
#include "hesperia/data/environment/EgoState.h"

namespace egocontroller {

class ControlBehaviour;

    using namespace std;

    class JoystickController : public Controller
    {
        public:
            JoystickController(ControlBehaviour& m_behaviour, const string& device);
            virtual ~JoystickController();

            void doWork();
            hesperia::data::environment::EgoState getEgoState();

        protected:
            ControlBehaviour& m_behaviour;
            double MAX;
            double FACTOR_ACCELERATION;
            double FACTOR_ROTATION;

            int m_joy_fd;
            int* m_axes;
            double m_lastAxis0;
            double m_lastAxis1;

        private:
            JoystickController(const JoystickController&);
            JoystickController& operator=(const JoystickController&);
    };
}

#endif // EGOCONTROLLER_CONTROLLER_H_
