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

#ifndef HESPERIA_SCENARIO_LANEVISITOR_H_
#define HESPERIA_SCENARIO_LANEVISITOR_H_

#include "opendavinci/core/opendavinci.h"

#include "opendlv/core/wrapper/graph/DirectedGraph.h"
#include "opendlv/core/wrapper/graph/Edge.h"

#include "opendlv/data/environment/NamedLine.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/StraightLine.h"
#include "opendlv/data/scenario/Arc.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Scenario.h"

namespace opendlv {
    namespace scenario {

        using namespace std;

        /**
         * This class implements a visitor for constructing the graph.
         */
        class LaneVisitor : public opendlv::data::scenario::ScenarioVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                LaneVisitor(const LaneVisitor &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                LaneVisitor& operator=(const LaneVisitor &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param g Graph.
                 * @param scenario Scenario.
                 */
                LaneVisitor(core::wrapper::graph::DirectedGraph &g, opendlv::data::scenario::Scenario &scenario);

                virtual ~LaneVisitor();

                virtual void visit(opendlv::data::scenario::ScenarioNode &node);

                vector<opendlv::data::environment::NamedLine> getListOfLines() const;

            private:
                core::wrapper::graph::DirectedGraph &m_graph;
                opendlv::data::scenario::Scenario &m_scenario;

                // This vector contains all line between start and end points from lanes (arcs are approximated).
                vector<opendlv::data::environment::NamedLine> m_listOfLines;

                /**
                 * This method is called by the generic visit method.
                 *
                 * @param pm PointModel to visit.
                 */
                void visit(const opendlv::data::scenario::PointModel *pm);

                /**
                 * This method is called by the generic visit method.
                 *
                 * @param sl StraightLine to visit. Covers also arcs.
                 */
                void visit(const opendlv::data::scenario::StraightLine *sl);

                /**
                 * This method is called by the generic visit method.
                 *
                 * @param arc Arc to visit. Covers also arcs.
                 */
                void visit(const opendlv::data::scenario::Arc *arc);

                /**
                 * This method returns true if the start and endvertex of
                 * a connector have been found in an Arc, Clothoid, Point-,
                 * or StraightLine model.
                 *
                 * @param c connector to be checked.
                 */
                bool hasStartAndEndVertex(const opendlv::data::scenario::Connector &c);
        };

    }
} // opendlv::scenario

#endif /*HESPERIA_SCENARIO_LANEVISITOR_H_*/
