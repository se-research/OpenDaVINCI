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

#ifndef HESPERIA_CORE_THREED_MODELS_XYZAXES_H_
#define HESPERIA_CORE_THREED_MODELS_XYZAXES_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            /**
             * This class represents the cartesian axes system.
             */
            class OPENDAVINCI_API XYZAxes : public Node {
                public:
                    /**
                     * Constructor.
                     *
                     * @param nodeDesciptor Description for this node.
                     */
                    XYZAxes(const NodeDescriptor &nodeDescriptor);

                    /**
                     * Constructor.
                     *
                     * @param lineWidth Axis' line width.
                     * @param lineLength Axis' line length.
                     */
                    XYZAxes(const NodeDescriptor &nodeDescriptor, const float &lineWidth, const float &lineLength);

                    virtual ~XYZAxes();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    XYZAxes(const XYZAxes &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    XYZAxes& operator=(const XYZAxes &obj);

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                private:
                    float m_lineWidth;
                    float m_lineLength;
            };

        }
    }
} // hesperia::threeD::models

#endif /*HESPERIA_CORE_THREED_MODELS_XYZAXES_H_*/
