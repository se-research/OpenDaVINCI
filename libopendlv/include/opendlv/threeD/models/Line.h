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

#ifndef HESPERIA_CORE_THREED_MODELS_LINE_H_
#define HESPERIA_CORE_THREED_MODELS_LINE_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendlv/data/environment/Point3.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"

namespace opendlv {
    namespace threeD {
        namespace models {

            using namespace std;

            /**
             * This class represents a regular line.
             */
            class Line : public Node {
                public:
                    /**
                     * Constructor.
                     *
                    * @param nodeDesciptor Description for this node.
                     * @param positionA Point A for the line.
                     * @param positionB Point B for the line.
                     * @param color Line's color.
                     * @param width Line's width.
                     */
                    Line(const NodeDescriptor &nodeDescriptor, const opendlv::data::environment::Point3 &positionA, const opendlv::data::environment::Point3 &positionB, const opendlv::data::environment::Point3 &color, const float &width);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Line(const Line &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Line& operator=(const Line &obj);

                    virtual ~Line();

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                private:
                    opendlv::data::environment::Point3 m_positionA;
                    opendlv::data::environment::Point3 m_positionB;
                    opendlv::data::environment::Point3 m_color;
                    float m_width;
            };

        }
    }
} // opendlv::threeD::models

#endif /*HESPERIA_CORE_THREED_MODELS_LINE_H_*/
