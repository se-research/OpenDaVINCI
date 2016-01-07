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

#include <string>

#include "core/opendavinci.h"
#include "core/exceptions/Exceptions.h"
#include "core/wrapper/parser/ASTNode.h"
#include "hesperia/data/scenario/Connector.h"
#include "hesperia/data/scenario/Ground.h"
#include "hesperia/data/scenario/Header.h"
#include "hesperia/data/scenario/HeightImage.h"
#include "hesperia/data/scenario/IDVertex3.h"
#include "hesperia/data/scenario/Image.h"
#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/LaneAttribute.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/Perimeter.h"
#include "hesperia/data/scenario/Road.h"
#include "hesperia/data/scenario/Spot.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/data/scenario/Vertex3.h"
#include "hesperia/data/scenario/WGS84CoordinateSystem.h"
#include "hesperia/data/scenario/Zone.h"
#include "hesperia/scenario/SCNScenarioVisitor.h"

namespace hesperia { namespace data { namespace scenario { class Arc; } } }
namespace hesperia { namespace data { namespace scenario { class Clothoid; } } }
namespace hesperia { namespace data { namespace scenario { class ComplexModel; } } }
namespace hesperia { namespace data { namespace scenario { class Cylinder; } } }
namespace hesperia { namespace data { namespace scenario { class PointModel; } } }
namespace hesperia { namespace data { namespace scenario { class Polygon; } } }
namespace hesperia { namespace data { namespace scenario { class Scenario; } } }
namespace hesperia { namespace data { namespace scenario { class Shape; } } }
namespace hesperia { namespace data { namespace scenario { class StraightLine; } } }
namespace hesperia { namespace data { namespace scenario { class TrafficLight; } } }
namespace hesperia { namespace data { namespace scenario { class TrafficSign; } } }

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace data::scenario;
        using namespace core::exceptions;
        using namespace core::wrapper::parser;

        SCNScenarioVisitor::SCNScenarioVisitor(Scenario &s) :
                m_scenario(s) {}

        SCNScenarioVisitor::~SCNScenarioVisitor() {}

        const IDVertex3 SCNScenarioVisitor::visitIDVertex3(ASTNode *node) {
            IDVertex3 idV;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ID expected.");
                }
                idV.setIdentifier(n->getValue<uint32_t>());

                Vertex3 v = visitVertex3(node->getLastChild());
                idV.setX(v.getX());
                idV.setY(v.getY());
            }

            return idV;
        }

        const Vertex3 SCNScenarioVisitor::visitVertex3(ASTNode *node) {
            Vertex3 v;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("X");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from X expected.");
                }
                v.setX(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("Y");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from Y expected.");
                }
                v.setY(n->getValue<double>());

                // Try to parse three dimensional coordinates. If Z is omitted, it is a two dimensonal input coordinate.
                // Therefore, don't throw an exception but set the value.
                n = node->getNodeFromFirstMatchingChildFor("Z");
                if (n != NULL) {
                    v.setZ(n->getValue<double>());
                }
            }

            return v;
        }

        ComplexModel* SCNScenarioVisitor::visitComplexModel(ASTNode *node) {
            ComplexModel *cm = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                cm = new ComplexModel();

                n = node->getNodeFromFirstMatchingChildFor("MODELFILE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from MODELFILE expected.");
                }
                cm->setModelFile(n->getValue<string>());

                n = *(node->getChildren("POSITION").begin() + 1); // Skip keyword "POSITION".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from POSITION expected.");
                }
                cm->setPosition(visitVertex3(n));

                n = *(node->getChildren("ROTATION").begin() + 1); // Skip keyword "ROTATION".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from ROTATION expected.");
                }
                cm->setRotation(visitVertex3(n));

                // Skip keyword BOUNDINGBOX.
                BoundingBox bb;
                vector<ASTNode*> boundingBox = node->getChildren("BOUNDINGBOX");
                if (boundingBox.size() != 5) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from BOUNDINGBOX expected.");
                }
                bb.setUpperLeft(visitVertex3(boundingBox.at(1)));
                bb.setUpperRight(visitVertex3(boundingBox.at(2)));
                bb.setLowerRight(visitVertex3(boundingBox.at(3)));
                bb.setLowerLeft(visitVertex3(boundingBox.at(4)));

                cm->setBoundingBox(bb);
            }

            return cm;
        }

        Polygon* SCNScenarioVisitor::visitPolygon(ASTNode *node) {
            Polygon *p = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                p = new Polygon();

                n = node->getNodeFromFirstMatchingChildFor("HEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from HEIGHT expected.");
                }
                p->setHeight(n->getValue<double>());

                n = *(node->getChildren("COLOR").begin() + 1); // Skip keyword "COLOR".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from COLOR expected.");
                }
                p->setColor(visitVertex3(n));

                vector<ASTNode*> listOfVertices = node->getChildren("COLOR");
                vector<ASTNode*>::iterator it = listOfVertices.begin() + 2; // Vertices start directly after color.
                while (it != listOfVertices.end()) {
                    n = (*it++);
                    p->add(visitVertex3(n));
                }
            }

            return p;
        }

        Cylinder* SCNScenarioVisitor::visitCylinder(ASTNode *node) {
            Cylinder *c = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getChildren()[1];
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from VERTEX2 expected.");
                }
                c = new Cylinder();
                c->setCenter(visitVertex3(n));

                n = node->getNodeFromFirstMatchingChildFor("RADIUS");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from RADIUS expected.");
                }
                c->setRadius(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("HEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from HEIGHT expected.");
                }
                c->setHeight(n->getValue<double>());

                n = *(node->getChildren("COLOR").begin() + 1); // Skip keyword "COLOR".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from COLOR expected.");
                }
                c->setColor(visitVertex3(n));
            }

            return c;
        }

        Shape* SCNScenarioVisitor::visitShape(ASTNode *node) {
            Shape *s = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get name from SHAPE expected.");
                }
                string name = n->getValue<string>();

                n = (node->getChildren().at(1))->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from SHAPE expected.");
                }
                string type = n->getValue<string>();

                if (type == "CYLINDER") {
                    Cylinder *c = visitCylinder(node->getChildren().at(1));
                    if (c != NULL) {
                        c->setName(name);
                    }
                    s = c;
                }

                if (type == "POLYGON") {
                    Polygon *p = visitPolygon(node->getChildren().at(1));
                    if (p != NULL) {
                        p->setName(name);
                    }
                    s = p;
                }

                if (type == "COMPLEXMODEL") {
                    ComplexModel *cm = visitComplexModel(node->getChildren().at(1));
                    if (cm != NULL) {
                        cm->setName(name);
                    }
                    s = cm;
                }
            }

            return s;
        }

        const Surroundings SCNScenarioVisitor::visitSurroundings(ASTNode *node) {
            Surroundings s;

            if (node != NULL) {
                vector<ASTNode*> listOfNodes = node->getChildren();
                vector<ASTNode*>::iterator it = listOfNodes.begin() + 1; // Skip keyword "SURROUNDING".
                while (it != listOfNodes.end()) {
                    // Parse shape from child.
                    ASTNode *n = (*it++);
                    Shape *shape = visitShape(n);
                    if (shape != NULL) {
                        s.addShape(shape);
                    }
                }
            }

            return s;
        }

        const HeightImage SCNScenarioVisitor::visitHeightImage(ASTNode *node) {
            HeightImage hi;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = *(node->getChildren("HEIGHTIMAGE").begin() + 1); // Skip keyword "HEIGHTIMAGE".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from HEIGHTIMAGE expected.");
                }
                Image i = visitImage(n);
                hi.setFileName(i.getFileName());
                hi.setOriginX(i.getOriginX());
                hi.setOriginY(i.getOriginY());
                hi.setMeterPerPixelX(i.getMeterPerPixelX());
                hi.setMeterPerPixelY(i.getMeterPerPixelY());
                hi.setRotationZ(i.getRotationZ());

                n = node->getNodeFromFirstMatchingChildFor("GROUNDHEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from GROUNDHEIGHT expected.");
                }
                hi.setGroundHeight(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("MINHEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from MINHEIGHT expected.");
                }
                hi.setMinimumHeight(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("MAXHEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from MAXHEIGHT expected.");
                }
                hi.setMaximumHeight(n->getValue<double>());
            }

            return hi;
        }

        const Image SCNScenarioVisitor::visitImage(ASTNode *node) {
            Image i;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("IMAGE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from IMAGE expected.");
                }
                i.setFileName(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("ORIGINX");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ORIGINX expected.");
                }
                i.setOriginX(n->getValue<uint32_t>());

                n = node->getNodeFromFirstMatchingChildFor("ORIGINY");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ORIGINY expected.");
                }
                i.setOriginY(n->getValue<uint32_t>());

                n = node->getNodeFromFirstMatchingChildFor("MPPX");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from MPPX expected.");
                }
                i.setMeterPerPixelX(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("MPPY");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from MPPY expected.");
                }
                i.setMeterPerPixelY(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("ROTZ");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROTZ expected.");
                }
                i.setRotationZ(n->getValue<double>());
            }

            return i;
        }

        const Ground SCNScenarioVisitor::visitGround(ASTNode *node) {
            Ground g;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("GROUND");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from GROUND expected.");
                }
                g.setName(n->getValue<string>());

                vector<ASTNode*> list = node->getChildren("GROUND");
                vector<ASTNode*>::iterator it = list.begin() + 1;
                while (it != list.end()) {
                    n = (*it++);
                    if (n->getFirstChild()->getKey() == "AERIALIMAGE") {
                        // Descend directly to child.
                        g.setAerialImage(visitImage(*(n->getChildren("AERIALIMAGE").begin() + 1))); // Skip keyword "AERIALIMAGE".
                    }
                    if (n->getFirstChild()->getKey() == "HEIGHTIMAGE") {
                        // The keyword is skipped elsewhere.
                        g.setHeightImage(visitHeightImage(n));
                    }
                    if (n->getFirstChild()->getKey() == "SURROUNDING") {
                        // The keyword is skipped elsewhere.
                        g.setSurroundings(visitSurroundings(n));
                    }
                }
            }

            return g;
        }

        const WGS84CoordinateSystem SCNScenarioVisitor::visitCoordinateSystem(ASTNode *node) {
            WGS84CoordinateSystem c;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("ROTATION");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROTATION expected.");
                }
                c.setRotation(n->getValue<double>());
                c.setType("WGS84");

                n = *(node->getFirstChild()->getChildren("ORIGIN").begin() + 1); // Descend to first child and skip keyword "ORIGIN".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ORIGIN expected.");
                }
                c.setOrigin(visitVertex3(n));
            }

            return c;
        }

        const Header SCNScenarioVisitor::visitScenarioHeader(ASTNode *node) {
            Header header;
            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("SCENARIO");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from SCENARIO expected.");
                }
                header.setName(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("VERSION");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from VERSION expected.");
                }
                header.setVersion(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("DATE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from DATE expected.");
                }
                header.setDate(n->getValue<string>());

                n = *(node->getChildren("ORIGINCOORDINATESYSTEM").begin() + 1); // Skip keyword "ORIGINCOORDINATESYSTEM".
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ORIGINCOORDINATESYSTEM expected.");
                }
                header.setWGS84CoordinateSystem(visitCoordinateSystem(n));
            }
            return header;
        }

        Connector SCNScenarioVisitor::visitConnector(ASTNode *node) {
            Connector c;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getParent()->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from CONNECTOR expected.");
                }

                // Remove parentheses: "(" ... ")".
                string s = n->getValue<string>();
                if (s.size() > 2) {
                    s = s.substr(1, s.size() - 2);
                }
                PointID source(s);

                n = node->getParent()->getLastChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from CONNECTOR expected.");
                }
                // Remove parentheses: "(" ... ")".
                s = n->getValue<string>();
                if (s.size() > 2) {
                    s = s.substr(1, s.size() - 2);
                }
                PointID target(s);

                c.setSource(source);
                c.setTarget(target);
            }

            return c;
        }

        Arc* SCNScenarioVisitor::visitArc(ASTNode *node) {
            Arc *a = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("RADIUS");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from RADIUS expected.");
                }
                a = new Arc();
                a->setRadius(n->getValue<double>());

                vector<ASTNode*> list = node->getChildren("[");
                if (list.size() != 2) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from interval expected.");
                }

                n = list.at(0);
                a->setBeginInterval(n->getValue<double>());
                n = list.at(1);
                a->setEndInterval(n->getValue<double>());

                // Skip keywords "START" and "END".
                a->setStart(visitIDVertex3(*(node->getChildren("START").begin() + 1)));
                a->setEnd(visitIDVertex3(*(node->getChildren("END").begin() + 1)));

                n = node->getNodeFromFirstMatchingChildFor("ROTZ");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROTZ expected.");
                }
                a->setRotationZ(n->getValue<double>());
            }

            return a;
        }

        Clothoid* SCNScenarioVisitor::visitClothoid(ASTNode *node) {
            Clothoid *c = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                c = new Clothoid();

                n = node->getNodeFromFirstMatchingChildFor("DK");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from DK expected.");
                }
                c->setDK(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("K");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from K expected.");
                }
                c->setK(n->getValue<double>());

                // Skip keywords "START" and "END".
                c->setStart(visitIDVertex3(*(node->getChildren("START").begin() + 1)));
                c->setEnd(visitIDVertex3(*(node->getChildren("END").begin() + 1)));

                n = node->getNodeFromFirstMatchingChildFor("ROTZ");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROTZ expected.");
                }
                c->setRotationZ(n->getValue<double>());
            }

            return c;
        }

        PointModel* SCNScenarioVisitor::visitPointModel(ASTNode *node) {
            PointModel *pm = NULL;

            if (node != NULL) {
                pm = new PointModel();
                vector<ASTNode*> list = node->getParent()->getChildren("POINTMODEL");
                vector<ASTNode*>::iterator it = list.begin() + 1; // Skip keyword "POINTMODEL".
                while (it != list.end()) {
                    pm->addIdentifiableVertex(visitIDVertex3((*it++)));
                }
            }

            return pm;
        }

        StraightLine* SCNScenarioVisitor::visitStraightLine(ASTNode *node) {
            StraightLine *sl = NULL;

            if (node != NULL) {
                sl = new StraightLine();

                // Skip keywords "START" and "END".
                sl->setStart(visitIDVertex3(*(node->getChildren("START").begin() + 1)));
                sl->setEnd(visitIDVertex3(*(node->getChildren("END").begin() + 1)));
            }

            return sl;
        }

        enum LaneAttribute::BOUNDARYSTYLE SCNScenarioVisitor::getBoundaryStyle(const string &s) const {
            LaneAttribute::BOUNDARYSTYLE bs = LaneAttribute::UNDEFINED;

            if (s != "") {
                if (s == "double_yellow") {
                    bs = LaneAttribute::DOUBLE_YELLOW;
                }
                if (s == "solid_yellow") {
                    bs = LaneAttribute::SOLID_YELLOW;
                }
                if (s == "solid_white") {
                    bs = LaneAttribute::SOLID_WHITE;
                }
                if (s == "broken_white") {
                    bs = LaneAttribute::BROKEN_WHITE;
                }
                if (s == "crosswalk") {
                    bs = LaneAttribute::CROSSWALK;
                }
            }

            return bs;
        }

        LaneAttribute SCNScenarioVisitor::visitLaneAttribute(ASTNode *node) {
            LaneAttribute la;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("LANEWIDTH");
                if (n != NULL) {
                    la.setWidth(n->getValue<double>());
                }

                n = node->getNodeFromFirstMatchingChildFor("LEFTLANEMARKING");
                if (n != NULL) {
                    la.setLeftLaneMarking(getBoundaryStyle(n->getValue<string>()));
                }

                n = node->getNodeFromFirstMatchingChildFor("RIGHTLANEMARKING");
                if (n != NULL) {
                    la.setRightLaneMarking(getBoundaryStyle(n->getValue<string>()));
                }
            }

            return la;
        }

        TrafficLight* SCNScenarioVisitor::visitTrafficLight(ASTNode *node) {
            TrafficLight *tl = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                // Name of the traffic control.
                n = node->getParent()->getChildren().at(1);
                tl = new TrafficLight();
                tl->setName(n->getValue<string>());

                tl->setPosition(visitIDVertex3(node->getParent()->getChildren().at(2)));

                tl->setShape(visitShape(node->getParent()->getChildren().at(3)));
            }

            return tl;
        }

        TrafficSign* SCNScenarioVisitor::visitTrafficSign(ASTNode *node) {
            TrafficSign *ts = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                // Value of the traffic sign.
                n = node->getParent()->getNodeFromFirstMatchingChildFor("VALUE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from VALUE expected.");
                }
                ts = new TrafficSign();
                ts->setValue(n->getValue<string>());

                // Name of the traffic control.
                n = node->getParent()->getParent()->getChildren().at(1);
                ts->setName(n->getValue<string>());

                ts->setPosition(visitIDVertex3(node->getParent()->getParent()->getChildren().at(2)));

                ts->setShape(visitShape(node->getParent()->getParent()->getChildren().at(3)));
            }

            return ts;
        }

        Lane SCNScenarioVisitor::visitLane(ASTNode *node) {
            Lane l;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("LANEID");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from LANEID expected.");
                }
                l.setIdentifier(n->getValue<uint32_t>());

                LaneAttribute la;
                vector<TrafficControl*> listOfTrafficControls;
                vector<Connector> listOfConnectors;
                vector<ASTNode*> list = (*(node->getChildren("LANEID").begin() + 1))->getChildren(); // Lane's description starts directly behind LANEID.
                vector<ASTNode*>::iterator it = list.begin();
                while (it != list.end()) {
                    ASTNode *nd = (*it++);

                    // Check for POINTMODEL.
                    n = findByKey("POINTMODEL", nd, 3);
                    if (n != NULL) {
                        // Skip the keyword "POINTMODEL".
                        l.setLaneModel(visitPointModel(n));
                        continue;
                    }

                    // Check for FUNCTIONMODEL.
                    n = findByKey("FUNCTIONMODEL", nd, 3);
                    if (n != NULL) {
                        // Skip the keyword "FUNCTIONMODEL".
                        n = n->getParent();
                        n = *(n->getChildren("FUNCTIONMODEL").begin() + 1);
                        if (n->getFirstChild()->getValue<string>() == "ARC") {
                            l.setLaneModel(visitArc(n));
                        }
                        if (n->getFirstChild()->getValue<string>() == "CLOTHOID") {
                            l.setLaneModel(visitClothoid(n));
                        }
                        if (n->getFirstChild()->getValue<string>() == "STRAIGHTLINE") {
                            l.setLaneModel(visitStraightLine(n));
                        }
                        continue;
                    }

                    // Check for CONNECTORS.
                    n = findByKey("->", nd, 3);
                    if (n != NULL) {
                        listOfConnectors.push_back(visitConnector(n));
                        continue;
                    }

                    // Check for TRAFFICLIGHT.
                    n = findByValue("TRAFFICLIGHT", nd, 3);
                    if (n != NULL) {
                        TrafficControl *tc = visitTrafficLight(n);
                        if (tc != NULL) {
                            listOfTrafficControls.push_back(tc);
                        }
                        continue;
                    }

                    // Check for TRAFFICSIGN.
                    n = findByValue("TRAFFICSIGN", nd, 3);
                    if (n != NULL) {
                        TrafficControl *tc = visitTrafficSign(n);
                        if (tc != NULL) {
                            listOfTrafficControls.push_back(tc);
                        }
                        continue;
                    }

                    // Check for LANEATTRIBUTE.
                    if ( (nd->getNodeFromFirstMatchingChildFor("LANEWIDTH") != NULL) ||
                            (nd->getNodeFromFirstMatchingChildFor("LEFTLANEMARKING") != NULL) ||
                            (nd->getNodeFromFirstMatchingChildFor("RIGHTLANEMARKING") != NULL) ) {
                        la = visitLaneAttribute(nd);
                    }
                }

                // Add traffic controls, connectors and lane's attributes.
                LaneModel *lm = l.getLaneModel();
                if (lm != NULL) {
                    vector<TrafficControl*>::iterator jt = listOfTrafficControls.begin();
                    while (jt != listOfTrafficControls.end()) {
                        lm->addTrafficControl((*jt++));
                    }

                    vector<Connector>::iterator kt = listOfConnectors.begin();
                    while (kt != listOfConnectors.end()) {
                        lm->addConnector((*kt++));
                    }

                    lm->setLaneAttribute(la);
                }
            }

            return l;
        }

        Road SCNScenarioVisitor::visitRoad(ASTNode *node) {
            Road r;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("ROADID");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROADID expected.");
                }
                r.setIdentifier(n->getValue<uint32_t>());

                n = node->getNodeFromFirstMatchingChildFor("ROADNAME");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ROADNAME expected.");
                }
                r.setName(n->getValue<string>());

                vector<ASTNode*> list = node->getChildren("ROADNAME");
                vector<ASTNode*>::iterator it = list.begin(); // Lanes are accessible by ROADNAME as well...
                while (it != list.end()) {
                    ASTNode *nd = (*it++);
                    if (nd->getFirstChild() != NULL) {
                        if (nd->getFirstChild()->getKey() == "LANE") {
                            r.addLane(visitLane(nd));
                        }
                    }
                }
            }

            return r;
        }

        Perimeter SCNScenarioVisitor::visitPerimeter(ASTNode *node) {
            Perimeter p;

            if (node != NULL) {
                vector<ASTNode*> list = node->getChildren("PERIMETER");
                vector<ASTNode*>::iterator it = list.begin() + 1; // Skip keyword "PERIMETER".
                while (it != list.end()) {
                    ASTNode *nd = (*it++);
                    p.addIdentifiableVertex(visitIDVertex3(nd));
                }
            }

            return p;
        }

        Spot SCNScenarioVisitor::visitSpot(ASTNode *node) {
            Spot s;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getChildren("SPOTID").at(0);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from SPOTID expected.");
                }
                s.setIdentifier(n->getValue<uint32_t>());

                n = node->getChildren("SPOTID").at(1);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value for first vertex expected.");
                }
                s.setFirstVertex(visitVertex3(n));

                n = node->getChildren("SPOTID").at(2);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value for second vertex expected.");
                }
                s.setSecondVertex(visitVertex3(n));
            }

            return s;
        }

        Zone SCNScenarioVisitor::visitZone(ASTNode *node) {
            Zone z;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("ZONEID");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ZONEID expected.");
                }
                z.setIdentifier(n->getValue<uint32_t>());

                n = node->getNodeFromFirstMatchingChildFor("ZONENAME");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from ZONENAME expected.");
                }
                z.setName(n->getValue<string>());

                vector<Connector> listOfConnectors;
                vector<ASTNode*> list = node->getChildren("ZONENAME");
                vector<ASTNode*>::iterator it = list.begin();
                while (it != list.end()) {
                    ASTNode *nd = (*it++);
                    if (nd->getFirstChild() != NULL) {
                        if (nd->getFirstChild()->getKey() == "PERIMETER") {
                            z.setPerimeter(visitPerimeter(nd));
                        }
                        if (nd->getFirstChild()->getKey() == "SPOT") {
                            z.addSpot(visitSpot(nd));
                        }
                        if ( (nd->getLastChild() != NULL) && (nd->getLastChild()->getKey() == "->") ) {
                            listOfConnectors.push_back(visitConnector(nd->getFirstChild()));
                        }
                    }
                }

                // Add connectors.
                vector<Connector>::iterator jt = listOfConnectors.begin();
                while (jt != listOfConnectors.end()) {
                    z.addConnector((*jt++));
                }
            }

            return z;
        }

        Layer SCNScenarioVisitor::visitLayer(ASTNode *node) {
            Layer l;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("LAYER");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from LAYER expected.");
                }
                l.setName(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("LAYERID");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from LAYERID expected.");
                }
                l.setIdentifier(n->getValue<uint32_t>());

                n = node->getNodeFromFirstMatchingChildFor("HEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SCNScenarioVisitorException, "Node to get value from HEIGHT expected.");
                }
                l.setHeight(n->getValue<double>());

                vector<ASTNode*> list = node->getChildren("HEIGHT");
                vector<ASTNode*>::iterator it = list.begin() + 1; // Skip Height, the following roads and zones are accessible by HEIGHT as  well...
                while (it != list.end()) {
                    ASTNode *nd = (*it++);
                    if (nd->getFirstChild()->getKey() == "ROAD") {
                        l.addRoad(visitRoad(nd));
                        continue;
                    }
                    if (nd->getFirstChild()->getKey() == "ZONE") {
                        l.addZone(visitZone(nd));
                        continue;
                    }
                }
            }

            return l;
        }

        ASTNode* SCNScenarioVisitor::findByKey(const string &key, ASTNode *node, const int32_t &maxDepth) {
            ASTNode *n = NULL;
            if (node != NULL) {
                if (maxDepth >= 0) {
                    if (node->getKey() == key) {
                        return node;
                    } else {
                        vector<ASTNode*> nodes = node->getChildren();
                        vector<ASTNode*>::iterator it = nodes.begin();
                        while ( (it != nodes.end()) && (n == NULL) ) {
                            n = findByKey(key, (*it++), maxDepth - 1);
                        }
                    }
                }
            }
            return n;
        }

        ASTNode* SCNScenarioVisitor::findByValue(const string &value, ASTNode *node, const int32_t &maxDepth) {
            ASTNode *n = NULL;
            if (node != NULL) {
                if (maxDepth >= 0) {
                    if (node->getValue<string>() == value) {
                        return node;
                    } else {
                        vector<ASTNode*> nodes = node->getChildren();
                        vector<ASTNode*>::iterator it = nodes.begin();
                        while ( (it != nodes.end()) && (n == NULL) ) {
                            n = findByValue(value, (*it++), maxDepth - 1);
                        }
                    }
                }
            }
            return n;
        }

        void SCNScenarioVisitor::visit(ASTNode *node) throw (SCNScenarioVisitorException) {
            if (node != NULL) {
                if (node->getParent() == NULL) {
                    m_scenario.setHeader(visitScenarioHeader(node->getChildren().at(0)));
                    m_scenario.setGround(visitGround(node->getChildren().at(1)));

                    vector<ASTNode*> list = node->getChildren();
                    vector<ASTNode*>::iterator it = list.begin();
                    while (it != list.end()) {
                        ASTNode *n = (*it++);
                        if ((n->getFirstChild() != NULL) && (n->getFirstChild()->getKey() == "LAYER") ) {
                            m_scenario.addLayer(visitLayer(n));
                        }
                    }
                }
            }
        }

    }
} // hesperia::scenario
