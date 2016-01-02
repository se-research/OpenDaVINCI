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

#ifndef HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENEGRAPHFACTORY_H_
#define HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENEGRAPHFACTORY_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "core/base/Mutex.h"
#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/SceneNodeDescriptor.h"

namespace hesperia {
    namespace scenegraph {
        namespace transformation {

            using namespace std;

            /**
             * This class creates an appropriate visualization for a given SCNX file.
             */
            class OPENDAVINCI_API SceneGraphFactory {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    SceneGraphFactory(const SceneGraphFactory &);
                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    SceneGraphFactory& operator=(const SceneGraphFactory &);

                private:
                    SceneGraphFactory();

                public:
                    virtual ~SceneGraphFactory();

                    /**
                     * This method returns a static instance for this factory.
                     *
                     * @return Instance of this factory.
                     */
                    static SceneGraphFactory& getInstance();

                    /**
                     * This method returns a renderable scenegraph
                     * node for the given data structure.
                     *
                     * @param scnxArchive SCNXArchive to be visualized.
                     * @return Renderable node or NULL.
                     */
                    SceneNode* transform(scenario::SCNXArchive &scnxArchive);

                    /**
                     * This method returns a renderable scenegraph
                     * node for the given data structure.
                     *
                     * @param scnxArchive SCNXArchive to be visualized.
                     * @param showLaneConnectors if true, the red connectors between lane segments will be rendered.
                     * @return Renderable node or NULL.
                     */
                    SceneNode* transform(scenario::SCNXArchive &scnxArchive, const bool &showLaneConnectors);

                private:
                    static core::base::Mutex m_singletonMutex;
                    static SceneGraphFactory* m_singleton;
            };

        }
    }
} // hesperia::scenegraph::transformation

#endif /*HESPERIA_SCENEGRAPH_TRANSFORMATION_SCENEGRAPHFACTORY_H_*/
