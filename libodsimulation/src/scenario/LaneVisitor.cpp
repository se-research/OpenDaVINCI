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

#include <vector>

#include "core/wrapper/parser/ASTNode.h"
#include "hesperia/data/environment/NamedLine.h"
#include "hesperia/data/scenario/Arc.h"
#include "hesperia/data/scenario/Connector.h"
#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/StraightLine.h"
#include "hesperia/scenario/FindNodeByPointIDVisitor.h"
#include "hesperia/scenario/LaneVisitor.h"
#include "hesperia/data/graph/WaypointsEdge.h"
#include "hesperia/data/graph/WaypointVertex.h"

namespace core { namespace wrapper { namespace graph { class DirectedGraph; } } }

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace hesperia::data::environment;
        using namespace hesperia::data::graph;
        using namespace hesperia::data::scenario;

        LaneVisitor::LaneVisitor(core::wrapper::graph::DirectedGraph &g, hesperia::data::scenario::Scenario &scenario) :
            m_graph(g),
            m_scenario(scenario),
            m_listOfLines() {}

        LaneVisitor::~LaneVisitor() {}

        void LaneVisitor::visit(ScenarioNode &node) {
            try {
                Lane &l = dynamic_cast<Lane&>(node);

                if (l.getLaneModel() != NULL) {
                    const PointModel *pm = dynamic_cast<PointModel*>(l.getLaneModel());
                    bool wasPM = false;
                    if (!wasPM && pm != NULL) {
                        visit(pm);
                        wasPM = true;
                    }

                    bool wasArc = false;
                    const Arc *arc = dynamic_cast<Arc*>(l.getLaneModel());
                    if (!wasArc && !wasPM && arc != NULL) {
                        visit(arc);
                        wasArc = true;
                    }

                    const StraightLine *sl = dynamic_cast<StraightLine*>(l.getLaneModel());
                    bool wasSL = false;
                    if (!wasSL && !wasArc && !wasPM && (sl != NULL)) {
                        visit(sl);
                        wasSL = true;
                    }
                }
            }
            catch(...) {}
        }

        void LaneVisitor::visit(const hesperia::data::scenario::PointModel *pm) {
            if (pm != NULL) {
                stringstream name;
                name << pm->getLane()->getRoad()->getLayer()->getID() << "." << pm->getLane()->getRoad()->getID() << "." << pm->getLane()->getID();
                cerr << "Found PointModel Lane: " << name.str() << endl;

                const vector<IDVertex3> &listOfWaypoints = pm->getListOfIdentifiableVertices();
                const uint32_t SIZE = listOfWaypoints.size();
                for(uint32_t i = 0; i < (SIZE-1); i++) {
                    IDVertex3 vt1 = listOfWaypoints.at(i);
                    IDVertex3 vt2 = listOfWaypoints.at(i+1);

                    // Construct a line between to consecutive points.
                    hesperia::data::environment::NamedLine line(name.str(), vt1, vt2);
                    m_listOfLines.push_back(line);

                    WaypointVertex *v1 = new WaypointVertex();
                    v1->setLayerID(pm->getLane()->getRoad()->getLayer()->getID());
                    v1->setRoadID(pm->getLane()->getRoad()->getID());
                    v1->setLaneID(pm->getLane()->getID());
                    v1->setWaypointID(vt1.getID());
                    v1->setPosition(vt1);
                    cerr << "Constructed node: " << pm->getLane()->getRoad()->getLayer()->getID() << "." << pm->getLane()->getRoad()->getID() << "." << pm->getLane()->getID() << "." << vt1.getID() << endl;

                    WaypointVertex *v2 = new WaypointVertex();
                    v2->setLayerID(pm->getLane()->getRoad()->getLayer()->getID());
                    v2->setRoadID(pm->getLane()->getRoad()->getID());
                    v2->setLaneID(pm->getLane()->getID());
                    v2->setWaypointID(vt2.getID());
                    v2->setPosition(vt2);

                    cerr << "Constructed node: " << pm->getLane()->getRoad()->getLayer()->getID() << "." << pm->getLane()->getRoad()->getID() << "." << pm->getLane()->getID() << "." << vt2.getID() << endl;

                    WaypointsEdge *edge = new WaypointsEdge();
                    edge->setCosts(vt1.getXYDistanceTo(vt2));

                    // Add vertices and edge to graph.
                    m_graph.updateEdge(v1, v2, edge);
                }

                // Add edges for the connectors.
                const vector<Connector> &listOfConnectors = pm->getListOfConnectors();
                vector<Connector>::const_iterator mt = listOfConnectors.begin();
                while (mt != listOfConnectors.end()) {
                    Connector c = (*mt++);

                    cerr << "Found connector: " << c.toString() << " to add." << endl;
                    try {
                        // Find start vertex.
                        FindNodeByPointIDVisitor startVertexFinder(c.getSource());
                        m_scenario.accept(startVertexFinder);

                        // Find end vertex.
                        FindNodeByPointIDVisitor endVertexFinder(c.getTarget());
                        m_scenario.accept(endVertexFinder);

                        // Check if valid models.
                        if ( hasStartAndEndVertex(c) ) {
//                            const IDVertex3 startV = startPointModel->getIDVertex3(c.getSource().getPointID());
//                            const IDVertex3 endV = endPointModel->getIDVertex3(c.getTarget().getPointID());
                            const IDVertex3 startV = startVertexFinder.getIDVertex3();
                            const IDVertex3 endV = endVertexFinder.getIDVertex3();

                            WaypointVertex *v1 = new WaypointVertex();
                            v1->setLayerID(c.getSource().getLayerID());
                            v1->setRoadID(c.getSource().getRoadID());
                            v1->setLaneID(c.getSource().getLaneID());
                            v1->setWaypointID(c.getSource().getPointID());
                            v1->setPosition(startV);

                            WaypointVertex *v2 = new WaypointVertex();
                            v2->setLayerID(c.getTarget().getLayerID());
                            v2->setRoadID(c.getTarget().getRoadID());
                            v2->setLaneID(c.getTarget().getLaneID());
                            v2->setWaypointID(c.getTarget().getPointID());
                            v2->setPosition(endV);

                            WaypointsEdge *edge = new WaypointsEdge();
                            edge->setCosts(startV.getXYDistanceTo(endV));

                            m_graph.updateEdge(v1, v2, edge);
                            cerr << "Adding edge for connector between " << v1->toString() << " and " << v2->toString() << endl;
                        }
                    }
                    catch(...) {}
                }
            }
        }


        void LaneVisitor::visit(const hesperia::data::scenario::Arc *arc) {
            if (arc != NULL) {
                stringstream name;
                name << arc->getLane()->getRoad()->getLayer()->getID() << "." << arc->getLane()->getRoad()->getID() << "." << arc->getLane()->getID();
                cerr << "Found Arc Lane: " << name.str() << endl;

                IDVertex3 vt1 = arc->getStart();
                IDVertex3 vt2 = arc->getEnd();

                // Approximate arc by a set of lines.
                {
                    // ScUI graphical modeling tool starts Arc at 6pm but we use 3pm. Thus, we have to correct the Z-rotation.
                    double correctRotation = cartesian::Constants::PI / 2.0;

                    // Transposition of the arc.
                    hesperia::data::environment::Point3 t(0, 0, 0);
                    t.setX(vt1.getX() - arc->getRadius() * cos(arc->getRotationZ() - correctRotation));
                    t.setY(vt1.getY() - arc->getRadius() * sin(arc->getRotationZ() - correctRotation));      
                    t.setZ(0.05);

                    double beginInterval = arc->getBeginInterval();
                    double endInterval = arc->getEndInterval();
                    double stepSize = 5.0 * cartesian::Constants::PI / 180.0; // 5° to rad.
                    uint32_t steps = (unsigned int) round( (endInterval - beginInterval) / stepSize );

                    hesperia::data::environment::Point3 centerOld = vt1;

                    for(uint32_t i = 0; i < steps; i++) {
                        // Calculate the skeleton approximation.
                        hesperia::data::environment::Point3 center(0, 0, 0);
                        center.setX(arc->getRadius() * cos(arc->getRotationZ() - correctRotation + i * stepSize));
                        center.setY(arc->getRadius() * sin(arc->getRotationZ() - correctRotation + i * stepSize));

                        // Transpose the points.
                        center += t;

                        // Construct a line between to consecutive points.
                        hesperia::data::environment::NamedLine line(name.str(), centerOld, center);
                        m_listOfLines.push_back(line);

                        // Keep old point.
                        centerOld = center;
                    }
                }

                WaypointVertex *v1 = new WaypointVertex();
                v1->setLayerID(arc->getLane()->getRoad()->getLayer()->getID());
                v1->setRoadID(arc->getLane()->getRoad()->getID());
                v1->setLaneID(arc->getLane()->getID());
                v1->setWaypointID(vt1.getID());
                v1->setPosition(vt1);
                cerr << "Constructed node: " << arc->getLane()->getRoad()->getLayer()->getID() << "." << arc->getLane()->getRoad()->getID() << "." << arc->getLane()->getID() << "." << vt1.getID() << endl;

                WaypointVertex *v2 = new WaypointVertex();
                v2->setLayerID(arc->getLane()->getRoad()->getLayer()->getID());
                v2->setRoadID(arc->getLane()->getRoad()->getID());
                v2->setLaneID(arc->getLane()->getID());
                v2->setWaypointID(vt2.getID());
                v2->setPosition(vt2);

                cerr << "Constructed node: " << arc->getLane()->getRoad()->getLayer()->getID() << "." << arc->getLane()->getRoad()->getID() << "." << arc->getLane()->getID() << "." << vt2.getID() << endl;

                WaypointsEdge *edge = new WaypointsEdge();
                edge->setCosts(vt1.getXYDistanceTo(vt2));

                // Add vertices and edge to graph.
                m_graph.updateEdge(v1, v2, edge);

                // Add edges for the connectors.
                const vector<Connector> &listOfConnectors = arc->getListOfConnectors();
                vector<Connector>::const_iterator mt = listOfConnectors.begin();
                while (mt != listOfConnectors.end()) {
                    Connector c = (*mt++);

                    cerr << "Found connector: " << c.toString() << " to add." << endl;
                    try {
                        // Find start vertex.
                        FindNodeByPointIDVisitor startVertexFinder(c.getSource());
                        m_scenario.accept(startVertexFinder);

                        // Find end vertex.
                        FindNodeByPointIDVisitor endVertexFinder(c.getTarget());
                        m_scenario.accept(endVertexFinder);

                        // Check if valid models.
                        if ( hasStartAndEndVertex(c) ) {
                            const IDVertex3 startV = startVertexFinder.getIDVertex3();
                            const IDVertex3 endV = endVertexFinder.getIDVertex3();

                            v1 = new WaypointVertex();
                            v1->setLayerID(c.getSource().getLayerID());
                            v1->setRoadID(c.getSource().getRoadID());
                            v1->setLaneID(c.getSource().getLaneID());
                            v1->setWaypointID(c.getSource().getPointID());
                            v1->setPosition(startV);

                            v2 = new WaypointVertex();
                            v2->setLayerID(c.getTarget().getLayerID());
                            v2->setRoadID(c.getTarget().getRoadID());
                            v2->setLaneID(c.getTarget().getLaneID());
                            v2->setWaypointID(c.getTarget().getPointID());
                            v2->setPosition(endV);

                            edge = new WaypointsEdge();
                            edge->setCosts(startV.getXYDistanceTo(endV));

                            m_graph.updateEdge(v1, v2, edge);
                            cerr << "Adding edge for connector between " << v1->toString() << " and " << v2->toString() << endl;
                        }
                    }
                    catch(...) {}
                }
            }
        }

        void LaneVisitor::visit(const hesperia::data::scenario::StraightLine *sl) {
            if (sl != NULL) {
                stringstream name;
                name << sl->getLane()->getRoad()->getLayer()->getID() << "." << sl->getLane()->getRoad()->getID() << "." << sl->getLane()->getID();
                cerr << "Found StraightLine Lane: " << name.str() << endl;

                IDVertex3 vt1 = sl->getStart();
                IDVertex3 vt2 = sl->getEnd();

                // Construct a line between to consecutive points.
                hesperia::data::environment::NamedLine line(name.str(), vt1, vt2);
                m_listOfLines.push_back(line);

                WaypointVertex *v1 = new WaypointVertex();
                v1->setLayerID(sl->getLane()->getRoad()->getLayer()->getID());
                v1->setRoadID(sl->getLane()->getRoad()->getID());
                v1->setLaneID(sl->getLane()->getID());
                v1->setWaypointID(vt1.getID());
                v1->setPosition(vt1);
                cerr << "Constructed node: " << sl->getLane()->getRoad()->getLayer()->getID() << "." << sl->getLane()->getRoad()->getID() << "." << sl->getLane()->getID() << "." << vt1.getID() << endl;

                WaypointVertex *v2 = new WaypointVertex();
                v2->setLayerID(sl->getLane()->getRoad()->getLayer()->getID());
                v2->setRoadID(sl->getLane()->getRoad()->getID());
                v2->setLaneID(sl->getLane()->getID());
                v2->setWaypointID(vt2.getID());
                v2->setPosition(vt2);

                cerr << "Constructed node: " << sl->getLane()->getRoad()->getLayer()->getID() << "." << sl->getLane()->getRoad()->getID() << "." << sl->getLane()->getID() << "." << vt2.getID() << endl;

                WaypointsEdge *edge = new WaypointsEdge();
                edge->setCosts(vt1.getXYDistanceTo(vt2));

                // Add vertices and edge to graph.
                m_graph.updateEdge(v1, v2, edge);

                // Add edges for the connectors.
                const vector<Connector> &listOfConnectors = sl->getListOfConnectors();
                vector<Connector>::const_iterator mt = listOfConnectors.begin();
                while (mt != listOfConnectors.end()) {
                    Connector c = (*mt++);

                    cerr << "Found connector: " << c.toString() << " to add." << endl;
                    try {
                        // Find start vertex.
                        FindNodeByPointIDVisitor startVertexFinder(c.getSource());
                        m_scenario.accept(startVertexFinder);

                        // Find end vertex.
                        FindNodeByPointIDVisitor endVertexFinder(c.getTarget());
                        m_scenario.accept(endVertexFinder);

                        // Check if valid models.
                        if ( hasStartAndEndVertex(c) ) {
                            const IDVertex3 startV = startVertexFinder.getIDVertex3();
                            const IDVertex3 endV = endVertexFinder.getIDVertex3();

                            v1 = new WaypointVertex();
                            v1->setLayerID(c.getSource().getLayerID());
                            v1->setRoadID(c.getSource().getRoadID());
                            v1->setLaneID(c.getSource().getLaneID());
                            v1->setWaypointID(c.getSource().getPointID());
                            v1->setPosition(startV);

                            v2 = new WaypointVertex();
                            v2->setLayerID(c.getTarget().getLayerID());
                            v2->setRoadID(c.getTarget().getRoadID());
                            v2->setLaneID(c.getTarget().getLaneID());
                            v2->setWaypointID(c.getTarget().getPointID());
                            v2->setPosition(endV);

                            edge = new WaypointsEdge();
                            edge->setCosts(startV.getXYDistanceTo(endV));

                            m_graph.updateEdge(v1, v2, edge);
                            cerr << "Adding edge for connector between " << v1->toString() << " and " << v2->toString() << endl;
                        }
                    }
                    catch(...) {}
                }
            }
        }

        bool LaneVisitor::hasStartAndEndVertex(const hesperia::data::scenario::Connector &c) {
            bool startVertexFound = false;
            bool endVertexFound = false;

            // Find start vertex.
            {
                FindNodeByPointIDVisitor startVertexFinder(c.getSource());
                m_scenario.accept(startVertexFinder);

                const Arc *startArc = dynamic_cast<const Arc*>(startVertexFinder.getLaneModel());
//                const Clothoid *startClothoid = dynamic_cast<const Clothoid*>(startVertexFinder.getLaneModel());
                const PointModel *startPointModel = dynamic_cast<const PointModel*>(startVertexFinder.getLaneModel());
                const StraightLine *startStraightLine = dynamic_cast<const StraightLine*>(startVertexFinder.getLaneModel());

                startVertexFound |= (startArc != NULL) ||
//                                    (startClothoid != NULL) ||
                                    (startPointModel != NULL) ||
                                    (startStraightLine != NULL);
            }

            // Find end vertex.
            {
                FindNodeByPointIDVisitor endVertexFinder(c.getTarget());
                m_scenario.accept(endVertexFinder);

                const Arc *endArc = dynamic_cast<const Arc*>(endVertexFinder.getLaneModel());
//                const Clothoid *endClothoid = dynamic_cast<const Clothoid*>(endVertexFinder.getLaneModel());
                const PointModel *endPointModel = dynamic_cast<const PointModel*>(endVertexFinder.getLaneModel());
                const StraightLine *endStraightLine = dynamic_cast<const StraightLine*>(endVertexFinder.getLaneModel());

                endVertexFound |= (endArc != NULL) ||
//                                  (endClothoid != NULL) ||
                                  (endPointModel != NULL) ||
                                  (endStraightLine != NULL);
            }

            return (startVertexFound && endVertexFound);
        }

        vector<hesperia::data::environment::NamedLine> LaneVisitor::getListOfLines() const {
            return m_listOfLines;
        }

    }
} // hesperia::scenario
