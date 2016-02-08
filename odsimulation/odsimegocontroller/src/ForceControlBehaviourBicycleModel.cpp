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

#include "ForceControlBehaviourBicycleModel.h"
#include "automotivedata/generated/cartesian/Constants.h"

namespace egocontroller {
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;

    ForceControlBehaviourBicycleModel::ForceControlBehaviourBicycleModel(
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
            const double &lF,
            const double &lR,
            const double &iM,
            const double &cF,
            const double &cR ) :
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
        m_distanceCenterOfMassToFrontAxle(lF),
        m_distanceCenterOfMassToRearAxle(lR),
        m_inertiaMoment(iM),
        m_skewStiffnessFront(cF),
        m_skewStiffnessRear(cR),
        m_steeringRate(0),
        m_motorForce(0),
        m_brakeForce(0),
        m_adherenceForce(0),
        m_velocity(0),
        m_yawRate(0),
        m_yaw(0),
        m_attitudeAngle(0),
        m_steeringAngle(0),
        m_vehicleDesiredRotationalEffort(0),
        m_vehicleDesiredLinearEffortX(0),
        m_vehicleDesiredResistiveEffortX((idleForce/(KstaticBrake * tauBrake)) + 0.1),
        m_vehicleRotationalEffort(0),
        m_vehicleLinearEffortX(0),
        m_vehicleResistiveEffortX(0),
        m_previousTime(),
        m_oldPosition(),
        m_orientation(1,0,0)
    {}

    ForceControlBehaviourBicycleModel::~ForceControlBehaviourBicycleModel()
    {}

    void ForceControlBehaviourBicycleModel::accelerate(const double& value)
    {
        m_vehicleDesiredLinearEffortX += value;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    void ForceControlBehaviourBicycleModel::brake(const double& value)
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX += value;
    }

    void ForceControlBehaviourBicycleModel::turnLeft(const double &/*value*/)
    {
//        turnRight(value);

        double val = cartesian::Constants::DEG2RAD * 1;
        m_vehicleDesiredRotationalEffort += val;
    }

    void ForceControlBehaviourBicycleModel::turnRight(const double &/*value*/)
    {
        double val = -1 * cartesian::Constants::DEG2RAD * 1;

//        m_vehicleDesiredRotationalEffort += value;
        m_vehicleDesiredRotationalEffort += val;
    }

    void ForceControlBehaviourBicycleModel::stop()
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    EgoState ForceControlBehaviourBicycleModel::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        ////////////////////////////////////////////////////////////////////////
        // Desired inputs.

//        m_steeringRate = m_Ksteering * (m_vehicleDesiredRotationalEffort - m_vehicleRotationalEffort);
//        if (m_steeringRate > m_maximumSteeringRate) {
//            m_steeringRate = m_maximumSteeringRate;
//        }
//        else if (m_steeringRate < (-1 * m_maximumSteeringRate)) {
//            m_steeringRate = -1 * m_maximumSteeringRate;
//        }
//        m_vehicleRotationalEffort += m_steeringRate * timeStep;
//        m_steeringAngle = -1 * m_vehicleRotationalEffort / 100.0 / m_minimumTurningRadius;

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

        if (fabs(m_velocity) < 1e-5) {
            return EgoState(m_oldPosition, m_orientation, Point3(0, 0, 0), Point3(0, 0, 0));
        }

        ////////////////////////////////////////////////////////////////////////

        // Bicycle model.
        double x = timeStep * m_velocity * cos(m_yaw - m_attitudeAngle);
        double y = timeStep * m_velocity * sin(m_yaw - m_attitudeAngle);
        double relativeYawAngle = m_yawRate;

        // Somehow, the sign got lost...
        relativeYawAngle *= ((m_steeringAngle < 0) ? -1 : 1);

        m_yaw = m_yaw + relativeYawAngle;


//        double cAlphaFront = m_steeringAngle - atan2( (m_distanceCenterOfMassToFrontAxle * m_yawRate + m_velocity * sin(m_attitudeAngle)) , (m_velocity * cos(m_attitudeAngle)) );
//        double cAlphaRear = atan2( (m_distanceCenterOfMassToRearAxle * m_yawRate - m_velocity * sin(m_attitudeAngle)) , (m_velocity * cos(m_attitudeAngle)) );
        double cAlphaFront = m_steeringAngle - atan( (m_distanceCenterOfMassToFrontAxle * m_yawRate - m_velocity * sin(m_attitudeAngle)) / (m_velocity * cos(m_attitudeAngle)) );
        double cAlphaRear = atan( (m_distanceCenterOfMassToRearAxle * m_yawRate + m_velocity * sin(m_attitudeAngle)) / (m_velocity * cos(m_attitudeAngle)) );

        // Do approximation.
        double alphaFrontApprox = m_steeringAngle -m_attitudeAngle - m_distanceCenterOfMassToFrontAxle * (m_yawRate/m_velocity);
        double alphaRearApprox = m_distanceCenterOfMassToRearAxle * (m_yawRate / m_velocity) - m_attitudeAngle;

        cAlphaFront = alphaFrontApprox;
        cAlphaRear = alphaRearApprox;

        double yawRate = timeStep * (
                   ( ( (m_skewStiffnessRear*cAlphaRear*m_distanceCenterOfMassToRearAxle - m_skewStiffnessFront*cAlphaFront*m_distanceCenterOfMassToFrontAxle) / m_inertiaMoment ) * m_attitudeAngle )
                 - ( ( ( (m_skewStiffnessRear*cAlphaRear * m_distanceCenterOfMassToRearAxle * m_distanceCenterOfMassToRearAxle)
                        +(m_skewStiffnessFront*cAlphaFront * m_distanceCenterOfMassToFrontAxle * m_distanceCenterOfMassToFrontAxle) ) / (m_inertiaMoment * m_velocity) ) * m_yawRate )
                 + ( ( (m_skewStiffnessFront*cAlphaFront * m_distanceCenterOfMassToFrontAxle) / m_inertiaMoment) * m_steeringAngle)
                );

        double attitudeAngle = timeStep * (
                    ( -1 * ( (m_skewStiffnessFront*cAlphaFront + m_skewStiffnessRear*cAlphaRear) / (m_vehicleMass * m_velocity) ) * m_attitudeAngle )
                    + ( ( ( (m_skewStiffnessRear*cAlphaRear*m_distanceCenterOfMassToRearAxle - m_skewStiffnessFront*cAlphaFront*m_distanceCenterOfMassToFrontAxle) / (m_vehicleMass * m_velocity * m_velocity) ) - 1) * m_yawRate)
                    + ( (m_skewStiffnessFront*cAlphaFront / (m_vehicleMass * m_velocity)) * m_steeringAngle )
                    );

        attitudeAngle = timeStep * (
                -1 * m_steeringAngle / 100.0 / m_minimumTurningRadius
                );

        m_yawRate = yawRate;
        m_attitudeAngle = attitudeAngle;

        if (m_vehicleDesiredRotationalEffort > 0.5) {
            m_vehicleDesiredRotationalEffort = 0.5;
        }
        if (m_vehicleDesiredRotationalEffort < -0.5) {
            m_vehicleDesiredRotationalEffort = -0.5;
        }

        m_steeringAngle = timeStep * (m_vehicleDesiredRotationalEffort - m_steeringAngle);
//        m_steeringAngle = m_vehicleDesiredRotationalEffort;

        cerr << "X: " << x << ", Y: " << y << ", cAF: " << cAlphaFront << ", cAR: " << cAlphaRear << ", m_yaw = " << m_yaw << ", m_yawRate = " << m_yawRate << ", m_attitudeAngle = " << m_attitudeAngle << ", m_steeringRate: " << m_steeringRate << ", m_steeringAngle: " << m_steeringAngle << ", desiredRot: " << m_vehicleDesiredRotationalEffort << endl;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_yaw);
        m_orientation.normalize();

        Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
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
