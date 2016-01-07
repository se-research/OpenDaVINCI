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

#include <sstream>
#include <string>

#include "IRUS.h"
#include "core/opendavinci.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "hesperia/data/environment/EgoState.h"
#include "vehiclecontext/model/IRUS.h"

namespace core { namespace base { class KeyValueDataStore; } }

namespace irus {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;

    IRUS::IRUS(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimirus") {}

    IRUS::~IRUS() {}

    void IRUS::setUp() {}

    void IRUS::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode IRUS::body() {
<<<<<<< HEAD
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
                Container c = Container(polygonObstacle);
                getConference().send(c);

                cerr << "Found polygon: " << it->second.toString() << endl;
                it++;
            }
        }
=======
        stringstream sstrConfiguration;
        getKeyValueConfiguration().writeTo(sstrConfiguration);
>>>>>>> master

        // Use libodsimulation's odsimirus implementation.
        string config = sstrConfiguration.str();
        vehiclecontext::model::IRUS irus(config);
        irus.setup();

        // Use the most recent EgoState available.
        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Get current EgoState.
            Container c = kvs.get(Container::EGOSTATE);
            EgoState es = c.getData<EgoState>();

<<<<<<< HEAD
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
    		c = Container(sensorBoardData, Container::USER_DATA_0);

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
                    c = Container(FOVobstacle);
                    getConference().send(c);
=======
            // Calculate result and propagate it.
            vector<Container> toBeSent = irus.calculate(es);
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();
                while(it != toBeSent.end()) {
                    getConference().send(*it);
                    it++;
                    Thread::usleepFor(50);
>>>>>>> master
                }
            }
        }

<<<<<<< HEAD
        // Delete all point sensors.
        map<string, PointSensor*, core::strings::StringComparator>::const_iterator sensorIterator = m_mapOfPointSensors.begin();
        for (; sensorIterator != m_mapOfPointSensors.end(); sensorIterator++) {
            PointSensor *sensor = sensorIterator->second;
            OPENDAVINCI_CORE_DELETE_POINTER(sensor);
        }
        m_mapOfPointSensors.clear();
=======
        irus.tearDown();
>>>>>>> master

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // irus
