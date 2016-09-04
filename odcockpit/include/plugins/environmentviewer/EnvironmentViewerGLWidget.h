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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendlv/data/environment/Position.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/NodeDescriptorComparator.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "plugins/AbstractGLWidget.h"
#include "plugins/environmentviewer/SelectableNodeDescriptorTreeListener.h"

class QWidget;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { template <typename T> class TreeNode; } }
namespace odcore { namespace data { class Container; } }
namespace opendlv { namespace threeD { class Node; } }
namespace opendlv { namespace threeD { class TransformGroup; } }

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            /**
             * This class is the viewport for a 3D scene.
             */
class CameraAssignableNodesListener;
class SelectableNodeDescriptor;

            class EnvironmentViewerGLWidget : public AbstractGLWidget, public odcore::io::conference::ContainerListener, public SelectableNodeDescriptorTreeListener {
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

                    virtual void nextContainer(odcore::data::Container &c);

                    /**
                     * This method sets the NodeDescriptor to which the camera
                     * should be assigned.
                     *
                     * @param nd NodeDescriptor to which the camera should be assigned.
                     */
                    void assignCameraTo(const opendlv::threeD::NodeDescriptor &nd);

                    virtual void update(odcore::base::TreeNode<SelectableNodeDescriptor> *node);

                protected:
                    virtual void setupOpenGL();

                    virtual void initScene();

                    virtual void drawScene();

                private:
                    odcore::base::Mutex m_rootMutex;
                    opendlv::threeD::TransformGroup *m_root;
                    opendlv::threeD::TransformGroup *m_stationaryElements;
                    opendlv::threeD::TransformGroup *m_dynamicElements;
                    opendlv::threeD::TransformGroup *m_measurements;
                    opendlv::threeD::TransformGroup *m_plannedRoute;
                    opendlv::threeD::TransformGroup *m_lines;

                    opendlv::threeD::NodeDescriptor m_egoStateNodeDescriptor;
                    uint32_t m_numberOfReceivedEgoStates;
                    opendlv::threeD::TransformGroup *m_egoStateNode;
                    map<opendlv::threeD::NodeDescriptor, opendlv::threeD::TransformGroup*, opendlv::threeD::NodeDescriptorComparator> m_mapOfTraceablePositions;
                    opendlv::threeD::TransformGroup *m_contouredObjectsNode;
                    opendlv::threeD::RenderingConfiguration m_renderingConfiguration;
                    opendlv::threeD::TransformGroup *m_obstaclesRoot;
                    map<uint32_t, opendlv::threeD::Node*> m_mapOfObstacles;

                    CameraAssignableNodesListener &m_cameraAssignableNodesListener;
                    vector<opendlv::threeD::NodeDescriptor> m_listOfCameraAssignableNodes;
                    opendlv::threeD::NodeDescriptor m_cameraAssignedNodeDescriptor;
                    map<opendlv::threeD::NodeDescriptor, opendlv::data::environment::Position, opendlv::threeD::NodeDescriptorComparator> m_mapOfCurrentPositions;

                    odcore::base::TreeNode<SelectableNodeDescriptor> *m_selectableNodeDescriptorTree;
                    SelectableNodeDescriptorTreeListener &m_selectableNodeDescriptorTreeListener;

                    /**
                     * This method actually modifies the rendering configuration.
                     *
                     * @param node Node to evaluate.
                     */
                    void modifyRenderingConfiguration(odcore::base::TreeNode<SelectableNodeDescriptor> *node);

                    /**
                     * This method creates the scene graph.
                     */
                    void createSceneGraph();
            };
        }
    }
} // plugins::environmentviewer

#endif /*PLUGINS_ENVIRONMENTVIEWER_ENVIRONMENTVIEWERGLWIDGET_H_*/
