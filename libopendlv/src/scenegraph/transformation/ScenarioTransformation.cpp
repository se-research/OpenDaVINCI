/**
 * hesperia - Simulation environment
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

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/LaneAttribute.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/Perimeter.h"
#include "opendlv/data/scenario/Polygon.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/scenario/StraightLine.h"
#include "opendlv/data/scenario/Surroundings.h"
#include "opendlv/data/scenario/TrafficControl.h"
#include "opendlv/data/scenario/TrafficSign.h"
#include "opendlv/data/scenario/Zone.h"
#include "opendlv/scenegraph/SceneNode.h"
#include "opendlv/scenegraph/SceneNodeDescriptor.h"
#include "opendlv/scenegraph/transformation/ScenarioTransformation.h"
#include "opendlv/scenegraph/primitives/Line.h"
#include "opendlv/scenegraph/primitives/Point.h"
#include "opendlv/scenegraph/primitives/Polygon.h"

namespace hesperia { namespace data { namespace scenario { class Shape; } } }

namespace hesperia {
    namespace scenegraph {
        namespace transformation {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;
            using namespace data::scenario;

            ScenarioTransformation::ScenarioTransformation() :
                m_root(NULL),
                m_renderLaneConnectors(true) {
                m_root = new hesperia::scenegraph::SceneNode();
            }

            ScenarioTransformation::ScenarioTransformation(const bool &renderLaneConnectors) :
                m_root(NULL),
                m_renderLaneConnectors(renderLaneConnectors) {
                m_root = new hesperia::scenegraph::SceneNode();
            }

            ScenarioTransformation::~ScenarioTransformation() {}

            hesperia::scenegraph::SceneNode* ScenarioTransformation::getRoot() const {
                return m_root;
            }

            void ScenarioTransformation::transform(Surroundings &surroundings, hesperia::scenegraph::SceneNode *sn) {
                vector<Shape*> listOfShapes = surroundings.getListOfShapes();
                vector<Shape*>::const_iterator it = listOfShapes.begin();
                while (it != listOfShapes.end()) {
                    Shape *s = (*it++);
                    if ( (s != NULL) && (s->getType() == Shape::POLYGON) ) {
                        Polygon *p = dynamic_cast<Polygon*>(s);
                        if (p != NULL) {
                            vector<Point3> vertices;

                            // Convert vertices.
                            const vector<Vertex3> &originalVertices = p->getListOfVertices();
                            vector<Vertex3>::const_iterator jt = originalVertices.begin();
                            while (jt != originalVertices.end()) {
                                Vertex3 v3 = (*jt++);
                                vertices.push_back(v3);
                            }

                            Point3 color(p->getColor());
                            sn->addChild(new hesperia::scenegraph::primitives::Polygon(hesperia::scenegraph::SceneNodeDescriptor(p->getName()), vertices, color, static_cast<float>(p->getHeight())));
                        }
                    }
                }
            }

            void ScenarioTransformation::transform(const Layer &layer, const Road &road, const Lane &lane, const PointModel &pointModel, hesperia::scenegraph::SceneNode *layerSceneNode) {
                const vector<IDVertex3> &listOfVertices = pointModel.getListOfIdentifiableVertices();
                const uint32_t SIZE = listOfVertices.size();
                if (SIZE > 1) {
                    for (uint32_t i = 0; i < (SIZE-1); i++) {
                        // Get to adjacent vertices, determine direction, construct orthogonal direction
                        Point3 ptA = listOfVertices.at(i);
                        ptA.setZ(layer.getHeight());

                        Point3 ptB = listOfVertices.at(i+1);
                        ptB.setZ(layer.getHeight());

                        stringstream namePtA;
                        namePtA << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << listOfVertices.at(i).getID();

                        stringstream namePtB;
                        namePtB << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << listOfVertices.at(i+1).getID();

                        if (m_renderLaneConnectors) {
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtA.str()), ptA, Point3(1, 0, 0), 5));
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtB.str()), ptB, Point3(1, 0, 0), 5));
                        }
/*
                        Point3 colorSkeleton(0.05, 0.05, 0.05);
                        stringstream nameLane;
                        nameLane << "Lane: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(nameLane.str()), ptA, ptB, colorSkeleton, 1));
*/
                        const double halfWidth = pointModel.getLaneAttribute().getWidth() / 2.0;
                        if (halfWidth > 1) {
                            Point3 orthonormalDirection = (ptB - ptA);
                            orthonormalDirection.normalizeXY();
                            orthonormalDirection.setZ(0);
                            orthonormalDirection.rotateZ(cartesian::Constants::PI/2.0);

                            Point3 colorLeftMarking;
                            switch (pointModel.getLaneAttribute().getLeftLaneMarking()) {
                                case LaneAttribute::SOLID_YELLOW:
                                case LaneAttribute::DOUBLE_YELLOW:
                                    colorLeftMarking = Point3(1, 1, 0);
                                break;

                                case LaneAttribute::BROKEN_WHITE:
                                case LaneAttribute::SOLID_WHITE:
                                    colorLeftMarking = Point3(1, 1, 1);
                                break;

                                case LaneAttribute::UNDEFINED:
                                case LaneAttribute::CROSSWALK:
                                    colorLeftMarking = Point3(0, 0, 0);
                                break;
                            }
                            Point3 leftLanePtA = ptA + (orthonormalDirection * halfWidth);
                            Point3 leftLanePtB = ptB + (orthonormalDirection * halfWidth);

                            stringstream leftLaneMarkingName;
                            leftLaneMarkingName << "Left lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(leftLaneMarkingName.str()), leftLanePtA, leftLanePtB, colorLeftMarking, 5));

                            Point3 colorRightMarking;
                            switch (pointModel.getLaneAttribute().getRightLaneMarking()) {
                                case LaneAttribute::SOLID_YELLOW:
                                case LaneAttribute::DOUBLE_YELLOW:
                                    colorRightMarking = Point3(1, 1, 0);
                                break;

                                case LaneAttribute::BROKEN_WHITE:
                                case LaneAttribute::SOLID_WHITE:
                                    colorRightMarking = Point3(1, 1, 1);
                                break;

                                case LaneAttribute::UNDEFINED:
                                case LaneAttribute::CROSSWALK:
                                    colorRightMarking = Point3(0, 0, 0);
                                break;
                            }
                            Point3 rightLanePtA = ptA - (orthonormalDirection * halfWidth);
                            Point3 rightLanePtB = ptB - (orthonormalDirection * halfWidth);

                            stringstream rightLaneMarkingName;
                            rightLaneMarkingName << "Right lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(rightLaneMarkingName.str()), rightLanePtA, rightLanePtB, colorRightMarking, 5));
                        }
                    }
                }
            }

            void ScenarioTransformation::transform(const Layer &layer, const Road &road, const Lane &lane, const StraightLine &straightLine, hesperia::scenegraph::SceneNode *layerSceneNode) {
                // Get to adjacent vertices, determine direction, construct orthogonal direction
                Point3 ptA = straightLine.getStart();
                ptA.setZ(layer.getHeight());

                Point3 ptB = straightLine.getEnd();
                ptB.setZ(layer.getHeight());

                stringstream namePtA;
                namePtA << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << straightLine.getStart().getID();

                stringstream namePtB;
                namePtB << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << straightLine.getEnd().getID();

                if (m_renderLaneConnectors) {
                    layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtA.str()), ptA, Point3(1, 0, 0), 5));
                    layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtB.str()), ptB, Point3(1, 0, 0), 5));
                }
/*
                Point3 colorSkeleton(0.01, 0.01, 0.01);
                stringstream nameLane;
                nameLane << "Lane: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(nameLane.str()), ptA, ptB, colorSkeleton, 1));
*/
                bool brokenLeft = true;
                bool brokenRight = true;
                bool showLeft = true;
                bool showRight = true;
                const double halfWidth = straightLine.getLaneAttribute().getWidth() / 2.0;
                if (halfWidth > 1) {
                    Point3 direction = (ptB - ptA);
                    const double length = direction.lengthXY();

                    direction.normalizeXY();
                    direction.setZ(0);

                    Point3 orthonormalDirection = direction;
                    orthonormalDirection.rotateZ(cartesian::Constants::PI/2.0);

                    const double lanePart = 2.0;
                    const uint32_t steps = (uint32_t) round(length/lanePart);
                    Point3 leftLanePtAOld = ptA + (orthonormalDirection * halfWidth);
                    Point3 rightLanePtAOld = ptA - (orthonormalDirection * halfWidth);

                    Point3 colorLeftMarking;
                    Point3 colorRightMarking;

                    for(uint32_t i = 0; i < steps - 1; i++) {
                        switch (straightLine.getLaneAttribute().getLeftLaneMarking()) {
                            case LaneAttribute::SOLID_YELLOW:
                            case LaneAttribute::DOUBLE_YELLOW:
                                colorLeftMarking = Point3(1, 1, 0);
                            break;

                            case LaneAttribute::BROKEN_WHITE:
                                colorLeftMarking = Point3(1, 1, 1);
                                brokenLeft = !brokenLeft;
                            break;

                            case LaneAttribute::SOLID_WHITE:
                                colorLeftMarking = Point3(1, 1, 1);
                            break;

                            case LaneAttribute::UNDEFINED:
                                showLeft = false;
                            break;

                            case LaneAttribute::CROSSWALK:
                                colorLeftMarking = Point3(0, 0, 0);
                            break;
                        }

                        Point3 leftLanePtA = (ptA + direction * (i + 1) * lanePart) + (orthonormalDirection * halfWidth);
                        if (brokenLeft && showLeft) {
                            stringstream leftLaneMarkingName;
                            leftLaneMarkingName << "Left lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(leftLaneMarkingName.str()), leftLanePtAOld, leftLanePtA, colorLeftMarking, 5));
                        }
                        leftLanePtAOld = leftLanePtA;

                        switch (straightLine.getLaneAttribute().getRightLaneMarking()) {
                            case LaneAttribute::SOLID_YELLOW:
                            case LaneAttribute::DOUBLE_YELLOW:
                                colorRightMarking = Point3(1, 1, 0);
                            break;

                            case LaneAttribute::BROKEN_WHITE:
                                colorRightMarking = Point3(1, 1, 1);
                                brokenRight = !brokenRight;
                            break;

                            case LaneAttribute::SOLID_WHITE:
                                colorRightMarking = Point3(1, 1, 1);
                            break;

                            case LaneAttribute::UNDEFINED:
                                showRight = false;
                            break;

                            case LaneAttribute::CROSSWALK:
                                colorRightMarking = Point3(0, 0, 0);
                            break;
                        }

                        Point3 rightLanePtA = (ptA + direction * (i + 1) * lanePart) - (orthonormalDirection * halfWidth);
                        if (brokenRight && showRight) {

                            stringstream rightLaneMarkingName;
                            rightLaneMarkingName << "Right lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                            layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(rightLaneMarkingName.str()), rightLanePtAOld, rightLanePtA, colorRightMarking, 5));
                        }
                        rightLanePtAOld = rightLanePtA;
                    }

                    Point3 leftLaneLastPt = ptB + (orthonormalDirection * halfWidth);
                    if (brokenLeft && showLeft) {
                        stringstream leftLaneMarkingName;
                        leftLaneMarkingName << "Left lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(leftLaneMarkingName.str()), leftLanePtAOld, leftLaneLastPt, colorLeftMarking, 5));
                    }

                    Point3 rightLaneLastPt = ptB - (orthonormalDirection * halfWidth);
                    if (brokenRight && showRight) {
                        stringstream rightLaneMarkingName;
                        rightLaneMarkingName << "Right lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID();
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(rightLaneMarkingName.str()), rightLanePtAOld, rightLaneLastPt, colorRightMarking, 5));
                    }

                }
            }

            void ScenarioTransformation::transform(const Layer &layer, const Road &road, const Lane &lane, const Arc &arc, hesperia::scenegraph::SceneNode *layerSceneNode) {
                // Get to adjacent vertices, determine direction, construct orthogonal direction
                Point3 ptA = arc.getStart();
                ptA.setZ(layer.getHeight());

                Point3 ptB = arc.getEnd();
                ptB.setZ(layer.getHeight());

                stringstream namePtA;
                namePtA << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << arc.getStart().getID();

                stringstream namePtB;
                namePtB << "Waypoint: " << layer.getID() << "." << road.getID() << "." << lane.getID() << "." << arc.getEnd().getID();

                if (m_renderLaneConnectors) {
                    layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtA.str()), ptA, Point3(1, 0, 0), 5));
                    layerSceneNode->addChild(new hesperia::scenegraph::primitives::Point(hesperia::scenegraph::SceneNodeDescriptor(namePtB.str()), ptB, Point3(1, 0, 0), 5));
                }

                // ScUI starts Arc at 6pm but we use 3pm. Thus, we have to correct the Z-rotation.
                double correctRotation = cartesian::Constants::PI / 2.0;

                // Transposition of the arc.
                Point3 t(0, 0, 0);
                t.setX(ptA.getX() - arc.getRadius() * cos(arc.getRotationZ() - correctRotation));
                t.setY(ptA.getY() - arc.getRadius() * sin(arc.getRotationZ() - correctRotation));      
                t.setZ(layer.getHeight());

                // Calculate skeleton points.
                Point3 colorSkeleton(0.01, 0.01, 0.01);

                double beginInterval = arc.getBeginInterval();
                double endInterval = arc.getEndInterval();
                double stepSize = 5.0 * cartesian::Constants::PI / 180.0; // 5° to rad.
                uint32_t steps = (unsigned int) round( (endInterval - beginInterval) / stepSize );

                double width = arc.getLaneAttribute().getWidth();

                Point3 leftOld;
                leftOld.setX(t.getX() + (arc.getRadius() - width/2.0) * cos(arc.getRotationZ() - correctRotation));
                leftOld.setY(t.getY() + (arc.getRadius() - width/2.0) * sin(arc.getRotationZ() - correctRotation));      
                leftOld.setZ(layer.getHeight());

                Point3 rightOld;
                rightOld.setX(t.getX() + (arc.getRadius() + width/2.0) * cos(arc.getRotationZ() - correctRotation));
                rightOld.setY(t.getY() + (arc.getRadius() + width/2.0) * sin(arc.getRotationZ() - correctRotation));      
                rightOld.setZ(layer.getHeight());

                Point3 centerOld = ptA;

                bool brokenLeft = true;
                bool brokenRight = true;
                bool showLeft = true;
                bool showRight = true;
                for(uint32_t i = 0; i < steps; i++) {
                    // Calculate the skeleton approximation.                
                    Point3 center(0, 0, 0);
                    center.setX(arc.getRadius() * cos(arc.getRotationZ() - correctRotation + i * stepSize));
                    center.setY(arc.getRadius() * sin(arc.getRotationZ() - correctRotation + i * stepSize));

                    // Calculate left point.
                    Point3 left(0, 0, 0);
                    left.setX((arc.getRadius() - width/2.0) * cos(arc.getRotationZ() - correctRotation + i * stepSize));
                    left.setY((arc.getRadius() - width/2.0) * sin(arc.getRotationZ() - correctRotation + i * stepSize));

                    Point3 right(0, 0, 0);
                    right.setX((arc.getRadius() + width/2.0) * cos(arc.getRotationZ() - correctRotation + i * stepSize));
                    right.setY((arc.getRadius() + width/2.0) * sin(arc.getRotationZ() - correctRotation + i * stepSize));

                    // Transpose the points.
                    center += t;
                    left += t;
                    right += t;
/*
                    // Add center point to TG.
                    stringstream nameLane;
                    nameLane << "Lane: " << layer.getID() << "." << road.getID() << "." << lane.getID() << " (" << i << ")";
                    layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(nameLane.str()), centerOld, center, colorSkeleton, 1));
*/
                    // Add left point to TG.
                    Point3 colorLeftMarking;
                    switch (arc.getLaneAttribute().getLeftLaneMarking()) {
                        case LaneAttribute::SOLID_YELLOW:
                        case LaneAttribute::DOUBLE_YELLOW:
                            colorLeftMarking = Point3(1, 1, 0);
                        break;

                        case LaneAttribute::BROKEN_WHITE:
                            if (brokenLeft) {
                                colorLeftMarking = Point3(0, 0, 0);
                            }
                            else {                        
                                colorLeftMarking = Point3(1, 1, 1);
                            }
                            brokenLeft = !brokenLeft;
                        break;

                        case LaneAttribute::SOLID_WHITE:
                            colorLeftMarking = Point3(1, 1, 1);
                        break;

                        case LaneAttribute::UNDEFINED:
                            showLeft = false;
                        break;

                        case LaneAttribute::CROSSWALK:
                            colorLeftMarking = Point3(0, 0, 0);
                        break;
                    }

                    if (brokenLeft && showLeft) {
                        stringstream leftLaneMarkingName;
                        leftLaneMarkingName << "Left lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID() << " (" << i << ")";
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(leftLaneMarkingName.str()), leftOld, left, colorLeftMarking, 5));
                    }

                    // Add right point to TG.
                    Point3 colorRightMarking;
                    switch (arc.getLaneAttribute().getRightLaneMarking()) {
                        case LaneAttribute::SOLID_YELLOW:
                        case LaneAttribute::DOUBLE_YELLOW:
                            colorRightMarking = Point3(1, 1, 0);
                        break;

                        case LaneAttribute::BROKEN_WHITE:
                            if (brokenRight) {
                                colorRightMarking = Point3(0, 0, 0);
                            }
                            else {                        
                                colorRightMarking = Point3(1, 1, 1);
                            }
                            brokenRight = !brokenRight;
                        break;

                        case LaneAttribute::SOLID_WHITE:
                            colorRightMarking = Point3(1, 1, 1);
                        break;

                        case LaneAttribute::UNDEFINED:
                            showRight = false;
                        break;

                        case LaneAttribute::CROSSWALK:
                            colorRightMarking = Point3(0, 0, 0);
                        break;
                    }

                    if (brokenRight && showRight) {
                        stringstream rightLaneMarkingName;
                        rightLaneMarkingName << "Right lane marking: " << layer.getID() << "." << road.getID() << "." << lane.getID() << " (" << i << ")";
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(rightLaneMarkingName.str()), rightOld, right, colorRightMarking, 5));
                    }

                    // Keep old points.
                    centerOld = center;
                    leftOld = left;
                    rightOld = right;
                }
            }

            void ScenarioTransformation::transform(const data::scenario::LaneModel &laneModel, hesperia::scenegraph::SceneNode *layerSceneNode) {
                const vector<TrafficControl*>& listOfTrafficControls = laneModel.getListOfTrafficControls();
                vector<TrafficControl*>::const_iterator it = listOfTrafficControls.begin();
                while(it != listOfTrafficControls.end()) {
                    TrafficControl *tc = (*it++);
                    if (tc->getType() == TrafficControl::TRAFFICSIGN) {
                        TrafficSign *ts = (TrafficSign*)tc;
                        if (ts != NULL) {
                            cerr << "Stopline: " << ts->toString() << endl;
                            Shape *s = ts->getShape();
                            if ( (s != NULL) && (s->getType() == Shape::POLYGON) ) {
                                Polygon *p = dynamic_cast<Polygon*>(s);
                                if (p != NULL) {
                                    vector<Point3> vertices;

                                    // Convert vertices.
                                    const vector<Vertex3> &originalVertices = p->getListOfVertices();
                                    vector<Vertex3>::const_iterator jt = originalVertices.begin();
                                    while (jt != originalVertices.end()) {
                                        Vertex3 v3 = (*jt++);
                                        vertices.push_back(v3);
                                    }

                                    Point3 color(p->getColor());
                                    if (vertices.size() == 2) {
                                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(p->getName()), vertices.at(0), vertices.at(1), color, 5));
                                    }
                                }
                            }
                        }
                    }
                }
            }

            void ScenarioTransformation::transform(const data::scenario::Layer &/*layer*/, const data::scenario::Zone &z, hesperia::scenegraph::SceneNode *layerSceneNode) {
                Point3 color(Point3(1, 1, 1));

                // Convert vertices.
                const vector<IDVertex3> &originalVertices = z.getPerimeter().getListOfIdentifiableVertices();
                vector<IDVertex3>::const_iterator jt = originalVertices.begin();

                Point3 startPoint = (*jt);
                Point3 oldPoint = startPoint;
                Point3 nextPoint = startPoint;

                bool firstCycle = true;
                while (jt != originalVertices.end()) {
                    IDVertex3 idv3 = (*jt++);
                    nextPoint = idv3;

                    if (!firstCycle) {
                        layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(z.getName()), oldPoint, nextPoint, color, 5));
                    }
                    oldPoint = nextPoint;

                    firstCycle = false;
                }
                layerSceneNode->addChild(new hesperia::scenegraph::primitives::Line(hesperia::scenegraph::SceneNodeDescriptor(z.getName()), nextPoint, startPoint, color, 5));
            }

            void ScenarioTransformation::visit(ScenarioNode &node) {
                try {
                    Surroundings &surroundings = dynamic_cast<Surroundings&>(node);
                    clog << "Surroundings found." <<  endl;
                    transform(surroundings, m_root);
                } catch (...) {}

                try {
                    Layer &layer = dynamic_cast<Layer&>(node);
                    clog << "Layer found." <<  endl;
                    hesperia::scenegraph::SceneNode *layerSceneNode = new hesperia::scenegraph::SceneNode(hesperia::scenegraph::SceneNodeDescriptor("Layer: " + layer.getName()));
                    m_root->addChild(layerSceneNode);

                    const vector<Road> &listOfRoads = layer.getListOfRoads();
                    vector<Road>::const_iterator it = listOfRoads.begin();
                    while (it != listOfRoads.end()) {
                        Road road = (*it++);
                        const vector<Lane> &listOfLanes = road.getListOfLanes();
                        vector<Lane>::const_iterator jt = listOfLanes.begin();
                        while (jt != listOfLanes.end()) {
                            Lane lane = (*jt++);
                            LaneModel *laneModel = lane.getLaneModel();
                            if (laneModel != NULL) {
                                // Draw stop lines.
                                transform(*laneModel, layerSceneNode);

                                // Draw lane models.
                                bool drawn = false;
                                Arc *arc = dynamic_cast<Arc*>(laneModel);
                                if ( !drawn && (arc != NULL) ) {
                                    transform(layer, road, lane, *arc, layerSceneNode);
                                    drawn = true;
                                }

                                Clothoid *clothoid = dynamic_cast<Clothoid*>(laneModel);
                                if (clothoid != NULL) {
                                    clog << "SceneGraph transformation for Clothoid not implemented yet." << endl;
                                }

                                PointModel *pointModel = dynamic_cast<PointModel*>(laneModel);
                                if ( !drawn && (pointModel != NULL) ) {
                                    transform(layer, road, lane, *pointModel, layerSceneNode);
                                    drawn = true;
                                }

                                StraightLine *straightLine = dynamic_cast<StraightLine*>(laneModel);
                                if ( !drawn && (straightLine != NULL) ) {
                                    transform(layer, road, lane, *straightLine, layerSceneNode);
                                    drawn = true;
                                }
                            }
                        }
                    }

                    const vector<Zone> &listOfZones = layer.getListOfZones();
                    vector<Zone>::const_iterator jt = listOfZones.begin();
                    while (jt != listOfZones.end()) {
                        Zone zone = (*jt++);

                        transform(layer, zone, layerSceneNode);
                    }

                } catch (...) {}
            }

        }
    }
} // hesperia::scenegraph::transformation
