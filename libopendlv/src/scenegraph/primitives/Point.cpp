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

#include "opendlv/scenegraph/primitives/Point.h"

namespace hesperia {
    namespace scenegraph {
        namespace primitives {

            using namespace hesperia::data::environment;

            Point::Point(const SceneNodeDescriptor &sceneNodeDescriptor, const Point3 &position, const Point3 &color, const float &width) :
                SceneNode(sceneNodeDescriptor),
                m_position(position),
                m_color(color),
                m_width(width) {}

            Point::Point(const Point &obj) :
                SceneNode(obj.getSceneNodeDescriptor()),
                m_position(obj.m_position),
                m_color(obj.m_color),
                m_width(obj.m_width) {}

            Point::~Point() {}

            Point& Point::operator=(const Point &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor());
                m_position = obj.m_position;
                m_color = obj.m_color;
                m_width = obj.m_width;

                return (*this);
            }

            const Point3& Point::getPosition() const {
                return m_position;
            }

            const Point3& Point::getColor() const {
                return m_color;
            }

            float Point::getWidth() const {
                return m_width;
            }

        }
    }
} // hesperia::scenegraph::primitives
