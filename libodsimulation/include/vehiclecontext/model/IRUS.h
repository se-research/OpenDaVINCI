/**
 * libvehiclecontext - Models for simulating automotive systems.
 * Copyright (C) 2012 - 2016 Christian Berger
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

#ifndef VEHICLECONTEXT_MODEL_IRUS_H_
#define VEHICLECONTEXT_MODEL_IRUS_H_

#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"

#include "context/base/SystemFeedbackComponent.h"

#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Polygon.h"

#include "vehiclecontext/model/PointSensor.h"

namespace vehiclecontext {
    namespace model {

        using namespace std;

        /**
         * This class realizes the model for IRUS.
         */
        class OPENDAVINCI_API IRUS : public context::base::SystemFeedbackComponent {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                IRUS(const IRUS&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                IRUS& operator=(const IRUS&);

            public:
                /**
                 * Constructor to create a IRUS.
                 *
                 * @param configuration Configuration data.
                 */
                IRUS(const string &configuration);

                /**
                 * Constructor to create a IRUS. This constructor overrides
                 * any specified frequency in the configuration.
                 *
                 * @param freq Desired runtime frequency.
                 * @param configuration Configuration data.
                 */
                IRUS(const float &freq, const string &configuration);

                virtual ~IRUS();

                virtual float getFrequency() const;

                virtual void setup();

                virtual void tearDown();

                virtual void step(const core::wrapper::Time &t, context::base::SendContainerToSystemsUnderTest &sender);

            public:
                /**
                 * This method calculates the results from odsimirus
                 * based on the given EgoState.
                 *
                 * @param es EgoState of the vehicle.
                 * @return List of containers with the results.
                 */
                vector<core::data::Container> calculate(const hesperia::data::environment::EgoState &es);

            private:
                core::base::KeyValueConfiguration m_kvc;
                float m_freq;

                uint32_t m_numberOfPolygons;
                map<uint32_t, hesperia::data::environment::Polygon> m_mapOfPolygons;
                vector<uint32_t> m_listOfPolygonsInsideFOV;
                map<string, PointSensor*> m_mapOfPointSensors;
                map<string, double> m_distances;
                map<string, hesperia::data::environment::Polygon> m_FOVs;
        };

    }
} // vehiclecontext::model

#endif /*VEHICLECONTEXT_MODEL_SIMPLIFIEDBICYCLEMODEL_H_*/
