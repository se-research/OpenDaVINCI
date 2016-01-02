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

#ifndef HESPERIA_CORE_DECORATOR_SCENARIORENDERER_H_
#define HESPERIA_CORE_DECORATOR_SCENARIORENDERER_H_

#include <map>
#include <string>
#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/base/Mutex.h"
#include "core/wrapper/Image.h"

#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ComplexModel.h"
#include "hesperia/data/scenario/HeightImage.h"
#include "hesperia/data/scenario/Image.h"
#include "hesperia/data/scenario/Polygon.h"
#include "hesperia/data/scenario/PointModel.h"
#include "hesperia/data/scenario/Surroundings.h"
#include "hesperia/decorator/Renderer.h"
#include "hesperia/decorator/models/OBJXArchive.h"
#include "hesperia/decorator/models/TriangleSet.h"
#include "hesperia/scenario/SCNXArchive.h"

namespace hesperia {
    namespace decorator {

        using namespace std;

        /**
         * This class is a device independent drawing visitor for scenarios.
         */
        class OPENDAVINCI_API ScenarioRenderer : public hesperia::data::scenario::ScenarioVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ScenarioRenderer(const ScenarioRenderer &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuseScenarioRenderer
                 * of the assignment operator.
                 */
                ScenarioRenderer& operator=(const ScenarioRenderer &/*obj*/);

            public:
                ScenarioRenderer();

                virtual ~ScenarioRenderer();

                virtual void visit(hesperia::data::scenario::ScenarioNode &node);

                /**
                 * This method sets the renderer to be used for rendering.
                 *
                 * @param renderer Renderer to be used.
                 */
                void setRenderer(Renderer *renderer);

                /**
                 * This method can be used to set the associated SCNXArchive
                 * to load more data like images or models.
                 *
                 * @param scnxArchive SCNXArchive to be used. If set to NULL no archive will be used. The given point won't get freed.
                 */
                void setSCNXArchive(hesperia::scenario::SCNXArchive *scnxArchive);

            private:
                /**
                 * This method is called when visit(ScenarioNode &node); encounters
                 * a polygon.
                 *
                 * @param p Polygon to visit.
                 */
                void visitPolygon(hesperia::data::scenario::Polygon &p);

                /**
                 * This method is called when visit(ScenarioNode &node); encounters
                 * a pointmodel.
                 *
                 * @param p PointModel to visit.
                 */
                void visitPointModel(hesperia::data::scenario::PointModel &p);

                /**
                 * This method is called when visit(ScenarioNode &node); encounters
                 * a Surroundings.
                 *
                 * @param s Surroundings to visit.
                 */
                void visitSurroundings(hesperia::data::scenario::Surroundings &s);

                /**
                 * This method is called to load a ground based complex model.
                 *
                 * @param cm ComplexModel to visit.
                 */
                void loadGroundBasedComplexModel(hesperia::data::scenario::ComplexModel &cm);

                /**
                 * This method is called when visit(ScenarioNode &node); encounters
                 * an image.
                 *
                 * @param image Image to visit.
                 */
                void visitImage(hesperia::data::scenario::Image &image);

                /**
                 * This method is called when visit(ScenarioNode &node); encounters
                 * a height image.
                 *
                 * @param hi HeightImage to visit.
                 */
                void visitHeightImage(hesperia::data::scenario::HeightImage &hi);

            private:
                core::base::Mutex m_scenarioRendererMutex;
                hesperia::scenario::SCNXArchive *m_scnxArchive;
                Renderer *m_renderer;

                map<string, vector<hesperia::decorator::models::TriangleSet> > m_mapOfGroundBasedComplexModels;
                vector<hesperia::decorator::models::OBJXArchive*> m_listOfLoadedOBJXArchives;
        };

    }
} // hesperia::decorator

#endif /*HESPERIA_CORE_DECORATOR_SCENARIORENDERER_H_*/
