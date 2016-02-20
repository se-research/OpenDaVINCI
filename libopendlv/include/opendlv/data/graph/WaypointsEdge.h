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

#ifndef HESPERIA_DATA_GRAPH_WAYPOINTSEDGE_H_
#define HESPERIA_DATA_GRAPH_WAYPOINTSEDGE_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendlv/core/wrapper/graph/Edge.h"

namespace opendlv {
    namespace data {
        namespace graph{

            using namespace std;

            /**
             * This class implements the core::wrapper::Edge interface for implementing
             * a digital map using the road network from the scenario.
             */
            class WaypointsEdge : public core::wrapper::graph::Edge {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    WaypointsEdge(const WaypointsEdge &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    WaypointsEdge& operator=(const WaypointsEdge &/*obj*/);

                public:
                    WaypointsEdge();

                    virtual ~WaypointsEdge();

                    /**
                     * This method sets the costs.
                     *
                     * @param c Costs.
                     */
                    void setCosts(const double &c);

                    virtual const string toString() const;

                    virtual double getCosts() const;

                private:
                    double m_costs;
            };

        }
    }
} // opendlv::data::graph

#endif /*HESPERIA_DATA_GRAPH_WAYPOINTSEDGE_H_*/
