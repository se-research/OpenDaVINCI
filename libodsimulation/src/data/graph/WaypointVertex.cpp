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

#include <sstream>
#include <string>

#include "core/opendavinci.h"
#include "hesperia/core/wrapper/graph/Vertex.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/graph/WaypointVertex.h"

namespace hesperia {
    namespace data {
        namespace graph {

            using namespace std;
            using namespace hesperia::data::environment;

            WaypointVertex::WaypointVertex() :
                m_layerID(0),
                m_roadID(0),
                m_laneID(0),
                m_waypointID(0),
                m_position() {}

            WaypointVertex::~WaypointVertex() {}

            uint32_t WaypointVertex::getLayerID() const {
                return m_layerID;
            }

            void WaypointVertex::setLayerID(const uint32_t &layerID) {
                m_layerID = layerID;
            }

            uint32_t WaypointVertex::getRoadID() const {
                return m_roadID;
            }

            void WaypointVertex::setRoadID(const uint32_t &roadID) {
                m_roadID = roadID;
            }

            uint32_t WaypointVertex::getLaneID() const {
                return m_laneID;
            }

            void WaypointVertex::setLaneID(const uint32_t &laneID) {
                m_laneID = laneID;
            }

            uint32_t WaypointVertex::getWaypointID() const {
                return m_waypointID;
            }

            void WaypointVertex::setWaypointID(const uint32_t &waypointID) {
                m_waypointID = waypointID;
            }

            void WaypointVertex::setPosition(const Point3 &pos) {
                m_position = pos;
            }

            const Point3 WaypointVertex::getPosition() const {
                return m_position;
            }

            const string WaypointVertex::toString() const {
                stringstream sstr;
                sstr << m_layerID << "." << m_roadID << "." << m_laneID << "." << m_waypointID << "@" << m_position.toString();
                return sstr.str();
            }

            int32_t WaypointVertex::getIdentifier() const {
                return static_cast<int32_t>(m_layerID * 100000 + m_roadID * 10000 + m_laneID * 100 + m_waypointID);
            }

            double WaypointVertex::getDistanceTo(const Vertex &v2) const {
                double value = -1;
                try {
                    const WaypointVertex &wpv2 = dynamic_cast<const WaypointVertex&>(v2);
                    value = m_position.getXYDistanceTo(wpv2.getPosition());
                }
                catch(...) {}
                return value;
            }

        }
    }
} // hesperia::data::graph
