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

#include <GL/gl.h>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/NodeRenderingConfiguration.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "opendlv/threeD/models/Grid.h"

namespace opendlv {
    namespace threeD {
        namespace models {

            Grid::Grid(const NodeDescriptor &nodeDescriptor, const uint32_t &size, const float &lineWidth) :
                    Node(nodeDescriptor),
                    m_size(size),
                    m_lineWidth(lineWidth) {}

            Grid::Grid(const Grid &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_size(obj.m_size),
                    m_lineWidth(obj.m_lineWidth) {}

            Grid::~Grid() {}

            Grid& Grid::operator=(const Grid &obj) {
                setNodeDescriptor(obj.getNodeDescriptor()),
                m_size = obj.m_size;
                m_lineWidth = obj.m_lineWidth;
                return (*this);
            }

            void Grid::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        glLineWidth(m_lineWidth);
                        glColor3f(1, 1, 1);

                        glBegin(GL_LINES);
                        int32_t size = m_size;
                        for (int32_t y = -size; y <= size; y++) {
                            for (int32_t x = -size; x <= size; x++) {
                                // X-axis.
                                glVertex3f(0, static_cast<float>(y), 0);
                                glVertex3f(static_cast<float>(x), static_cast<float>(y), 0);

                                // Y-axis.
                                glVertex3f(static_cast<float>(x), 0, 0);
                                glVertex3f(static_cast<float>(x), static_cast<float>(y), 0);
                            }
                        }
                        glEnd();

                        glLineWidth(1);
                    }
                    glPopMatrix();
                }
            }

        }
    }
} // threeDengine::models
