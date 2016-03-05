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

// The following include is necessary on Win32 platforms to set up necessary macro definitions.
#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
    #include <OpenGL/gl.h>
#else
    #include <GL/gl.h>
#endif

#include <string>

#include "opendlv/data/environment/Point3.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/NodeRenderingConfiguration.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "opendlv/threeD/models/Point.h"

namespace opendlv {
    namespace threeD {
        namespace models {

            using namespace opendlv::data::environment;

            Point::Point(const NodeDescriptor &nodeDescriptor, const Point3 &position, const Point3 &color, const float &width) :
                    Node(nodeDescriptor),
                    m_position(position),
                    m_color(color),
                    m_width(width) {}

            Point::Point(const Point &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_position(obj.m_position),
                    m_color(obj.m_color),
                    m_width(obj.m_width) {}

            Point::~Point() {}

            Point& Point::operator=(const Point &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_position = obj.m_position;
                m_color = obj.m_color;
                m_width = obj.m_width;

                return (*this);
            }

            void Point::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glPointSize(m_width);
                        glColor3d(m_color.getX(), m_color.getY(), m_color.getZ());

                        glBegin(GL_POINTS);
                        glVertex3d(m_position.getX(), m_position.getY(), m_position.getZ());
                        glEnd();

                        glPointSize(1);
                    }
                    glPopMatrix();
                }
            }

        }
    }
} // opendlv::threeD::models
