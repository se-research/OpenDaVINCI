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

#include "opendlv/scenegraph/primitives/Polygon.h"

namespace opendlv {
    namespace scenegraph {
        namespace primitives {

            using namespace std;
            using namespace opendlv::data::environment;

            Polygon::Polygon(const SceneNodeDescriptor &sceneNodeDescriptor, const vector<Point3> &listOfGroundVertices, const Point3 &color, const float &height) :
                SceneNode(sceneNodeDescriptor),
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
                SceneNode(obj.getSceneNodeDescriptor()),
                m_listOfGroundVertices(obj.m_listOfGroundVertices),
                m_color(obj.m_color),
                m_height(obj.m_height) {}

            Polygon::~Polygon() {}

            Polygon& Polygon::operator=(const Polygon &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor());
                m_listOfGroundVertices = obj.m_listOfGroundVertices;
                m_color = obj.m_color;
                m_height = obj.m_height;
                return (*this);
            }

            const vector<Point3>& Polygon::getListOfGroundVertices() const {
                return m_listOfGroundVertices;
            }

            const Point3& Polygon::getColor() const {
                return m_color;
            }

            float Polygon::getHeight() const {
                return m_height;
            }

        }
    }
} // opendlv::scenegraph::primitives
