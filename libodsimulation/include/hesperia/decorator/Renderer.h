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

#ifndef HESPERIA_CORE_DECORATOR_RENDERER_H_
#define HESPERIA_CORE_DECORATOR_RENDERER_H_

#include <string>
#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "hesperia/data/environment/Point3.h"

namespace core { namespace wrapper { class Image; } }

namespace hesperia {
    namespace decorator {

namespace models { class TriangleSet; }

        using namespace std;

        // TODO: Capabilities: DRAW_TEXTURES, NAME==ENABLED, ...

        /**
         * This interface encapsulates all rudimentary painting methods.
         */
        class OPENDAVINCI_API Renderer {
            protected:
                Renderer();

            public:
                virtual ~Renderer();

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Renderer(const Renderer &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuseScenarioRenderer
                 * of the assignment operator.
                 */
                Renderer& operator=(const Renderer &/*obj*/);

            public:
                /**
                 * This method is called right before the primitive drawing
                 * calls are triggered.
                 */
                virtual void beginPainting() = 0;

                /**
                 * This method is called right after the primitive drawing
                 * calls were triggered.
                 */
                virtual void endPainting() = 0;

                /**
                 * This method is called to set the color for the next
                 * drawing operations.
                 *
                 * @param c Color in RGB [0;1].
                 */
                virtual void setColor(const hesperia::data::environment::Point3 &c) = 0;

                /**
                 * This method sets the point's width for the next paint operation.
                 *
                 * @param width Point's width for painting operation.
                 */
                virtual void setPointWidth(const double &width) = 0;

                /**
                 * This method sets the line's width for the next paint operation.
                 *
                 * @param width Line's width for painting operation.
                 */
                virtual void setLineWidth(const double &width) = 0;

                /**
                 * This method draws the given text.
                 *
                 * @param position Position where to draw the text.
                 * @param text Text to be drawn.
                 */
                virtual void drawText(const hesperia::data::environment::Point3 &p, const string &text) = 0;

                /**
                 * This method draws a point.
                 *
                 * @param p Point.
                 */
                virtual void drawPoint(const hesperia::data::environment::Point3 &p) = 0;

                /**
                 * This method draws a line.
                 *
                 * @param A Point A.
                 * @param B Point B.
                 */
                virtual void drawLine(const hesperia::data::environment::Point3 &A, const hesperia::data::environment::Point3 &B) = 0;

                /**
                 * This method draws a line consisting of several vertices.
                 *
                 * @param listOfPoints List of points.
                 */
                virtual void drawPolyLine(const vector<hesperia::data::environment::Point3> &listOfPoints) = 0;

                /**
                 * This method draws a line consisting of several vertices with
                 * an additional height.
                 *
                 * @param listOfPoints List of points.
                 * @param h height
                 */
                virtual void drawPolyLine(const vector<hesperia::data::environment::Point3> &listOfPoints, const double &height) = 0;

                /**
                 * This method draws an image.
                 *
                 * @param image Image to be drawn.
                 * @param originPixelXY Pixel for origin.
                 * @param scalingPixelXY Scaling for the image.
                 * @param rotationZ Rotation around Z-axis.
                 */
                virtual void drawImage(const core::wrapper::Image *image, const hesperia::data::environment::Point3 &originPixelXY, const hesperia::data::environment::Point3 &scalingPixelXY, const float &rotationZ) = 0;

                /**
                 * This method draws a TriangleSet.
                 *
                 * @param ts Triangle set.
                 */
                virtual void drawTriangleSet(const hesperia::decorator::models::TriangleSet &ts) = 0;

                /**
                 * This method draws a list of TriangleSets.
                 *
                 * @param listOfTriangleSets List of triangle sets.
                 */
                virtual void drawListOfTriangleSets(const vector<hesperia::decorator::models::TriangleSet> &listOfTriangleSets) = 0;

                /**
                 * This method draws a TriangleSet at the given position with the given rotation.
                 *
                 * @param ts Triangle set.
                 * @param position Position.
                 * @param rotation Rotation.
                 */
                virtual void drawTriangleSet(const hesperia::decorator::models::TriangleSet &ts, const hesperia::data::environment::Point3 &position, const hesperia::data::environment::Point3 &rotation) = 0;

                /**
                 * This method draws a list of TriangleSets.
                 *
                 * @param listOfTriangleSets List of triangle sets.
                 * @param position Position.
                 * @param rotation Rotation.
                 */
                virtual void drawListOfTriangleSets(const vector<hesperia::decorator::models::TriangleSet> &listOfTriangleSets, const hesperia::data::environment::Point3 &position, const hesperia::data::environment::Point3 &rotation) = 0;
        };

    }
} // hesperia::decorator

#endif /*HESPERIA_CORE_DECORATOR_RENDERER_H_*/
