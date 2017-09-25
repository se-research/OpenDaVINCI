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
#include <memory>
#include <string>
#include <vector>
#include <array>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendlv/data/environment/Position.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/NodeDescriptorComparator.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "plugins/AbstractGLWidget.h"
#include "plugins/environmentviewer/SelectableNodeDescriptorTreeListener.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/generated/odcore/data/SharedPointCloud.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendavinci/generated/odcore/data/CompactPointCloud.h"
//#include "automotivedata/generated/cartesian/Constants.h"

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
                    void drawOneCPCPointNoIntensity(const uint16_t &distance_integer, const float &azimuth, const float &verticalAngle, const uint8_t &distanceEncoding);
                    void drawOneCPCPointWithIntensity(const uint16_t &distance_integer, const float &azimuth, const float &verticalAngle, const uint8_t &distanceEncoding, const uint8_t &numberOfBitsForIntensity, const uint8_t &intensityPlacement, const uint16_t &mask, const float &intensityMaxValue);
                    /** 
                     * Assuming 10Hz rotation rate, HDL-32E is able to fire up to 70,000 points per scan, 
                     * which cannot be all squeezed into one single UDP packet by CPC.
                     * Therefore, the data of a complete scan of HDL-32E is stored into three separate CPC messages, 
                     * with each CPC containing a subset of the 32 layers.

                     * part == 1: the first CPC of a HDL-32E scan with 12 layers -> including layers 0, 1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31
                     * part == 2: the second CPC of a HDL-32E scan with 11 layers -> including layers 2, 3, 6, 9, 12, 15, 18, 21, 24, 27, 30
                     * part == 3: the third CPC of a HDL-32E scan with 9 layers -> including layers 5, 8, 11, 14, 17, 20, 23, 26, 29
                     */
                    void drawCPC32noIntensity(const uint8_t &part, const uint8_t &entriesPerAzimuth, const float &startAzimuth, const float &endAzimuth, const uint8_t &distanceEncoding);
                    void drawCPC32withIntensity(const uint8_t &part, const uint8_t &entriesPerAzimuth, const float &startAzimuth, const float &endAzimuth, const uint8_t &distanceEncoding, const uint8_t &numberOfBitsForIntensity, const uint8_t &intensityPlacement, const uint16_t &mask, const float &intensityMaxValue);
                    void drawSceneInternal();

                private:
                    odcore::base::Mutex m_rootMutex;
                    opendlv::threeD::TransformGroup *m_root;
                    opendlv::threeD::TransformGroup *m_stationaryElements;
                    opendlv::threeD::TransformGroup *m_dynamicElements;
                    opendlv::threeD::TransformGroup *m_measurements;
                    opendlv::threeD::TransformGroup *m_plannedRoute;
                    opendlv::threeD::TransformGroup *m_lines;
                    opendlv::threeD::TransformGroup *m_velodyne;
                    opendlv::data::environment::EgoState m_egoState;

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

                    std::shared_ptr<odcore::wrapper::SharedMemory> m_velodyneSharedMemory;
                    bool m_hasAttachedToSharedImageMemory;
                    odcore::data::SharedPointCloud m_velodyneFrame;
                    const float START_V_ANGLE = -15.0; //For each azimuth there are 16 points with unique vertical angles from -15 to 15 degrees
                    const float V_INCREMENT = 2.0; //The vertical angle increment for the 16 points with the same azimuth is 2 degrees
                    const float START_V_ANGLE_32 = -30.67; //The starting angle for HDL-32E. Vertical angle ranges from -30.67 to 10.67 degress, with alternating increment 1.33 and 1.34
                    const float V_INCREMENT_32_A = 1.33; //The first vertical angle increment for HDL-32E
                    const float V_INCREMENT_32_B = 1.34; //The second vertical angle increment for HDL-32E
                    uint8_t m_12_startingSensorID_32; //From which layer for the first part(12 layers) of CPC for HDL-32E
                    uint8_t m_11_startingSensorID_32; //From which layer for the second part(11 layers) of CPC for HDL-32E
                    uint8_t m_9_startingSensorID_32; //From which layer for the third part(9 layers) of CPC for HDL-32E
                    std::array<float, 12>  m_12_verticalAngles; //Store the 12 vertical angles for the first part (including 12 layers) of CPC for HDL-32E
                    std::array<float, 11> m_11_verticalAngles; //Store the 11 vertical angles for the second part (including 11 layers) of CPC for HDL-32E
                    std::array<float, 9> m_9_verticalAngles; //Store the 9 vertical angles for the third part (including 9 layers) of CPC for HDL-32E
                    std::string m_12_cpcDistance_32; //The distance string for the first part of CPC for HDL-32E    
                    std::string m_11_cpcDistance_32; //The distance string for the second part of CPC for HDL-32E    
                    std::string m_9_cpcDistance_32; //The distance string for the third part of CPC for HDL-32E    
                    uint64_t m_previousCPC32TimeStamp;//The sample time of the previous CPC container belonging to a HDL-32E scan
                    uint8_t m_cpcMask_32; //The lowest 3 bits represent which part(s) of HDL-32E CPC of the same scan has been received. 0100 means the first part has arrived; 0010 means the second part has arrived; 0001 means the third part has arrived.                   
                    odcore::data::CompactPointCloud m_cpc;
                    odcore::base::Mutex m_cpcMutex;
                    bool m_SPCReceived;//Set to true when the first shared point cloud is received
                    bool m_CPCReceived;//Set to true when the first compact point cloud is received
                    uint32_t m_recordingYear;//The year when a recording with CPC was taken

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
