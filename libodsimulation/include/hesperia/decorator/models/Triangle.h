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

#ifndef HESPERIA_CORE_DECORATOR_MODELS_TRIANGLE_H_
#define HESPERIA_CORE_DECORATOR_MODELS_TRIANGLE_H_

#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace decorator {
        namespace models {

            using namespace std;

            /**
             * This class represents a triangle.
             */
            class OPENDAVINCI_API Triangle {
                public:
                    Triangle();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Triangle(const Triangle &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Triangle& operator=(const Triangle &obj);

                    virtual ~Triangle();

                    /**
                     * This method sets the triangle's vertices.
                     *
                     * @param a Vertex a.
                     * @param b Vertex b.
                     * @param c Vertex c.
                     */
                    void setVertices(const hesperia::data::environment::Point3 &a, const hesperia::data::environment::Point3 &b, const hesperia::data::environment::Point3 &c);

                    /**
                     * This method returns the triangle's vertices.
                     *
                     * @return Triangle's vertices.
                     */
                    vector<hesperia::data::environment::Point3> getVertices() const;

                    /**
                     * This method sets the triangle's normal.
                     *
                     * @param n Normal.
                     */
                    void setNormal(const hesperia::data::environment::Point3 &n);

                    /**
                     * This method returns the triangle's normal.
                     *
                     * @return Triangle's normal.
                     */
                    hesperia::data::environment::Point3 getNormal() const;

                    /**
                     * This method sets the triangle's texture coordinates.
                     *
                     * @param ta Texture coordinate for vertex a.
                     * @param tc Texture coordinate for vertex b.
                     * @param tb Texture coordinate for vertex c.
                     */
                    void setTextureCoordinates(const hesperia::data::environment::Point3 &ta, const hesperia::data::environment::Point3 &tb, const hesperia::data::environment::Point3 &tc);

                    /**
                     * This method returns the triangle's texture coordinates.
                     *
                     * @return Triangle's texture coordinates.
                     */
                    vector<hesperia::data::environment::Point3> getTextureCoordinates() const;

                private:
                    vector<hesperia::data::environment::Point3> m_vertices;
                    hesperia::data::environment::Point3 m_normal;
                    vector<hesperia::data::environment::Point3> m_textureCoordinates;
            };

        }
    }
} // hesperia::decorator::models

#endif /*HESPERIA_CORE_DECORATOR_MODELS_TRIANGLE_H_*/
