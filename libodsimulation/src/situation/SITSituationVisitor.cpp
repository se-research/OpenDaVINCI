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

#include <iostream>

#include "hesperia/data/situation/BoundingBox.h"
#include "hesperia/data/situation/Immediately.h"
#include "hesperia/data/situation/PointID.h"
#include "hesperia/data/situation/ReturnToStart.h"
#include "hesperia/data/situation/Stop.h"
#include "hesperia/data/situation/WarpToStart.h"
#include "hesperia/situation/SITSituationVisitor.h"
#include "core/wrapper/parser/ASTNode.h"
#include "core/wrapper/parser/ASTPrettyPrinter.h"

namespace hesperia {
    namespace situation {

        using namespace std;
        using namespace data::situation;
        using namespace core::exceptions;
        using namespace core::wrapper::parser;

        SITSituationVisitor::SITSituationVisitor(Situation &s) :
                m_situation(s) {}

        SITSituationVisitor::~SITSituationVisitor() {}

        const Header SITSituationVisitor::visitSituationHeader(ASTNode *node) {
            Header header;
            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("SITUATION");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from SITUATION expected.");
                }
                header.setName(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("VERSION");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from VERSION expected.");
                }
                header.setVersion(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("DATE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from DATE expected.");
                }
                header.setDate(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("SCENARIO");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from SCENARIO expected.");
                }
                header.setScenario(n->getValue<string>());

            }
            return header;
        }

        Object SITSituationVisitor::visitObject(ASTNode *node) {
            Object o;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("OBJECT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from OBJECT expected.");
                }
                o.setName(n->getValue<string>());

                n = node->getNodeFromFirstMatchingChildFor("OBJECTID");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from OBJECTID expected.");
                }
                o.setID(n->getValue<uint32_t>());

                // Parse shape from child.
                vector<ASTNode*> listOfChildren = node->getChildren("OBJECTID");
                vector<ASTNode*>::iterator it = listOfChildren.begin() + 1; // Skip first OBJECTID.
                while (it != listOfChildren.end()) {
                    ASTNode *child = (*it++)->getFirstChild();
                    if (child != NULL) {
                        if (child->getKey() == "SHAPENAME") {
                            Shape *shape = visitShape(child->getParent());
                            o.setShape(shape);
                        }
                    }
                }

                n = node->getNodeFromFirstMatchingChildFor("ROTZ");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from ROTZ expected.");
                }
                o.setRotationZ(n->getValue<double>());

                n = *(node->getChildren("ROTZ").begin() + 1); // BEHAVIOR starts directly after ROTZ.
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from BEHAVIOR expected.");
                }
                o.setBehavior(visitBehavior(n));
            }

            return o;
        }

        Shape* SITSituationVisitor::visitShape(ASTNode *node) {
            Shape *s = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from SHAPE expected.");
                }
                string name = n->getValue<string>();

                n = (node->getChildren().at(1))->getFirstChild();
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from SHAPE expected.");
                }
                string type = n->getValue<string>();

                if (type == "RECTANGLE") {
                    Rectangle *r = visitRectangle(node->getChildren().at(1));
                    if (r != NULL) {
                        r->setName(name);
                    }
                    s = r;
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

        const Vertex3 SITSituationVisitor::visitVertex3(ASTNode *node) {
            Vertex3 v;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = node->getNodeFromFirstMatchingChildFor("X");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from X expected.");
                }
                v.setX(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("Y");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get value from Y expected.");
                }
                v.setY(n->getValue<double>());

                // Try to parse three dimensional coordinates. If Z is omitted, it is a two dimensional input coordinate.
                // Therefore, don't throw an exception but set the value.
                n = node->getNodeFromFirstMatchingChildFor("Z");
                if (n != NULL) {
                    v.setZ(n->getValue<double>());
                }
            }

            return v;
        }

        Polygon* SITSituationVisitor::visitPolygon(ASTNode *node) {
            Polygon *p = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                p = new Polygon();

                n = node->getNodeFromFirstMatchingChildFor("HEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from HEIGHT expected.");
                }
                p->setHeight(n->getValue<double>());

                n = *(node->getChildren("COLOR").begin() + 1); // Skip keyword COLOR.
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from COLOR expected.");
                }
                p->setColor(visitVertex3(n));

                bool setFrontVertex = true;
                vector<ASTNode*> listOfVertices = node->getChildren("COLOR");
                vector<ASTNode*>::iterator it = listOfVertices.begin() + 2; // Vertices start directly after color and skip keyword COLOR.
                while (it != listOfVertices.end()) {
                    n = (*it++);

                    if (setFrontVertex) {
                        // The first vertex after color is the front position.
                        p->setFront(visitVertex3(n));
                        setFrontVertex = false;
                    } else {
                        p->add(visitVertex3(n));
                    }
                }
            }

            return p;
        }

        Rectangle* SITSituationVisitor::visitRectangle(ASTNode *node) {
            Rectangle *r = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                r = new Rectangle();

                n = node->getNodeFromFirstMatchingChildFor("HEIGHT");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from HEIGHT expected.");
                }
                r->setHeight(n->getValue<double>());

                n = *(node->getChildren("COLOR").begin() + 1); // Skip keyword COLOR.
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from COLOR expected.");
                }
                r->setColor(visitVertex3(n));

                n = *(node->getChildren("COLOR").begin() + 2); // Front starts directly after color.
                r->setFront(visitVertex3(n));

                n = node->getNodeFromFirstMatchingChildFor("LENGTH");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from LENGTH expected.");
                }
                r->setLength(n->getValue<double>());

                n = node->getNodeFromFirstMatchingChildFor("WIDTH");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from WIDTH expected.");
                }
                r->setWidth(n->getValue<double>());
            }

            return r;
        }

        ComplexModel* SITSituationVisitor::visitComplexModel(ASTNode *node) {
            ComplexModel *cm = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                cm = new ComplexModel();

                n = node->getNodeFromFirstMatchingChildFor("MODELFILE");
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from MODELFILE expected.");
                }
                cm->setModelFile(n->getValue<string>());

                n = *(node->getChildren("MODELFILE").begin() + 1); // Front starts directly after MODELFILE.
                cm->setFront(visitVertex3(n));

                n = *(node->getChildren("POSITION").begin() + 1); // Skip keyword POSITION.
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from POSITION expected.");
                }
                cm->setPosition(visitVertex3(n));

                n = *(node->getChildren("ROTATION").begin() + 1); // Skip keyword POSITION.
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from ROTATION expected.");
                }
                cm->setRotation(visitVertex3(n));

                BoundingBox bb;
                vector<ASTNode*> boundingBox = node->getChildren("BOUNDINGBOX");
                if (boundingBox.size() != 5) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from BOUNDINGBOX expected.");
                }
                bb.setUpperLeft(visitVertex3(boundingBox.at(1)));
                bb.setUpperRight(visitVertex3(boundingBox.at(2)));
                bb.setLowerRight(visitVertex3(boundingBox.at(3)));
                bb.setLowerLeft(visitVertex3(boundingBox.at(4)));

                cm->setBoundingBox(bb);
            }

            return cm;
        }

        Behavior* SITSituationVisitor::visitBehavior(ASTNode *node) {
            Behavior *b = NULL;

            if (node != NULL) {
                ASTNode *n = NULL;

                n = findByKey("POINTIDDRIVER", node, 3);
                if (n == NULL) {
                    b = visitExternalDriver(node->getFirstChild());
                } else {
                    b = visitPointIDDriver(node->getFirstChild());
                }
            }

            return b;
        }

        ExternalDriver* SITSituationVisitor::visitExternalDriver(ASTNode *node) {
            ExternalDriver *ed = NULL;
            if (node != NULL) {
                ed = new ExternalDriver();
            }
            return ed;
        }

        PointIDDriver* SITSituationVisitor::visitPointIDDriver(ASTNode *node) {
            PointIDDriver *pidd = NULL;
            if (node != NULL) {
                pidd = new PointIDDriver();

                // Check for acceleration and velocity.
                ASTNode *n = findByKey("A", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setConstantAcceleration(n->getValue<double>());
                }

                n = findByKey("V", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setConstantVelocity(n->getValue<double>());
                }

                // Check for start type.
                n = findByKey("IMMEDIATELY", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStartType(new Immediately());
                }
                n = findByKey("ONMOVING", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStartType(visitOnMoving(node));
                }
                n = findByKey("ONENTERINGPOLYGON", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStartType(visitOnEnteringPolygon(node));
                }

                // Check for stop type.
                n = findByKey("STOP", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStopType(new Stop());
                }
                n = findByKey("RETURNTOSTART", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStopType(new ReturnToStart());
                }
                n = findByKey("WARPTOSTART", node->getParent(), 3);
                if (n != NULL) {
                    pidd->setStopType(new WarpToStart());
                }

//                // Look for parental POINTIDDRIVER and loop through all POINTIDDRIVER with a value which starts with "(".
//                ASTPrettyPrinter pp;
//                pp.visit(node->getParent()->getLastChild());

                vector<ASTNode*> listOfChildren = node->getParent()->getLastChild()->getChildren("POINTIDDRIVER");
                vector<ASTNode*>::iterator it = listOfChildren.begin();
                while (it != listOfChildren.end()) {
                	string value = (*it++)->getValue<string>();
                	if ( (value.length() > 2) && (value.at(0) == '(') ) {
						value = value.substr(1, value.size() - 2);

						PointID pid(value);
	                    pidd->addPointID(pid);
                	}
                }

            }
            return pidd;
        }

        OnMoving* SITSituationVisitor::visitOnMoving(ASTNode *node) {
            OnMoving *om = NULL;

            if (node != NULL) {
                om = new OnMoving();

                ASTNode *n = findByKey("OBJECTID", node->getParent(), 3);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from OBJECTID expected.");
                }
                om->setID(n->getValue<uint32_t>());
            }

            return om;
        }

        OnEnteringPolygon* SITSituationVisitor::visitOnEnteringPolygon(ASTNode *node) {
            OnEnteringPolygon *oep = NULL;

            if (node != NULL) {
                oep = new OnEnteringPolygon();

                ASTNode *n = findByKey("OBJECTID", node->getParent(), 3);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from OBJECTID expected.");
                }
                oep->setID(n->getValue<uint32_t>());

                n = findByKey("VERTEX2", node->getParent(), 4);
                if (n == NULL) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(SITSituationVisitorException, "Node to get name from VERTEX222 expected.");
                }
                n = n->getParent()->getParent();
                vector<ASTNode*> listOfEnteringPolygon = n->getChildren();
                vector<ASTNode*>::iterator it = listOfEnteringPolygon.begin();
                while (it != listOfEnteringPolygon.end()) {
                    n = (*it++);
                    if (n->getFirstChild()->getKey() == "VERTEX2") {
                        oep->add(visitVertex3(n));
                    }
                }
            }

            return oep;
        }

        ASTNode* SITSituationVisitor::findByKey(const string &key, ASTNode *node, const int32_t &maxDepth) {
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

        ASTNode* SITSituationVisitor::findByValue(const string &value, ASTNode *node, const int32_t &maxDepth) {
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

        void SITSituationVisitor::visit(ASTNode *node) throw (SITSituationVisitorException) {
            if (node != NULL) {
                if (node->getParent() == NULL) {
                    m_situation.setHeader(visitSituationHeader(node->getFirstChild()));

                    vector<ASTNode*> list = node->getChildren();
                    vector<ASTNode*>::iterator it = list.begin();
                    while (it != list.end()) {
                        ASTNode *n = (*it++);
                        if ((n->getFirstChild() != NULL) && (n->getFirstChild()->getKey() == "OBJECT") ) {
                            m_situation.addObject(visitObject(n));
                        }
                    }
                }
            }
        }

    }
} // hesperia::situation
