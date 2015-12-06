/**
 * simpledriver is an example application to demonstrate how to 
 *              generate driving commands from an application realized
 *              with OpenDaVINCI
 * Copyright (C) 2015 Christian Berger
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

#include <cstdio>
#include <cmath>

#include "core/data/Container.h"
#include "core/io/conference/ContainerConference.h"
#include "core/io/URL.h"
#include "core/wrapper/graph/DirectedGraph.h"
#include "core/wrapper/graph/Edge.h"
#include "core/wrapper/graph/Vertex.h"
#include "hesperia/data/graph/WaypointsEdge.h"
#include "hesperia/data/graph/WaypointVertex.h"
#include "hesperia/data/planning/Route.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/scenario/ScenarioFactory.h"
#include "hesperia/scenario/LaneVisitor.h"

#include "GeneratedHeaders_AutomotiveData.h"

#include "SimpleDriver.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace coredata;
        using namespace automotive;
        using namespace automotive::miniature;

        SimpleDriver::SimpleDriver(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "simpledriver") {
        }

        SimpleDriver::~SimpleDriver() {}

        void SimpleDriver::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void SimpleDriver::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        // This method will do the main data processing job.
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode SimpleDriver::body() {
            const core::io::URL urlOfSCNXFile(getKeyValueConfiguration().getValue<string>("global.scenario"));

            core::wrapper::graph::DirectedGraph m_graph;
            if (urlOfSCNXFile.isValid()) {
                hesperia::scenario::SCNXArchive &scnxArchive = hesperia::scenario::SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

                hesperia::data::scenario::Scenario &scenario = scnxArchive.getScenario();

                // Construct road network.
                hesperia::scenario::LaneVisitor lv(m_graph, scenario);
                scenario.accept(lv);
            }

            string startWaypoint = "1.1.1.1";
            string endWaypoint = "1.4.1.2";

            cout << endl;
            cout << "Welcome to SimpleDriver" << endl << endl;
            if (startWaypoint == "") {
                cout << "Where do you want to start your route? (The point should be in front of us! Example: 1.1.1.1)." << endl;
                cin >> startWaypoint;
            }
            if (endWaypoint == "") {
                cout << "Where do you want to end your route? (Example: 1.4.1.2)." << endl;
                cin >> endWaypoint;
            }

            cout << "Start: '" << startWaypoint << "'" << endl;
            cout << "End: '" << endWaypoint << "'" << endl;

            hesperia::data::scenario::PointID pidStart(startWaypoint);
            hesperia::data::scenario::PointID pidEnd(endWaypoint);

            hesperia::data::graph::WaypointVertex v1;
            v1.setLayerID(pidStart.getLayerID());
            v1.setRoadID(pidStart.getRoadID());
            v1.setLaneID(pidStart.getLaneID());
            v1.setWaypointID(pidStart.getPointID());

            hesperia::data::graph::WaypointVertex v2;
            v2.setLayerID(pidEnd.getLayerID());
            v2.setRoadID(pidEnd.getRoadID());
            v2.setLaneID(pidEnd.getLaneID());
            v2.setWaypointID(pidEnd.getPointID());

            hesperia::data::planning::Route route;
            vector<const core::wrapper::graph::Vertex*> resultingRoute = m_graph.getShortestPath(v1, v2);
            if (resultingRoute.size() > 0) {
                vector<const core::wrapper::graph::Vertex*>::const_iterator it = resultingRoute.begin();
                while (it != resultingRoute.end()) {
                    const hesperia::data::graph::WaypointVertex *v = dynamic_cast<const hesperia::data::graph::WaypointVertex*>(*it++);
                    if (v != NULL) {
                        route.add(v->getPosition());
                    }
                }
            }

            if (route.getSize() > 0) {
                cout << "Shortest route from " << v1.toString() << " to " << v2.toString() << ": " << endl;
                cout << route.toString() << endl;

                Container c;
                c = Container(Container::ROUTE, route);
                getConference().send(c);
            }


            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                // In the following, you find example for the various data sources that are available:

                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
                VehicleData vd = containerVehicleData.getData<VehicleData> ();
                cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;

//                // 2. Get most recent sensor board data:
//                Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
//                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
//                cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;

//                // 3. Get most recent user button data:
//                Container containerUserButtonData = getKeyValueDataStore().get(Container::USER_BUTTON);
//                UserButtonData ubd = containerUserButtonData.getData<UserButtonData> ();
//                cerr << "Most recent user button data: '" << ubd.toString() << "'" << endl;

//                // 4. Get most recent steering data as fill from lanedetector for example:
//                Container containerSteeringData = getKeyValueDataStore().get(Container::USER_DATA_1);
//                SteeringData sd = containerSteeringData.getData<SteeringData> ();
//                cerr << "Most recent steering data: '" << sd.toString() << "'" << endl;



                // Design your control algorithm here depending on the input data from above.



                // Create vehicle control data.
                VehicleControl vc;

                // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
                vc.setSpeed(0.4);

                // With setSteeringWheelAngle, you can steer in the range of -26 (left) .. 0 (straight) .. +25 (right)
                double desiredSteeringWheelAngle = 4; // 4 degree but SteeringWheelAngle expects the angle in radians!
                vc.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);

                // You can also turn on or off various lights:
                vc.setBrakeLights(false);
                vc.setFlashingLightsLeft(false);
                vc.setFlashingLightsRight(true);

                // Create container for finally sending the data.
                Container c(Container::VEHICLECONTROL, vc);
                // Send container.
                getConference().send(c);
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

