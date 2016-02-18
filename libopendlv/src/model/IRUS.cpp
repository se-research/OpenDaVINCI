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

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/context/base/SendContainerToSystemsUnderTest.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/strings/StringComparator.h"
#include "opendavinci/core/wrapper/Time.h"
#include "automotivedata/generated/automotive/miniature/SensorBoardData.h"
#include "opendlv/data/environment/Obstacle.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/scenario/Ground.h"
#include "opendlv/data/scenario/Polygon.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/data/scenario/Surroundings.h"
#include "opendlv/scenario/SCNXArchive.h"
#include "opendlv/scenario/SCNXArchiveFactory.h"
#include "opendlv/vehiclecontext/model/IRUS.h"
#include "opendlv/vehiclecontext/model/PointSensor.h"

namespace core { namespace exceptions { class ValueForKeyNotFoundException; } }
namespace opendlv { namespace data { namespace scenario { class Shape; } } }

namespace vehiclecontext {
    namespace model {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace context::base;
        using namespace core::io;
        using namespace opendlv::data;
        using namespace opendlv::data::environment;
        using namespace opendlv::scenario;

        IRUS::IRUS(const string &configuration) :
            m_kvc(),
            m_freq(0),
            m_numberOfPolygons(0),
            m_mapOfPolygons(),
            m_listOfPolygonsInsideFOV(),
            m_mapOfPointSensors(),
            m_distances(),
            m_FOVs() {

            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        IRUS::IRUS(const float &freq, const string &configuration) :
            m_kvc(),
            m_freq(freq),
            m_numberOfPolygons(0),
            m_mapOfPolygons(),
            m_listOfPolygonsInsideFOV(),
            m_mapOfPointSensors(),
            m_distances(),
            m_FOVs() {

            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        IRUS::~IRUS() {}

        float IRUS::getFrequency() const {
            return m_freq;
        }

        void IRUS::setup() {
            // Load scenario.
            const URL urlOfSCNXFile(m_kvc.getValue<string>("global.scenario"));
            if (urlOfSCNXFile.isValid()) {
                SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

                opendlv::data::scenario::Scenario &scenario = scnxArchive.getScenario();

                const opendlv::data::scenario::Surroundings &surroundings = scenario.getGround().getSurroundings();
                const vector<opendlv::data::scenario::Shape*> &listOfShapes = surroundings.getListOfShapes();
                vector<opendlv::data::scenario::Shape*>::const_iterator it = listOfShapes.begin();
                while (it != listOfShapes.end()) {
                    opendlv::data::scenario::Shape *shape = (*it++);
                    if (shape != NULL) {
                        if (shape->getType() == opendlv::data::scenario::Shape::POLYGON) {
                            opendlv::data::scenario::Polygon *polygon = dynamic_cast<opendlv::data::scenario::Polygon*>(shape);
                            if (polygon != NULL) {
                                Polygon p;
                                m_numberOfPolygons++;

                                const vector<opendlv::data::scenario::Vertex3> &listOfVertices = polygon->getListOfVertices();
                                vector<opendlv::data::scenario::Vertex3>::const_iterator jt = listOfVertices.begin();
                                while (jt != listOfVertices.end()) {
                                    p.add(*jt++);
                                }
                                m_mapOfPolygons[m_numberOfPolygons] = p;

                                cerr << "[IRUS] Found polygon: " << p.toString() << endl;
                            }
                        }
                    }
                }
            }

            // Setup all point sensors.
            for (uint32_t i = 0; i < m_kvc.getValue<uint32_t>("odsimirus.numberOfSensors"); i++) {
                stringstream sensorID;
                sensorID << "odsimirus.sensor" << i << ".id";
                uint16_t id(m_kvc.getValue<uint16_t>(sensorID.str()));

                stringstream sensorName;
                sensorName << "odsimirus.sensor" << i << ".name";
                string name(m_kvc.getValue<string>(sensorName.str()));
                
                stringstream sensorTranslation;
                sensorTranslation << "odsimirus.sensor" << i << ".translation";
                Point3 translation(m_kvc.getValue<string>(sensorTranslation.str()));

                stringstream sensorRotZ;
                sensorRotZ << "odsimirus.sensor" << i << ".rotZ";
                const double rotZ = m_kvc.getValue<double>(sensorRotZ.str());
                
                stringstream sensorAngleFOV;
                sensorAngleFOV << "odsimirus.sensor" << i << ".angleFOV";
                const double angleFOV = m_kvc.getValue<double>(sensorAngleFOV.str());
                
                stringstream sensorDistanceFOV;
                sensorDistanceFOV << "odsimirus.sensor" << i << ".distanceFOV";
                const double distanceFOV = m_kvc.getValue<double>(sensorDistanceFOV.str());
                
                stringstream sensorClampDistance;
                sensorClampDistance << "odsimirus.sensor" << i << ".clampDistance";
                const double clampDistance = m_kvc.getValue<double>(sensorClampDistance.str());
                
                stringstream sensorShowFOV;
                sensorShowFOV << "odsimirus.sensor" << i << ".showFOV";
                const bool showFOV = m_kvc.getValue<bool>(sensorShowFOV.str());

                // Don't skip any values as default.
                double faultModelSkip = 0;
                try {
                    stringstream faultModelSkipStr;
                    faultModelSkipStr << "odsimirus.sensor" << i << ".faultModel.skip";
                    faultModelSkip = m_kvc.getValue<double>(faultModelSkipStr.str());

                    if (faultModelSkip < 0) {
                        faultModelSkip = 0;
                    }
                    if (faultModelSkip > 1) {
                        faultModelSkip = 1;
                    }
                }
                catch (const core::exceptions::ValueForKeyNotFoundException &e) {
                }

                // Don't add any noise as default.
                double faultModelNoise = 0;
                try {
                    stringstream faultModelNoiseStr;
                    faultModelNoiseStr << "odsimirus.sensor" << i << ".faultModel.noise";
                    faultModelNoise = m_kvc.getValue<double>(faultModelNoiseStr.str());
                }
                catch (const core::exceptions::ValueForKeyNotFoundException &e) {
                }

                PointSensor *ps = new PointSensor(id, name, translation, rotZ, angleFOV, distanceFOV, clampDistance, showFOV, faultModelSkip, faultModelNoise);

                if (ps != NULL) {
                    // Save for later.
                    m_mapOfPointSensors[ps->getName()] = ps;

                    // Initialize distance map entry.
                    m_distances[ps->getName()] = -1;

                    // Initialize FOV map entry.
                    Polygon f;
                    m_FOVs[ps->getName()] = f;

                    cout << "[IRUS] Registered point sensor " << ps->toString() << "." << endl;
                }
            }
        }

        void IRUS::tearDown() {
            // Delete all point sensors.
            map<string, PointSensor*, core::strings::StringComparator>::const_iterator sensorIterator = m_mapOfPointSensors.begin();
            for (; sensorIterator != m_mapOfPointSensors.end(); sensorIterator++) {
                PointSensor *sensor = sensorIterator->second;
                OPENDAVINCI_CORE_DELETE_POINTER(sensor);
            }
            m_mapOfPointSensors.clear();
        }

        vector<Container> IRUS::calculate(const EgoState &es) {
            vector<Container> retVal;

            // Store distance information.
            automotive::miniature::SensorBoardData sensorBoardData;

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

                // Store data for sensorboard.
                sensorBoardData.putTo_MapOfDistances(sensor->getID(), m_distances[sensor->getName()]);
            }

            // Create a container with type USER_DATA_0.
            Container c = Container(Container::USER_DATA_0, sensorBoardData);

            // Enqueue container.
            retVal.push_back(c);

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

                    Container c2 = Container(Container::OBSTACLE, FOVobstacle);
                    // Enqueue container.
                    retVal.push_back(c2);
                }
            }

            return retVal;
        }

        void IRUS::step(const core::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            cerr << "[IRUS] Call for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Get last EgoState.
            EgoState egoState;

            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                cerr << "[IRUS] Received: " << c.toString() << endl;
                if (c.getDataType() == Container::EGOSTATE) {
                    egoState = c.getData<EgoState>();
                }
            }

            // Calculate result and propagate it.
            vector<Container> toBeSent = calculate(egoState);
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();
                while(it != toBeSent.end()) {
                    sender.sendToSystemsUnderTest(*it);
                    it++;
                }
            }
        }

    }
} // vehiclecontext::model
