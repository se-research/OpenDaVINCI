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

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"

#include "opendavinci/odcontext/base/SystemFeedbackComponent.h"

#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Polygon.h"

#include "opendlv/vehiclecontext/model/PointSensor.h"

namespace opendlv { namespace vehiclecontext {
    namespace model {

        using namespace std;

        /**
         * This class realizes the model for IRUS.
         */
        class OPENDAVINCI_API IRUS : public odcontext::base::SystemFeedbackComponent {
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

                virtual void step(const odcore::wrapper::Time &t, odcontext::base::SendContainerToSystemsUnderTest &sender);

            public:
                /**
                 * This method calculates the results from odsimirus
                 * based on the given EgoState.
                 *
                 * @param es EgoState of the vehicle.
                 * @return List of containers with the results.
                 */
                vector<odcore::data::Container> calculate(const opendlv::data::environment::EgoState &es);

            private:
                odcore::base::KeyValueConfiguration m_kvc;
                float m_freq;

                uint32_t m_numberOfPolygons;
                map<uint32_t, opendlv::data::environment::Polygon> m_mapOfPolygons;
                vector<uint32_t> m_listOfPolygonsInsideFOV;
                map<string, PointSensor*> m_mapOfPointSensors;
                map<string, double> m_distances;
                map<string, opendlv::data::environment::Polygon> m_FOVs;
        };

    }
} } // opendlv::vehiclecontext::model

#endif /*VEHICLECONTEXT_MODEL_SIMPLIFIEDBICYCLEMODEL_H_*/
