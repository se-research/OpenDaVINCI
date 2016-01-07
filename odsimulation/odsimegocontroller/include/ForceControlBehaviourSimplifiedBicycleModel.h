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

#ifndef EGOCONTROLLER_FORCECONTROLBEHAVIOURSIMPLIFIEDBICYCLEMODEL_H_
#define EGOCONTROLLER_FORCECONTROLBEHAVIOURSIMPLIFIEDBICYCLEMODEL_H_

#include "ControlBehaviour.h"
#include "core/data/TimeStamp.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Point3.h"

namespace egocontroller {

    using namespace std;

    class ForceControlBehaviourSimplifiedBicycleModel : public ControlBehaviour
    {
        public:
            ForceControlBehaviourSimplifiedBicycleModel(
                    const double& minimumTurningRadius,
                    const double& vehicleMass,
                    const double& adherenceCoefficient,
                    const double& idleForce,
                    const double& Ksteering,
                    const double& maximumSteeringRate,
                    const double& Kthrottle,
                    const double& tauBrake,
                    const double& KstaticBrake,
                    const double& KdynamicBrake,
                    const double &l);
            virtual ~ForceControlBehaviourSimplifiedBicycleModel();

            virtual void accelerate(const double& value);
            virtual void brake(const double& value);
            virtual void turnLeft(const double& value);
            virtual void turnRight(const double& value);
            virtual void stop();
            virtual hesperia::data::environment::EgoState computeEgoState();

        protected:
            double m_minimumTurningRadius;
            double m_vehicleMass;
            double m_adherenceCoefficient;
            double m_idleForce;
            double m_Ksteering;
            double m_maximumSteeringRate;
            double m_Kthrottle;
            double m_tauBrake;
            double m_KstaticBrake;
            double m_KdynamicBrake;
            double m_length;

            double m_steeringRate;
            double m_motorForce;
            double m_brakeForce;
            double m_adherenceForce;
            double m_velocity;

            double m_yaw;
            double m_steeringAngle;

            double m_vehicleDesiredSteeringAngle;
            double m_vehicleSteeringAngle;

            double m_vehicleDesiredLinearEffortX;
            double m_vehicleDesiredResistiveEffortX;

            double m_vehicleLinearEffortX;
            double m_vehicleResistiveEffortX;

            core::data::TimeStamp m_previousTime;
            hesperia::data::environment::Point3 m_oldPosition;
            hesperia::data::environment::Point3 m_orientation;
    };
}

#endif // EGOCONTROLLER_FORCECONTROLBEHAVIOURSIMPLIFIEDBICYCLEMODEL_H_
