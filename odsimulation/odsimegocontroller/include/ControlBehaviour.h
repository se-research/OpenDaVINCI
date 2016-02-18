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

#ifndef EGOCONTROLLER_CONTROLBEHAVIOUR_H_
#define EGOCONTROLLER_CONTROLBEHAVIOUR_H_

#include "opendlv/data/environment/EgoState.h"

namespace egocontroller {

    using namespace std;

    class ControlBehaviour
    {
        public:
            ControlBehaviour();
            virtual ~ControlBehaviour();

            virtual void accelerate(const double& value) = 0;
            virtual void brake(const double& value) = 0;
            virtual void turnLeft(const double& value) = 0;
            virtual void turnRight(const double& value) = 0;
            virtual void stop() = 0;

            virtual hesperia::data::environment::EgoState computeEgoState() = 0;
    };
}

#endif // EGOCONTROLLER_CONTROLBEHAVIOUR_H_
