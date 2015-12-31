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

#ifndef VEHICLE_LINEARBICYCLEMODELNEW_H_
#define VEHICLE_LINEARBICYCLEMODELNEW_H_

#include <stdint.h>

#include "core/data/TimeStamp.h"
#include "generated/automotive/VehicleData.h"
#include "generated/cartesian/Point2.h"
#include "hesperia/data/environment/EgoState.h"

namespace core { namespace base { class KeyValueConfiguration; } }

namespace vehicle {

    using namespace std;

    class LinearBicycleModelNew {
        public:
            LinearBicycleModelNew(const core::base::KeyValueConfiguration &kvc, const bool &useSpeedController);
            virtual ~LinearBicycleModelNew();

            void accelerate(const double& value);
            void speed(const double& value);
            void steer(const double& value);

            virtual hesperia::data::environment::EgoState computeEgoState();

            automotive::VehicleData getVehicleData() const;

        protected:
            double m_wheelbase;
            double m_maxSteeringLeftRad;
            double m_maxSteeringRightRad;
            int32_t m_invertedSteering;
            double m_maxSpeed;
            bool m_useSpeedControl;
            double m_esum;
            double m_desiredSpeed;
            double m_desiredAcceleration;
            double m_desiredSteer;
            double m_speed;
            core::data::TimeStamp m_previousTime;
            float m_oldPositionData[2];
            float m_orientationData[2];
            cartesian::Point2 m_oldPosition;
            cartesian::Point2 m_orientation;
            double m_heading;
            automotive::VehicleData m_vehicleData;
    };
}

#endif // VEHICLE_LINEARBICYCLEMODELNEW_H_
