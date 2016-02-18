/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPRENDERER_H_
#define PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPRENDERER_H_

#include "opendavinci/core/opendavinci.h"
#include "opendlv/scenegraph/renderer/AbstractRenderer.h"

class QPainter;
namespace opendlv { namespace scenegraph { namespace primitives { class Line; } } }
namespace opendlv { namespace scenegraph { namespace primitives { class Point; } } }
namespace opendlv { namespace scenegraph { namespace primitives { class Polygon; } } }
namespace opendlv { namespace scenegraph { namespace renderer { class RenderingConfiguration; } } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            /**
             * This class is responsible for rendering scenegraph primitives.
             */
            class BirdsEyeMapRenderer : public opendlv::scenegraph::renderer::AbstractRenderer {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BirdsEyeMapRenderer(const BirdsEyeMapRenderer &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BirdsEyeMapRenderer& operator=(const BirdsEyeMapRenderer &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @painter QPainter to be used for rendering.
                     * @rC RenderingConfiguration.
                     * @pixelPerMeter Pixel per meter ratio (default: 1px = 1mm --> 1000px = 1m).
                     */
                    BirdsEyeMapRenderer(QPainter *painter, opendlv::scenegraph::renderer::RenderingConfiguration &rc, const uint32_t &pixelPerMeter = 1000);

                    virtual ~BirdsEyeMapRenderer();

                protected:
                    virtual void render(opendlv::scenegraph::primitives::Point *p);

                    virtual void render(opendlv::scenegraph::primitives::Line *l);

                    virtual void render(opendlv::scenegraph::primitives::Polygon *p);

                private:
                    QPainter *m_painter;
                    opendlv::scenegraph::renderer::RenderingConfiguration &m_renderingConfiguration;
                    uint32_t m_pixelPerMeter;
            };
        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPRENDERER_H_*/
