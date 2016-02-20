/**
 * libvehiclecontext - Models for simulating automotive systems.
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

#include <iostream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendavinci/core/base/KeyValueDataStore.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/wrapper/Time.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Line.h"
#include "hesperia/data/environment/Obstacle.h"
#include "hesperia/data/environment/OtherVehicleState.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Polygon.h"
#include "vehiclecontext/report/DistanceToObjectsReport.h"

namespace vehiclecontext {
    namespace report {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;
        using namespace hesperia::data;
        using namespace hesperia::data::environment;

        DistanceToObjectsReport::DistanceToObjectsReport(const string &configuration, const float &threshold) :
            m_configuration(),
            m_threshold(threshold),
            m_correctDistance(true) {
            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_configuration.readFrom(sstrConfiguration);
        }

        DistanceToObjectsReport::~DistanceToObjectsReport() {}

        void DistanceToObjectsReport::setup() {}

        void DistanceToObjectsReport::tearDown() {}

        bool DistanceToObjectsReport::hasCorrectDistance() const {
            return m_correctDistance;
        }

        void DistanceToObjectsReport::report(const core::wrapper::Time &t) {
            cerr << "Call to DistanceToObjectsReport for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Get last EgoState.
            KeyValueDataStore &kvds = getKeyValueDataStore();
            Container c = kvds.get(hesperia::data::environment::EgoState::ID());
            EgoState es = c.getData<EgoState>();

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                c = getFIFO().leave();
                cerr << "Received: " << c.toString() << endl;

                if (c.getDataType() == hesperia::data::environment::Obstacle::ID()) {
                    Obstacle o = c.getData<Obstacle>();

                    const float DISTANCE = (es.getPosition().getDistanceTo(o.getPosition()));
                    cerr << "DistanceToObjectsReport: Distance to object: " << DISTANCE << ", E: " << es.toString() << ", o: " << o.getPosition().toString() << endl;

                    // Continuously check distance.
                    m_correctDistance &= (DISTANCE > m_threshold);

                    vector<Point3> shape = o.getPolygon().getVertices();
                    Point3 head = shape.front();
                    shape.push_back(head);
                    const uint32_t NUMVERTICES = shape.size();
                    for(uint32_t j = 1; j < NUMVERTICES; j++) {
                        Point3 pA = shape.at(j-1);
                        Point3 pB = shape.at(j);

                        // TODO: Check polygonal data as well as perpendicular to all sides.
                        // Create line.
                        Line l(pA, pB);

                        // Compute perpendicular point.
                        Point3 perpendicularPoint = l.getPerpendicularPoint(es.getPosition());

                        // Compute distance between current position and perpendicular point.
                        const float DISTANCE_PP = (es.getPosition().getDistanceTo(perpendicularPoint));

                        cerr << "DistanceToObjectsReport: Distance to object's shape: " << DISTANCE_PP << ", E: " << es.toString() << ", o: " << o.getPosition().toString() << ", perpendicular point:" << perpendicularPoint.toString() << endl;

                        // Continuously check distance.
                        m_correctDistance &= (DISTANCE > m_threshold);
                    }
                }

                if (c.getDataType() == hesperia::data::environment::OtherVehicleState::ID()) {
                    OtherVehicleState o = c.getData<OtherVehicleState>();

                    const float DISTANCE = (es.getPosition().getDistanceTo(o.getPosition()));

                    // Compute distance between current position and perpendicular point.
                    cerr << "DistanceToObjectsReport: Distance to other vehicle: " << DISTANCE << ", E: " << es.toString() << ", o: " << o.getPosition().toString() << endl;

                    // Continuously check distance.
                    m_correctDistance &= (DISTANCE > m_threshold);
                }
            }
        }

    }
} // vehiclecontext::report
