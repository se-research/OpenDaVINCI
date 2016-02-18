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

#ifndef HESPERIA_CORE_THREED_MODELS_GRID_H_
#define HESPERIA_CORE_THREED_MODELS_GRID_H_

#include "opendavinci/core/opendavinci.h"

#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"

namespace opendlv {
    namespace threeD {
        namespace models {

            /**
             * This class represents a grid in the XY-layer.
             */
            class OPENDAVINCI_API Grid : public Node {
                public:
                    /**
                     * Constructor.
                     *
                    * @param nodeDesciptor Description for this node.
                     * @param size Size of the grid in positive XY-direction (i.e. the resulting grid is 2*size).
                     * @param lineWidth Width of the grid's lines.
                     */
                    Grid(const NodeDescriptor &nodeDescriptor, const uint32_t &size, const float &lineWidth);

                    virtual ~Grid();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Grid(const Grid &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Grid& operator=(const Grid &obj);

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                private:
                    uint32_t m_size;
                    float m_lineWidth;
            };

        }
    }
} // opendlv::threeD::models

#endif /*HESPERIA_CORE_THREED_MODELS_GRID_H_*/
