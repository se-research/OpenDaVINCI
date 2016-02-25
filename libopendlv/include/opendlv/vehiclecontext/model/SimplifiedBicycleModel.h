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

#ifndef VEHICLECONTEXT_MODEL_SIMPLIFIEDBICYCLEMODEL_H_
#define VEHICLECONTEXT_MODEL_SIMPLIFIEDBICYCLEMODEL_H_

#include <string>

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendlv/data/environment/Point3.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/generated/automotive/VehicleControl.h"

#include "opendavinci/odcontext/base/SystemFeedbackComponent.h"

namespace opendlv { namespace vehiclecontext {
    namespace model {

        using namespace std;

        /**
         * This class realizes the simplified bicycle model.
         */
        class OPENDAVINCI_API SimplifiedBicycleModel : public odcontext::base::SystemFeedbackComponent {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SimplifiedBicycleModel(const SimplifiedBicycleModel&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SimplifiedBicycleModel& operator=(const SimplifiedBicycleModel&);

            public:
                /**
                 * Constructor to create a SimplifiedBicycleModel.
                 *
                 * @param configuration Configuration data.
                 */
                SimplifiedBicycleModel(const string &configuration);

                /**
                 * Constructor to create a SimplifiedBicycleModel. This constructor overrides
                 * any specified frequency in the configuration.
                 *
                 * @param freq Desired runtime frequency.
                 * @param configuration Configuration data.
                 */
                SimplifiedBicycleModel(const float &freq, const string &configuration);

                virtual ~SimplifiedBicycleModel();

                virtual float getFrequency() const;

                virtual void setup();

                virtual void tearDown();

                virtual void step(const odcore::wrapper::Time &t, odcontext::base::SendContainerToSystemsUnderTest &sender);

            public:
                /**
                 * This method calculates the results from odsimvehicle
                 * based on the given VehicleControl.
                 *
                 * @param vc Data to control the vehicle.
                 * @param timeStep Elapsed time.
                 * @return List of containers with the results.
                 */
                vector<odcore::data::Container> calculate(const automotive::VehicleControl &vc, const double &timeStep);

            private:
                odcore::base::KeyValueConfiguration m_kvc;
                float m_freq;

                double m_wheelbase;
                double m_maxSteeringLeftRad;
                double m_maxSteeringRightRad;
                int32_t m_invertedSteering;

                double m_maxSpeed;
                bool m_useSpeedControl;
                double m_faultModelNoise;

                double m_esum;
                double m_desiredSpeed;
                double m_desiredAcceleration;
                double m_desiredSteer;

                double m_speed;
                odcore::data::TimeStamp m_previousTime;
                opendlv::data::environment::Point3 m_oldPosition;
                opendlv::data::environment::Point3 m_orientation;
                double m_heading;
                automotive::VehicleData m_vehicleData;

                automotive::VehicleControl m_vehicleControl;
                bool m_hasReceivedVehicleControl;
        };

    }
} } // opendlv::vehiclecontext::model

#endif /*VEHICLECONTEXT_MODEL_SIMPLIFIEDBICYCLEMODEL_H_*/
