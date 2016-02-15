/**
 * libvehiclecontext - Models for simulating automotive systems.
 * Copyright (C) 2016 Christian Berger
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

#include "core/wrapper/Eigen.h"

#include "core/opendavinci.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/wrapper/Time.h"
#include "context/base/SendContainerToSystemsUnderTest.h"
#include "generated/automotive/VehicleData.h"
#include "generated/cartesian/Constants.h"
#include "generated/cartesian/Point2.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Point3.h"
#include "vehiclecontext/model/SimplifiedBicycleModel.h"

namespace core { namespace exceptions { class ValueForKeyNotFoundException; } }

namespace vehiclecontext {
    namespace model {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;
        using namespace context::base;
        using namespace hesperia::data::environment;

        SimplifiedBicycleModel::SimplifiedBicycleModel(const string &configuration) :
            m_kvc(),
            m_freq(0),
            m_wheelbase(1),
            m_maxSteeringLeftRad(0),
            m_maxSteeringRightRad(0),
            m_invertedSteering(0),
            m_maxSpeed(0),
            m_useSpeedControl(true),
            m_faultModelNoise(0),
            m_esum(0),
            m_desiredSpeed(0),
            m_desiredAcceleration(0),
            m_desiredSteer(0),
            m_speed(0),
            m_previousTime(),
            m_oldPosition(),
            m_orientation(1,0,0),
            m_heading(0),
            m_vehicleData(),
            m_vehicleControl(),
            m_hasReceivedVehicleControl(false) {

            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        SimplifiedBicycleModel::SimplifiedBicycleModel(const float &freq, const string &configuration) :
            m_kvc(),
            m_freq(freq),
            m_wheelbase(1),
            m_maxSteeringLeftRad(0),
            m_maxSteeringRightRad(0),
            m_invertedSteering(0),
            m_maxSpeed(0),
            m_useSpeedControl(true),
            m_faultModelNoise(0),
            m_esum(0),
            m_desiredSpeed(0),
            m_desiredAcceleration(0),
            m_desiredSteer(0),
            m_speed(0),
            m_previousTime(),
            m_oldPosition(),
            m_orientation(1,0,0),
            m_heading(0),
            m_vehicleData(),
            m_vehicleControl(),
            m_hasReceivedVehicleControl(false) {

            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        SimplifiedBicycleModel::~SimplifiedBicycleModel() {}

        float SimplifiedBicycleModel::getFrequency() const {
            return m_freq;
        }

        void SimplifiedBicycleModel::setup() {
            // Setup initial position.
            m_oldPosition = Point3(m_kvc.getValue<double>("odsimvehicle.posX"), m_kvc.getValue<double>("odsimvehicle.posY"), 0);
            m_heading = cartesian::Constants::DEG2RAD * m_kvc.getValue<double>("odsimvehicle.headingDEG");

            // Calculate maximum steering wheel angles to left and right.
            m_wheelbase = m_kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.wheelbase");
            m_maxSteeringLeftRad = atan(m_wheelbase/m_kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusLeft") );
            m_maxSteeringRightRad = atan(m_wheelbase/m_kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusRight"));

            m_invertedSteering = (m_kvc.getValue<int32_t>("odsimvehicle.LinearBicycleModelNew.invertedSteering") == 0) ? -1 : 1;
            m_maxSpeed = fabs(m_kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.maxspeed"));

            m_useSpeedControl = (m_kvc.getValue<int32_t>("odsimvehicle.LinearBicycleModelNew.withSpeedController") == 1) ? true: false;

            try {
                m_faultModelNoise = m_kvc.getValue<double>("odsimvehicle.LinearBicycleModelNew.faultModel.noise");
            }
            catch (const core::exceptions::ValueForKeyNotFoundException &e) {
            }

            cerr << "max turning wheel angle to the left: " << m_maxSteeringLeftRad << endl;
            cerr << "max turning wheel angle to the right: " << m_maxSteeringRightRad << endl;
            cerr << "inverted steering: " << m_invertedSteering << endl;
            cerr << "fault model noise: " << m_faultModelNoise << endl;

            // Initialize random number generator.
            srand(10);
        }

        void SimplifiedBicycleModel::tearDown() {}

        vector<Container> SimplifiedBicycleModel::calculate(const automotive::VehicleControl &vc, const double &timeStep) {
            vector<Container> retVal;

            m_desiredAcceleration = vc.getAcceleration();
            m_desiredSpeed = vc.getSpeed();

            double s = vc.getSteeringWheelAngle();
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
                cerr << endl << endl << "[SimplifiedBicycleModel] PID y = " << y << endl;
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

            m_orientation = Point3(1, 0, 0);
            m_orientation.rotateZ(m_heading + m_deltaHeading);
            m_orientation.normalize();

            double x = cos(m_heading) * m_speed * timeStep;
            double y = sin(m_heading) * m_speed * timeStep;

            m_heading += m_deltaHeading;
            m_heading = fmod(m_heading, 2 * cartesian::Constants::PI);

            Point3 position(m_oldPosition.getX() + x, m_oldPosition.getY() + y, 0);
            double relDrivenPath = fabs((position - m_oldPosition).lengthXY());
            m_oldPosition = position;

            Point3 acceleration;
            Point3 velocity(cos(m_heading) * m_speed * direction,
                            sin(m_heading) * m_speed * direction,
                            0);

            // Update internal data.
            cartesian::Point2 pos;
            cartesian::Point2 vel;

            // Use Eigen library to modify the data.
            Map<Vector2f> _pos(pos.getP()); // Map the data field from Point2.
            _pos << position.getX(), position.getY(); // Set values.

            Map<Vector2f> _vel(vel.getP()); // Map the data field from Point2.
            _vel << velocity.getX(), velocity.getY(); // Set values.

            // Set values to VehicleData
            m_vehicleData.setPosition(pos);
            m_vehicleData.setVelocity(vel);
            m_vehicleData.setHeading(m_heading);
            m_vehicleData.setSpeed(m_speed);
            m_vehicleData.setV_log(0);
            m_vehicleData.setV_batt(0);
            // For fake :-)
            m_vehicleData.setTemp(19.5 + cos(m_heading + m_deltaHeading));
            m_vehicleData.setRelTraveledPath(relDrivenPath);

            // Determine the random data from the range -1.0 .. 1.0 multiplied by the defined m_faultModelNoise.
            const double FAULT = ((100-(1 + (rand()%200)))/100.0) * m_faultModelNoise;
            // No fault model was specified, FAULT is set to 1.0 to simply add the unmodified value.
            m_vehicleData.setAbsTraveledPath(m_vehicleData.getAbsTraveledPath() + (relDrivenPath * (1 + FAULT)));
            if ( (FAULT > 0) || (FAULT < 0) ) {
                cerr << "[SimplifiedBicycleModel] faultModel.noise: " << "Adding " << FAULT << " to travelled distance." << endl;
            }

            // Resulting EgoState.
            EgoState nextEgoState(m_oldPosition, m_orientation, velocity, acceleration);

            cerr << "[SimplifiedBicycleModel] " << nextEgoState.toString() << endl;
            cerr << "[SimplifiedBicycleModel] " << m_vehicleData.toString() << endl;

            // Send EgoState to System-Under-Test.
            Container c(nextEgoState);
            retVal.push_back(c);

            // Send VehicleData to System-Under-Test.
            Container c2(m_vehicleData);
            retVal.push_back(c2);

            return retVal;
        }

        void SimplifiedBicycleModel::step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            cerr << "[SimplifiedBicycleModel] Call for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Get last VehicleControl.
            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                cerr << "[SimplifiedBicycleModel] Received: " << c.toString() << endl;
                if (c.getDataType() == automotive::VehicleControl::ID()) {
                    m_hasReceivedVehicleControl = true;
                    m_vehicleControl = c.getData<automotive::VehicleControl>();
                    break;
                }
            }

            ////////////////////////////////////////////////////////////////////

            TimeStamp currentTime;
            double timeStep = (currentTime.toMicroseconds() - m_previousTime.toMicroseconds()) / (1000.0 * 1000.0);

            vector<Container> toBeSent;
            if (m_hasReceivedVehicleControl) {
                toBeSent = calculate(m_vehicleControl, timeStep);
            }
            else {
                // Send current position.
                EgoState nextEgoState(m_oldPosition, m_orientation, Point3(0, 0, 0), Point3(0, 0, 0));

                cerr << "[SimplifiedBicycleModel] " << nextEgoState.toString() << endl;
                cerr << "[SimplifiedBicycleModel] " << m_vehicleData.toString() << endl;

                // Send EgoState to System-Under-Test.
                Container c(nextEgoState);
                toBeSent.push_back(c);

                // Send VehicleData to System-Under-Test.
                Container c2(m_vehicleData);
                toBeSent.push_back(c2);
            }

            // Distribute containers.
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();
                while(it != toBeSent.end()) {
                    sender.sendToSystemsUnderTest(*it);
                    it++;
                }
            }

            // Keep time stamp.
            m_previousTime = currentTime;
        }

    }
} // vehiclecontext::model
