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

#include "GeneratedHeaders_AutomotiveData.h"
#include "hesperia/scenegraph/models/XYAxes.h"

namespace hesperia {
    namespace scenegraph {
        namespace models {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;
            using namespace hesperia::scenegraph::primitives;

            XYAxes::XYAxes(const SceneNodeDescriptor &sceneNodeDescriptor, const hesperia::data::environment::Point3 &color, const float &thickness) :
                SceneNode(sceneNodeDescriptor),
                m_color(color),
                m_thickness(thickness) {
                createAxes();
            }

            XYAxes::XYAxes(const XYAxes &obj) :
                SceneNode(obj.getSceneNodeDescriptor()),
                m_color(obj.m_color),
                m_thickness(obj.m_thickness) {
                createAxes();
            }

            XYAxes& XYAxes::operator=(const XYAxes &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor());
                m_color = obj.m_color;
                m_thickness = obj.m_thickness;

                deleteAllChildren();

                createAxes();

                return *this;
            }

            XYAxes::~XYAxes() {}

            void XYAxes::createAxes() {
                const double AXES_LENGTH = 10;

                Point3 xAxisMax(AXES_LENGTH, 0, 0);
                Point3 yAxisMax(0, AXES_LENGTH, 0);

                // X-Arrow.
                addChild(new Line(getSceneNodeDescriptor(), Point3(), xAxisMax, m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), xAxisMax, xAxisMax+Point3(-.5, .5, 0), m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), xAxisMax, xAxisMax+Point3(-.5, -.5, 0), m_color, m_thickness));

                // X label.
                addChild(new Line(getSceneNodeDescriptor(), xAxisMax+Point3(-.6 + -.5, -.6 + .5, 0), xAxisMax+Point3(-.6 + .5, -.6 + -.5, 0), m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), xAxisMax+Point3(-.6 + .5, -.6 + .5, 0), xAxisMax+Point3(-.6 - .5, -.6 + -.5, 0), m_color, m_thickness));

                // Y-Arrow.
                addChild(new Line(getSceneNodeDescriptor(), Point3(), yAxisMax, m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), yAxisMax, yAxisMax+Point3(.5, -.5, 0), m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), yAxisMax, yAxisMax+Point3(-.5, -.5, 0), m_color, m_thickness));

                // Y label.
                addChild(new Line(getSceneNodeDescriptor(), yAxisMax+Point3(-.6 + -.5, -.6, 0), yAxisMax+Point3(-.6 + 0, -.6 + -.5, 0), m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), yAxisMax+Point3(-.6 + .5, -.6, 0), yAxisMax+Point3(-.6 + 0, -.6 + -.5, 0), m_color, m_thickness));
                addChild(new Line(getSceneNodeDescriptor(), yAxisMax+Point3(-.6 + 0, -.6 + -.5, 0), yAxisMax+Point3(-.6 - 0, -.6 + -.9, 0), m_color, m_thickness));

/*
                        // Y-label.
                        glVertex3f(-0.3f + -0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0.1f, m_lineLength, 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);

                        glVertex3f(-0.3f + 0, (m_lineLength - 0.1f), 0);
                        glVertex3f(-0.3f + 0, (m_lineLength - 0.2f), 0);
*/
            }

        }
    }
}  // hesperia::scenegraph::models

