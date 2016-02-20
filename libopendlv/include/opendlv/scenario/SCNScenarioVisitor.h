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

#ifndef HESPERIA_SCENARIO_SCNSCENARIOVISITOR_H_
#define HESPERIA_SCENARIO_SCNSCENARIOVISITOR_H_

#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendlv/core/wrapper/parser/ASTVisitor.h"

#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/ComplexModel.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/Cylinder.h"
#include "opendlv/data/scenario/Ground.h"
#include "opendlv/data/scenario/Header.h"
#include "opendlv/data/scenario/HeightImage.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Image.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/LaneAttribute.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/Perimeter.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/Polygon.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/Spot.h"
#include "opendlv/data/scenario/StraightLine.h"
#include "opendlv/data/scenario/Surroundings.h"
#include "opendlv/data/scenario/TrafficLight.h"
#include "opendlv/data/scenario/TrafficSign.h"
#include "opendlv/data/scenario/Vertex3.h"
#include "opendlv/data/scenario/WGS84CoordinateSystem.h"
#include "opendlv/data/scenario/Zone.h"


namespace opendlv {
    namespace scenario {

        using namespace std;

        /**
         * This class prints the parsed AST.
         */
        class SCNScenarioVisitor : public core::wrapper::parser::ASTVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SCNScenarioVisitor(const SCNScenarioVisitor &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SCNScenarioVisitor& operator=(const SCNScenarioVisitor &);

            public:
                SCNScenarioVisitor(data::scenario::Scenario &s);

                virtual ~SCNScenarioVisitor();

                virtual void visit(core::wrapper::parser::ASTNode *node) throw (odcore::exceptions::SCNScenarioVisitorException);

            private:
                data::scenario::Scenario &m_scenario;

                /**
                 * Read SCENARIOHEADER.
                 *
                 * @param node Node describing the scenario header.
                 * @return Parsed scenario header.
                 */
                const data::scenario::Header visitScenarioHeader(core::wrapper::parser::ASTNode *node);

                /**
                 * Read COORDINATESYSTEM.
                 *
                 * @param node Node describing the coordinate system.
                 * @return Parsed coordinate system.
                 */
                const data::scenario::WGS84CoordinateSystem visitCoordinateSystem(core::wrapper::parser::ASTNode *node);

                /**
                 * Read IDVERTEX2.
                 *
                 * @param node Node describing the identifiable vertex2.
                 * @return Parsed identifiable vertex2.
                 */
                const data::scenario::IDVertex3 visitIDVertex3(core::wrapper::parser::ASTNode *node);

                /**
                 * Read VERTEX3.
                 *
                 * @param node Node describing the vertex3.
                 * @return Parsed vertex3.
                 */
                const data::scenario::Vertex3 visitVertex3(core::wrapper::parser::ASTNode *node);

                /**
                 * Read GROUND.
                 *
                 * @param node Node describing the ground.
                 * @return Parsed ground.
                 */
                const data::scenario::Ground visitGround(core::wrapper::parser::ASTNode *node);

                /**
                 * Read IMAGE.
                 *
                 * @param node Node describing the image.
                 * @return Parsed image.
                 */
                const data::scenario::Image visitImage(core::wrapper::parser::ASTNode *node);

                /**
                 * Read HEIGHTIMAGE.
                 *
                 * @param node Node describing the height image.
                 * @return Parsed height image.
                 */
                const data::scenario::HeightImage visitHeightImage(core::wrapper::parser::ASTNode *node);

                /**
                 * Read SURROUNDINGS.
                 *
                 * @param node Node describing the surroundings.
                 * @return Parsed surroundings.
                 */
                const data::scenario::Surroundings visitSurroundings(core::wrapper::parser::ASTNode *node);

                /**
                 * Read SHAPE.
                 *
                 * @param node Node describing the shape.
                 * @return Parsed shape.
                 */
                data::scenario::Shape* visitShape(core::wrapper::parser::ASTNode *node);

                /**
                 * Read CYLINDER.
                 *
                 * @param node Node describing the cylinder.
                 * @return Parsed cylinder.
                 */
                data::scenario::Cylinder* visitCylinder(core::wrapper::parser::ASTNode *node);

                /**
                 * Read POLYGON.
                 *
                 * @param node Node describing the polygon.
                 * @return Parsed polygon.
                 */
                data::scenario::Polygon* visitPolygon(core::wrapper::parser::ASTNode *node);

                /**
                 * Read COMPLEXMODEL.
                 *
                 * @param node Node describing the complex model.
                 * @return Parsed complex model.
                 */
                data::scenario::ComplexModel* visitComplexModel(core::wrapper::parser::ASTNode *node);

                /**
                 * Read LAYER.
                 *
                 * @param node Node describing the layer.
                 * @return Parsed layer.
                 */
                data::scenario::Layer visitLayer(core::wrapper::parser::ASTNode *node);

                /**
                 * Read ROAD.
                 *
                 * @param node Node describing the road.
                 * @return Parsed road.
                 */
                data::scenario::Road visitRoad(core::wrapper::parser::ASTNode *node);

                /**
                 * Read LANE.
                 *
                 * @param node Node describing the lane.
                 * @return Parsed lane.
                 */
                data::scenario::Lane visitLane(core::wrapper::parser::ASTNode *node);

                /**
                 * Read LANEATTRIBUTE.
                 *
                 * @param node Node describing the lane's attributes.
                 * @return Parsed lane attribute.
                 */
                data::scenario::LaneAttribute visitLaneAttribute(core::wrapper::parser::ASTNode *node);

                /**
                 * Read TRAFFICLIGHT.
                 *
                 * @param node Node describing the traffic light.
                 * @return Parsed traffic light.
                 */
                data::scenario::TrafficLight* visitTrafficLight(core::wrapper::parser::ASTNode *node);

                /**
                 * Read TRAFFICSIGN.
                 *
                 * @param node Node describing the traffic sign.
                 * @return Parsed traffic sign.
                 */
                data::scenario::TrafficSign* visitTrafficSign(core::wrapper::parser::ASTNode *node);

                /**
                 * This method gets the proper boundary style
                 * from the given string.
                 *
                 * @param s String to be parsed.
                 * @return Boundary style.
                 */
                enum data::scenario::LaneAttribute::BOUNDARYSTYLE getBoundaryStyle(const string &s) const;

                /**
                 * Read ZONE.
                 *
                 * @param node Node describing the zone.
                 * @return Parsed zone.
                 */
                data::scenario::Zone visitZone(core::wrapper::parser::ASTNode *node);

                /**
                 * Read PERIMETER.
                 *
                 * @param node Node describing the perimeter.
                 * @return Parsed perimeter.
                 */
                data::scenario::Perimeter visitPerimeter(core::wrapper::parser::ASTNode *node);

                /**
                 * Read SPOT.
                 *
                 * @param node Node describing the spot.
                 * @return Parsed spot.
                 */
                data::scenario::Spot visitSpot(core::wrapper::parser::ASTNode *node);

                /**
                 * Read CONNECTOR.
                 *
                 * @param node Node describing the connector.
                 * @return Parsed connector.
                 */
                data::scenario::Connector visitConnector(core::wrapper::parser::ASTNode *node);

                /**
                 * Read ARC.
                 *
                 * @param node Node describing the arc.
                 * @return Parsed arc.
                 */
                data::scenario::Arc* visitArc(core::wrapper::parser::ASTNode *node);

                /**
                 * Read CLOTHOID.
                 *
                 * @param node Node describing the clothoid.
                 * @return Parsed clothoid.
                 */
                data::scenario::Clothoid* visitClothoid(core::wrapper::parser::ASTNode *node);

                /**
                 * Read POINTMODEL.
                 *
                 * @param node Node describing the point model.
                 * @return Parsed point model.
                 */
                data::scenario::PointModel* visitPointModel(core::wrapper::parser::ASTNode *node);

                /**
                 * Read STRAIGHTLINE.
                 *
                 * @param node Node describing the straight line.
                 * @return Parsed straight line.
                 */
                data::scenario::StraightLine* visitStraightLine(core::wrapper::parser::ASTNode *node);

                /**
                 * This method tries to find a node with the given key.
                 *
                 * @param key Key to be found.
                 * @param node Node from which the search should be started.
                 * @param maxDepth Maximum depth to descend.
                 * @return Node or NULL.
                 */
                core::wrapper::parser::ASTNode* findByKey(const string &key, odcore::wrapper::parser::ASTNode *node, const int32_t &maxDepth);

                /**
                 * This method tries to find a node with the given value.
                 *
                 * @param value Value to be found.
                 * @param node Node from which the search should be started.
                 * @param maxDepth Maximum depth to descend.
                 * @return Node or NULL.
                 */
                core::wrapper::parser::ASTNode* findByValue(const string &value, odcore::wrapper::parser::ASTNode *node, const int32_t &maxDepth);
        };

    }
} // opendlv::scenario

#endif /*HESPERIA_SCENARIO_SCNSCENARIOVISITOR_H_*/
