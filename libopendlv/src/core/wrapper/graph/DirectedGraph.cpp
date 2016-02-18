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

#include <algorithm>
#include <iostream>
#include <list>

#include <boost/graph/astar_search.hpp>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/strings/StringToolbox.h"
#include "opendlv/core/wrapper/graph/DirectedGraph.h"
#include "opendlv/core/wrapper/graph/Edge.h"
#include "opendlv/core/wrapper/graph/Vertex.h"

namespace core {
    namespace wrapper {
        namespace graph {

// The following compiler switches are added to ignore -Weffc++ warnings in Boost.
class Edge;
#ifdef __GNUC__
#  if __GNUC__ >= 4
#    if __GNUC_MINOR__ >= 6
#      pragma GCC diagnostic push
#      pragma GCC diagnostic ignored "-Weffc++"
#    endif
#  endif
#endif
            // Euclidean Distances, see: http://www.cs.rpi.edu/~beevek/research/astar_bgl04.pdf
            template<class Graph, class EdgeWeight>
            class DistanceHeuristic : public boost::astar_heuristic<Graph, EdgeWeight> {
                public:
                    typedef typename boost::graph_traits<Graph>::vertex_descriptor Vertex;

                    DistanceHeuristic(Graph &g, Vertex goal) :
                        m_graph(g),
                        m_goal(goal) {}

                    EdgeWeight operator()(Vertex u) {
                        EdgeWeight value = 0;
                        if ( (m_graph[m_goal] != NULL) && (m_graph[u] != NULL) ) {
                            value = m_graph[m_goal]->getDistanceTo(*(m_graph[u]));
                        }
                        cerr << "Value = " << value << endl;
                        return value;
                    }

                private:
                    Graph &m_graph;
                    Vertex m_goal;
            };

            // This class is thrown as exception if the goal was found.
            struct found_goal {};

            // This class is used as visitor to find the goal.
            template <class Vertex>
            class AStarGoalVisitor : public boost::default_astar_visitor {
                public:
                    AStarGoalVisitor(Vertex goal) :
                        m_goal(goal) {}

                    template <class Graph>
                    void examine_vertex(Vertex u, Graph &/*g*/) {
                        if (u == m_goal) {
                            throw found_goal();
                        }
                    }

                private:
                    Vertex m_goal;
            };
#ifdef __GNUC__
#  if __GNUC__ >= 4
#    if __GNUC_MINOR__ >= 6
#      pragma GCC diagnostic pop
#    endif
#  endif
#endif

            ////////////////////////////////////////////////////////////////////

            DirectedGraph::DirectedGraph() :
                m_graph(),
                m_weightMap(),
                m_mapOfVertices(),
                m_listOfVertices(),
                m_listOfEdges() {}

            DirectedGraph::~DirectedGraph() {
                // Delete all vertices.
                vector<const Vertex*>::iterator it = m_listOfVertices.begin();
                while (it != m_listOfVertices.end()) {
                    const Vertex *v = (*it++);
                    OPENDAVINCI_CORE_DELETE_POINTER(v);
                }

                // Delete all edges.
                vector<const Edge*>::iterator jt = m_listOfEdges.begin();
                while (jt != m_listOfEdges.end()) {
                    const Edge *e = (*jt++);
                    OPENDAVINCI_CORE_DELETE_POINTER(e);
                }
            }

            void DirectedGraph::addVertex(const Vertex *v) {
                if ( (v != NULL) && (!hasVertex(*v)) ) {
                    GraphDefinition::vertex_descriptor vertex = boost::add_vertex(m_graph);

                    // Safe newly created vertex for further usage.
                    m_mapOfVertices[v->getIdentifier()] = vertex;

                    // Safe pointer for removal.
                    m_listOfVertices.push_back(v);

                    // Actually add vertex to graph.
                    m_graph[vertex] = v;
                }
            }

            bool DirectedGraph::hasVertex(const Vertex &v) {
                map<int32_t, GraphDefinition::vertex_descriptor>::iterator result = m_mapOfVertices.find(v.getIdentifier());
                return (result != m_mapOfVertices.end());
            }

            void DirectedGraph::updateEdge(const Vertex *v1, const Vertex *v2, const Edge *e) {
                if ( (v1 != NULL) && (v2 != NULL) && (e != NULL) ) {
                    // If both vertices are not in the graph, they are added. Otherwise, both calls are simply ignored.
                    addVertex(v1);
                    addVertex(v2);
                    m_listOfEdges.push_back(e);

                    GraphDefinition::vertex_descriptor vertex1 = m_mapOfVertices[v1->getIdentifier()];
                    GraphDefinition::vertex_descriptor vertex2 = m_mapOfVertices[v2->getIdentifier()];

                    bool found = false;
                    GraphDefinition::edge_descriptor edge;
                    boost::tie(edge, found) = boost::add_edge(vertex1, vertex2, m_graph);
                    m_weightMap[edge] = e->getCosts();

                    clog << "Edge " << e->toString() << " between " << v1->toString() << " and " << v2->toString() << " added to graph." << endl;
                }
            }

            const string DirectedGraph::toString() const {
                stringstream sstr;

                sstr << "edges(g) = ";
                boost::graph_traits<GraphDefinition>::edge_iterator ei, ei_end;
                for(boost::tie(ei, ei_end) = boost::edges(m_graph); ei != ei_end; ei++) {
                    sstr << "(" << m_graph[boost::source(*ei, m_graph)]->toString() << "-" << m_weightMap[*ei] << "->" << m_graph[boost::target(*ei, m_graph)]->toString() << ") ";
                }

                return sstr.str();
            }

            const string DirectedGraph::toGraphizDot() const {
                stringstream sstr;

                sstr << "digraph RouteNetwork" << endl;
                sstr << "{" << endl;
                    boost::graph_traits<GraphDefinition>::edge_iterator ei, ei_end;
                    for(boost::tie(ei, ei_end) = boost::edges(m_graph); ei != ei_end; ei++) {
                        string source_ = m_graph[boost::source(*ei, m_graph)]->toString();
                        string target_ = m_graph[boost::target(*ei, m_graph)]->toString();

                        string source = core::strings::StringToolbox::split(source_, '@').at(0);
                        string target = core::strings::StringToolbox::split(target_, '@').at(0);

                        replace(source.begin(), source.end(), '.', '_');
                        replace(target.begin(), target.end(), '.', '_');

                        sstr << "\tWP_" << source << "->WP_" << target << " [label=\"" << m_weightMap[*ei] << "\"];" << endl;;
                    }
                sstr << "}" << endl;

                return sstr.str();
            }

            vector<const Vertex*> DirectedGraph::getShortestPath(const Vertex &v1, const Vertex &v2) {
                vector<const Vertex*> route;
                if (hasVertex(v1) && hasVertex(v2)) {
                    clog << "Getting route from " << v1.toString() << " to " << v2.toString() << endl;

                    GraphDefinition::vertex_descriptor start = m_mapOfVertices[v1.getIdentifier()];
                    GraphDefinition::vertex_descriptor end = m_mapOfVertices[v2.getIdentifier()];

                    vector<GraphDefinition::vertex_descriptor> p(boost::num_vertices(m_graph));
                    vector<double> d(boost::num_vertices(m_graph));

                    try {
                        // Call A* algorithm.
                        boost::astar_search(m_graph, start,
                                          DistanceHeuristic<GraphDefinition, double>(m_graph, end),
                                          boost::predecessor_map(&p[0]).distance_map(&d[0]).visitor(AStarGoalVisitor<GraphDefinition::vertex_descriptor>(end)));
                    }
                    catch(found_goal &/*fg*/) {
                        // An exception is thrown if end was found.
                        list<GraphDefinition::vertex_descriptor> path;
                        for (GraphDefinition::vertex_descriptor v = end; ; v = p[v]) {
                            path.push_front(v);
                            if (v == p[v]) {
                                break;
                            }
                        }

                        list<GraphDefinition::vertex_descriptor>::iterator it = path.begin();
                        stringstream sstr;
                        while (it != path.end()) {
                            route.push_back(m_graph[*it]);
                            sstr << m_graph[*it]->toString() << " ";
                            it++;
                        }
                        cout << "Route: " << sstr.str() << endl;
                    }
                }
                return route;
            }
        }
    }
} // core::wrapper::graph
