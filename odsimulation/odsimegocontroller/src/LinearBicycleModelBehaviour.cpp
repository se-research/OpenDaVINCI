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

#include "LinearBicycleModelBehaviour.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "opendlv/data/environment/Point3.h"

namespace egocontroller {
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace opendlv::data::environment;
    using namespace opendlv::data::environment;

    LinearBicycleModelBehaviour::LinearBicycleModelBehaviour(const Point3 &translation, const double &rotZ,
        const double &wheelbase, const double &maxSteeringLeftRad, const double &maxSteeringRightRad,
        const double &maxSpeed) :
        m_previousTime(),
        m_oldPosition(translation),
        m_orientation(1,0,0),
        m_angle(rotZ * cartesian::Constants::DEG2RAD),
        m_speed(0.0),
        m_speedInLastCycle(0.0),
        m_wheelbase(wheelbase),
        m_maxSteeringLeftRad(maxSteeringLeftRad),
        m_maxSteeringRightRad(maxSteeringRightRad),
        m_maxSpeed(maxSpeed),
        m_esum(0),
        m_desiredSpeed(0),
        m_desiredAcceleration(0),
        m_desiredSteer(0)
    {}

    LinearBicycleModelBehaviour::~LinearBicycleModelBehaviour()
    {}

    void LinearBicycleModelBehaviour::accelerate(const double& value)
    {
        m_desiredSpeed += value;
    }

    void LinearBicycleModelBehaviour::brake(const double& value)
    {
        m_desiredSpeed -= value;
    }

    void LinearBicycleModelBehaviour::turnLeft(const double& value)
    {
        m_desiredSteer += value;

        if (fabs(m_desiredSteer) > m_maxSteeringLeftRad) {
            m_desiredSteer = (-1)*m_maxSteeringLeftRad;
        }
    }

    void LinearBicycleModelBehaviour::turnRight(const double& value)
    {
        m_desiredSteer -= value;

        if (fabs(m_desiredSteer) > m_maxSteeringRightRad) {
            m_desiredSteer = m_maxSteeringRightRad;
        }
    }

    void LinearBicycleModelBehaviour::stop()
    {
        m_speed = 0.0;
    }

    EgoState LinearBicycleModelBehaviour::computeEgoState() {
        cerr << endl << endl << "m_desiredSpeed = " << m_desiredSpeed << ", m_desiredSteer = " << m_desiredSteer << endl;

        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        double e = (m_desiredSpeed - m_speed);
        if (fabs(e) < 1e-2) {
            m_esum = 0;
        }
        else {
            m_esum += e;
        }
        const double Kp = 0.75;
        const double Ki = 0.2;
        const double p = Kp * e;
        const double i = Ki * timeStep * m_esum;
        const double y = p + i;
        if (fabs(e) < 1e-2) {
            m_desiredAcceleration = 0;
        }
        else {
            m_desiredAcceleration = y;
        }

        double m_deltaSpeed = m_desiredAcceleration * timeStep;

        if (fabs(m_speed + m_deltaSpeed) < m_maxSpeed) {
            m_speed += m_deltaSpeed;
        }

        const double direction = (m_speed < 0) ? -1 : +1; // +1 = forwards, -1 = backwards

        const double invertedSteering = 1.0;
        double m_deltaHeading = fabs(m_speed)/m_wheelbase * tan(invertedSteering * direction * m_desiredSteer) * timeStep;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_angle + m_deltaHeading);
        m_orientation.normalize();

        double xPos = cos(m_angle) * m_speed * timeStep;
        double yPos = sin(m_angle) * m_speed * timeStep;

        m_angle += m_deltaHeading;
        m_angle = fmod(m_angle, 2 * cartesian::Constants::PI);

        Point3 position(m_oldPosition.getX() + xPos, m_oldPosition.getY() + yPos, 0);
        m_oldPosition = position;

        Point3 acceleration;
        Point3 velocity(cos(m_angle) * m_speed * direction,
                        sin(m_angle) * m_speed * direction,
                        0);

        m_previousTime = currentTime;
        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
