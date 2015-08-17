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

#ifndef HESPERIA_CORE_DECORATOR_THREED_RENDERER3D_H_
#define HESPERIA_CORE_DECORATOR_THREED_RENDERER3D_H_

#include <string>
#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "core/strings/StringComparator.h"

#include "hesperia/decorator/Renderer.h"

namespace hesperia {
    namespace decorator {
        namespace threeD {

            using namespace std;

            /**
             * This class decorates any data structure for rendering with OpenGL.
             */
            class OPENDAVINCI_API Renderer3D : public hesperia::decorator::Renderer {
                public:
                    Renderer3D();

                    virtual ~Renderer3D();

                public:
                    virtual void beginPainting();

                    virtual void endPainting();

                    virtual void setColor(const hesperia::data::environment::Point3 &c);

                    virtual void setPointWidth(const double &width);

                    virtual void setLineWidth(const double &width);

                    virtual void drawText(const hesperia::data::environment::Point3 &p, const string &text);

                    virtual void drawPoint(const hesperia::data::environment::Point3 &p);

                    virtual void drawLine(const hesperia::data::environment::Point3 &A, const hesperia::data::environment::Point3 &B);

                    virtual void drawPolyLine(const vector<hesperia::data::environment::Point3> &listOfPoints);

                    virtual void drawPolyLine(const vector<hesperia::data::environment::Point3> &listOfPoints, const double &height);

                    virtual void drawImage(const core::wrapper::Image *image, const hesperia::data::environment::Point3 &originPixelXY, const hesperia::data::environment::Point3 &scalingPixelXY, const float &rotationZ);

                    virtual void drawTriangleSet(const hesperia::decorator::models::TriangleSet &ts);

                    virtual void drawListOfTriangleSets(const vector<hesperia::decorator::models::TriangleSet> &listOfTriangleSets);

                    virtual void drawTriangleSet(const hesperia::decorator::models::TriangleSet &ts, const hesperia::data::environment::Point3 &position, const hesperia::data::environment::Point3 &rotation);

                    virtual void drawListOfTriangleSets(const vector<hesperia::decorator::models::TriangleSet> &listOfTriangleSets, const hesperia::data::environment::Point3 &position, const hesperia::data::environment::Point3 &rotation);

                private:
                    vector<string> m_listOfImagesRegisteredAtTextureManager;
            };

        }
    }
} // hesperia::decorator::threeD

#endif /*HESPERIA_CORE_DECORATOR_THREED_RENDERER3D_H_*/
