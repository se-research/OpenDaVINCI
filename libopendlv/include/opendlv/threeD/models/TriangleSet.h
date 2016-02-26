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

#ifndef HESPERIA_CORE_THREED_MODELS_TRIANGLESET_H_
#define HESPERIA_CORE_THREED_MODELS_TRIANGLESET_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"

#include "opendlv/data/environment/Point3.h"
#include "opendlv/threeD/Material.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/models/Triangle.h"

namespace opendlv {
    namespace threeD {
        namespace models {

            using namespace std;

            /**
             * This class represents a set of triangles.
             */
            class OPENDAVINCI_API TriangleSet : public Node {
                public:
                    TriangleSet();

                    /**
                     * Constructor.
                     *
                     * @param nodeDesciptor Description for this node.
                     */
                    TriangleSet(const NodeDescriptor &nodeDescriptor);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    TriangleSet(const TriangleSet &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    TriangleSet& operator=(const TriangleSet &obj);

                    virtual ~TriangleSet();

                    virtual void render(RenderingConfiguration &renderingConfiguration);

                    /**
                     * This method adds a new triangle.
                     *
                     * @param triangle Triangle to be added.
                     */
                    void addTriangle(const Triangle &triangle);

                    /**
                     * This method sets the material for this triangle set.
                     *
                     * @param material Material for this triangle set.
                     */
                    void setMaterial(const Material &material);

                private:
                    mutable bool m_compiled;
                    mutable uint32_t m_callList;
                    Material m_material;
                    vector<opendlv::data::environment::Point3> m_vertices;
                    vector<opendlv::data::environment::Point3> m_normals;
                    vector<opendlv::data::environment::Point3> m_textureCoordinates;

                    /**
                     * This method compiles this triangle set using OpenGL
                     * compile lists.
                     */
                    void compile() const;
            };

        }
    }
} // opendlv::threeD::models

#endif /*HESPERIA_CORE_THREED_MODELS_TRIANGLESET_H_*/
