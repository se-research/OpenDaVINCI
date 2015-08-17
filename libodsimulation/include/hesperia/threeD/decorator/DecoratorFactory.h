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

#ifndef HESPERIA_CORE_THREED_DECORATOR_DECORATORFACTORY_H_
#define HESPERIA_CORE_THREED_DECORATOR_DECORATORFACTORY_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/base/Mutex.h"
#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/loaders/OBJXArchive.h"

namespace hesperia {
    namespace threeD {
        namespace decorator {

            using namespace std;

            /**
             * This class creates an appropriate visualization for a given datatype.
             */
            class OPENDAVINCI_API DecoratorFactory {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    DecoratorFactory(const DecoratorFactory &);
                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    DecoratorFactory& operator=(const DecoratorFactory &);

                private:
                    DecoratorFactory();

                public:
                    virtual ~DecoratorFactory();

                    /**
                     * This method returns a static instance for this factory.
                     *
                     * @return Instance of this factory.
                     */
                    static DecoratorFactory& getInstance();

                    /**
                     * This method returns an OpenGL-displayable scenegraph
                     * node for the given data structure.
                     *
                     * @param scnxArchive SCNXArchive to be visualized.
                     * @return OpenGL displayable node or NULL.
                     */
                    Node* decorate(scenario::SCNXArchive &scnxArchive);

                    /**
                     * This method returns an OpenGL-displayable scenegraph
                     * node for the given data structure.
                     *
                     * @param scnxArchive SCNXArchive to be visualized.
                     * @param showLaneConnectors if true, the red connectors between lane segments will be rendered.
                     * @return OpenGL displayable node or NULL.
                     */
                    Node* decorate(scenario::SCNXArchive &scnxArchive, const bool &showLaneConnectors);

                    /**
                     * This method returns an OpenGL-displayable scenegraph
                     * node for the given data structure.
                     *
                     * @param objxArchive OBJXArchive to be visualized.
                     * @param nd NodeDescriptor.
                     * @return OpenGL displayable node or NULL.
                     */
                    Node* decorate(loaders::OBJXArchive &objxArchive, const NodeDescriptor &nd);

                private:
                    static core::base::Mutex m_singletonMutex;
                    static DecoratorFactory* m_singleton;
            };

        }
    }
} // hesperia::threeD::decorator

#endif /*HESPERIA_CORE_THREED_DECORATOR_DECORATORFACTORY_H_*/
