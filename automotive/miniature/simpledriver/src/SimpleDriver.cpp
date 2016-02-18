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

#include <iostream>

#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/io/conference/ContainerConference.h"
#include "opendavinci/core/io/URL.h"
#include "opendlv/core/wrapper/graph/DirectedGraph.h"
#include "opendlv/core/wrapper/graph/Edge.h"
#include "opendlv/core/wrapper/graph/Vertex.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Polygon.h"
#include "opendlv/data/environment/Obstacle.h"
#include "opendlv/data/graph/WaypointsEdge.h"
#include "opendlv/data/graph/WaypointVertex.h"
#include "opendlv/data/planning/Route.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/scenario/SCNXArchive.h"
#include "opendlv/scenario/SCNXArchiveFactory.h"
#include "opendlv/scenario/ScenarioFactory.h"
#include "opendlv/scenario/LaneVisitor.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "SimpleDriver.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace coredata;
        using namespace automotive;
        using namespace automotive::miniature;
        using namespace opendlv::data::environment;

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
            const double GAIN = 1.0;
            const double LENGTH_OF_STEERING_DRAWBAR = 5.0;
            const double LENGTH_OF_VELOCITY_DRAWBAR = 5.0;



            core::wrapper::graph::DirectedGraph m_graph;
            if (urlOfSCNXFile.isValid()) {
                opendlv::scenario::SCNXArchive &scnxArchive = opendlv::scenario::SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

                opendlv::data::scenario::Scenario &scenario = scnxArchive.getScenario();

                // Construct road network.
                opendlv::scenario::LaneVisitor lv(m_graph, scenario);
                scenario.accept(lv);

                // Print graph in dot format.
                cout << m_graph.toGraphizDot() << endl << endl;
            }

            string startWaypoint = "";
            string endWaypoint = "";

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

            opendlv::data::scenario::PointID pidStart(startWaypoint);
            opendlv::data::scenario::PointID pidEnd(endWaypoint);

            opendlv::data::graph::WaypointVertex v1;
            v1.setLayerID(pidStart.getLayerID());
            v1.setRoadID(pidStart.getRoadID());
            v1.setLaneID(pidStart.getLaneID());
            v1.setWaypointID(pidStart.getPointID());

            opendlv::data::graph::WaypointVertex v2;
            v2.setLayerID(pidEnd.getLayerID());
            v2.setRoadID(pidEnd.getRoadID());
            v2.setLaneID(pidEnd.getLaneID());
            v2.setWaypointID(pidEnd.getPointID());

            opendlv::data::planning::Route route;
            vector<const core::wrapper::graph::Vertex*> resultingRoute = m_graph.getShortestPath(v1, v2);
            if (resultingRoute.size() > 0) {
                vector<const core::wrapper::graph::Vertex*>::const_iterator it = resultingRoute.begin();
                while (it != resultingRoute.end()) {
                    const opendlv::data::graph::WaypointVertex *v = dynamic_cast<const opendlv::data::graph::WaypointVertex*>(*it++);
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



                // Check, if the first point is in our field of view.
                c = getKeyValueDataStore().get(Container::EGOSTATE);
                EgoState es = c.getData<EgoState>();

                Polygon FOV;
                const double ANGLE_FOV_IN_DEG = 45.0;
                Point3 leftBoundary(10, 0, 0);
                leftBoundary.rotateZ(ANGLE_FOV_IN_DEG/2.0 * cartesian::Constants::DEG2RAD + es.getRotation().getAngleXY());
                leftBoundary += es.getPosition();

                Point3 rightBoundary(10, 0, 0);
                rightBoundary.rotateZ(-ANGLE_FOV_IN_DEG/2.0 * cartesian::Constants::DEG2RAD + es.getRotation().getAngleXY());
                rightBoundary += es.getPosition();

                FOV.add(es.getPosition() + Point3(1, 0, 0));
                FOV.add(leftBoundary);
                FOV.add(rightBoundary);

                // Visualize FOV.
                Obstacle obstacleFOV(1, Obstacle::UPDATE);
                obstacleFOV.setPolygon(FOV);
                c = Container(Container::OBSTACLE, obstacleFOV);
                getConference().send(c);

                uint32_t waitingBeforeStart = 5;
                while (waitingBeforeStart > 0) {
                    cout << "Still waiting " << waitingBeforeStart << " seconds..." << endl;
                    waitingBeforeStart--;
                    Thread::usleepFor(1 * 1000 * 1000);
                }

                Point3 currentPoint = (*route.getListOfPoints().begin());
                if (FOV.containsIgnoreZ(currentPoint) || true) {
                    cerr << "Ready, first point of planned route is in our FOV. Let's go using our simple drawbar controller!" << endl;


                    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                        TimeStamp startTime;
                        double totalDrivenWay = 0;

                        // Start at current position.
                        currentPoint = es.getPosition();
                        Point3 nextPoint;
                        vector<Point3> listOfPointsWaypoints = route.getListOfPoints();

                        Point3 nextPointUOR;
                        vector<Point3> listOfPointsWaypointsUOR = route.getListOfPoints();
                        nextPointUOR = listOfPointsWaypointsUOR.front();

                        const uint32_t SIZE = listOfPointsWaypoints.size();
                        for (uint32_t i = 0; (i < SIZE) && (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING); i++) {
                            // Get next point.
                            nextPoint = listOfPointsWaypoints.at(i);

                            // Determine direction of (nextPoint - currentPoint).
                            Point3 directionSegment = nextPoint - currentPoint;

                            bool nextWaypointInFrontOfDrawBar = true;

                            // Simply use the previously retrieved egostate.
                            EgoState oldEgoState = es;
                            TimeStamp oldTimeStamp;
                            double V = 0;
                            while ( (nextWaypointInFrontOfDrawBar) && (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) ) {
                                c = getKeyValueDataStore().get(Container::EGOSTATE);
                                es = c.getData<EgoState>();
                                TimeStamp currentTimeStamp;

                                // Compute velocity.
                                double drivenWay = (es.getPosition() - oldEgoState.getPosition()).lengthXY();
                                double passedTimeMS = (currentTimeStamp - oldTimeStamp).toMicroseconds();
                                double passedTime = (static_cast<double>(passedTimeMS) / (1000.0 * 1000.0));
                                if (passedTime > 0) {
                                    V = fabs( drivenWay / passedTime );
                                }
                                if (drivenWay > 0) {
                                	oldEgoState = es;
                                	oldTimeStamp = currentTimeStamp;
                                }

                                totalDrivenWay += drivenWay;
                                if (isVerbose()) {
                                    cerr << "V: " << V << ", driven way: " << drivenWay << ", total driven way: " << totalDrivenWay << ", passedTime MS= " << passedTimeMS << ", passedTime: " << passedTime << endl;
                                }

                                // Compute drawbar point of velocity control.
                                Point3 drawbarVelocityPoint(LENGTH_OF_VELOCITY_DRAWBAR, 0, 0);
                                drawbarVelocityPoint.rotateZ(es.getRotation().getAngleXY());
                                drawbarVelocityPoint += es.getPosition();

                                // Compute drawbar point of steering control.
                                Point3 drawbarSteeringPoint(LENGTH_OF_STEERING_DRAWBAR, 0, 0);
                                drawbarSteeringPoint.rotateZ(es.getRotation().getAngleXY());
                                drawbarSteeringPoint += es.getPosition();

                                nextWaypointInFrontOfDrawBar = drawbarSteeringPoint.isInFront(nextPoint, (drawbarSteeringPoint - es.getPosition()).getAngleXY());

                                //isPointFromUORInFrontOfDrawBar = drawbarSteeringPoint.isInFront(nextPointUOR, (drawbarSteeringPoint - es.getPosition()).getAngleXY());

                                bool isPointFromUORInFrontOfDrawBar = false;
                                while ( (!isPointFromUORInFrontOfDrawBar) && (listOfPointsWaypointsUOR.size() > 1) ) {
                                    isPointFromUORInFrontOfDrawBar = drawbarSteeringPoint.isInFront(nextPointUOR, (drawbarSteeringPoint - es.getPosition()).getAngleXY());

                                    if (!isPointFromUORInFrontOfDrawBar) {
                                        if (listOfPointsWaypointsUOR.size() > 1) {
                                            listOfPointsWaypointsUOR.erase(listOfPointsWaypointsUOR.begin());
                                            nextPointUOR = listOfPointsWaypointsUOR.front();
                                        }
                                    }
                                }

                                if ( isPointFromUORInFrontOfDrawBar && nextWaypointInFrontOfDrawBar ) {
                                    // Compute perpendicular point of drawbarPoint to direction of line segment.
                                    Line l(currentPoint, nextPointUOR);

                                    // Compute track error for steering.
                                    Point3 perpendicularPointSteering = l.getPerpendicularPoint(drawbarSteeringPoint);
                                    const double TRACK_ERROR_STEERING_UOR = (drawbarSteeringPoint - perpendicularPointSteering).lengthXY();
                                    if (isVerbose()) {
                                        cerr << "Error steering (unoptimized route): " << TRACK_ERROR_STEERING_UOR << endl;
                                    }
                                }

                                if (nextWaypointInFrontOfDrawBar) {
                                    // Compute perpendicular point of drawbarPoint to direction of line segment.
                                    Line l(currentPoint, nextPoint);

                                    // Compute track error for steering.
                                    Point3 perpendicularPointSteering = l.getPerpendicularPoint(drawbarSteeringPoint);
                                    const double TRACK_ERROR_STEERING = (drawbarSteeringPoint - perpendicularPointSteering).lengthXY();
                                    if (isVerbose()) {
                                        cerr << "Error steering: " << TRACK_ERROR_STEERING << endl;
                                    }

                                    // Compute track error for velocity.
                                    Point3 perpendicularPointVelocity = l.getPerpendicularPoint(drawbarVelocityPoint);
                                    const double TRACK_ERROR_VELOCITY = (drawbarVelocityPoint - perpendicularPointVelocity).lengthXY();
                                    if (isVerbose()) {
                                        cerr << "Error velocity: " << TRACK_ERROR_VELOCITY << endl;
                                    }

                                    // Compute orientation segment/egostate.
                                    double psi = es.getRotation().getAngleXY() - directionSegment.getAngleXY();
                                    if (isVerbose()) {
                                        cerr << "psi (local): " << psi << endl;
                                    }

                                    // Normalize difference angle to interval -PI .. PI.
                                    while (psi < -cartesian::Constants::PI) {
                                        psi += 2.0*cartesian::Constants::PI;
                                    }
                                    while (psi > cartesian::Constants::PI) {
                                        psi -= 2.0*cartesian::Constants::PI;
                                    }

                                    // Determine, if drawbar is left or right from the line to determine steering direction (depends on driving direction!).
                                    const bool IS_RIGHT = perpendicularPointSteering.isInFront(drawbarSteeringPoint, directionSegment.getAngleXY() - cartesian::Constants::PI/2.0);
                                    if (isVerbose()) {
                                        cerr << "IS_RIGHT = " << IS_RIGHT << endl;
                                    }
                                    const bool IS_LEFT = perpendicularPointSteering.isInFront(drawbarSteeringPoint, directionSegment.getAngleXY() + cartesian::Constants::PI/2.0);
                                    if (isVerbose()) {
                                        cerr << "IS_LEFT = " << IS_LEFT << endl;
                                    }

                                    const double SIGN = (IS_RIGHT ? -1.0 : 1.0);
                                    const double SIGNED_TRACK_ERROR_STEERING = SIGN * TRACK_ERROR_STEERING;

                                    if (isVerbose()) {
                                        cerr << "SIGNED_TRACK_ERROR_STEERING: " << SIGNED_TRACK_ERROR_STEERING << endl;
                                    }

                                    // Compute steering angle.
                                    double steering = 0;
                                    if (fabs(V) > 1e-5) {
                                        steering = psi + atan( (GAIN/V) * SIGNED_TRACK_ERROR_STEERING );
                                    }
                                    else {
                                        steering = psi + atan(GAIN * SIGNED_TRACK_ERROR_STEERING);
                                    }

                                    // Create vehicle control data.
                                    VehicleControl vc;

                                    // With setSpeed you can set a desired speed for the vehicle in the range of -2.0 (backwards) .. 0 (stop) .. +2.0 (forwards)
                                    vc.setSpeed(2);

//                                    // With setSteeringWheelAngle, you can steer in the range of -26 (left) .. 0 (straight) .. +25 (right)
                                    vc.setSteeringWheelAngle(steering);

                                    // You can also turn on or off various lights:
                                    vc.setBrakeLights(false);
                                    vc.setFlashingLightsLeft(false);
                                    vc.setFlashingLightsRight(false);

                                    // Create container for finally sending the data.
                                    Container c2(Container::VEHICLECONTROL, vc);
                                    // Send container.
                                    getConference().send(c2);

                                    cerr << "VehicleControl: " << vc.toString() << endl;

                                    // Visualize drawbar.
                                    Polygon p;
                                    p.add(es.getPosition());
                                    p.add(drawbarSteeringPoint);
                                    p.add(perpendicularPointSteering);

                                    cerr << es.getPosition().toString() << " " << drawbarSteeringPoint.toString() << " " << perpendicularPointSteering.toString() << endl;

                                    Obstacle o(1, Obstacle::UPDATE);
                                    o.setPolygon(p);
                                    c2 = Container(Container::OBSTACLE, o);
                                    getConference().send(c2);

                                    cerr << endl;
                                }
                                else {
                                    cerr << "Next waypoint reached." << endl;
                                }

                                // Sleeping is realized by --freq and isRunning().
                            }
                            currentPoint = nextPoint;
                        }
                        VehicleControl vc;

                        // Create container for finally sending the data.
                        Container c2(Container::VEHICLECONTROL, vc);
                        // Send container.
                        getConference().send(c2);

                        cerr << "VehicleControl: " << vc.toString() << endl;

                        TimeStamp endTime;

                        cerr << "Thank you for using simpledriver. Trip took " << ((endTime - startTime).toMicroseconds() / (1000*1000)) << "s for " << totalDrivenWay << "m." << endl;
                        break;
                    }
                }
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

