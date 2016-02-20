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

#include <cmath>
#include <iostream>

#include "ForceControlBehaviourSimplifiedBicycleModel.h"
#include "automotivedata/generated/cartesian/Constants.h"

namespace egocontroller {
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace opendlv::data::environment;
    using namespace opendlv::data::environment;

    ForceControlBehaviourSimplifiedBicycleModel::ForceControlBehaviourSimplifiedBicycleModel(
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
            const double &l ) :
        m_minimumTurningRadius(minimumTurningRadius),
        m_vehicleMass(vehicleMass),
        m_adherenceCoefficient(adherenceCoefficient),
        m_idleForce(idleForce),
        m_Ksteering(Ksteering),
        m_maximumSteeringRate(maximumSteeringRate),
        m_Kthrottle(Kthrottle),
        m_tauBrake(tauBrake),
        m_KstaticBrake(KstaticBrake),
        m_KdynamicBrake(KdynamicBrake),
        m_length(l),
        m_steeringRate(0),
        m_motorForce(0),
        m_brakeForce(0),
        m_adherenceForce(0),
        m_velocity(0),
        m_yaw(0),
        m_steeringAngle(0),
        m_vehicleDesiredSteeringAngle(0),
        m_vehicleSteeringAngle(0),
        m_vehicleDesiredLinearEffortX(0),
        m_vehicleDesiredResistiveEffortX((idleForce/(KstaticBrake * tauBrake)) + 0.1),
        m_vehicleLinearEffortX(0),
        m_vehicleResistiveEffortX(0),
        m_previousTime(),
        m_oldPosition(),
        m_orientation(1,0,0)
    {}

    ForceControlBehaviourSimplifiedBicycleModel::~ForceControlBehaviourSimplifiedBicycleModel()
    {}

    void ForceControlBehaviourSimplifiedBicycleModel::accelerate(const double& value)
    {
        m_vehicleDesiredLinearEffortX += value;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    void ForceControlBehaviourSimplifiedBicycleModel::brake(const double& value)
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX += value;
    }

    void ForceControlBehaviourSimplifiedBicycleModel::turnLeft(const double &/*value*/)
    {
        const double value = cartesian::Constants::DEG2RAD * 1;
        const double MAX_STEERING_WHEEL_ANGLE = 0.3;
        if (m_vehicleDesiredSteeringAngle < MAX_STEERING_WHEEL_ANGLE) {
            m_vehicleDesiredSteeringAngle += value;
        }
    }

    void ForceControlBehaviourSimplifiedBicycleModel::turnRight(const double &/*value*/)
    {
        const double value = cartesian::Constants::DEG2RAD * 1;
        const double MIN_STEERING_WHEEL_ANGLE = -0.3;
        if (m_vehicleDesiredSteeringAngle > MIN_STEERING_WHEEL_ANGLE) {
            m_vehicleDesiredSteeringAngle -= value;
        }
    }

    void ForceControlBehaviourSimplifiedBicycleModel::stop()
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    EgoState ForceControlBehaviourSimplifiedBicycleModel::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        ////////////////////////////////////////////////////////////////////////
        // Longitudinal input.

        m_vehicleLinearEffortX = m_vehicleDesiredLinearEffortX;
        m_motorForce = m_Kthrottle * m_vehicleLinearEffortX + m_idleForce;

        m_vehicleResistiveEffortX += m_tauBrake * (m_vehicleDesiredResistiveEffortX - m_vehicleResistiveEffortX);
        if (m_velocity < 5e-3) {
            m_brakeForce = m_KstaticBrake * m_vehicleResistiveEffortX;

            if (m_brakeForce > m_motorForce) {
                m_brakeForce = m_motorForce + 1.0;
            }
        }
        else {
            m_brakeForce = m_KdynamicBrake * m_vehicleResistiveEffortX;
        }
        m_adherenceForce = m_adherenceCoefficient * m_velocity * m_velocity;

        m_velocity += (m_motorForce - m_brakeForce - m_adherenceForce) / m_vehicleMass * timeStep;

        if (m_velocity < 0) {
            m_velocity = 0;
        }

        ////////////////////////////////////////////////////////////////////////

        // Simplified bicycle model.
        m_steeringRate = (m_vehicleDesiredSteeringAngle - m_steeringAngle);
        double relativeSteeringAngle = timeStep * m_steeringRate;
        m_steeringAngle = m_steeringAngle + relativeSteeringAngle;

        double relativeX = timeStep * m_velocity * cos(m_yaw);
        double relativeY = timeStep * m_velocity * sin(m_yaw);
        double relativeYaw = timeStep * (1/m_length) * tan(m_steeringAngle) * m_velocity;

        m_yaw = m_yaw + relativeYaw;

        cerr << "X: " << relativeX << ", Y: " << relativeY << ", relYaw: " << relativeYaw << ", relSteeringAngle: " << relativeSteeringAngle << ", yaw: " << m_yaw << "velocity: " << m_velocity << ", m_steeringRate: " << m_steeringRate << ", m_steeringAngle: " << m_steeringAngle << ", desiredAngle: " << m_vehicleDesiredSteeringAngle << endl;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_yaw);
        m_orientation.normalize();

        Point3 position(m_oldPosition.getX() + relativeX, m_oldPosition.getY() + relativeY, 0);
        m_oldPosition = position;

        // Set velocity.
        Point3 velocity(cos(m_yaw) * m_velocity,
                        sin(m_yaw) * m_velocity,
                        0);

        Point3 acceleration;

        m_previousTime = currentTime;
        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
