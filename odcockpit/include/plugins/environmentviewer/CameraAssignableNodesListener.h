/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifndef PLUGINS_ENVIRONMENTVIEWER_CAMERAASSIGNABLENODESLISTENER_H_
#define PLUGINS_ENVIRONMENTVIEWER_CAMERAASSIGNABLENODESLISTENER_H_

#include <vector>

namespace hesperia { namespace threeD { class NodeDescriptor; } }

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace std;

            /**
             * This interface encapsulates the access for getting a list
             * of node to which a camera can be assigned.
             */
            class CameraAssignableNodesListener {
                public:
                    virtual ~CameraAssignableNodesListener();

                    /**
                     * This method is called by EnvironmentViewerGLWidget to update
                     * the list of camera assignable nodes.
                     *
                     * @param list List of camera assignable nodes.
                     */
                    virtual void updateListOfCameraAssignableNodes(const vector<hesperia::threeD::NodeDescriptor> &list) = 0;
            };

        }
    }
} // plugins::environmentviewer

#endif /*PLUGINS_ENVIRONMENTVIEWER_CAMERAASSIGNABLENODESLISTENER_H_*/
