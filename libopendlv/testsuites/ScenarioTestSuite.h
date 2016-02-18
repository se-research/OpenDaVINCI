/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef HESPERIA_SCENARIOTESTSUITE_H_
#define HESPERIA_SCENARIOTESTSUITE_H_

#include <iostream>
#include <sstream>
#include <string>

#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/BoundingBox.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/ComplexModel.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/Cylinder.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/LaneAttribute.h"
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/Polygon.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/Spot.h"
#include "opendlv/data/scenario/StraightLine.h"
#include "opendlv/data/scenario/TrafficLight.h"
#include "opendlv/data/scenario/TrafficSign.h"
#include "opendlv/data/scenario/Vertex3.h"
#include "opendlv/data/scenario/Zone.h"
#include "opendlv/scenario/ScenarioFactory.h"
#include "opendlv/scenario/ScenarioPrettyPrinter.h"

using namespace std;
using namespace opendlv::data::scenario;
using namespace core::exceptions;
using namespace opendlv::scenario;
using namespace core::wrapper::parser;

class ScenarioTest : public CxxTest::TestSuite {
    public:
        void testIDVertex3() {
            // This testcase tests the correct serialization of IDVertex3.
            stringstream sstr;
            IDVertex3 idv;
            idv.setID(1);
            idv.setX(233.1);
            idv.setY(-233.5);
            sstr << idv;

            IDVertex3 idv2;
            sstr >> idv2;
            TS_ASSERT(idv.toString() == idv2.toString());
        }

        void testParsingCorruptSCNGrammar() {
            stringstream s;
            s << "SCENARIO" << " " << "Test-Scenario" << endl
            << "VERSION"  << " " << "v1.0" << endl
            << "DATE3"     << " " << "July-15-2008" << endl;

            bool failed = true;
            try {
                Scenario scn = ScenarioFactory::getInstance().getScenario(s.str());
            } catch (InvalidArgumentException &iae) {
                //failed = (iae.toString() != "InvalidArgumentException: SCNGrammarErrorListener caught an unknown parser error at line: 3 in context \'SCENARIO Test-Scenario\nVERSION v1.0\n===Erroneous line===>>> DATE3 July-15-2008\n\'. at build/libopendlv/testing/src/scenario/ScenarioFactory.cpp: 60");
               failed = false;
            }
            TS_ASSERT(!failed);
        }

        void testParsingSCNGrammar() {
            stringstream s;
            s << "SCENARIO Test-Scenario" << endl
            << "VERSION v1.0" << endl
            << "DATE July-15-2008" << endl

            << "ORIGINCOORDINATESYSTEM" << endl
            << "WGS84" << endl
            << "ORIGIN" << endl
            << "VERTEX2" << endl
            << "X 52.247041" << endl
            << "Y 10.575832" << endl
            << "ROTATION 0" << endl

            << "GROUND Groundlayer" << endl
            << "AERIALIMAGE" << endl
            << "IMAGE Test1.png" << endl
            << "ORIGINX 1630" << endl
            << "ORIGINY 2420" << endl
            << "MPPX 0.202" << endl
            << "MPPY 0.197" << endl
            << "ROTZ 0" << endl

            << "HEIGHTIMAGE" << endl
            << "IMAGE Test2.png" << endl
            << "ORIGINX 1631" << endl
            << "ORIGINY 2421" << endl
            << "MPPX 0.302" << endl
            << "MPPY 0.297" << endl
            << "ROTZ 1" << endl
            << "GROUNDHEIGHT 127" << endl
            << "MINHEIGHT -0.4" << endl
            << "MAXHEIGHT 1.2" << endl

            << "SURROUNDING" << endl
            << "SHAPENAME Cylinder1" << endl
            << "CYLINDER" << endl
            << "VERTEX2" << endl
            << "X 42.1" << endl
            << "Y -42.5" << endl
            << "RADIUS 5.2" << endl
            << "HEIGHT 7" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X 0" << endl
            << "Y 1" << endl
            << "Z 0" << endl

            << "SHAPENAME Polygon1" << endl
            << "POLYGON" << endl
            << "HEIGHT 4" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X 1" << endl
            << "Y 0" << endl
            << "Z 1" << endl
            << "VERTEX2" << endl
            << "X 2.1" << endl
            << "Y -2.5" << endl
            << "VERTEX2" << endl
            << "X 22.1" << endl
            << "Y -22.5" << endl

            << "SHAPENAME"    << " " << "ComplexModel1" << endl
            << "COMPLEXMODEL" << endl
            << "MODELFILE Test2.3ds" << endl
            << "POSITION" << endl
            << "VERTEX3" << endl
            << "X 1.1" << endl
            << "Y -1.5" << endl
            << "Z 5.5" << endl
            << "ROTATION" << endl
            << "VERTEX3" << endl
            << "X 0.1" << endl
            << "Y -0.5" << endl
            << "Z 0.5" << endl
            << "BOUNDINGBOX" << endl
            << "VERTEX2" << endl
            << "X 1.1" << endl
            << "Y 1.2" << endl
            << "VERTEX2" << endl
            << "X 2.1" << endl
            << "Y 2.2" << endl
            << "VERTEX2" << endl
            << "X 3.1" << endl
            << "Y 3.2" << endl
            << "VERTEX2" << endl
            << "X 4.1" << endl
            << "Y 4.2" << endl

            << "ENDGROUND" << endl

            << "LAYER FirstLayer" << endl
            << "LAYERID 1" << endl
            << "HEIGHT 0.1" << endl

            << "ROAD" << endl
            << "ROADID 1" << endl
            << "ROADNAME Road1" << endl

            << "LANE" << endl
            << "LANEID 1" << endl
            << "LANEWIDTH 4.5" << endl
            << "LEFTLANEMARKING solid_yellow" << endl
            << "RIGHTLANEMARKING solid_white" << endl
            << "(1.1.1.2) -> (1.1.2.1)" << endl // Layer1.Road1.Lane1.Point2 is connected to Layer1.Road1.Lane2.Point1
            << "(3.2.1.2) -> (3.5.2.1)" << endl // Layer1.Road1.Lane1.Point2 is connected to Layer1.Road1.Lane2.Point1

            << "TRAFFICLIGHT" << endl
            << "NAME TrafficLight1" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 832.1" << endl
            << "Y -832.5" << endl
            << "SHAPENAME TrafficLightCylinder1" << endl
            << "CYLINDER" << endl
            << "VERTEX2" << endl
            << "X 832.1" << endl
            << "Y -832.5" << endl
            << "RADIUS 0.3" << endl
            << "HEIGHT 7" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X 0" << endl
            << "Y 1" << endl
            << "Z 0" << endl

            << "POINTMODEL" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 32.1" << endl
            << "Y -32.5" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 52.1" << endl
            << "Y -52.5" << endl
            << "ENDPOINTMODEL" << endl
            << "ENDLANE" << endl


            << "LANE" << endl
            << "LANEID 2" << endl

            << "TRAFFICSIGN" << endl
            << "VALUE stopline" << endl
            << "NAME Stopline1" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 932.1" << endl
            << "Y -932.5" << endl
            << "SHAPENAME StoplinePolygon1" << endl
            << "POLYGON" << endl
            << "HEIGHT 1" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X 1" << endl
            << "Y 1" << endl
            << "Z 1" << endl
            << "VERTEX2" << endl
            << "X 932.1" << endl
            << "Y -932.5" << endl
            << "VERTEX2" << endl
            << "X 932.1" << endl
            << "Y -932.7" << endl

            << "FUNCTIONMODEL" << endl
            << "STRAIGHTLINE" << endl
            << "START" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 662.1" << endl
            << "Y -662.5" << endl
            << "END" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 772.1" << endl
            << "Y -772.5" << endl
            << "ENDFUNCTIONMODEL" << endl
            << "ENDLANE" << endl


            << "LANE" << endl
            << "LANEID 3" << endl
            << "(3.3.3.3) -> (1.1.2.1)" << endl // Layer1.Road1.Lane1.Point2 is connected to Layer1.Road1.Lane2.Point1
            << "FUNCTIONMODEL" << endl
            << "CLOTHOID" << endl
            << "DK -0.0000234065942902206" << endl
            << "K 0.0036564644663092702" << endl
            << "START" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 5662.1" << endl
            << "Y -5662.5" << endl
            << "END" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 5772.1" << endl
            << "Y -5772.5" << endl
            << "ROTZ -0.3" << endl
            << "ENDFUNCTIONMODEL" << endl
            << "ENDLANE" << endl


            << "LANE" << endl
            << "LANEID 4" << endl
            << "FUNCTIONMODEL" << endl
            << "ARC" << endl
            << "RADIUS 20" << endl
            << "[ 0 0.785398164 ]" << endl
            << "START" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 7662.1" << endl
            << "Y -7662.5" << endl
            << "END" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 7772.1" << endl
            << "Y -7772.5" << endl
            << "ROTZ 0" << endl
            << "ENDFUNCTIONMODEL" << endl
            << "ENDLANE" << endl

            << "ENDROAD" << endl

            << "ZONE" << endl
            << "ZONEID 1" << endl
            << "ZONENAME Zone1" << endl
            << "(1.1.1.1) -> (1.1.2.1)" << endl
            << "PERIMETER" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 33.1" << endl
            << "Y -33.5" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 55.1" << endl
            << "Y -55.5" << endl
            << "ID 3" << endl
            << "VERTEX2" << endl
            << "X 66.1" << endl
            << "Y -66.5" << endl
            << "ENDPERIMETER" << endl

            << "SPOT" << endl
            << "SPOTID 1" << endl
            << "VERTEX2" << endl
            << "X 77.1" << endl
            << "Y -77.5" << endl
            << "VERTEX2" << endl
            << "X 78.1" << endl
            << "Y -78.5" << endl
            << "ENDSPOT" << endl

            << "ENDZONE" << endl

            << "ZONE" << endl
            << "ZONEID 2" << endl
            << "ZONENAME Zone2" << endl
            << "(2.2.2.2) -> (1.1.2.1)" << endl
            << "PERIMETER" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 233.1" << endl
            << "Y -233.5" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 255.1" << endl
            << "Y -255.5" << endl
            << "ID 3" << endl
            << "VERTEX2" << endl
            << "X 266.1" << endl
            << "Y -266.5" << endl
            << "ENDPERIMETER" << endl

            << "ENDZONE" << endl

            << "ZONE" << endl
            << "ZONEID 3" << endl
            << "ZONENAME Zone3" << endl
            << "PERIMETER" << endl
            << "ID 1" << endl
            << "VERTEX2" << endl
            << "X 333.1" << endl
            << "Y -333.5" << endl
            << "ID 2" << endl
            << "VERTEX2" << endl
            << "X 355.1" << endl
            << "Y -355.5" << endl
            << "ID 3" << endl
            << "VERTEX2" << endl
            << "X 366.1" << endl
            << "Y -366.5" << endl
            << "ENDPERIMETER" << endl

            << "ENDZONE" << endl

            << "ENDLAYER" << endl

            << "ENDSCENARIO" << endl;

            bool failed = true;
            try {
                Scenario scn = ScenarioFactory::getInstance().getScenario(s.str());

                // Test original.
                clog << "First check." << endl;
                checkData(scn);

                // Test deep copy.
                Scenario scn2(scn);
                clog << "Second check." << endl;
                checkData(scn2);

                // Test serialized data.
                stringstream sstr;
                sstr << scn2;
                Scenario scn3;
                sstr >> scn3;
                clog << "Third check." << endl;
                checkData(scn3);

                // Do some visiting.
                ScenarioPrettyPrinter scnpp;
                scn3.accept(scnpp);

                failed = false;
            } catch (InvalidArgumentException &iae) {
                clog << iae.toString() << endl;
            }
            TS_ASSERT(!failed);
        }

        void checkData(const Scenario &scn) {
            TS_ASSERT(scn.getHeader().getName() == "Test-Scenario");
            TS_ASSERT(scn.getHeader().getVersion() == "v1.0");
            TS_ASSERT(scn.getHeader().getDate() == "July-15-2008");
            TS_ASSERT(scn.getHeader().getWGS84CoordinateSystem().getType() == "WGS84");
            TS_ASSERT_DELTA(scn.getHeader().getWGS84CoordinateSystem().getRotation(), 0, 1e-5);
            TS_ASSERT_DELTA(scn.getHeader().getWGS84CoordinateSystem().getOrigin().getX(), 52.247041, 1e-6);
            TS_ASSERT_DELTA(scn.getHeader().getWGS84CoordinateSystem().getOrigin().getY(), 10.575832, 1e-6);

            TS_ASSERT(scn.getGround().getName() == "Groundlayer");
            TS_ASSERT(scn.getGround().getAerialImage().getFileName() == "Test1.png");
            TS_ASSERT(scn.getGround().getAerialImage().getOriginX() == 1630);
            TS_ASSERT(scn.getGround().getAerialImage().getOriginY() == 2420);
            TS_ASSERT_DELTA(scn.getGround().getAerialImage().getMeterPerPixelX(), 0.202, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getAerialImage().getMeterPerPixelY(), 0.197, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getAerialImage().getRotationZ(), 0, 1e-3);
            TS_ASSERT(scn.getGround().getHeightImage().getFileName() == "Test2.png");
            TS_ASSERT(scn.getGround().getHeightImage().getOriginX() == 1631);
            TS_ASSERT(scn.getGround().getHeightImage().getOriginY() == 2421);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getMeterPerPixelX(), 0.302, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getMeterPerPixelY(), 0.297, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getRotationZ(), 1, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getGroundHeight(), 127, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getMinimumHeight(), -0.4, 1e-3);
            TS_ASSERT_DELTA(scn.getGround().getHeightImage().getMaximumHeight(), 1.2, 1e-3);

            const vector<opendlv::data::scenario::Shape*> &listOfShapes = scn.getGround().getSurroundings().getListOfShapes();
            TS_ASSERT(listOfShapes.size() == 3);

            TS_ASSERT(listOfShapes.at(0)->getType() == opendlv::data::scenario::Shape::CYLINDER);
            Cylinder *c = dynamic_cast<Cylinder*>(listOfShapes.at(0));
            TS_ASSERT(c->getType() == opendlv::data::scenario::Shape::CYLINDER);
            TS_ASSERT(c->getName() == "Cylinder1");
            TS_ASSERT_DELTA(c->getCenter().getX(), 42.1, 1e-3);
            TS_ASSERT_DELTA(c->getCenter().getY(), -42.5, 1e-3);
            TS_ASSERT_DELTA(c->getRadius(), 5.2, 1e-3);
            TS_ASSERT_DELTA(c->getHeight(), 7, 1e-3);
            TS_ASSERT_DELTA(c->getColor().getX(), 0, 1e-3);
            TS_ASSERT_DELTA(c->getColor().getY(), 1, 1e-3);
            TS_ASSERT_DELTA(c->getColor().getZ(), 0, 1e-3);

            TS_ASSERT(listOfShapes.at(1)->getType() == opendlv::data::scenario::Shape::POLYGON);
            opendlv::data::scenario::Polygon *p = dynamic_cast<opendlv::data::scenario::Polygon*>(listOfShapes.at(1));
            TS_ASSERT(p->getType() == opendlv::data::scenario::Shape::POLYGON);
            TS_ASSERT(p->getName() == "Polygon1");
            TS_ASSERT_DELTA(p->getHeight(), 4, 1e-3);
            TS_ASSERT_DELTA(p->getColor().getX(), 1, 1e-3);
            TS_ASSERT_DELTA(p->getColor().getY(), 0, 1e-3);
            TS_ASSERT_DELTA(p->getColor().getZ(), 1, 1e-3);
            const vector<opendlv::data::scenario::Vertex3>& listOfVertices = p->getListOfVertices();
            TS_ASSERT(listOfVertices.size() == 2);
            TS_ASSERT_DELTA(listOfVertices.at(0).getX(), 2.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices.at(0).getY(), -2.5, 1e-5);
            TS_ASSERT_DELTA(listOfVertices.at(1).getX(), 22.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices.at(1).getY(), -22.5, 1e-5);

            TS_ASSERT(listOfShapes.at(2)->getType() == opendlv::data::scenario::Shape::COMPLEXMODEL);
            opendlv::data::scenario::ComplexModel *cm = dynamic_cast<opendlv::data::scenario::ComplexModel*>(listOfShapes.at(2));
            TS_ASSERT(cm->getType() == opendlv::data::scenario::Shape::COMPLEXMODEL);
            TS_ASSERT(cm->getName() == "ComplexModel1");
            TS_ASSERT(cm->getModelFile() == "Test2.3ds");
            const opendlv::data::scenario::Vertex3 &position = cm->getPosition();
            TS_ASSERT_DELTA(position.getX(), 1.1, 1e-5);
            TS_ASSERT_DELTA(position.getY(), -1.5, 1e-5);
            TS_ASSERT_DELTA(position.getZ(), 5.5, 1e-5);

            const opendlv::data::scenario::Vertex3 &rotation = cm->getRotation();
            TS_ASSERT_DELTA(rotation.getX(), 0.1, 1e-5);
            TS_ASSERT_DELTA(rotation.getY(), -0.5, 1e-5);
            TS_ASSERT_DELTA(rotation.getZ(), 0.5, 1e-5);

            const opendlv::data::scenario::BoundingBox &bb = cm->getBoundingBox();
            TS_ASSERT_DELTA(bb.getUpperLeft().getX(), 1.1, 1e-5);
            TS_ASSERT_DELTA(bb.getUpperLeft().getY(), 1.2, 1e-5);
            TS_ASSERT_DELTA(bb.getUpperRight().getX(), 2.1, 1e-5);
            TS_ASSERT_DELTA(bb.getUpperRight().getY(), 2.2, 1e-5);
            TS_ASSERT_DELTA(bb.getLowerRight().getX(), 3.1, 1e-5);
            TS_ASSERT_DELTA(bb.getLowerRight().getY(), 3.2, 1e-5);
            TS_ASSERT_DELTA(bb.getLowerLeft().getX(), 4.1, 1e-5);
            TS_ASSERT_DELTA(bb.getLowerLeft().getY(), 4.2, 1e-5);

            TS_ASSERT(scn.getListOfLayers().size() == 1);
            const vector<opendlv::data::scenario::Layer> &listOfLayers = scn.getListOfLayers();
            TS_ASSERT_DELTA(listOfLayers.at(0).getHeight(), 0.1, 1e-3);
            TS_ASSERT(listOfLayers.at(0).getID() == 1);
            TS_ASSERT(listOfLayers.at(0).getName() == "FirstLayer");

            const vector<opendlv::data::scenario::Road> &listOfRoads = listOfLayers.at(0).getListOfRoads();
            TS_ASSERT(listOfRoads.size() == 1);
            TS_ASSERT(listOfRoads.at(0).getID() == 1);
            TS_ASSERT(listOfRoads.at(0).getName() == "Road1");

            const vector<opendlv::data::scenario::Lane> &listOfLanes = listOfRoads.at(0).getListOfLanes();
            TS_ASSERT(listOfLanes.size() == 4);
            TS_ASSERT(listOfLanes.at(0).getID() == 1);
            TS_ASSERT(listOfLanes.at(1).getID() == 2);
            TS_ASSERT(listOfLanes.at(2).getID() == 3);
            TS_ASSERT(listOfLanes.at(3).getID() == 4);

            const opendlv::data::scenario::Lane& lane1 = listOfLanes.at(0);
            const vector<opendlv::data::scenario::Connector> &listOfConnectorsLane1 = lane1.getLaneModel()->getListOfConnectors();
            TS_ASSERT(listOfConnectorsLane1.size() == 2);
            TS_ASSERT(listOfConnectorsLane1.at(0).toString() == "(1.1.1.2) -> (1.1.2.1)");
            TS_ASSERT(listOfConnectorsLane1.at(1).toString() == "(3.2.1.2) -> (3.5.2.1)");

            const opendlv::data::scenario::LaneAttribute& la = lane1.getLaneModel()->getLaneAttribute();
            TS_ASSERT_DELTA(la.getWidth(), 4.5, 1e-3);
            TS_ASSERT(la.getLeftLaneMarking() == opendlv::data::scenario::LaneAttribute::SOLID_YELLOW);
            TS_ASSERT(la.getRightLaneMarking() == opendlv::data::scenario::LaneAttribute::SOLID_WHITE);

            const vector<opendlv::data::scenario::TrafficControl*> listOfTrafficControlsLane1 = lane1.getLaneModel()->getListOfTrafficControls();
            TS_ASSERT(listOfTrafficControlsLane1.size() == 1);

            const opendlv::data::scenario::TrafficLight *tl = dynamic_cast<opendlv::data::scenario::TrafficLight*>(listOfTrafficControlsLane1.at(0));
            TS_ASSERT(tl != NULL);
            TS_ASSERT(tl->getName() == "TrafficLight1");
            TS_ASSERT(tl->getPosition().getID() == 1);
            TS_ASSERT_DELTA(tl->getPosition().getX(), 832.1, 1e-4);
            TS_ASSERT_DELTA(tl->getPosition().getY(), -832.5, 1e-4);

            const opendlv::data::scenario::Cylinder *tlc = dynamic_cast<opendlv::data::scenario::Cylinder*>(tl->getShape());
            TS_ASSERT(tlc != NULL);
            TS_ASSERT(tlc->getName() == "TrafficLightCylinder1");
            TS_ASSERT_DELTA(tlc->getCenter().getX(), 832.1, 1e-3);
            TS_ASSERT_DELTA(tlc->getCenter().getY(), -832.5, 1e-3);
            TS_ASSERT_DELTA(tlc->getRadius(), 0.3, 1e-3);
            TS_ASSERT_DELTA(tlc->getHeight(), 7, 1e-3);
            TS_ASSERT_DELTA(tlc->getColor().getX(), 0, 1e-1);
            TS_ASSERT_DELTA(tlc->getColor().getY(), 1, 1e-1);
            TS_ASSERT_DELTA(tlc->getColor().getZ(), 0, 1e-1);

            opendlv::data::scenario::PointModel *pm = dynamic_cast<opendlv::data::scenario::PointModel*>(lane1.getLaneModel());
            TS_ASSERT(pm != NULL);

            const vector<opendlv::data::scenario::IDVertex3> &listOfIdentifiableVerticesLane1 = pm->getListOfIdentifiableVertices();
            TS_ASSERT(listOfIdentifiableVerticesLane1.size() == 2);
            TS_ASSERT(listOfIdentifiableVerticesLane1.at(0).getID() == 1);
            TS_ASSERT_DELTA(listOfIdentifiableVerticesLane1.at(0).getX(), 32.1, 1e-3);
            TS_ASSERT_DELTA(listOfIdentifiableVerticesLane1.at(0).getY(), -32.5, 1e-3);
            TS_ASSERT(listOfIdentifiableVerticesLane1.at(1).getID() == 2);
            TS_ASSERT_DELTA(listOfIdentifiableVerticesLane1.at(1).getX(), 52.1, 1e-3);
            TS_ASSERT_DELTA(listOfIdentifiableVerticesLane1.at(1).getY(), -52.5, 1e-3);

            const opendlv::data::scenario::Lane& lane2 = listOfLanes.at(1);
            opendlv::data::scenario::StraightLine *sl = dynamic_cast<StraightLine*>(lane2.getLaneModel());
            TS_ASSERT(sl != NULL);

            const vector<opendlv::data::scenario::TrafficControl*> listOfTrafficControlsLane2 = lane2.getLaneModel()->getListOfTrafficControls();
            TS_ASSERT(listOfTrafficControlsLane2.size() == 1);

            const opendlv::data::scenario::TrafficSign *ts = dynamic_cast<opendlv::data::scenario::TrafficSign*>(listOfTrafficControlsLane2.at(0));
            TS_ASSERT(ts != NULL);
            TS_ASSERT(ts->getName() == "Stopline1");
            TS_ASSERT(ts->getValue() == "stopline");
            TS_ASSERT(ts->getPosition().getID() == 1);
            TS_ASSERT_DELTA(ts->getPosition().getX(), 932.1, 1e-4);
            TS_ASSERT_DELTA(ts->getPosition().getY(), -932.5, 1e-4);

            const opendlv::data::scenario::Polygon *tsp = dynamic_cast<opendlv::data::scenario::Polygon*>(ts->getShape());
            TS_ASSERT(tsp != NULL);
            TS_ASSERT(tsp->getName() == "StoplinePolygon1");
            TS_ASSERT_DELTA(tsp->getHeight(), 1, 1e-3);
            TS_ASSERT_DELTA(tsp->getColor().getX(), 1, 1e-1);
            TS_ASSERT_DELTA(tsp->getColor().getY(), 1, 1e-1);
            TS_ASSERT_DELTA(tsp->getColor().getZ(), 1, 1e-1);

            const vector<opendlv::data::scenario::Vertex3> &tspVertices = tsp->getListOfVertices();
            TS_ASSERT(tspVertices.size() == 2);
            TS_ASSERT_DELTA(tspVertices.at(0).getX(), 932.1, 1e-3);
            TS_ASSERT_DELTA(tspVertices.at(0).getY(), -932.5, 1e-3);
            TS_ASSERT_DELTA(tspVertices.at(1).getX(), 932.1, 1e-3);
            TS_ASSERT_DELTA(tspVertices.at(1).getY(), -932.7, 1e-3);

            TS_ASSERT(sl->getStart().getID() == 1);
            TS_ASSERT_DELTA(sl->getStart().getX(), 662.1, 1e-3);
            TS_ASSERT_DELTA(sl->getStart().getY(), -662.5, 1e-3);
            TS_ASSERT(sl->getEnd().getID() == 2);
            TS_ASSERT_DELTA(sl->getEnd().getX(), 772.1, 1e-3);
            TS_ASSERT_DELTA(sl->getEnd().getY(), -772.5, 1e-3);

            const opendlv::data::scenario::Lane& lane3 = listOfLanes.at(2);
            const vector<opendlv::data::scenario::Connector> listOfConnectorsLane3 = lane3.getLaneModel()->getListOfConnectors();
            TS_ASSERT(listOfConnectorsLane3.size() == 1);
            TS_ASSERT(listOfConnectorsLane3.at(0).toString() == "(3.3.3.3) -> (1.1.2.1)");

            opendlv::data::scenario::Clothoid *cl = dynamic_cast<opendlv::data::scenario::Clothoid*>(lane3.getLaneModel());
            TS_ASSERT(cl != NULL);

            TS_ASSERT(cl->getStart().getID() == 1);
            TS_ASSERT_DELTA(cl->getDK(), -0.0000234065942902206, 1e-19);
#ifndef WIN32
            TS_ASSERT_DELTA(cl->getK(), 0.0036564644663092702, 1e-19);
#endif
            TS_ASSERT_DELTA(cl->getStart().getX(), 5662.1, 1e-3);
            TS_ASSERT_DELTA(cl->getStart().getY(), -5662.5, 1e-3);
            TS_ASSERT(cl->getEnd().getID() == 2);
            TS_ASSERT_DELTA(cl->getEnd().getX(), 5772.1, 1e-3);
            TS_ASSERT_DELTA(cl->getEnd().getY(), -5772.5, 1e-3);
            TS_ASSERT_DELTA(cl->getRotationZ(), -0.3, 1e-3);

            const opendlv::data::scenario::Lane& lane4 = listOfLanes.at(3);
            opendlv::data::scenario::Arc *a = dynamic_cast<opendlv::data::scenario::Arc*>(lane4.getLaneModel());
            TS_ASSERT(a != NULL);

            TS_ASSERT(a->getStart().getID() == 1);
            TS_ASSERT_DELTA(a->getRadius(), 20, 1e-3);
            TS_ASSERT_DELTA(a->getBeginInterval(), 0, 1e-3);
            TS_ASSERT_DELTA(a->getEndInterval(), 0.785398164, 1e-9);
            TS_ASSERT_DELTA(a->getStart().getX(), 7662.1, 1e-3);
            TS_ASSERT_DELTA(a->getStart().getY(), -7662.5, 1e-3);
            TS_ASSERT(a->getEnd().getID() == 2);
            TS_ASSERT_DELTA(a->getEnd().getX(), 7772.1, 1e-3);
            TS_ASSERT_DELTA(a->getEnd().getY(), -7772.5, 1e-3);
            TS_ASSERT_DELTA(a->getRotationZ(), 0, 1e-3);

            const vector<Zone> &listOfZones = listOfLayers.at(0).getListOfZones();
            TS_ASSERT(listOfZones.size() == 3);
            TS_ASSERT(listOfZones.at(0).getID() == 1);
            TS_ASSERT(listOfZones.at(0).getName() == "Zone1");

            const Zone& zone1 = listOfZones.at(0);
            const vector<Connector> listOfConnectorsZone1 = zone1.getListOfConnectors();
            TS_ASSERT(listOfConnectorsZone1.size() == 1);
            TS_ASSERT(listOfConnectorsZone1.at(0).toString() == "(1.1.1.1) -> (1.1.2.1)");

            const Zone& zone2 = listOfZones.at(1);
            const vector<Connector> listOfConnectorsZone2 = zone2.getListOfConnectors();
            TS_ASSERT(listOfConnectorsZone2.size() == 1);
            TS_ASSERT(listOfConnectorsZone2.at(0).toString() == "(2.2.2.2) -> (1.1.2.1)");

            const vector<IDVertex3> &listOfIDVertex3 = listOfZones.at(0).getPerimeter().getListOfIdentifiableVertices();
            TS_ASSERT(listOfIDVertex3.size() == 3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(0).getX(), 33.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(0).getY(), -33.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(1).getX(), 55.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(1).getY(), -55.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(2).getX(), 66.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3.at(2).getY(), -66.5, 1e-3);

            const vector<Spot> &listOfSpots = listOfZones.at(0).getListOfSpots();
            TS_ASSERT(listOfSpots.size() == 1);
            TS_ASSERT_DELTA(listOfSpots.at(0).getFirstVertex().getX(), 77.1, 1e-3);
            TS_ASSERT_DELTA(listOfSpots.at(0).getFirstVertex().getY(), -77.5, 1e-3);
            TS_ASSERT_DELTA(listOfSpots.at(0).getSecondVertex().getX(), 78.1, 1e-3);
            TS_ASSERT_DELTA(listOfSpots.at(0).getSecondVertex().getY(), -78.5, 1e-3);

            TS_ASSERT(listOfZones.at(1).getID() == 2);
            TS_ASSERT(listOfZones.at(1).getName() == "Zone2");

            const vector<IDVertex3> &listOfIDVertex3_zone2 = listOfZones.at(1).getPerimeter().getListOfIdentifiableVertices();
            TS_ASSERT(listOfIDVertex3_zone2.size() == 3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(0).getX(), 233.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(0).getY(), -233.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(1).getX(), 255.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(1).getY(), -255.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(2).getX(), 266.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone2.at(2).getY(), -266.5, 1e-3);

            TS_ASSERT(listOfZones.at(2).getID() == 3);
            TS_ASSERT(listOfZones.at(2).getName() == "Zone3");

            const vector<IDVertex3> &listOfIDVertex3_zone3 = listOfZones.at(2).getPerimeter().getListOfIdentifiableVertices();
            TS_ASSERT(listOfIDVertex3_zone3.size() == 3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(0).getX(), 333.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(0).getY(), -333.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(1).getX(), 355.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(1).getY(), -355.5, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(2).getX(), 366.1, 1e-3);
            TS_ASSERT_DELTA(listOfIDVertex3_zone3.at(2).getY(), -366.5, 1e-3);
        }
};

#endif /*HESPERIA_SCENARIOTESTSUITE_H_*/
