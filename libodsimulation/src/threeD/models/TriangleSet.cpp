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

// The following include is necessary on Win32 platforms to set up necessary macro definitions.
#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <string>
#include <vector>

#include "core/platform.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Material.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/models/Triangle.h"
#include "hesperia/threeD/models/TriangleSet.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace hesperia::data::environment;

            TriangleSet::TriangleSet() :
                    Node(),
                    m_compiled(false),
                    m_callList(0),
                    m_material(),
                    m_vertices(),
                    m_normals(),
                    m_textureCoordinates() {}

            TriangleSet::TriangleSet(const NodeDescriptor &nodeDescriptor) :
                    Node(nodeDescriptor),
                    m_compiled(false),
                    m_callList(0),
                    m_material(),
                    m_vertices(),
                    m_normals(),
                    m_textureCoordinates() {}

            TriangleSet::TriangleSet(const TriangleSet &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_compiled(obj.m_compiled),
                    m_callList(obj.m_callList),
                    m_material(obj.m_material),
                    m_vertices(obj.m_vertices),
                    m_normals(obj.m_normals),
                    m_textureCoordinates(obj.m_textureCoordinates) {}

            TriangleSet::~TriangleSet() {}

            TriangleSet& TriangleSet::operator=(const TriangleSet &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_compiled = obj.m_compiled;
                m_callList = obj.m_callList;
                m_material = obj.m_material;
                m_vertices = obj.m_vertices;
                m_normals = obj.m_normals;
                m_textureCoordinates = obj.m_textureCoordinates;

                return (*this);
            }

            void TriangleSet::addTriangle(const Triangle &triangle) {
                vector<Point3> vertices = triangle.getVertices();
                m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());

                m_normals.push_back(triangle.getNormal());

                vector<Point3> textureCoordinates = triangle.getTextureCoordinates();
                m_textureCoordinates.insert(m_textureCoordinates.end(), textureCoordinates.begin(), textureCoordinates.end());
            }

            void TriangleSet::setMaterial(const Material &material) {
                m_material = material;
            }

            void TriangleSet::compile() const {
                m_callList = glGenLists(1);
                glNewList(m_callList, GL_COMPILE);

                uint32_t normalIndexCounter = 0;
                glBegin(GL_TRIANGLES);
                for (uint32_t i = 0; i < m_vertices.size(); i++) {
                    if (i < m_textureCoordinates.size()) {
                        glTexCoord2d(m_textureCoordinates[i].getX(), m_textureCoordinates[i].getY());
                    }
                    if ((i % 3) == 0) {
                        if (normalIndexCounter < m_normals.size()) {
                            glNormal3d(m_normals[normalIndexCounter].getX(), m_normals[normalIndexCounter].getY(), m_normals[normalIndexCounter].getZ());
                        }
                        normalIndexCounter++;
                    }
                    glVertex3d(m_vertices[i].getX(), m_vertices[i].getY(), m_vertices[i].getZ());
                }
                glEnd();


                glEndList();
                m_compiled = true;
            }


            void TriangleSet::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        // Try to load an apropriate texture.
                        int32_t textureHandle = m_material.getTextureHandle();

                        if (textureHandle > 0) {
                            if (renderingConfiguration.hasDrawTextures()) {
                                glEnable(GL_TEXTURE_2D);
                                glBindTexture(GL_TEXTURE_2D, static_cast<uint32_t>(textureHandle));
                                glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                            }
                        }
                        else {
                            glEnable(GL_COLOR_MATERIAL);
                            glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
                            float ambient[] = { static_cast<float>(m_material.getAmbient().getX()),
                                                static_cast<float>(m_material.getAmbient().getY()),
                                                static_cast<float>(m_material.getAmbient().getZ()) };
//                            float ambient[] = { 0,
//                                                0,
//                                                0
//                                              };

                            glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);

                            float diffuse[] = { static_cast<float>(m_material.getDiffuse().getX()),
                                                static_cast<float>(m_material.getDiffuse().getY()),
                                                static_cast<float>(m_material.getDiffuse().getZ())
                                              };

                            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

                            float specular[] = { static_cast<float>(m_material.getSpecular().getX()),
                                                static_cast<float>(m_material.getSpecular().getY()),
                                                static_cast<float>(m_material.getSpecular().getZ()) };

                            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);

                            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, static_cast<float>(m_material.getShininess()));

                            glColor3d(m_material.getDiffuse().getX(), m_material.getDiffuse().getY(), m_material.getDiffuse().getZ());
                        }

                        // Use compiled lists.
                        if (!m_compiled) {
                            compile();
                        }

                        glCallList(m_callList);

                        if (textureHandle) {
                            if (renderingConfiguration.hasDrawTextures()) {
                                glDisable(GL_TEXTURE_2D);
                            }
                        }
                    }
                    glPopMatrix();
                }
            }
        }
    }
} // hesperia::threeD::models
