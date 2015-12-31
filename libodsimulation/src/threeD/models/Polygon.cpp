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
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/models/Polygon.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace std;
            using namespace hesperia::data::environment;

            Polygon::Polygon(const NodeDescriptor &nodeDescriptor, const vector<Point3> &listOfGroundVertices, const Point3 &color, const float &height) :
                    Node(nodeDescriptor),
                    m_listOfGroundVertices(listOfGroundVertices),
                    m_color(color),
                    m_height(height) {
                // Add the first point to the end to close the polyon.
                if (m_listOfGroundVertices.size() > 0) {
                    Point3 p = *(m_listOfGroundVertices.begin());
                    m_listOfGroundVertices.push_back(p);
                }
            }

            Polygon::Polygon(const Polygon &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_listOfGroundVertices(obj.m_listOfGroundVertices),
                    m_color(obj.m_color),
                    m_height(obj.m_height) {}

            Polygon::~Polygon() {}

            Polygon& Polygon::operator=(const Polygon &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_listOfGroundVertices = obj.m_listOfGroundVertices;
                m_color = obj.m_color;
                m_height = obj.m_height;
                return (*this);
            }

            void Polygon::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glColor3d(m_color.getX(), m_color.getY(), m_color.getZ());

                        glBegin(GL_QUADS);
                        for (uint32_t i = 0; i < m_listOfGroundVertices.size() - 1; i++) {
                            const Point3 &p1 = m_listOfGroundVertices[i];
                            const Point3 &p2 = m_listOfGroundVertices[i+1];

                            Point3 P12 = p2 - p1;
                            P12.setZ(0);
                            const Point3 P1H = Point3(p1.getX(), p1.getY(), m_height);
                            const Point3 P1HxP12 = P1H.cross(P12);

                            glVertex3d(p1.getX(), p1.getY(), 0);
                            glVertex3d(p1.getX(), p1.getY(), m_height);
                            glVertex3d(p2.getX(), p2.getY(), m_height);
                            glVertex3d(p2.getX(), p2.getY(), 0);
                            glNormal3d(P1HxP12.getX(), P1HxP12.getY(), P1HxP12.getZ());
                        }
                        glEnd();

                        // Bottom of the polygon.
                        glBegin(GL_POLYGON);
                        for (uint32_t i = 0; i < m_listOfGroundVertices.size(); i++) {
                            const Point3 &p1 = m_listOfGroundVertices[i];
                            glVertex3d(p1.getX(), p1.getY(), 0);
                        }
                        glEnd();

                        // Top of the polygon.
                        glBegin(GL_POLYGON);
                        for (uint32_t i = 0; i < m_listOfGroundVertices.size(); i++) {
                            const Point3 &p1 = m_listOfGroundVertices[i];
                            glVertex3d(p1.getX(), p1.getY(), m_height);
                        }
                        glEnd();
                    }
                    glPopMatrix();
                }
            }

        }
    }
} // hesperia::threeD::models
