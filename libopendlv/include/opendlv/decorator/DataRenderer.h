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

#ifndef HESPERIA_CORE_DECORATOR_DATARENDERER_H_
#define HESPERIA_CORE_DECORATOR_DATARENDERER_H_

#include <map>
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendavinci/core/data/Container.h"

#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Obstacle.h"
#include "opendlv/data/environment/OtherVehicleState.h"
#include "opendlv/data/planning/Route.h"
#include "opendlv/data/sensor/ContouredObjects.h"
#include "opendlv/data/situation/ComplexModel.h"
#include "opendlv/decorator/Renderer.h"
#include "opendlv/decorator/models/OBJXArchive.h"
#include "opendlv/decorator/models/TriangleSet.h"
#include "opendlv/scenario/SCNXArchive.h"

namespace hesperia {
    namespace decorator {

        using namespace std;

        /**
         * This class is a device independent data painter.
         */
        class OPENDAVINCI_API DataRenderer {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                DataRenderer(const DataRenderer &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuseScenarioRenderer
                 * of the assignment operator.
                 */
                DataRenderer& operator=(const DataRenderer &/*obj*/);

            public:
                DataRenderer();

                virtual ~DataRenderer();

                /**
                 * This method tries to draw an arbitrary container.
                 *
                 * @param c Container to draw.
                 */
                void draw(core::data::Container &c);

                /**
                 * This method draws an EgoState.
                 *
                 * @param es EgoState to be drawn.
                 */
                void draw(const hesperia::data::environment::EgoState &es);

                /**
                 * This method draws a ContouredObjects.
                 *
                 * @param cos ContouredObjectes to be drawn.
                 */
                void draw(const hesperia::data::sensor::ContouredObjects &cos);

                /**
                 * This method draws an Obstacle.
                 *
                 * @param o Obstacle to be drawn.
                 */
                void draw(const hesperia::data::environment::Obstacle &o);

                /**
                 * This method draws the planned Route.
                 *
                 * @param r Planned route to be drawn.
                 */
                void draw(const hesperia::data::planning::Route &r);

                /**
                 * This method draws another object.
                 *
                 * @param o Other object.
                 */
                void draw(const hesperia::data::environment::OtherVehicleState &o);

                /**
                 * This method sets the renderer to be used for rendering.
                 *
                 * @param renderer Renderer to be used.
                 */
                void setRenderer(Renderer *renderer);

                /**
                 * This method sets a model for the decorating the EgoState.
                 *
                 * @param fn Filename to load *.objx model.
                 */
                void setEgoStateModel(const string &fn);

                /**
                 * This method can be used to set the associated SCNXArchive
                 * to load more data like images or models.
                 *
                 * @param scnxArchive SCNXArchive to be used. If set to NULL no archive will be used. The given point won't get freed.
                 */
                void setSCNXArchive(hesperia::scenario::SCNXArchive *scnxArchive);

            private:
                core::base::Mutex m_dataRendererMutex;
                Renderer *m_renderer;

                hesperia::scenario::SCNXArchive *m_scnxArchive;

                vector<hesperia::decorator::models::TriangleSet> m_egoStateModel;
                vector<hesperia::decorator::models::OBJXArchive*> m_listOfLoadedOBJXArchives;

                map<uint32_t, vector<hesperia::decorator::models::TriangleSet> > m_mapOfModels;

                /**
                 * Load complex model from SCNX archive.
                 *
                 * @param id Identifier.
                 * @param cm ComplexModel data structure.
                 */
                void loadComplexModel(const uint32_t &id, hesperia::data::situation::ComplexModel &cm);
        };

    }
} // hesperia::decorator

#endif /*HESPERIA_CORE_DECORATOR_DATARENDERER_H_*/
