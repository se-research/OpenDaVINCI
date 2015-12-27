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

#include <iostream>

#include "core/platform.h"

#include "core/wrapper/Eigen.h"

#include "LinearBicycleModelNew.h"

namespace vehicle {

    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data;
    using namespace hesperia::data::environment;

    LinearBicycleModelNew::LinearBicycleModelNew(const KeyValueConfiguration &kvc, const bool &useSpeedController) :
        m_wheelbase(1),
        m_maxSteeringLeftRad(0),
        m_maxSteeringRightRad(0),
        m_invertedSteering(0),
        m_maxSpeed(0),
        m_useSpeedControl(useSpeedController),
        m_esum(0),
        m_desiredSpeed(0),
        m_desiredAcceleration(0),
        m_desiredSteer(0),
        m_speed(0),
        m_previousTime(),
        m_oldPositionData(),
        m_orientationData(),
        m_oldPosition(),
        m_orientation(),
        m_heading(0),
        m_vehicleData()
    {
        m_oldPositionData[0] = kvc.getValue<double>("odsimvehicle.posX");
        m_oldPositionData[1] = kvc.getValue<double>("odsimvehicle.posY");

        m_orientationData[0] = 0;
        m_orientationData[1] = 0;

        m_oldPosition.getP()[0] = kvc.getValue<double>("odsimvehicle.posX");
        m_oldPosition.getP()[1] = kvc.getValue<double>("odsimvehicle.posY");

        m_orientation.getP()[0] = 0;
        m_orientation.getP()[1] = 0;

        // Setup initial position.
        m_heading = cartesian::Constants::DEG2RAD * kvc.getValue<double>("odsimvehicle.headingDEG");

        // Calculate maximum steering wheel angles to left and right.
        m_wheelbase = kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.wheelbase");
        m_maxSteeringLeftRad = atan(m_wheelbase/kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusLeft") );
        m_maxSteeringRightRad = atan(m_wheelbase/kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusRight"));

        m_invertedSteering = (kvc.getValue<int32_t>("odsimvehicle.LinearBicycleModelNew.invertedSteering") == 0) ? -1 : 1;
        m_maxSpeed = fabs(kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.maxspeed"));

        cerr << "max turning wheel angle to the left: " << m_maxSteeringLeftRad << endl;
        cerr << "max turning wheel angle to the right: " << m_maxSteeringRightRad << endl;
        cerr << "inverted steering: " << m_invertedSteering << endl;

        // Initialize random number generator.
        srand(10);
    }

    LinearBicycleModelNew::~LinearBicycleModelNew() {}

    void LinearBicycleModelNew::accelerate(const double &a) {
        m_desiredAcceleration = a;
    }

    void LinearBicycleModelNew::speed(const double &s) {
        m_desiredSpeed = s;
    }

    void LinearBicycleModelNew::steer(const double &s) {
        if (s < 0) {
            // Steer to the left is assumed to be negative (inverting is done below).
            if (fabs(s) > m_maxSteeringLeftRad) {
                m_desiredSteer = (-1)*m_maxSteeringLeftRad;
            }
            else {
                m_desiredSteer = s;
            }
        }
        else {
            // Steer to the right.
            if (s > m_maxSteeringRightRad) {
                m_desiredSteer = m_maxSteeringRightRad;
            }
            else {
                m_desiredSteer = s;
            }
        }
    }

    automotive::VehicleData LinearBicycleModelNew::getVehicleData() const {
        return m_vehicleData;
    }

    EgoState LinearBicycleModelNew::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        if (m_useSpeedControl) {
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
            cerr << endl << endl << "PID y = " << y << endl;
        }
        else {
            m_esum = 0;
        }

        double m_deltaSpeed = m_desiredAcceleration * timeStep;

        if (fabs(m_speed + m_deltaSpeed) < m_maxSpeed) {
            m_speed += m_deltaSpeed;
        }

        const double direction = (m_speed < 0) ? -1 : +1; // +1 = forwards, -1 = backwards

        double m_deltaHeading = fabs(m_speed)/m_wheelbase * tan(m_invertedSteering * direction * m_desiredSteer) * timeStep;

        // Calculate the orientation.
//        m_orientation = Point3(1, 0, 0);
//        m_orientation.rotateZ(m_heading + m_deltaHeading);
//        m_orientation.normalize();
        Map<Vector2f> orientation(m_orientation.getP()); // Map the data field (TODO: Here, we need to map the raw data area from the auto-generation Point3 for the orientation data)
        orientation << 1, 0;
        Rotation2D<float> rotationZ(m_heading + m_deltaHeading);
        orientation = rotationZ * orientation;
        orientation.normalize();

        double x = cos(m_heading) * m_speed * timeStep;
        double y = sin(m_heading) * m_speed * timeStep;

        m_heading += m_deltaHeading;
        m_heading = fmod(m_heading, 2 * cartesian::Constants::PI);

        // Calculate the new position.
//        Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
//        double relDrivenPath = fabs((position - m_oldPosition).lengthXY());
//        m_oldPosition = position;
        Map<Vector2f> oldPosition(m_oldPosition.getP()); // Map the data field (TODO: Here, we need to map the raw data area from the auto-generation Point3 for the position data)

        Vector2f position(oldPosition.x() + x, oldPosition.y() + y);
        Vector2f distance = position - oldPosition;
        double relDrivenPath = distance.norm();
        oldPosition = position;

        // These fields are simply results of the calculations from this time step (i.e. no historical data is required).
        Point3 acceleration;
        Point3 velocity(cos(m_heading) * m_speed * direction,
                        sin(m_heading) * m_speed * direction,
                        0);

        // Use Eigen library to modify the data.
        cartesian::Point2 pos;
        cartesian::Point2 vel;
        Map<Vector2f> _pos(pos.getP()); // Map the data field from Point2.
        _pos << position.x(), position.y(); // Set values.

        Map<Vector2f> _vel(vel.getP()); // Map the data field from Point2.
        _vel << velocity.getX(), velocity.getY(); // Set values.

        // Update internal data.
        m_vehicleData.setPosition(pos);
        m_vehicleData.setHeading(m_heading);
        m_vehicleData.setVelocity(vel);
        m_vehicleData.setSpeed(m_speed);
        m_vehicleData.setV_log(0);
        m_vehicleData.setV_batt(0);
        // For fake :-)
        m_vehicleData.setTemp(19.5 + cos(m_heading + m_deltaHeading));
        m_vehicleData.setRelTraveledPath(relDrivenPath);
//        const double FAULT = (1+(rand()%10)/300.0);
        const double FAULT = 1.0;
        m_vehicleData.setAbsTraveledPath(m_vehicleData.getAbsTraveledPath() + (relDrivenPath * FAULT));
//cerr << "FAULT: " << FAULT << ", tD: " << m_vehicleData.getAbsTraveledPath() << endl;
        m_previousTime = currentTime;
        return EgoState(Point3(position.x(), position.y(), 0), Point3(orientation.x(), orientation.y(), 0), velocity, acceleration);
    }
}
