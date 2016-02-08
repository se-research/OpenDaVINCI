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

#include "SimpleControlBehaviour.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "hesperia/data/environment/Point3.h"

namespace egocontroller {
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;

    SimpleControlBehaviour::SimpleControlBehaviour(const Point3 &translation, const double &rotZ) :
        m_previousTime(),
        m_oldPosition(translation),
        m_orientation(1,0,0),
        m_angle(rotZ * cartesian::Constants::DEG2RAD),
        m_speed(0.0),
        m_speedInLastCycle(0.0)
    {}

    SimpleControlBehaviour::~SimpleControlBehaviour()
    {}

    void SimpleControlBehaviour::accelerate(const double& value)
    {
        m_speed += value;
    }

    void SimpleControlBehaviour::brake(const double& value)
    {
        m_speed -= value;
    }

    void SimpleControlBehaviour::turnLeft(const double& value)
    {
        m_angle += value;
    }

    void SimpleControlBehaviour::turnRight(const double& value)
    {
        m_angle -= value;
    }

    void SimpleControlBehaviour::stop()
    {
        m_speed = 0.0;
    }

    EgoState SimpleControlBehaviour::computeEgoState() {
        //TimeStamp currentTime;
        //double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_angle);
        m_orientation.normalize();

        //Point3 position( m_oldPosition + (m_orientation * distanceToMove));
        Point3 position( m_oldPosition + (m_orientation*m_speed));

        // Set velocity.
        Point3 velocity(m_orientation.getX() * m_speed,
                        m_orientation.getY() * m_speed,
                        0);

        // Set acceleration.
//        double accelerationBase = (m_speed - m_speedInLastCycle) / diff;
//        accelerationBase = (fabs(accelerationBase) < 1e-5) ? 0 : accelerationBase;
//
//        Point3 acceleration(m_orientation.getX() * accelerationBase,
//                            m_orientation.getY() * accelerationBase,
//                            0);
        Point3 acceleration;
        m_speedInLastCycle = m_speed;
        m_oldPosition = position;

        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
