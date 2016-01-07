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

#ifdef WIN32
#include <windows.h>
#endif

#include <GL/gl.h>
#include <string>

#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/models/XYZAxes.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            XYZAxes::XYZAxes(const NodeDescriptor &nodeDescriptor) :
                    Node(nodeDescriptor),
                    m_lineWidth(1),
                    m_lineLength(2) {}

            XYZAxes::XYZAxes(const NodeDescriptor &nodeDescriptor, const float &lineWidth, const float &lineLength) :
                    Node(nodeDescriptor),
                    m_lineWidth(lineWidth),
                    m_lineLength(lineLength) {}

            XYZAxes::XYZAxes(const XYZAxes &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_lineWidth(obj.m_lineWidth),
                    m_lineLength(obj.m_lineLength) {}

            XYZAxes::~XYZAxes() {}

            XYZAxes& XYZAxes::operator=(const XYZAxes &obj) {
                setNodeDescriptor(obj.getNodeDescriptor()),
                m_lineWidth = obj.m_lineWidth;
                m_lineLength = obj.m_lineLength;
                return (*this);
            }

            void XYZAxes::render(RenderingConfiguration &renderingConfiguration) {
                // Render if unnamed or not disabled.
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glLineWidth(m_lineWidth);
                        glColor3f(1, 1, 1);

                        glBegin(GL_LINES);
                        // X-axis.
                        glVertex3f(0, 0, 0);
                        glVertex3f(m_lineLength, 0, 0);

                        // Arrow.
                        glVertex3f(m_lineLength, 0, 0);
                        glVertex3f((m_lineLength - 0.1f), 0.1f, 0);

                        glVertex3f(m_lineLength, 0, 0);
                        glVertex3f((m_lineLength - 0.1f), -0.1f, 0);

                        // X-label.
                        glVertex3f(-0.3f + (m_lineLength - 0.1f), -0.3f + 0.1f, 0);
                        glVertex3f(-0.3f + (m_lineLength + 0.1f), -0.3f + -0.1f, 0);

                        glVertex3f(-0.3f + (m_lineLength + 0.1f), -0.3f + 0.1f, 0);
                        glVertex3f(-0.3f + (m_lineLength - 0.1f), -0.3f + -0.1f, 0);

                        // Y-axis
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, m_lineLength, 0);

                        // Arrow.
                        glVertex3f(0, m_lineLength, 0);
                        glVertex3f(0.1f, (m_lineLength - 0.1f), 0);

                        glVertex3f(0, m_lineLength, 0);
                        glVertex3f(-0.1f, (m_lineLength - 0.1f), 0);

                        // Y-label.
                        glVertex3f(-0.3f + -0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.2f), 0);

                        // Z-axis
                        glVertex3f(0, 0, 0);
                        glVertex3f(0, 0, m_lineLength);

                        // Arrow.
                        glVertex3f(0, 0, m_lineLength);
                        glVertex3f(0.1f, 0, (m_lineLength - 0.1f));

                        glVertex3f(0, 0, m_lineLength);
                        glVertex3f(-0.1f, 0, (m_lineLength - 0.1f));

                        // Z-label.
                        glVertex3f(-0.3f + -0.1f, 0, m_lineLength);
                        glVertex3f(-0.3f + 0.1f, 0, m_lineLength);

                        glVertex3f(-0.3f + 0.1f, 0, m_lineLength);
                        glVertex3f(-0.3f + -0.1f, 0, (m_lineLength - 0.1f));

                        glVertex3f(-0.3f + -0.1f, 0, (m_lineLength - 0.1f));
                        glVertex3f(-0.3f + 0.1f, 0, (m_lineLength - 0.1f));
                        glEnd();

                        glLineWidth(1);
                    }

                    glPopMatrix();
                }
            }

        }
    }
} // core::threeD::models
