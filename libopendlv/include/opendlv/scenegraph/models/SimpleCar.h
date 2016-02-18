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

#ifndef HESPERIA_SCENEGRAPH_MODELS_SIMPLECAR_H_
#define HESPERIA_SCENEGRAPH_MODELS_SIMPLECAR_H_

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
             * This class represents a simple car:
             *
             * ---------Length------------
             * |                         |
             * |                         W
             * |                         i      \
             * |           X-------------d-------+
             * |                         t      /
             * |                         h
             * |                         |
             * ---------Length------------
             *
             * X = Position, + = ROTZ.
             */
            class OPENDAVINCI_API SimpleCar : public SceneNode {
                public:
                    /**
                     * Constructor.
                     *
                     * @param sceneNodeDesciptor Description for this node.
                     * @param length Length of the car.
                     * @param width Width of the car.
                     * @param position Position of the car.
                     * @param rotZ Rotation around Z axis of the car.
                     * @param color Color for this simple car.
                     * @param height SimpleCar's height.
                     */
                    SimpleCar(const SceneNodeDescriptor &sceneNodeDescriptor, const double &length, const double &width, const hesperia::data::environment::Point3 &position, const double &rotZ, const hesperia::data::environment::Point3 &color, const float &height);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    SimpleCar(const SimpleCar &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    SimpleCar& operator=(const SimpleCar &obj);

                    virtual ~SimpleCar();

                    /**
                     * This method updates the position of the car.
                     *
                     * @param position Position of the car.
                     * @param rotZ Rotation around Z axis of the car.
                     */
                    void setPosition(const hesperia::data::environment::Point3 &position, const double &rotZ);

                private:
                    double m_length;
                    double m_width;

                    hesperia::data::environment::Point3 m_color;
                    float m_height;

                    hesperia::scenegraph::primitives::Line *m_rearLeft;
                    hesperia::scenegraph::primitives::Line *m_rearRight;
                    hesperia::scenegraph::primitives::Line *m_sideLeft;
                    hesperia::scenegraph::primitives::Line *m_sideRight;
                    hesperia::scenegraph::primitives::Line *m_front;
                    hesperia::scenegraph::primitives::Line *m_arrowLeft;
                    hesperia::scenegraph::primitives::Line *m_arrowRight;
                    hesperia::scenegraph::primitives::Line *m_arrowRear;
            };

        }
    }
} // hesperia::scenegraph::models

#endif /*HESPERIA_SCENEGRAPH_MODELS_SIMPLECAR_H_*/
