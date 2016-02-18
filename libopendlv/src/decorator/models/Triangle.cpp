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

#include "opendlv/decorator/models/Triangle.h"

namespace hesperia {
    namespace decorator {
        namespace models {

            using namespace hesperia::data::environment;

            Triangle::Triangle() :
                    m_vertices(),
                    m_normal(),
                    m_textureCoordinates() {}

            Triangle::Triangle(const Triangle &obj) :
                    m_vertices(obj.m_vertices),
                    m_normal(obj.m_normal),
                    m_textureCoordinates(obj.m_textureCoordinates) {}

            Triangle::~Triangle() {}

            Triangle& Triangle::operator=(const Triangle &obj) {
                m_vertices = obj.m_vertices;
                m_normal = obj.m_normal;
                m_textureCoordinates = obj.m_textureCoordinates;

                return (*this);
            }

            void Triangle::setVertices(const Point3 &a, const Point3 &b, const Point3 &c) {
                m_vertices.clear();
                m_vertices.push_back(a);
                m_vertices.push_back(b);
                m_vertices.push_back(c);
            }

            vector<Point3> Triangle::getVertices() const {
                return m_vertices;
            }

            void Triangle::setNormal(const Point3 &n) {
                m_normal = n;
            }

            Point3 Triangle::getNormal() const {
                return m_normal;
            }

            void Triangle::setTextureCoordinates(const Point3 &ta, const Point3 &tb, const Point3 &tc) {
                m_textureCoordinates.clear();
                m_textureCoordinates.push_back(ta);
                m_textureCoordinates.push_back(tb);
                m_textureCoordinates.push_back(tc);
            }

            vector<Point3> Triangle::getTextureCoordinates() const {
                return m_textureCoordinates;
            }

//            void Triangle::render(const RenderingConfiguration &renderingConfiguration) const {
//                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
//                    glPushMatrix();
//                    {
//                        glBegin(GL_TRIANGLES);
//                        glNormal3d(m_normal.getX(), m_normal.getY(), m_normal.getZ());
//                        for (uint32_t i = 0; i < 3; i++) {
//                            if (m_textureCoordinates.size() == 3) {
//                                glTexCoord2d(m_textureCoordinates[i].getX(), m_textureCoordinates[i].getY());
//                            }
//                            glVertex3d(m_vertices[i].getX(), m_vertices[i].getY(), m_vertices[i].getZ());
//                        }
//                        glEnd();
//                    }
//                    glPopMatrix();
//                }
//            }

        }
    }
} // hesperia::threeD::models
