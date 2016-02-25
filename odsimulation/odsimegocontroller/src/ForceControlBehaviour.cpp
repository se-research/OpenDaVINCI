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

#include "ForceControlBehaviour.h"
#include "automotivedata/generated/cartesian/Constants.h"

namespace egocontroller {
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace opendlv::data::environment;
    using namespace opendlv::data::environment;

    ForceControlBehaviour::ForceControlBehaviour(
            const double& minimumTurningRadius,
            const double& vehicleMass,
            const double& adherenceCoefficient,
            const double& idleForce,
            const double& Ksteering,
            const double& maximumSteeringRate,
            const double& Kthrottle,
            const double& tauBrake,
            const double& KstaticBrake,
            const double& KdynamicBrake ) :
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
        m_steeringRate(0.0),
        m_motorForce(0.0),
        m_brakeForce(0.0),
        m_adherenceForce(0.0),
        m_turningCurvature(0.0),
        m_deltaHeading(0.0),
        m_vehicleDesiredRotationalEffort(0.0),
        m_vehicleDesiredLinearEffortX(0.0),
        m_vehicleDesiredResistiveEffortX((idleForce/(KstaticBrake * tauBrake)) + 0.1),
        m_vehicleRotationalEffort(0.0),
        m_vehicleLinearEffortX(0.0),
        m_vehicleResistiveEffortX(0.0),
        m_speed(0),
        m_heading(0),
        m_previousTime(),
        m_oldPosition(),
        m_orientation(1,0,0)
    {}

    ForceControlBehaviour::~ForceControlBehaviour()
    {}

    void ForceControlBehaviour::accelerate(const double& value)
    {
        m_vehicleDesiredLinearEffortX = value;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    void ForceControlBehaviour::brake(const double& value)
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX = value;
    }

    void ForceControlBehaviour::turnLeft(const double &value)
    {
        turnRight(-value);
    }

    void ForceControlBehaviour::turnRight(const double &value)
    {
        m_vehicleDesiredRotationalEffort = value;
    }

    void ForceControlBehaviour::stop()
    {
        m_vehicleDesiredLinearEffortX = 0;
        m_vehicleDesiredResistiveEffortX = 0;
    }

    EgoState ForceControlBehaviour::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        m_steeringRate = m_Ksteering * (m_vehicleDesiredRotationalEffort - m_vehicleRotationalEffort);
        if (m_steeringRate > m_maximumSteeringRate) {
            m_steeringRate = m_maximumSteeringRate;
        }
        else if (m_steeringRate < (-1 * m_maximumSteeringRate)) {
            m_steeringRate = -1 * m_maximumSteeringRate;
        }
        m_vehicleRotationalEffort += m_steeringRate * timeStep;
        m_turningCurvature = -1 * m_vehicleRotationalEffort / 100.0 / m_minimumTurningRadius;

        m_vehicleLinearEffortX = m_vehicleDesiredLinearEffortX;
        m_motorForce = m_Kthrottle * m_vehicleLinearEffortX + m_idleForce;

        m_vehicleResistiveEffortX += m_tauBrake * (m_vehicleDesiredResistiveEffortX - m_vehicleResistiveEffortX);
        if (m_speed < 5e-3) {
            m_brakeForce = m_KstaticBrake * m_vehicleResistiveEffortX;

            if (m_brakeForce > m_motorForce) {
                m_brakeForce = m_motorForce + 1.0;
            }
        }
        else {
            m_brakeForce = m_KdynamicBrake * m_vehicleResistiveEffortX;
        }
        m_adherenceForce = m_adherenceCoefficient * m_speed * m_speed;

        m_speed += (m_motorForce - m_brakeForce - m_adherenceForce) / m_vehicleMass * timeStep;

        if (m_speed < 0) {
            m_speed = 0;
        }

        m_deltaHeading = m_turningCurvature * m_speed * timeStep;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_heading + m_deltaHeading/2.0);
        m_orientation.normalize();

        double x = cos(m_heading + m_deltaHeading/2.0) * m_speed * timeStep;
        double y = sin(m_heading + m_deltaHeading/2.0) * m_speed * timeStep;

        m_heading += m_deltaHeading;
        m_heading = fmod(m_heading, 2 * cartesian::Constants::PI);

        Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
        m_oldPosition = position;

        // Set velocity.
        Point3 velocity(cos(m_heading + m_deltaHeading/2.0) * m_speed,
                        sin(m_heading + m_deltaHeading/2.0) * m_speed,
                        0);

        Point3 acceleration;

        m_previousTime = currentTime;
        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
