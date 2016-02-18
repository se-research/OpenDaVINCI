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

#ifndef HESPERIA_SCENEGRAPH_PRIMITIVES_LINE_H_
#define HESPERIA_SCENEGRAPH_PRIMITIVES_LINE_H_

#include "opendlv/data/environment/Point3.h"
#include "opendlv/scenegraph/SceneNode.h"
#include "opendlv/scenegraph/SceneNodeDescriptor.h"

namespace opendlv {
    namespace scenegraph {
        namespace primitives {

            using namespace std;

            /**
             * This class represents a regular line.
             */
            class Line : public SceneNode {
                public:
                    /**
                     * Constructor.
                     *
                     * @param sceneNodeDesciptor Description for this scene node.
                     * @param positionA Point A for the line.
                     * @param positionB Point B for the line.
                     * @param color Line's color.
                     * @param width Line's width.
                     */
                    Line(const SceneNodeDescriptor &sceneNodeDescriptor, const opendlv::data::environment::Point3 &positionA, const opendlv::data::environment::Point3 &positionB, const opendlv::data::environment::Point3 &color, const float &width);

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

                    /**
                     * @return Line's point A.
                     */
                    const opendlv::data::environment::Point3& getA() const;

                    /**
                     * @return Line's point B.
                     */
                    const opendlv::data::environment::Point3& getB() const;

                    /**
                     * @param A Line's point A.
                     */
                    void setA(const opendlv::data::environment::Point3 &A);

                    /**
                     * @param B Line's point B.
                     */
                    void setB(const opendlv::data::environment::Point3 &B);

                    /**
                     * @return Line's color.
                     */
                    const opendlv::data::environment::Point3& getColor() const;

                    /**
                     * @return Line's width.
                     */
                    float getWidth() const;

                private:
                    opendlv::data::environment::Point3 m_positionA;
                    opendlv::data::environment::Point3 m_positionB;
                    opendlv::data::environment::Point3 m_color;
                    float m_width;
            };

        }
    }
} // opendlv::threeD::primitives

#endif /*HESPERIA_SCENEGRAPH_PRIMITIVES_LINE_H_*/
