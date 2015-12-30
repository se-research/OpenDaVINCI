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

#ifndef HESPERIA_WRAPPER_GRAPH_VERTEX_H_
#define HESPERIA_WRAPPER_GRAPH_VERTEX_H_

#include <string>

#include "core/platform.h"

namespace core {
    namespace wrapper {
        namespace graph {

            using namespace std;

            /**
             * This interface encapsulates all necessary method for a graph's vertex.
             */
            class OPENDAVINCI_API Vertex {
                public:
                    virtual ~Vertex();

                    /**
                     * This method returns a human readable representation.
                     *
                     * @return Human readable representation.
                     */
                    virtual const string toString() const = 0;

                    /**
                     * This method returns a unique identifier for this vertex.
                     *
                     * @return Unique identifier.
                     */
                    virtual int32_t getIdentifier() const = 0;

                    /**
                     * This method returns the distance to the
                     * given other vertex.
                     *
                     * @param v2 Other vertex.
                     * @return Distance to v2 or -1 if v2 is invalid.
                     */
                    virtual double getDistanceTo(const Vertex &v2) const = 0;
            };

        }
    }
} // core::wrapper::graph

#endif /*HESPERIA_WRAPPER_GRAPH_VERTEX_H_*/
