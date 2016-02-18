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

#ifndef HESPERIA_SCENEGRAPH_MODELS_GRID_H_
#define HESPERIA_SCENEGRAPH_MODELS_GRID_H_

#include <vector>

#include "opendavinci/core/opendavinci.h"

#include "opendlv/data/environment/Point3.h"
#include "opendlv/scenegraph/SceneNode.h"
#include "opendlv/scenegraph/SceneNodeDescriptor.h"
#include "opendlv/scenegraph/primitives/Line.h"

namespace hesperia {
    namespace scenegraph {
        namespace models {

            using namespace std;

            /**
             * This class represents grid.
             */
            class OPENDAVINCI_API Grid : public SceneNode {
                public:
                    /**
                     * Constructor.
                     *
                     * @param sceneNodeDesciptor Description for this node.
                     */
                    Grid(const SceneNodeDescriptor &sceneNodeDescriptor);

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

                    virtual ~Grid();

                private:
                    void createGrid();
            };

        }
    }
} // hesperia::scenegraph::models

#endif /*HESPERIA_SCENEGRAPH_MODELS_GRID_H_*/
