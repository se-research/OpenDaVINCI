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

#ifndef HESPERIA_SCENEGRAPH_RENDERER_ABSTRACTRENDERER_H_
#define HESPERIA_SCENEGRAPH_RENDERER_ABSTRACTRENDERER_H_

#include "opendavinci/core/opendavinci.h"
#include "opendlv/scenegraph/SceneNodeVisitor.h"

namespace hesperia { namespace scenegraph { class SceneNode; } }
namespace hesperia { namespace scenegraph { namespace primitives { class Line; } } }
namespace hesperia { namespace scenegraph { namespace primitives { class Point; } } }
namespace hesperia { namespace scenegraph { namespace primitives { class Polygon; } } }

namespace hesperia {
    namespace scenegraph {
        namespace renderer {

            /**
             * Interface for all SceneNodeVisitors.
             */
            class OPENDAVINCI_API AbstractRenderer : public SceneNodeVisitor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    AbstractRenderer(const AbstractRenderer &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    AbstractRenderer& operator=(const AbstractRenderer &);

                protected:
                    AbstractRenderer();

                public:
                    virtual ~AbstractRenderer();

                    virtual void visit(SceneNode *sceneNode);

                protected:
                    /**
                     * This method needs to be implemented in sub classes to
                     * implement the rendering of a point.
                     *
                     * @param p Point to be rendered.
                     */
                    virtual void render(hesperia::scenegraph::primitives::Point *p) = 0;

                    /**
                     * This method needs to be implemented in sub classes to
                     * implement the rendering of a line.
                     *
                     * @param l Line to be rendered.
                     */
                    virtual void render(hesperia::scenegraph::primitives::Line *l) = 0;

                    /**
                     * This method needs to be implemented in sub classes to
                     * implement the rendering of a polygon.
                     *
                     * @param p Polygon to be rendered.
                     */
                    virtual void render(hesperia::scenegraph::primitives::Polygon *p) = 0;
            };

        }
    }
} // hesperia::scenegraph::renderer

#endif /*HESPERIA_SCENEGRAPH_RENDERER_ABSTRACTRENDERER_H_*/
