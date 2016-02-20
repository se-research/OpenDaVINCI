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

#ifndef HESPERIA_SITUATIONTESTSUITE_H_
#define HESPERIA_SITUATIONTESTSUITE_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendlv/data/situation/ComplexModel.h"
#include "opendlv/data/situation/Immediately.h"
#include "opendlv/data/situation/Object.h"
#include "opendlv/data/situation/OnEnteringPolygon.h"
#include "opendlv/data/situation/OnMoving.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/situation/PointIDDriver.h"
#include "opendlv/data/situation/Polygon.h"
#include "opendlv/data/situation/Rectangle.h"
#include "opendlv/data/situation/Situation.h"
#include "opendlv/data/situation/ReturnToStart.h"
#include "opendlv/data/situation/StartType.h"
#include "opendlv/data/situation/Stop.h"
#include "opendlv/data/situation/StopType.h"
#include "opendlv/data/situation/WarpToStart.h"
#include "opendlv/data/situation/Vertex3.h"
#include "opendlv/situation/SituationFactory.h"
#include "opendlv/situation/SituationPrettyPrinter.h"

using namespace std;
using namespace opendlv::data::situation;
using namespace odcore::exceptions;
using namespace opendlv::situation;
using namespace core::wrapper::parser;

class SituationTest : public CxxTest::TestSuite {
    public:
        void testParsingCorruptSITGrammar() {
            stringstream s;
            s << "SITUATION" << " " << "Test-Situation" << endl
            << "VERSION"  << " " << "v1.0" << endl
            << "DATE3"     << " " << "July-15-2008" << endl
            << "SCENARIO"     << " " << "Test-Szenario" << endl;

            bool failed = true;
            try {
                Situation sit = SituationFactory::getInstance().getSituation(s.str());
            } catch (InvalidArgumentException &iae) {
                //failed = (iae.toString() != "InvalidArgumentException: SITGrammarErrorListener caught an unknown parser error at line: 3 in context \'SITUATION Test-Situation\nVERSION v1.0\n===Erroneous line===>>> DATE3 July-15-2008\nSCENARIO Test-Szenario\n\'. at build/libopendlv/testing/src/situation/SituationFactory.cpp: 60");
                failed = false;
            }
            TS_ASSERT(!failed);
        }

        void testParsingSITGrammar() {
            stringstream s;
            s << "SITUATION" << " " << "Test-Situation" << endl
            << "VERSION"  << " " << "v1.0" << endl
            << "DATE"     << " " << "July-15-2008" << endl
            << "SCENARIO"     << " " << "Test-Szenario" << endl

            << "OBJECT" << " " << "Test-Objekt1" << endl
            << "OBJECTID" << " " << "1" << endl
            << "SHAPENAME" << " " << "Test-Polygon1" << endl
            << "POLYGON" << endl
            << "HEIGHT" << " " << "10.54321" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X" << " " << "0.1" << endl
            << "Y" << " " << "0.2" << endl
            << "Z" << " " << "0.3" << endl
            << "VERTEX2" << endl
            << "X" << " " << "1.1" << endl
            << "Y" << " " << "2.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "3.1" << endl
            << "Y" << " " << "4.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "5.1" << endl
            << "Y" << " " << "6.2" << endl
            << "ROTZ" << " " << "1.23456" << endl
            << "BEHAVIOR" << endl
            << "EXTERNALDRIVER" << endl
            << "ENDOBJECT" << endl

            << "OBJECT" << " " << "Test-Objekt2" << endl
            << "OBJECTID" << " " << "2" << endl
            << "SHAPENAME" << " " << "Test-Rectangle2" << endl
            << "RECTANGLE" << endl
            << "HEIGHT" << " " << "9.54321" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X" << " " << "0.5" << endl
            << "Y" << " " << "0.6" << endl
            << "Z" << " " << "0.7" << endl
            << "VERTEX2" << endl
            << "X" << " " << "11.1" << endl
            << "Y" << " " << "12.2" << endl
            << "LENGTH" << " " << "4.2" << endl
            << "WIDTH" << " " << "5.2" << endl
            << "ROTZ" << " " << "2.34567" << endl
            << "BEHAVIOR" << endl
            << "POINTIDDRIVER" << endl
            << "STARTTYPE" << endl
            << "IMMEDIATELY" << endl
            << "STOPTYPE" << endl
            << "STOP" << endl
            << "CONSTANTACCELERATION" << endl
            << "A" << " " << "1.2" << endl
            << "(1.2.3.4)" << endl
			<< "(5.6.7.8)" << endl
            << "ENDOBJECT" << endl

            << "OBJECT" << " " << "Test-Objekt3" << endl
            << "OBJECTID" << " " << "3" << endl
            << "SHAPENAME" << " " << "Test-ComplexModel3" << endl
            << "COMPLEXMODEL" << endl
            << "MODELFILE" << " " << "models/abc.objx" << endl
            << "VERTEX2" << endl
            << "X" << " " << "8.1" << endl
            << "Y" << " " << "8.2" << endl
            << "POSITION" << endl
            << "VERTEX3" << endl
            << "X" << " " << "13.1" << endl
            << "Y" << " " << "14.2" << endl
            << "Z" << " " << "15.2" << endl
            << "ROTATION" << endl
            << "VERTEX3" << endl
            << "X" << " " << "43.1" << endl
            << "Y" << " " << "54.2" << endl
            << "Z" << " " << "61.2" << endl
            << "BOUNDINGBOX" << endl
            << "VERTEX2" << endl
            << "X" << " " << "1.1" << endl
            << "Y" << " " << "2.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "3.1" << endl
            << "Y" << " " << "4.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "5.1" << endl
            << "Y" << " " << "6.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "7.1" << endl
            << "Y" << " " << "8.2" << endl
            << "ROTZ" << " " << "5.34567" << endl
            << "BEHAVIOR" << endl
            << "POINTIDDRIVER" << endl
            << "STARTTYPE" << endl
            << "ONMOVING" << endl
            << "OBJECTID" << " " << "3" << endl
            << "STOPTYPE" << endl
            << "RETURNTOSTART" << endl
            << "CONSTANTVELOCITY" << endl
            << "V" << " " << "3.2" << endl
			<< "(9.8.7.6)" << endl
			<< "(5.4.3.2)" << endl
            << "ENDOBJECT" << endl

            << "OBJECT" << " " << "Test-Objekt4" << endl
            << "OBJECTID" << " " << "4" << endl
            << "SHAPENAME" << " " << "Test-Polygon4" << endl
            << "POLYGON" << endl
            << "HEIGHT" << " " << "11.54321" << endl
            << "COLOR" << endl
            << "VERTEX3" << endl
            << "X" << " " << "0.5" << endl
            << "Y" << " " << "0.6" << endl
            << "Z" << " " << "0.7" << endl
            << "VERTEX2" << endl
            << "X" << " " << "11.1" << endl
            << "Y" << " " << "12.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "13.1" << endl
            << "Y" << " " << "14.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "15.1" << endl
            << "Y" << " " << "16.2" << endl
            << "ROTZ" << " " << "6.34567" << endl
            << "BEHAVIOR" << endl
            << "POINTIDDRIVER" << endl
            << "STARTTYPE" << endl
            << "ONENTERINGPOLYGON" << endl
            << "OBJECTID" << " " << "1" << endl
            << "VERTEX2" << endl
            << "X" << " " << "31.1" << endl
            << "Y" << " " << "32.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "41.1" << endl
            << "Y" << " " << "42.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "51.1" << endl
            << "Y" << " " << "52.2" << endl
            << "VERTEX2" << endl
            << "X" << " " << "61.1" << endl
            << "Y" << " " << "62.2" << endl
            << "STOPTYPE" << endl
            << "WARPTOSTART" << endl
            << "CONSTANTVELOCITY" << endl
            << "V" << " " << "31.2" << endl
			<< "(8.7.6.5)" << endl
			<< "(4.3.2.1)" << endl
            << "ENDOBJECT" << endl

            << "ENDSITUATION" << endl;

            bool failed = true;
            try {
                Situation sit = SituationFactory::getInstance().getSituation(s.str());

                // Test original.
                clog << "First check." << endl;
                checkData(sit);

                // Test deep copy.
                Situation sit2(sit);
                clog << "Second check." << endl;
                checkData(sit2);

                // Test serialized data.
                stringstream sstr;
                sstr << sit2;
                Situation sit3;
                sstr >> sit3;
                clog << "Third check." << endl;
                checkData(sit3);

                // Do some visiting.
                SituationPrettyPrinter sitpp;
                sit3.accept(sitpp);

                failed = false;
            } catch (InvalidArgumentException &iae) {
                clog << iae.toString() << endl;
            }
            TS_ASSERT(!failed);
        }

        void checkData(const Situation &sit) {
            TS_ASSERT(sit.getHeader().getName() == "Test-Situation");
            TS_ASSERT(sit.getHeader().getVersion() == "v1.0");
            TS_ASSERT(sit.getHeader().getDate() == "July-15-2008");
            TS_ASSERT(sit.getHeader().getScenario() == "Test-Szenario");

            vector<Object> listOfObjects = sit.getListOfObjects();

            TS_ASSERT(listOfObjects.size() == 4);
            TS_ASSERT(listOfObjects.at(0).getName() == "Test-Objekt1");
            TS_ASSERT(listOfObjects.at(0).getID() == 1);
            TS_ASSERT_DELTA(listOfObjects.at(0).getRotationZ(), 1.23456, 1e-5);
            opendlv::data::situation::Polygon *p1 = dynamic_cast<opendlv::data::situation::Polygon*>(listOfObjects.at(0).getShape());
            TS_ASSERT(p1 != NULL);
            TS_ASSERT(p1->getType() == opendlv::data::situation::Shape::POLYGON);
            TS_ASSERT(p1->getName() == "Test-Polygon1");
            TS_ASSERT_DELTA(p1->getHeight(), 10.5432, 1e-4);
            TS_ASSERT_DELTA(p1->getFront().getX(), 1.1, 1e-3);
            TS_ASSERT_DELTA(p1->getFront().getY(), 2.2, 1e-3);
            TS_ASSERT_DELTA(p1->getFront().getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(p1->getColor().getX(), 0.1, 1e-3);
            TS_ASSERT_DELTA(p1->getColor().getY(), 0.2, 1e-3);
            TS_ASSERT_DELTA(p1->getColor().getZ(), 0.3, 1e-3);
            const vector<opendlv::data::situation::Vertex3>& listOfVertices1 = p1->getListOfVertices();
            TS_ASSERT(listOfVertices1.size() == 2);
            TS_ASSERT_DELTA(listOfVertices1.at(0).getX(), 3.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices1.at(0).getY(), 4.2, 1e-5);
            TS_ASSERT_DELTA(listOfVertices1.at(0).getZ(), 0, 1e-5);
            TS_ASSERT_DELTA(listOfVertices1.at(1).getX(), 5.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices1.at(1).getY(), 6.2, 1e-5);
            TS_ASSERT_DELTA(listOfVertices1.at(1).getZ(), 0, 1e-5);
            TS_ASSERT(listOfObjects.at(0).getBehavior()->getType() == opendlv::data::situation::Behavior::EXTERNALDRIVER);


            TS_ASSERT(listOfObjects.at(1).getName() == "Test-Objekt2");
            TS_ASSERT(listOfObjects.at(1).getID() == 2);
            TS_ASSERT_DELTA(listOfObjects.at(1).getRotationZ(), 2.34567, 1e-5);
            Rectangle *r2 = dynamic_cast<Rectangle*>(listOfObjects.at(1).getShape());
            TS_ASSERT(r2 != NULL);
            TS_ASSERT(r2->getType() == opendlv::data::situation::Shape::RECTANGLE);
            TS_ASSERT(r2->getName() == "Test-Rectangle2");
            TS_ASSERT_DELTA(r2->getHeight(), 9.54321, 1e-5);
            TS_ASSERT_DELTA(r2->getFront().getX(), 11.1, 1e-3);
            TS_ASSERT_DELTA(r2->getFront().getY(), 12.2, 1e-3);
            TS_ASSERT_DELTA(r2->getFront().getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(r2->getLength(), 4.2, 1e-3);
            TS_ASSERT_DELTA(r2->getWidth(), 5.2, 1e-3);
            TS_ASSERT(listOfObjects.at(1).getBehavior()->getType() == opendlv::data::situation::Behavior::POINTIDDRIVER);
            TS_ASSERT(dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()) != NULL);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getConstantAcceleration(), 1.2, 1e-4);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getConstantVelocity(), 0, 1e-4);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getStartType()->getType() == opendlv::data::situation::StartType::IMMEDIATELY);
            TS_ASSERT(dynamic_cast<Immediately*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getStartType()) != NULL);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getStopType()->getType() == opendlv::data::situation::StopType::STOP);
            TS_ASSERT(dynamic_cast<Stop*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior()))->getStopType()) != NULL);
            vector<opendlv::data::situation::PointID> o1PIDs = dynamic_cast<PointIDDriver*>(listOfObjects.at(1).getBehavior())->getListOfPointIDs();
            TS_ASSERT(o1PIDs.size() == 2);
            TS_ASSERT(o1PIDs.at(0).toString() == "1.2.3.4");
            TS_ASSERT(o1PIDs.at(1).toString() == "5.6.7.8");


            TS_ASSERT(listOfObjects.at(2).getName() == "Test-Objekt3");
            TS_ASSERT(listOfObjects.at(2).getID() == 3);
            TS_ASSERT_DELTA(listOfObjects.at(2).getRotationZ(), 5.34567, 1e-5);
            opendlv::data::situation::ComplexModel *cm3 = dynamic_cast<opendlv::data::situation::ComplexModel*>(listOfObjects.at(2).getShape());
            TS_ASSERT(cm3 != NULL);
            TS_ASSERT(cm3->getType() == opendlv::data::situation::Shape::COMPLEXMODEL);
            TS_ASSERT(cm3->getName() == "Test-ComplexModel3");
            TS_ASSERT_DELTA(cm3->getFront().getX(), 8.1, 1e-3);
            TS_ASSERT_DELTA(cm3->getFront().getY(), 8.2, 1e-3);
            TS_ASSERT_DELTA(cm3->getFront().getZ(), 0, 1e-3);
            TS_ASSERT(cm3->getModelFile() == "models/abc.objx");
            TS_ASSERT_DELTA(cm3->getPosition().getX(), 13.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getPosition().getY(), 14.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getPosition().getZ(), 15.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getRotation().getX(), 43.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getRotation().getY(), 54.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getRotation().getZ(), 61.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperLeft().getX(), 1.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperLeft().getY(), 2.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperLeft().getZ(), 0, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperRight().getX(), 3.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperRight().getY(), 4.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getUpperRight().getZ(), 0, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerRight().getX(), 5.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerRight().getY(), 6.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerRight().getZ(), 0, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerLeft().getX(), 7.1, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerLeft().getY(), 8.2, 1e-4);
            TS_ASSERT_DELTA(cm3->getBoundingBox().getLowerLeft().getZ(), 0, 1e-4);
            TS_ASSERT(listOfObjects.at(2).getBehavior()->getType() == opendlv::data::situation::Behavior::POINTIDDRIVER);
            TS_ASSERT(dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()) != NULL);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getConstantAcceleration(), 0, 1e-4);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getConstantVelocity(), 3.2, 1e-4);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getStartType()->getType() == opendlv::data::situation::StartType::ONMOVING);
            TS_ASSERT(dynamic_cast<OnMoving*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getStartType()) != NULL);
            TS_ASSERT(dynamic_cast<OnMoving*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getStartType())->getID() == 3);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getStopType()->getType() == opendlv::data::situation::StopType::RETURNTOSTART);
            TS_ASSERT(dynamic_cast<ReturnToStart*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior()))->getStopType()) != NULL);
            vector<opendlv::data::situation::PointID> o2PIDs = dynamic_cast<PointIDDriver*>(listOfObjects.at(2).getBehavior())->getListOfPointIDs();
            TS_ASSERT(o2PIDs.size() == 2);
            TS_ASSERT(o2PIDs.at(0).toString() == "9.8.7.6");
            TS_ASSERT(o2PIDs.at(1).toString() == "5.4.3.2");


            TS_ASSERT(listOfObjects.at(3).getName() == "Test-Objekt4");
            TS_ASSERT(listOfObjects.at(3).getID() == 4);
            TS_ASSERT_DELTA(listOfObjects.at(3).getRotationZ(), 6.34567, 1e-5);
            opendlv::data::situation::Polygon *p4 = dynamic_cast<opendlv::data::situation::Polygon*>(listOfObjects.at(3).getShape());
            TS_ASSERT(p4 != NULL);
            TS_ASSERT(p4->getType() == opendlv::data::situation::Shape::POLYGON);
            TS_ASSERT(p4->getName() == "Test-Polygon4");
            TS_ASSERT_DELTA(p4->getHeight(), 11.5432, 1e-4);
            TS_ASSERT_DELTA(p4->getFront().getX(), 11.1, 1e-3);
            TS_ASSERT_DELTA(p4->getFront().getY(), 12.2, 1e-3);
            TS_ASSERT_DELTA(p4->getFront().getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(p4->getColor().getX(), 0.5, 1e-3);
            TS_ASSERT_DELTA(p4->getColor().getY(), 0.6, 1e-3);
            TS_ASSERT_DELTA(p4->getColor().getZ(), 0.7, 1e-3);
            const vector<opendlv::data::situation::Vertex3> listOfVertices4 = p4->getListOfVertices();
            TS_ASSERT(listOfVertices4.size() == 2);
            TS_ASSERT_DELTA(listOfVertices4.at(0).getX(), 13.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices4.at(0).getY(), 14.2, 1e-5);
            TS_ASSERT_DELTA(listOfVertices4.at(0).getZ(), 0, 1e-5);
            TS_ASSERT_DELTA(listOfVertices4.at(1).getX(), 15.1, 1e-5);
            TS_ASSERT_DELTA(listOfVertices4.at(1).getY(), 16.2, 1e-5);
            TS_ASSERT_DELTA(listOfVertices4.at(1).getZ(), 0, 1e-5);
            TS_ASSERT(listOfObjects.at(3).getBehavior()->getType() == opendlv::data::situation::Behavior::POINTIDDRIVER);
            TS_ASSERT(dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()) != NULL);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getConstantAcceleration(), 0, 1e-4);
            TS_ASSERT_DELTA((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getConstantVelocity(), 31.2, 1e-4);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStartType()->getType() == opendlv::data::situation::StartType::ONENTERINGPOLYGON);
            TS_ASSERT(dynamic_cast<OnEnteringPolygon*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStartType()) != NULL);
            OnEnteringPolygon *oep = dynamic_cast<OnEnteringPolygon*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStartType());
            TS_ASSERT(oep != NULL);
            vector<opendlv::data::situation::Vertex3> listOfVerticesOEP = oep->getListOfVertices();
            TS_ASSERT(listOfVerticesOEP.size() == 4);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(0).getX(), 31.1, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(0).getY(), 32.2, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(0).getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(1).getX(), 41.1, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(1).getY(), 42.2, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(1).getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(2).getX(), 51.1, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(2).getY(), 52.2, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(2).getZ(), 0, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(3).getX(), 61.1, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(3).getY(), 62.2, 1e-3);
            TS_ASSERT_DELTA(listOfVerticesOEP.at(3).getZ(), 0, 1e-3);
            TS_ASSERT(dynamic_cast<OnEnteringPolygon*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStartType())->getID() == 1);
            TS_ASSERT((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStopType()->getType() == opendlv::data::situation::StopType::WARPTOSTART);
            TS_ASSERT(dynamic_cast<WarpToStart*>((dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior()))->getStopType()) != NULL);
            vector<opendlv::data::situation::PointID> o3PIDs = dynamic_cast<PointIDDriver*>(listOfObjects.at(3).getBehavior())->getListOfPointIDs();
            TS_ASSERT(o3PIDs.size() == 2);
            TS_ASSERT(o3PIDs.at(0).toString() == "8.7.6.5");
            TS_ASSERT(o3PIDs.at(1).toString() == "4.3.2.1");
        }

};

#endif /*HESPERIA_SITUATIONTESTSUITE_H_*/
