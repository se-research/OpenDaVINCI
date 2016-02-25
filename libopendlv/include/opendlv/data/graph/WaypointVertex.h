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

#ifndef HESPERIA_DATA_GRAPH_WAYPOINTVERTEX_H_
#define HESPERIA_DATA_GRAPH_WAYPOINTVERTEX_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendlv/core/wrapper/graph/Vertex.h"

#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace graph {

            using namespace std;

            /**
             * This class implements the core::wrapper::Vertex interface for implementing
             * a digital map using the road network from the scenario.
             */
            class WaypointVertex : public core::wrapper::graph::Vertex {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    WaypointVertex(const WaypointVertex &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    WaypointVertex& operator=(const WaypointVertex &/*obj*/);

                public:
                    WaypointVertex();

                    virtual ~WaypointVertex();

                    /**
                     * This method returns the layerID.
                     *
                     * @return LayerID.
                     */
                    uint32_t getLayerID() const;

                    /**
                     * This method sets the layerID.
                     *
                     * @param layerID;
                     */
                    void setLayerID(const uint32_t &layerID);

                    /**
                     * This method returns the roadID.
                     *
                     * @return RoadID.
                     */
                    uint32_t getRoadID() const;

                    /**
                     * This method sets the roadID.
                     *
                     * @param roadID;
                     */
                    void setRoadID(const uint32_t &roadID);

                    /**
                     * This method returns the laneID.
                     *
                     * @return LaneID.
                     */
                    uint32_t getLaneID() const;

                    /**
                     * This method sets the laneID.
                     *
                     * @param laneID;
                     */
                    void setLaneID(const uint32_t &laneID);

                    /**
                     * This method returns the waypointID.
                     *
                     * @return WaypointID.
                     */
                    uint32_t getWaypointID() const;

                    /**
                     * This method sets the waypointID.
                     *
                     * @param waypointID;
                     */
                    void setWaypointID(const uint32_t &waypointID);

                    /**
                     * This method sets the position.
                     *
                     * @param pos Position.
                     */
                    void setPosition(const opendlv::data::environment::Point3 &pos);

                    /**
                     * This method returns the position.
                     *
                     * @return Position.
                     */
                    const opendlv::data::environment::Point3 getPosition() const;

                    virtual const string toString() const;

                    virtual int32_t getIdentifier() const;

                    virtual double getDistanceTo(const Vertex &v2) const;

                private:
                    uint32_t m_layerID;
                    uint32_t m_roadID;
                    uint32_t m_laneID;
                    uint32_t m_waypointID;

                    opendlv::data::environment::Point3 m_position;
            };

        }
    }
} // opendlv::data::graph

#endif /*HESPERIA_DATA_GRAPH_WAYPOINTVERTEX_H_*/
