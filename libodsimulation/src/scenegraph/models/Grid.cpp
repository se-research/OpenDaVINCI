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

#include "core/platform.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"
#include "hesperia/scenegraph/models/Grid.h"

namespace hesperia { namespace scenegraph { namespace primitives { class Line; } } }

namespace hesperia {
    namespace scenegraph {
        namespace models {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;
            using namespace hesperia::scenegraph::primitives;

            Grid::Grid(const SceneNodeDescriptor &sceneNodeDescriptor) :
                SceneNode(sceneNodeDescriptor) {
                createGrid();
            }

            Grid::Grid(const Grid &obj) :
                SceneNode(obj.getSceneNodeDescriptor()) {
                createGrid();
            }

            Grid& Grid::operator=(const Grid &obj) {
                setSceneNodeDescriptor(obj.getSceneNodeDescriptor());

                deleteAllChildren();

                createGrid();

                return *this;
            }

            Grid::~Grid() {}

            void Grid::createGrid() {
                const double MIN_AXES = -150;
                const double MAX_AXES = 150;

                for(int32_t y = MIN_AXES; y <= MAX_AXES; y++) {
                    Point3 yAxisGridLineA(MIN_AXES, y, 0);
                    Point3 yAxisGridLineB(MAX_AXES, y, 0);

                    Line* yAxisGridLine = new Line(getSceneNodeDescriptor(), yAxisGridLineA, yAxisGridLineB, Point3(.7, .7, .7), 1);

                    addChild(yAxisGridLine);
                }
                for(int32_t x = MIN_AXES; x <= MAX_AXES; x++) {
                    Point3 xAxisGridLineA(x, MIN_AXES, 0);
                    Point3 xAxisGridLineB(x, MAX_AXES, 0);

                    Line* xAxisGridLine = new Line(getSceneNodeDescriptor(), xAxisGridLineA, xAxisGridLineB, Point3(.7, .7, .7), 1);

                    addChild(xAxisGridLine);
                }
            }

        }
    }
}  // hesperia::scenegraph::models

