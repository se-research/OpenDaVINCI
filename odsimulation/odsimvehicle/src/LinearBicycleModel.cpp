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

#include <cmath>
#include <iostream>
#include <string>

#include "core/wrapper/Eigen.h"
#include "core/base/KeyValueConfiguration.h"
#include "generated/cartesian/Constants.h"
#include "generated/cartesian/Point2.h"
#include "hesperia/data/environment/Point3.h"

#include "LinearBicycleModel.h"

namespace vehicle {

    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;

    LinearBicycleModel::LinearBicycleModel(const KeyValueConfiguration &kvc) :
        m_minimumTurningRadius(0),
        m_vehicleMass(0),
        m_adherenceCoefficient(0),
        m_idleForce(0),
        m_Ksteering(0),
        m_maximumSteeringRate(0),
        m_Kthrottle(0),
        m_tauBrake(0),
        m_KstaticBrake(0),
        m_KdynamicBrake(0),
        m_steeringRate(0.0),
        m_motorForce(0.0),
        m_brakeForce(0.0),
        m_adherenceForce(0.0),
        m_turningCurvature(0.0),
        m_deltaHeading(0.0),
        m_vehicleDesiredRotationalEffort(0.0),
        m_vehicleDesiredLinearEffortX(0.0),
        m_vehicleDesiredResistiveEffortX(0),
        m_vehicleRotationalEffort(0.0),
        m_vehicleLinearEffortX(0.0),
        m_vehicleResistiveEffortX(0),
        m_speed(0),
        m_speedOld(0),
        m_heading(0),
        m_direction(+1), //driving direction: +1: forwards, -1: backwards
        m_previousTime(),
        m_oldPosition(),
        m_orientation(1,0,0),
        m_oldAcceleration(0,0,0),
        m_vehicleData()
    {
        m_minimumTurningRadius = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.minimumTurningRadius");
        m_vehicleMass = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.vehicleMass");
        m_adherenceCoefficient = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.adherenceCoefficient");
        m_idleForce = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.idleForce");
        m_Ksteering = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.Ksteering");
        m_maximumSteeringRate = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.maximumSteeringRate");
        m_Kthrottle = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.Kthrottle");
        m_tauBrake = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.tauBrake");
        m_KstaticBrake = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.KstaticBrake");
        m_KdynamicBrake = kvc.getValue<double>("odsimvehicle.LinearBicycleModel.KdynamicBrake");

        // Stop the vehicle.
        m_vehicleDesiredResistiveEffortX = (m_idleForce/(m_KstaticBrake * m_tauBrake)) + 0.1;

        // Setup initial position.
        m_oldPosition = Point3(kvc.getValue<double>("odsimvehicle.posX"), kvc.getValue<double>("odsimvehicle.posY"), 0);
        m_heading = cartesian::Constants::DEG2RAD * kvc.getValue<double>("odsimvehicle.headingDEG");
    }

    LinearBicycleModel::~LinearBicycleModel() {}

    void LinearBicycleModel::accelerate(const double& value)
    {
        m_vehicleDesiredLinearEffortX = value;
    }

    void LinearBicycleModel::brake(const double& value)
    {
        m_vehicleDesiredResistiveEffortX = value;
    }

    void LinearBicycleModel::steer(const double &value)
    {
        m_vehicleDesiredRotationalEffort = value;
    }

    automotive::VehicleData LinearBicycleModel::getVehicleData() const {
        return m_vehicleData;
    }

    EgoState LinearBicycleModel::computeEgoState() {
        TimeStamp currentTime;
        double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

        // Decide driving direction: +1: forwards, -1: backwards
        // Change only direction if m_speed is nearly zero.
        int32_t signLinearEffortX = (m_vehicleDesiredLinearEffortX < 0) ? -1 : +1;
        if (m_speed < 5e-3) {
            m_direction = signLinearEffortX;
        }
        cout << "Driving direction: " << ( (m_direction < 0) ? "backwards" : "forwards") << endl;

        // Steering.
        m_steeringRate = m_Ksteering * (m_vehicleDesiredRotationalEffort - m_vehicleRotationalEffort);
        if (m_steeringRate > m_maximumSteeringRate) {
            m_steeringRate = m_maximumSteeringRate;
        }
        else if (m_steeringRate < (-1 * m_maximumSteeringRate)) {
            m_steeringRate = -1 * m_maximumSteeringRate;
        }
        m_vehicleRotationalEffort += m_steeringRate * timeStep;
        m_turningCurvature = -1 * m_vehicleRotationalEffort / 100.0 / m_minimumTurningRadius;

        // Acceleration.
        m_vehicleLinearEffortX = fabs(m_vehicleDesiredLinearEffortX);
        m_motorForce = m_Kthrottle * m_vehicleLinearEffortX + m_idleForce;

        // Brake.
        if (m_vehicleDesiredResistiveEffortX > 6) {
            m_vehicleDesiredResistiveEffortX = 6.0;
        }
        else if (m_vehicleDesiredResistiveEffortX < -6) {
            m_vehicleDesiredResistiveEffortX = -6.0;
        }
        m_vehicleResistiveEffortX += m_tauBrake * (fabs(m_vehicleDesiredResistiveEffortX) - m_vehicleResistiveEffortX);
        
        // Calculate movement speed.
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

        // Stop car if speed is small enough.
        if (fabs(m_speed) < 5e-3) {
            m_speed = 0;
        }

        m_deltaHeading = m_turningCurvature * m_speed * timeStep * m_direction;

        m_orientation = Point3(1, 0, 0);
        m_orientation.rotateZ(m_heading + m_deltaHeading/2.0);
        m_orientation.normalize();

        double x = cos(m_heading + m_deltaHeading/2.0) * m_speed * timeStep * m_direction;
        double y = sin(m_heading + m_deltaHeading/2.0) * m_speed * timeStep * m_direction;

        m_heading += m_deltaHeading;
        m_heading = fmod(m_heading, 2 * cartesian::Constants::PI);

        Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
        double relDrivenPath = (position - m_oldPosition).lengthXY();
        m_oldPosition = position;

        // Set velocity.
        Point3 velocity(cos(m_heading + m_deltaHeading/2.0) * m_speed * m_direction,
                        sin(m_heading + m_deltaHeading/2.0) * m_speed * m_direction,
                        0);

        Point3 acceleration;

        // Use Eigen library to modify the data.
        cartesian::Point2 pos;
        cartesian::Point2 vel;
        Map<Vector2f> _pos(pos.getP()); // Map the data field from Point2.
        _pos << position.getX(), position.getY(); // Set values.

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
        m_vehicleData.setTemp(19.5 + cos(m_heading + m_deltaHeading/2.0));
        m_vehicleData.setRelTraveledPath(relDrivenPath);
        m_vehicleData.setAbsTraveledPath(m_vehicleData.getAbsTraveledPath() + relDrivenPath);

        m_previousTime = currentTime;
        return EgoState(position, m_orientation, velocity, acceleration);
    }
}
