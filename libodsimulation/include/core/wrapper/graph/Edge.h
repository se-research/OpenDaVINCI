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

#ifndef HESPERIA_WRAPPER_GRAPH_EDGE_H_
#define HESPERIA_WRAPPER_GRAPH_EDGE_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace core {
    namespace wrapper {
        namespace graph {

            using namespace std;

            /**
             * This interface encapsulates all necessary method for a graph's edge.
             */
            class OPENDAVINCI_API Edge {
                public:
                    virtual ~Edge();

                    /**
                     * This method returns a human readable representation.
                     *
                     * @return Human readable representation.
                     */
                    virtual const string toString() const = 0;

                    /**
                     * This method returns the costs between both vertices.
                     *
                     * @return Costs.
                     */
                    virtual double getCosts() const = 0;
            };

        }
    }
} // core::wrapper::graph

#endif /*HESPERIA_WRAPPER_GRAPH_EDGE_H_*/
