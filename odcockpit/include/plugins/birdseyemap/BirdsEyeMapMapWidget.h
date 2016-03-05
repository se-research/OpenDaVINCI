/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPMAPWIDGET_H_
#define PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPMAPWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/scenegraph/SceneNodeDescriptor.h"
#include "opendlv/scenegraph/renderer/RenderingConfiguration.h"
#include "plugins/birdseyemap/SelectableNodeDescriptorTreeListener.h"

class QMouseEvent;
class QPaintEvent;
class QTimer;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { template <typename T> class TreeNode; } }
namespace odcore { namespace data { class Container; } }
namespace opendlv { namespace scenegraph { class SceneNode; } }
namespace opendlv { namespace scenegraph { namespace models { class SimpleCar; } } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace std;

            /**
             * This class is the widget for a 2D scene.
             */
class CameraAssignableNodesListener;
class SelectableNodeDescriptor;

            class BirdsEyeMapMapWidget : public QWidget, public odcore::io::conference::ContainerListener, public SelectableNodeDescriptorTreeListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    BirdsEyeMapMapWidget(const BirdsEyeMapMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    BirdsEyeMapMapWidget& operator=(const BirdsEyeMapMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     * @param canl Listener to be informed about newly selectable nodes for assign a camera.
                     * @param sndtl Reference to the selectable node descriptor tree listener.
                     */
                    BirdsEyeMapMapWidget(const PlugIn &plugIn, QWidget *prnt, CameraAssignableNodesListener &canl, SelectableNodeDescriptorTreeListener &sndtl);

                    virtual ~BirdsEyeMapMapWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                    /**
                     * This method sets the zoom level to a value between 0 < val <= 1.0.
                     */
                    void setZoomLevel(float val);

                    /**
                     * This method reset the ego trace.
                     */
                    void resetEgoTrace();

                    /**
                     * This method sets the SceneNodeDescriptor to which the camera
                     * should be assigned.
                     *
                     * @param snd SceneNodeDescriptor to which the camera should be assigned.
                     */
                    void assignCameraTo(const opendlv::scenegraph::SceneNodeDescriptor &snd);

                    virtual void update(odcore::base::TreeNode<SelectableNodeDescriptor> *node);

                private:
                    virtual void paintEvent(QPaintEvent *evnt);

                    virtual void mouseMoveEvent(QMouseEvent *evnt);
                    virtual void mouseReleaseEvent(QMouseEvent *evnt);

                private:
                    const plugins::PlugIn &m_plugIn;

                    opendlv::scenegraph::renderer::RenderingConfiguration m_renderingConfiguration;

                    odcore::base::TreeNode<SelectableNodeDescriptor> *m_selectableNodeDescriptorTree;
                    SelectableNodeDescriptorTreeListener &m_selectableNodeDescriptorTreeListener;

                    CameraAssignableNodesListener &m_cameraAssignableNodesListener;
                    vector<opendlv::scenegraph::SceneNodeDescriptor> m_listOfCameraAssignableNodes;
                    opendlv::scenegraph::SceneNodeDescriptor m_cameraAssignedNodeDescriptor;

                    QTimer *m_timer;

                    odcore::base::Mutex m_rootMutex;

                    opendlv::scenegraph::SceneNode *m_root;
                    opendlv::scenegraph::SceneNode *m_scales;
                    opendlv::scenegraph::SceneNode *m_stationaryElements;
                    opendlv::scenegraph::SceneNode *m_dynamicElements;
                    opendlv::scenegraph::SceneNode *m_measurements;

                    double m_scaleFactor;
                    opendlv::data::environment::Point3 m_centerOfMap;
                    opendlv::data::environment::Point3 m_mouseOld;

                    uint32_t m_numberOfReceivedEgoStates;
                    opendlv::data::environment::EgoState m_egoState;
                    opendlv::data::environment::EgoState m_lastEgoState;
                    opendlv::scenegraph::models::SimpleCar *m_egoCar;
                    opendlv::scenegraph::SceneNode *m_egoCarTrace;

                    opendlv::scenegraph::SceneNode *m_obstaclesRoot;
                    map<uint32_t, opendlv::scenegraph::SceneNode*> m_mapOfObstacles;

                    opendlv::scenegraph::SceneNode *m_plannedRoute;

                    void createSceneGraph();

                    void modifyRenderingConfiguration(odcore::base::TreeNode<SelectableNodeDescriptor> *node);
            };

        }
    }
} // plugins::birdseyemap

#endif /*PLUGINS_BIRDSEYEMAP_BIRDSEYEMAPMAPWIDGET_H_*/
