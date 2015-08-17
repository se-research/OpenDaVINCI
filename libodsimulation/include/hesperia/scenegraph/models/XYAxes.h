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

#ifndef HESPERIA_SCENEGRAPH_MODELS_XYAXES_H_
#define HESPERIA_SCENEGRAPH_MODELS_XYAXES_H_

#include <vector>

#include "core/platform.h"

#include "hesperia/data/environment/Point3.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"
#include "hesperia/scenegraph/primitives/Line.h"

namespace hesperia {
    namespace scenegraph {
        namespace models {

            using namespace std;

            /**
             * This class represents an X/Y-axes.
             */
            class OPENDAVINCI_API XYAxes : public SceneNode {
                public:
                    /**
                     * Constructor.
                     *
                     * @param sceneNodeDesciptor Description for this node.
                     * @param color Color for these X/Y-axes.
                     * @param thickness of X/Y-axes.
                     */
                    XYAxes(const SceneNodeDescriptor &sceneNodeDescriptor, const hesperia::data::environment::Point3 &color, const float &thickness);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    XYAxes(const XYAxes &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    XYAxes& operator=(const XYAxes &obj);

                    virtual ~XYAxes();

                private:
                    hesperia::data::environment::Point3 m_color;
                    float m_thickness;

                    void createAxes();
            };

        }
    }
} // hesperia::scenegraph::models

#endif /*HESPERIA_SCENEGRAPH_MODELS_XYAXES_H_*/
