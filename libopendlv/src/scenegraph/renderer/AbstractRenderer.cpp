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

#include "opendavinci/core/opendavinci.h"

#include "hesperia/scenegraph/renderer/AbstractRenderer.h"
#include "hesperia/scenegraph/primitives/Line.h"
#include "hesperia/scenegraph/primitives/Point.h"
#include "hesperia/scenegraph/primitives/Polygon.h"

namespace hesperia { namespace scenegraph { class SceneNode; } }

namespace hesperia {
    namespace scenegraph {
        namespace renderer {

            using namespace hesperia::scenegraph::primitives;

                AbstractRenderer::AbstractRenderer() {}

                AbstractRenderer::~AbstractRenderer() {}

                void AbstractRenderer::visit(SceneNode *sceneNode) {
                    if (sceneNode != NULL) {
                        bool delegated = false;

                        Point *p = dynamic_cast<Point*>(sceneNode);
                        if (!delegated && p != NULL) {
                            delegated = true;

                            render(p);
                        }

                        Line *l = dynamic_cast<Line*>(sceneNode);
                        if (!delegated && l != NULL) {
                            delegated = true;

                            render(l);
                        }

                        Polygon *poly = dynamic_cast<Polygon*>(sceneNode);
                        if (!delegated && poly != NULL) {
                            delegated = true;

                            render(poly);
                        }
                    }
                }

        }
    }
} // hesperia::scenegraph::renderer

