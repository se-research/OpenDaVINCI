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

#include "opendavinci/core/opendavinci.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/models/CheckerBoard.h"

namespace hesperia {
    namespace threeD {
        namespace models {

            using namespace std;
            using namespace hesperia::data::environment;

            CheckerBoard::CheckerBoard(const NodeDescriptor &nodeDescriptor) :
                    Node(nodeDescriptor),
                    m_positionA(Point3(-0.5, 0, 0)),
                    m_positionB(Point3(0.5, 0, 0)),
                    m_height(0.7) {}

            CheckerBoard::CheckerBoard(const NodeDescriptor &nodeDescriptor, const Point3 &positionA, const Point3 &positionB, const float &height) :
                    Node(nodeDescriptor),
                    m_positionA(positionA),
                    m_positionB(positionB),
                    m_height(height) {}

            CheckerBoard::CheckerBoard(const CheckerBoard &obj) :
                    Node(obj.getNodeDescriptor()),
                    m_positionA(obj.m_positionA),
                    m_positionB(obj.m_positionB),
                    m_height(obj.m_height) {}

            CheckerBoard::~CheckerBoard() {}

            CheckerBoard& CheckerBoard::operator=(const CheckerBoard &obj) {
                setNodeDescriptor(obj.getNodeDescriptor());
                m_positionA = obj.m_positionA;
                m_positionB = obj.m_positionB;
                m_height = obj.m_height;
                return (*this);
            }

            void CheckerBoard::render(RenderingConfiguration &renderingConfiguration) {
                if ((getNodeDescriptor().getName().size() == 0) || (renderingConfiguration.getNodeRenderingConfiguration(getNodeDescriptor()).hasParameter(NodeRenderingConfiguration::ENABLED))) {
                    glPushMatrix();
                    {
                        bool color = false;
                        uint32_t squares = 0;
                        double height = 0;
                        while (height < m_height) {
                            Point3 p = m_positionA;
                            double d = p.getDistanceTo(m_positionB);
                            squares = 0;
                            while (d > 0.1) {
                                if (color) {
                                    glColor3d(1, 1, 1);
                                } else {
                                    glColor3d(0.1, 0.1, 0.1);
                                }

                                glBegin(GL_QUADS);
                                {
                                    glVertex3d(p.getX(), p.getY(), height);
                                    glVertex3d(p.getX(), p.getY(), height + 0.1);
                                    p += Point3(0.1, 0, 0);
                                    glVertex3d(p.getX(), p.getY(), height + 0.1);
                                    glVertex3d(p.getX(), p.getY(), height);
                                }
                                glEnd();
                                color = !color;
                                d = p.getDistanceTo(m_positionB);
                                squares++;
                            }
                            if ((squares % 2) == 0) {
                                color = !color;
                            }
                            height += 0.1;
                        }
                    }

                    glPopMatrix();
                }
            }
        }
    }
} // hesperia::threeD::models
