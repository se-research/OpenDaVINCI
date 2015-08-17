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

#ifndef HESPERIA_SCENEGRAPH_SCENENODEDESCRIPTOR_H_
#define HESPERIA_SCENEGRAPH_SCENENODEDESCRIPTOR_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace hesperia {
    namespace scenegraph {

        using namespace std;

        /**
         * This class provides a description for the current scene node.
         */
        class OPENDAVINCI_API SceneNodeDescriptor {
            public:
                SceneNodeDescriptor();

                /**
                 * Constructor.
                 *
                 * @param name Name of this scene node descriptor.
                 */
                SceneNodeDescriptor(const string &name);

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                SceneNodeDescriptor(const SceneNodeDescriptor &obj);

                virtual ~SceneNodeDescriptor();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                SceneNodeDescriptor& operator=(const SceneNodeDescriptor &obj);

                /**
                 * This method returns the name of this node.
                 *
                 * @return Name of this node.
                 */
                const string getName() const;

            private:
                string m_name;
        };

    }
} // hesperia::scenegraph

#endif /*HESPERIA_SCENEGRAPH_SCENENODEDESCRIPTOR_H_*/
