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

#include "hesperia/data/graph/WaypointsEdge.h"

namespace hesperia {
    namespace data {
        namespace graph {

            using namespace std;

            WaypointsEdge::WaypointsEdge() :
                m_costs(0) {}

            WaypointsEdge::~WaypointsEdge() {}

            void WaypointsEdge::setCosts(const double &c) {
                m_costs = c;
            }

            const string WaypointsEdge::toString() const {
                stringstream sstr;
                sstr << m_costs;
                return sstr.str();
            }

            double WaypointsEdge::getCosts() const {
                return m_costs;
            }

        }
    }
} // hesperia::data::graph
