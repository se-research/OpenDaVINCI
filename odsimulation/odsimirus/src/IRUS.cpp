/**
 * irus - Distance data generator (part of simulation environment)
 * Copyright (C) 2012 - 2015 Christian Berger
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
#include <algorithm>

#include "core/macros.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/KeyValueDataStore.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "core/strings/StringComparator.h"

#include "GeneratedHeaders_AutomotiveData.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Obstacle.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/data/scenario/Shape.h"
#include "hesperia/data/scenario/Polygon.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/data/scenario/Vertex3.h"
#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/scenario/ScenarioFactory.h"
#include "hesperia/scenario/ScenarioPrettyPrinter.h"

#include "hesperia/data/environment/Line.h"

#include "PointSensor.h"

#include "IRUS.h"

#include "GeneratedHeaders_AutomotiveData.h"

namespace irus {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io;
    using namespace hesperia::data;
    using namespace hesperia::data::environment;
    using namespace hesperia::scenario;

    IRUS::IRUS(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimirus"),
        m_numberOfPolygons(0),
        m_mapOfPolygons(),
        m_listOfPolygonsInsideFOV(),
        m_mapOfPointSensors(),
        m_distances(),
        m_FOVs()
    {}

    IRUS::~IRUS() {}

    void IRUS::setUp() {}

    void IRUS::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode IRUS::body() {
        // Load scenario.
        const URL urlOfSCNXFile(getKeyValueConfiguration().getValue<string>("global.scenario"));
        if (urlOfSCNXFile.isValid()) {
            SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

            hesperia::data::scenario::Scenario &scenario = scnxArchive.getScenario();

            const hesperia::data::scenario::Surroundings &surroundings = scenario.getGround().getSurroundings();
            const vector<hesperia::data::scenario::Shape*> &listOfShapes = surroundings.getListOfShapes();
            vector<hesperia::data::scenario::Shape*>::const_iterator it = listOfShapes.begin();
            while (it != listOfShapes.end()) {
                hesperia::data::scenario::Shape *shape = (*it++);
                if (shape != NULL) {
                    if (shape->getType() == hesperia::data::scenario::Shape::POLYGON) {
                        hesperia::data::scenario::Polygon *polygon = dynamic_cast<hesperia::data::scenario::Polygon*>(shape);
                        if (polygon != NULL) {
                            Polygon p;
                            m_numberOfPolygons++;

                            const vector<hesperia::data::scenario::Vertex3> &listOfVertices = polygon->getListOfVertices();
                            vector<hesperia::data::scenario::Vertex3>::const_iterator jt = listOfVertices.begin();
                            while (jt != listOfVertices.end()) {
                                p.add(*jt++);
                            }
                            m_mapOfPolygons[m_numberOfPolygons] = p;
                        }
                    }
                }
            }
        }

        // Show found polygons on console and in monitor.
        const bool showPolygons = getKeyValueConfiguration().getValue<bool>("odsimirus.showPolygons");
        if (showPolygons) {
            map<uint32_t, Polygon>::iterator it = m_mapOfPolygons.begin();
            while (it != m_mapOfPolygons.end()) {
                const uint32_t polygonID = it->first;
                Polygon p = it->second;

                Obstacle polygonObstacle(polygonID, Obstacle::UPDATE);
                polygonObstacle.setPolygon(p);

                // Send obstacle.
                Container c = Container(Container::OBSTACLE, polygonObstacle);
                getConference().send(c);

                cerr << "Found polygon: " << it->second.toString() << endl;
                it++;
            }
        }

        // Setup all point sensors.
        for (uint32_t i = 0; i < getKeyValueConfiguration().getValue<uint32_t>("odsimirus.numberOfSensors"); i++) {
            stringstream sensorID;
            sensorID << "odsimirus.sensor" << i << ".id";
            uint16_t id(getKeyValueConfiguration().getValue<uint16_t>(sensorID.str()));

            stringstream sensorName;
            sensorName << "odsimirus.sensor" << i << ".name";
            string name(getKeyValueConfiguration().getValue<string>(sensorName.str()));
            
            stringstream sensorTranslation;
            sensorTranslation << "odsimirus.sensor" << i << ".translation";
            Point3 translation(getKeyValueConfiguration().getValue<string>(sensorTranslation.str()));

            stringstream sensorRotZ;
            sensorRotZ << "odsimirus.sensor" << i << ".rotZ";
            const double rotZ = getKeyValueConfiguration().getValue<double>(sensorRotZ.str());
            
            stringstream sensorAngleFOV;
            sensorAngleFOV << "odsimirus.sensor" << i << ".angleFOV";
            const double angleFOV = getKeyValueConfiguration().getValue<double>(sensorAngleFOV.str());
            
            stringstream sensorDistanceFOV;
            sensorDistanceFOV << "odsimirus.sensor" << i << ".distanceFOV";
            const double distanceFOV = getKeyValueConfiguration().getValue<double>(sensorDistanceFOV.str());
            
            stringstream sensorClampDistance;
            sensorClampDistance << "odsimirus.sensor" << i << ".clampDistance";
            const double clampDistance = getKeyValueConfiguration().getValue<double>(sensorClampDistance.str());
            
            stringstream sensorShowFOV;
            sensorShowFOV << "odsimirus.sensor" << i << ".showFOV";
            const bool showFOV = getKeyValueConfiguration().getValue<bool>(sensorShowFOV.str());

            PointSensor *ps = new PointSensor(id, name, translation, rotZ, angleFOV, distanceFOV, clampDistance, showFOV);

            if (ps != NULL) {
                // Save for later.
                m_mapOfPointSensors[ps->getName()] = ps;

                // Initialize distance map entry.
                m_distances[ps->getName()] = -1;

                // Initialize FOV map entry.
                Polygon f;
                m_FOVs[ps->getName()] = f;

                cout << "Registered point sensor " << ps->toString() << "." << endl;
            }
        }

        // Use the most recent EgoState available.
        KeyValueDataStore &kvs = getKeyValueDataStore();

        // MSV: Variable for data from the sensorboard.
        automotive::miniature::SensorBoardData sensorBoardData;

        // Loop through the map of polygons with the current EgoState and intersect all with the point sensor's FOV.
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Get current EgoState.
            Container c = kvs.get(Container::EGOSTATE);
            EgoState es = c.getData<EgoState>();

            // Loop through point sensors.
            map<string, PointSensor*, core::strings::StringComparator>::iterator sensorIterator = m_mapOfPointSensors.begin();
            for (; sensorIterator != m_mapOfPointSensors.end(); sensorIterator++) {
                PointSensor *sensor = sensorIterator->second;

                // Update FOV.
                Polygon FOV = sensor->updateFOV(es.getPosition(), es.getRotation());
                m_FOVs[sensor->getName()] = FOV;

                // Calculate distance.
                m_distances[sensor->getName()] = sensor->getDistance(m_mapOfPolygons);
                cerr << sensor->getName() << ": " << m_distances[sensor->getName()] << endl;

                // MSV: Store data for sensorboard.
                sensorBoardData.putTo_MapOfDistances(sensor->getID(), m_distances[sensor->getName()]);
            }

    		// MSV: Create a container with type USER_DATA_0.
    		c = Container(Container::USER_DATA_0, sensorBoardData);

            // MSV: Send container.
            getConference().send(c);

            // Distribute FOV where necessary.
            uint32_t sensorID = 9000;
            map<string, Polygon, core::strings::StringComparator>::iterator FOVIterator = m_FOVs.begin();
            for (; FOVIterator != m_FOVs.end(); FOVIterator++) {
                string key = FOVIterator->first;
                Polygon FOV = FOVIterator->second;

                PointSensor *ps = m_mapOfPointSensors[key];
                if ( (ps != NULL) && (ps->hasShowFOV()) ) {
                    // Send FOV.
                    Obstacle FOVobstacle(sensorID++, Obstacle::UPDATE);
                    FOVobstacle.setPolygon(FOV);

                    // Send obstacle.
                    c = Container(Container::OBSTACLE, FOVobstacle);
                    getConference().send(c);
                }
            }
        }

        // Delete all point sensors.
        map<string, PointSensor*, core::strings::StringComparator>::const_iterator sensorIterator = m_mapOfPointSensors.begin();
        for (; sensorIterator != m_mapOfPointSensors.end(); sensorIterator++) {
            PointSensor *sensor = sensorIterator->second;
            OPENDAVINCI_CORE_DELETE_POINTER(sensor);           
        }
        m_mapOfPointSensors.clear();

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // irus
