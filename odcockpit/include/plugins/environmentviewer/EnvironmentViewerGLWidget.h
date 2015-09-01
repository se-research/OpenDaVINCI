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

#ifndef PLUGINS_ENVIRONMENTVIEWER_ENVIRONMENTVIEWERGLWIDGET_H_
#define PLUGINS_ENVIRONMENTVIEWER_ENVIRONMENTVIEWERGLWIDGET_H_

#include <map>
#include <vector>

#include "core/base/Mutex.h"
#include "core/base/TreeNode.h"

#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Position.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptorComparator.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/TransformGroup.h"

#include "plugins/AbstractGLWidget.h"
#include "plugins/environmentviewer/CameraAssignableNodesListener.h"
#include "plugins/environmentviewer/SelectableNodeDescriptor.h"
#include "plugins/environmentviewer/SelectableNodeDescriptorTreeListener.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            /**
             * This class is the viewport for a 3D scene.
             */
            class EnvironmentViewerGLWidget : public AbstractGLWidget, public core::io::conference::ContainerListener, public SelectableNodeDescriptorTreeListener {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    EnvironmentViewerGLWidget(const EnvironmentViewerGLWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    EnvironmentViewerGLWidget& operator=(const EnvironmentViewerGLWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     * @param canl Listener to be informed about newly selectable nodes for assign a camera.
                     * @param sndtl Reference to the selectable node descriptor tree listener.
                     */
                    EnvironmentViewerGLWidget(const PlugIn &plugIn, QWidget *prnt, CameraAssignableNodesListener &canl, SelectableNodeDescriptorTreeListener &sndtl);

                    virtual ~EnvironmentViewerGLWidget();

                    virtual void nextContainer(core::data::Container &c);

                    /**
                     * This method sets the NodeDescriptor to which the camera
                     * should be assigned.
                     *
                     * @param nd NodeDescriptor to which the camera should be assigned.
                     */
                    void assignCameraTo(const hesperia::threeD::NodeDescriptor &nd);

                    virtual void update(core::base::TreeNode<SelectableNodeDescriptor> *node);

                protected:
                    virtual void setupOpenGL();

                    virtual void initScene();

                    virtual void drawScene();

                private:
                    core::base::Mutex m_rootMutex;
                    hesperia::threeD::TransformGroup *m_root;
                    hesperia::threeD::TransformGroup *m_stationaryElements;
                    hesperia::threeD::TransformGroup *m_dynamicElements;
                    hesperia::threeD::TransformGroup *m_measurements;
                    hesperia::threeD::TransformGroup *m_plannedRoute;
                    hesperia::threeD::TransformGroup *m_lines;

                    hesperia::threeD::NodeDescriptor m_egoStateNodeDescriptor;
                    uint32_t m_numberOfReceivedEgoStates;
                    hesperia::threeD::TransformGroup *m_egoStateNode;
                    map<hesperia::threeD::NodeDescriptor, hesperia::threeD::TransformGroup*, hesperia::threeD::NodeDescriptorComparator> m_mapOfTraceablePositions;
                    hesperia::threeD::TransformGroup *m_contouredObjectsNode;
                    hesperia::threeD::RenderingConfiguration m_renderingConfiguration;
                    hesperia::threeD::TransformGroup *m_obstaclesRoot;
                    map<uint32_t, hesperia::threeD::Node*> m_mapOfObstacles;

                    CameraAssignableNodesListener &m_cameraAssignableNodesListener;
                    vector<hesperia::threeD::NodeDescriptor> m_listOfCameraAssignableNodes;
                    hesperia::threeD::NodeDescriptor m_cameraAssignedNodeDescriptor;
                    map<hesperia::threeD::NodeDescriptor, hesperia::data::environment::Position, hesperia::threeD::NodeDescriptorComparator> m_mapOfCurrentPositions;

                    core::base::TreeNode<SelectableNodeDescriptor> *m_selectableNodeDescriptorTree;
                    SelectableNodeDescriptorTreeListener &m_selectableNodeDescriptorTreeListener;

                    /**
                     * This method actually modifies the rendering configuration.
                     *
                     * @param node Node to evaluate.
                     */
                    void modifyRenderingConfiguration(core::base::TreeNode<SelectableNodeDescriptor> *node);

                    /**
                     * This method creates the scene graph.
                     */
                    void createSceneGraph();
            };
        }
    }
} // plugins::environmentviewer

#endif /*PLUGINS_ENVIRONMENTVIEWER_ENVIRONMENTVIEWERGLWIDGET_H_*/
