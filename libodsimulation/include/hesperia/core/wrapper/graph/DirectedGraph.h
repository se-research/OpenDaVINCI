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

#ifndef HESPERIA_WRAPPER_GRAPH_DIRECTEDGRAPH_H_
#define HESPERIA_WRAPPER_GRAPH_DIRECTEDGRAPH_H_

#include <map>
#include <string>
#include <vector>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace wrapper {
        namespace graph {

class Edge;
class Vertex;

            using namespace std;

            /**
             * This interface encapsulates all necessary method for a graph's vertex.
             */
            class OPENDAVINCI_API DirectedGraph {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    DirectedGraph(const DirectedGraph &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    DirectedGraph& operator=(const DirectedGraph &);

                public:
                    DirectedGraph();

                    virtual ~DirectedGraph();

                    /**
                     * This method adds a vertex to the graph  iff the vertex v
                     * is not in the graph. On destruction, all added vertices
                     * and edges will be destroyed.
                     *
                     * @param v Vertex to be added.
                     */
                    void addVertex(const Vertex *v);

                    /**
                     * This method returns true, if the vertex described by v
                     * is already in the graph.
                     *
                     * @param id Id to search for.
                     * @return true, if the graph contains a vertex with the given id.
                     */
                    bool hasVertex(const Vertex &v);

                    /**
                     * This method adds a directed edge from v1 to v2
                     * with the given edge. If one or both vertices
                     * do not exist, they  will be inserted into the graph.
                     * If the edge already exists, it is updated.
                     * If one parameter is NULL, the graph remain unmodified.
                     * If v1, v2 or e are not in the graph, they will be
                     * added AND deleted on destruction.
                     *
                     * @param v1 First vertex.
                     * @param v2 Second vertex.
                     * @param e Edge.
                     */
                    void updateEdge(const Vertex *v1, const Vertex *v2, const Edge *e);

                    /**
                     * This method returns a human readable representation of all edges.
                     *
                     * @return Human readable representation of all edges.
                     */
                    const string toString() const;

                    /**
                     * This method returns a representation of all edges in Graphviz's dot format.
                     *
                     * @return Graphviz dot representation of all edges.
                     */
                    const string toGraphizDot() const;

                    /**
                     * This method returns the shortest path between two given vertices.
                     *
                     * @param v1 Start vertex.
                     * @param v2 End vertex.
                     * @return List of vertices to choose to reach v2 from v1 using the shortest path.
                     */
                    vector<const Vertex*> getShortestPath(const Vertex &v1, const Vertex &v2);

                private:
                    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, const Vertex*, boost::property<boost::edge_weight_t, double> > GraphDefinition;
                    typedef boost::property_map<GraphDefinition, boost::edge_weight_t>::type WeightMap;

                    GraphDefinition m_graph; // Graph.
                    WeightMap m_weightMap; // Edges' weights.
                    map<int32_t, GraphDefinition::vertex_descriptor> m_mapOfVertices; // Map of vertices.
                    vector<const Vertex*> m_listOfVertices;
                    vector<const Edge*> m_listOfEdges;
            };

        }
    }
} // core::wrapper::graph

#endif /*HESPERIA_WRAPPER_GRAPH_DIRECTEDGRAPH_H_*/
