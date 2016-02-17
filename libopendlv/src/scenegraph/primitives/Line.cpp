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

#include "hesperia/scenegraph/primitives/Line.h"

namespace hesperia {
    namespace scenegraph {
        namespace primitives {

            using namespace hesperia::data::environment;

            Line::Line(const SceneNodeDescriptor &sceneNodeDescriptor, const Point3 &positionA, const Point3 &positionB, const Point3 &color, const float &width) :
                SceneNode(sceneNodeDescriptor),
                m_positionA(positionA),
                m_positionB(positionB),
                m_color(color),
                m_width(width) {}

            Line::Line(const Line &obj) :
                SceneNode(obj.getSceneNodeDescriptor()),
                m_positionA(obj.m_positionA),
                m_positionB(obj.m_positionB),
                m_color(obj.m_color),
                m_width(obj.m_width) {}

            Line::~Line() {}

            Line& Line::operator=(const Line &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor()),
                m_positionA = obj.m_positionA;
                m_positionB = obj.m_positionB;
                m_color = obj.m_color;
                m_width = obj.m_width;

                return (*this);
            }

            void Line::setA(const Point3 &A) {
                m_positionA = A;
            }

            void Line::setB(const Point3 &B) {
                m_positionB = B;
            }

            const Point3& Line::getA() const {
                return m_positionA;
            }

            const Point3& Line::getB() const {
                return m_positionB;
            }

            const Point3& Line::getColor() const {
                return m_color;
            }

            float Line::getWidth() const {
                return m_width;
            }

        }
    }
} // hesperia::scenegraph::primitives
