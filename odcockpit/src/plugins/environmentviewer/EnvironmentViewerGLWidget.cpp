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

#include <GL/gl.h>
#include <GL/glu.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "core/base/TreeNode.h"
#include "core/data/Container.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/URL.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Line.h"
#include "hesperia/data/environment/Obstacle.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Polygon.h"
#include "hesperia/data/planning/Route.h"
#include "hesperia/data/sensor/ContouredObject.h"
#include "hesperia/data/sensor/ContouredObjects.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/NodeRenderingConfiguration.h"
#include "hesperia/threeD/TransformGroup.h"
#include "hesperia/threeD/decorator/DecoratorFactory.h"
#include "hesperia/threeD/loaders/OBJXArchive.h"
#include "hesperia/threeD/loaders/OBJXArchiveFactory.h"
#include "hesperia/threeD/models/Grid.h"
#include "hesperia/threeD/models/Line.h"
#include "hesperia/threeD/models/Point.h"
#include "hesperia/threeD/models/XYZAxes.h"
#include "plugins/PlugIn.h"
#include "plugins/environmentviewer/CameraAssignableNodesListener.h"
#include "plugins/environmentviewer/EnvironmentViewerGLWidget.h"
#include "plugins/environmentviewer/SelectableNodeDescriptor.h"
#include "plugins/environmentviewer/TreeNodeVisitor.h"

#include <sstream>

#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"
#include "core/io/protocol/PCAPProtocol.h"

#include "GeneratedHeaders_CoreData.h"
#include <cmath>

const double rotCorrection[64]={-5.3328056,-3.2344019,2.4376695,4.7373252,-1.0502493,1.2386309,-1.8405367,0.4511103,
                                3.2611551,5.4685535,2.4743285,4.7189918,-5.3511744,-3.1158857,-6.1270261,-3.852011,
                                -1.1109436,1.1519098,-1.8682934,0.43604341,3.1763444,5.4284201,2.4024715,4.6698937,
                                -5.3977456,-3.1504908,-6.1759849,-3.8819003,-1.1136208,1.0969903,-1.9088749,0.36758029,
                                -8.3386211,-4.7629819,4.1516571,7.3577185,-1.2630961,2.1595552,-2.6141083,0.95595688,
                                5.5369682,8.9712191,4.4757471,7.8848143,-8.0466499,-4.595552,-9.3918352,-5.9566336,
                                -1.3779737,2.0754263,-2.5654242,0.87227631,5.2989287,8.7970304,4.1742177,7.5869775,
                                -7.8831077,-4.5919614,-9.1805763,-5.7835727,-1.2335371,1.9424959,-2.5727935,0.81118912};
const double vertCorrection[64]={-7.2988362,-6.9644198,0.250889,0.55538797,-6.6410818,-6.2594609,-8.6656351,-8.3104696,
                                5.9352221,5.587399,-7.9891219,-7.644258,-3.2475569,-2.850472,-5.204318,-4.9137921,
                                -2.4998751,-2.184176,-4.5764661,-4.2038751,-1.798143,-1.49388,-1.877563,-3.492661,
                                0.88327599,1.234519,-1.177825,-0.86169797,1.585669,1.925001,-0.486963,-0.123898,
                                -22.597513,-22.397568,-11.576517,-10.877901,-21.935509,-21.409546,-25.066507,-24.458101,
                                -20.777454,-20.243195,-23.863358,-23.352007,-16.629311,-16.230633,-19.788239,-19.21587,
                                -15.754419,-15.166914,-18.828558,-18.312876,-14.641928,-14.048302,-17.687857,-17.16544,
                                -10.436752,-10.085198,-13.484814,-13.107666,-9.5621262,-9.0374413,-12.651329,-12.115005};
const double distCorrection[64]={111.0,146.0,131.76823,138.12656,119.0,135.0,132.0,145.0,
                                116.0,133.99889,117.0,145.0,118.71672,142.90839,120.0,137.0,
                                101.71324,145.31258,130.0,147.0,115.82812,146.0,129.29713,157.97737,
                                124.12312,128.0,133.0,130.0,131.0,131.0,138.48773,137.21994,
                                117.0,100.0,130.0,102.0,106.0,91.0,127.0,95.0,
                                106.0,97.0,115.0,92.0,135.0,108.0,135.0,98.0,
                                116.0,105.0,138.0,105.0,123.0,86.0,135.0,92.0,
                                121.0,103.0,146.0,99.0,123.0,106.0,134.0,104.0,};
const double vertOffsetCorrection[64]={19.736338,19.778963,20.688799,20.727015,19.82012,19.868624,19.561426,19.606993,
                                19.909781,19.953875,19.648148,19.692244,20.249313,20.29929,20.00238,20.039125,
                                20.343384,20.38307,20.081753,20.128786,20.431576,20.469791,20.169943,20.218447,
                                20.768169,20.812265,20.509478,20.549164,20.856361,20.898987,20.596197,20.641764,
                                10.828748,10.854152,12.142142,12.220895,10.912581,10.978632,10.508655,10.588678,
                                11.057385,11.123436,10.666161,10.732212,11.559117,11.606115,11.179325,11.249186,
                                11.662004,11.730595,11.296184,11.358424,11.791565,11.860156,11.433367,11.495607,
                                12.270433,12.30981,11.924937,11.968124,12.368239,12.426669,12.020203,12.081173};
const double horizOffsetCorrection[64]={2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,
2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999,2.5999999,-2.5999999};

const double PI=3.1415926;
#define toRadian(x) ((x)*PI/180.0)

bool passed;
long packetNr(0);
long pointIndex(0);
long frameIndex(0);
double previousAzimuth(0.00);

class QWidget;
namespace hesperia { namespace scenario { class SCNXArchive; } }

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace core::base;
            using namespace core::data;
            using namespace core::exceptions;
            using namespace core::io;
            using namespace core::data;
            using namespace coredata;
            using namespace core::io::protocol;
            using namespace hesperia::data::environment;
            using namespace hesperia::data::environment;
            using namespace hesperia::data::planning;
            using namespace hesperia::data::scenario;
            using namespace hesperia::data::sensor;
            using namespace hesperia::scenario;
            using namespace hesperia::threeD;
            using namespace hesperia::threeD::decorator;
            using namespace hesperia::threeD::loaders;

            EnvironmentViewerGLWidget::EnvironmentViewerGLWidget(const PlugIn &plugIn, QWidget *prnt, CameraAssignableNodesListener &canl, SelectableNodeDescriptorTreeListener &sndtl) :
                    AbstractGLWidget(plugIn, prnt),
                    m_rootMutex(),
                    m_root(NULL),
                    m_stationaryElements(NULL),
                    m_dynamicElements(NULL),
                    m_measurements(NULL),
                    m_plannedRoute(NULL),
                    m_lines(NULL),
                    m_velodyne(NULL),
                    m_egoStateNodeDescriptor(),
                    m_numberOfReceivedEgoStates(0),
                    m_egoStateNode(NULL),
                    m_mapOfTraceablePositions(),
                    m_contouredObjectsNode(NULL),
                    m_renderingConfiguration(),
                    m_obstaclesRoot(NULL),
                    m_mapOfObstacles(),
                    m_cameraAssignableNodesListener(canl),
                    m_listOfCameraAssignableNodes(),
                    m_cameraAssignedNodeDescriptor(),
                    m_mapOfCurrentPositions(),
                    m_selectableNodeDescriptorTree(NULL),
                    m_selectableNodeDescriptorTreeListener(sndtl),
                    m_readFlag(true) {m_pcap.setContainerListener(this);lidlarStream.open("atwall.pcap", ios::binary|ios::in);}

            EnvironmentViewerGLWidget::~EnvironmentViewerGLWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_root);
                OPENDAVINCI_CORE_DELETE_POINTER(m_selectableNodeDescriptorTree);
            }

            void EnvironmentViewerGLWidget::createSceneGraph() {
                m_root = new TransformGroup();
                m_stationaryElements = new TransformGroup();
                m_dynamicElements = new TransformGroup();
                m_measurements = new TransformGroup();

                m_root->addChild(m_stationaryElements);
                m_root->addChild(m_dynamicElements);
                m_root->addChild(m_measurements);

                /*******************************************************************/
                /* Stationary elements.                                            */
                /*******************************************************************/
                m_stationaryElements->addChild(new hesperia::threeD::models::XYZAxes(NodeDescriptor("XYZAxes"), 1, 10));
                m_stationaryElements->addChild(new hesperia::threeD::models::Grid(NodeDescriptor("Grid"), 10, 1));

                // Setup surroundings.
                const URL urlOfSCNXFile(getPlugIn().getKeyValueConfiguration().getValue<string>("global.scenario"));
                if (urlOfSCNXFile.isValid()) {
                    SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

                    // Read scnxArchive and decorate it for getting displayed in an OpenGL scene.
                    Node *surroundings = DecoratorFactory::getInstance().decorate(scnxArchive);
                    if (surroundings != NULL) {
                        surroundings->setNodeDescriptor(NodeDescriptor("Surroundings"));
                        m_stationaryElements->addChild(surroundings);
                    }
                }

                /*******************************************************************/
                /* Dynamic elements.                                               */
                /*******************************************************************/
                const URL urlOfCar(getPlugIn().getKeyValueConfiguration().getValue<string>("global.car"));
                if (urlOfCar.isValid()) {
                    string objxModel(urlOfCar.getResource());
                    cout << "Opening file stream to car model " << objxModel << endl;
                    fstream fin(objxModel.c_str(), ios::in | ios::binary);
                    if (fin.good()) {
                        cout << "Loading car model" << endl;
                        OBJXArchive *objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(fin);

                        fin.close();
                        if (objxArchive != NULL) {
                            // Decorate objxArchive for getting displayed in an OpenGL scene.
                            m_egoStateNodeDescriptor = NodeDescriptor("EgoCar");
                            m_listOfCameraAssignableNodes.push_back(m_egoStateNodeDescriptor);
                            m_egoStateNode = objxArchive->createTransformGroup(m_egoStateNodeDescriptor);
                        }

                        if (m_egoStateNode == NULL) {
                            OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Could not load car model");
                        }
                        else {
                            m_dynamicElements->addChild(m_egoStateNode);

                            // EgoCar is traceable.
                            NodeDescriptor traceableNodeDescriptor = NodeDescriptor("EgoCar (Trace)");
                            TransformGroup *traceableNode = new TransformGroup(traceableNodeDescriptor);
                            m_mapOfTraceablePositions[traceableNodeDescriptor] = traceableNode;
                            m_dynamicElements->addChild(traceableNode);
                        }
                    }
                }

                m_plannedRoute = new TransformGroup(NodeDescriptor("Planned Route"));
                m_dynamicElements->addChild(m_plannedRoute);

                m_lines = new TransformGroup(NodeDescriptor("Individual Lines"));
                m_dynamicElements->addChild(m_lines);

                /*******************************************************************/
                /* Measurements.                                                   */
                /*******************************************************************/
                // Create node for showing contoured objects.
                m_contouredObjectsNode = new TransformGroup(NodeDescriptor("Contoured Objects"));
                m_measurements->addChild(m_contouredObjectsNode);

                m_obstaclesRoot = new TransformGroup(NodeDescriptor("Obstacles"));
                m_measurements->addChild(m_obstaclesRoot);
                
                m_velodyne = new TransformGroup(NodeDescriptor("Velodyne"));
                m_measurements->addChild(m_velodyne);
            }

            void EnvironmentViewerGLWidget::initScene() {
                // Setup scene graph.
                createSceneGraph();

                // Setup selectable scene graph.
                m_selectableNodeDescriptorTree = new TreeNode<SelectableNodeDescriptor>();
                TreeNode<SelectableNodeDescriptor> *stationaryElements = new TreeNode<SelectableNodeDescriptor>();
                stationaryElements->setValue(SelectableNodeDescriptor(NodeDescriptor("Stationary Elements"), false));
                m_selectableNodeDescriptorTree->addChild(stationaryElements);

                TreeNode<SelectableNodeDescriptor> *dynamicElements = new TreeNode<SelectableNodeDescriptor>();
                dynamicElements->setValue(SelectableNodeDescriptor(NodeDescriptor("Dynamic Elements"), false));
                m_selectableNodeDescriptorTree->addChild(dynamicElements);

                TreeNode<SelectableNodeDescriptor> *measuredData = new TreeNode<SelectableNodeDescriptor>();
                measuredData->setValue(SelectableNodeDescriptor(NodeDescriptor("Measured Data"), false));
                m_selectableNodeDescriptorTree->addChild(measuredData);

                // Collect data from scene graph using a visitor.
                TreeNodeVisitor tnvStationaryElements(m_renderingConfiguration, stationaryElements);
                m_stationaryElements->accept(tnvStationaryElements);

                TreeNodeVisitor tnvDynamicElements(m_renderingConfiguration, dynamicElements);
                m_dynamicElements->accept(tnvDynamicElements);

                TreeNodeVisitor tnvMeasuredData(m_renderingConfiguration, measuredData);
                m_measurements->accept(tnvMeasuredData);

                // Inform listener about selectable NodeDescriptors.
                m_selectableNodeDescriptorTreeListener.update(m_selectableNodeDescriptorTree);

                // Inform listener about assignable nodes.
                m_cameraAssignableNodesListener.updateListOfCameraAssignableNodes(m_listOfCameraAssignableNodes);
            }

            void EnvironmentViewerGLWidget::assignCameraTo(const NodeDescriptor &nd) {
                Lock l(m_rootMutex);
                m_cameraAssignedNodeDescriptor = nd;
            }

            void EnvironmentViewerGLWidget::setupOpenGL() {
                glEnable(GL_LIGHTING);

                glEnable(GL_LIGHT0);
                float light0Position[4] = {0, 0, 20, 0};
                float light0Ambient[4] = {0.5f, 0.5f, 0.5f, 0};
                float light0Diffuse[4] = {0.8f, 0.8f, 0.8f, 0};
                float light0Specular[4] = {0, 0, 0, 0};
                glLightfv(GL_LIGHT0, GL_POSITION, light0Position);
                glLightfv(GL_LIGHT0, GL_AMBIENT, light0Ambient);
                glLightfv(GL_LIGHT0, GL_DIFFUSE, light0Diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, light0Specular);
            }

            void EnvironmentViewerGLWidget::drawScene() {
                if (m_root != NULL) {
                    Lock l(m_rootMutex);

                    if (m_cameraAssignedNodeDescriptor.getName().size() > 0) {
                        Position assignedNode = m_mapOfCurrentPositions[m_cameraAssignedNodeDescriptor];
                        Point3 positionCamera;
                        Point3 lookAtPointCamera;
                        Point3 dirCamera(-10, 0, 0);
                        dirCamera.rotateZ(assignedNode.getRotation().getAngleXY());
                        positionCamera.setX(assignedNode.getPosition().getX() + dirCamera.getX());
                        positionCamera.setY(assignedNode.getPosition().getY() + dirCamera.getY());
                        positionCamera.setZ(10);

                        lookAtPointCamera.setX(assignedNode.getPosition().getX());
                        lookAtPointCamera.setY(assignedNode.getPosition().getY());
                        lookAtPointCamera.setZ(0);

                        glPushMatrix();
                            glLoadIdentity();

                            // Setup camera.
                            gluLookAt(positionCamera.getX(), positionCamera.getY(), positionCamera.getZ(),
                                      lookAtPointCamera.getX(), lookAtPointCamera.getY(), lookAtPointCamera.getZ(),
                                      0, 0, 1);

                            // Draw scene.

                            m_root->render(m_renderingConfiguration);
                        glPopMatrix();
                    }
                    else {
                        m_root->render(m_renderingConfiguration);
                    }
    /*
                    {
                        // Visualize camera using quaternions.
                        Position assignedNode = m_mapOfCurrentPositions[m_egoStateNodeDescriptor];
                        Point3 positionCamera(-10, 0, 8);

                        const double rotX = -cartesian::Constants::PI/2.0; // -90°
                        const double rotZ = assignedNode.getRotation().getAngleXY();

                        Quaternion qX;
                        qX.transform(rotX, Point3(1, 0, 0));

                        Quaternion qZ;
                        qZ.transform(rotZ, Point3(0, 0, 1));

                        Quaternion q;
                        q = qZ * qX;

                        positionCamera = positionCamera * qZ.transformToMatrix3x3();
                        positionCamera += assignedNode.getPosition();

                        Point3 up(0, 1, 0);
                        up = up * qZ.transformToMatrix3x3();

                        Point3 lookAtPointCamera;
                        lookAtPointCamera.setX(assignedNode.getPosition().getX());
                        lookAtPointCamera.setY(assignedNode.getPosition().getY());
                        lookAtPointCamera.setZ(0);

                        // Draw view direction.
                        glColor3f(0, 1, 0);
                        glBegin(GL_LINES);
                            glVertex3d(positionCamera.getX(), positionCamera.getY(), positionCamera.getZ());
                            glVertex3d(lookAtPointCamera.getX(), lookAtPointCamera.getY(), lookAtPointCamera.getZ());
                        glEnd();

                        // Draw up direction.
                        glColor3f(0, 0, 1);
                        glBegin(GL_LINES);
                            glVertex3d(positionCamera.getX(), positionCamera.getY(), positionCamera.getZ());
                            glVertex3d(positionCamera.getX()+5*up.getX(), positionCamera.getY()+5*up.getY(), positionCamera.getZ()+5*up.getZ());
                        glEnd();
                    }
                }
    */
    /*
                    {
                        // Visualize parallel scanner.
                        Position assignedNode = m_mapOfCurrentPositions[m_egoStateNodeDescriptor];
                        Point3 positionParallelScanner(0, 0, 1.65);

                        const double rotZ = assignedNode.getRotation().getAngleXY();

                        Quaternion qZ;
                        qZ.transform(rotZ, Point3(0, 0, 1));

                        positionParallelScanner = positionParallelScanner * qZ.transformToMatrix3x3();
                        positionParallelScanner += assignedNode.getPosition();

                        Point3 up(0, 1, 0);
                        up = up * qZ.transformToMatrix3x3();

                        Point3 lookAtPointCamera(15, 0, 0);
                        lookAtPointCamera.rotateZ(rotZ);
                        lookAtPointCamera += assignedNode.getPosition();
                        lookAtPointCamera.setZ(0);

                        // Draw view direction.
                        glColor3f(0, 1, 0);
                        glBegin(GL_LINES);
                            glVertex3d(positionParallelScanner.getX(), positionParallelScanner.getY(), positionParallelScanner.getZ());
                            glVertex3d(lookAtPointCamera.getX(), lookAtPointCamera.getY(), lookAtPointCamera.getZ());
                        glEnd();

                        // Draw up direction.
                        glColor3f(0, 0, 1);
                        glBegin(GL_LINES);
                            glVertex3d(positionParallelScanner.getX(), positionParallelScanner.getY(), positionParallelScanner.getZ());
                            glVertex3d(positionParallelScanner.getX()+5*up.getX(), positionParallelScanner.getY()+5*up.getY(), positionParallelScanner.getZ()+5*up.getZ());
                        glEnd();
                    }
    */
                }
            }

            void EnvironmentViewerGLWidget::update(TreeNode<SelectableNodeDescriptor> *node) {
                Lock l(m_rootMutex);
                if (node != NULL) {
                    modifyRenderingConfiguration(node);
                }
            }

            void EnvironmentViewerGLWidget::modifyRenderingConfiguration(TreeNode<SelectableNodeDescriptor> *node) {
                if (node != NULL) {
                    NodeDescriptor nd = node->getValue().getNodeDescriptor();
                    NodeRenderingConfiguration nrc = m_renderingConfiguration.getNodeRenderingConfiguration(nd);
                    nrc.setParameter(NodeRenderingConfiguration::ENABLED, node->getValue().isSelected());
                    m_renderingConfiguration.setNodeRenderingConfiguration(nd, nrc);

                    vector<TreeNode<SelectableNodeDescriptor>* > childrenOfNode = node->getChildren();
                    vector<TreeNode<SelectableNodeDescriptor>* >::iterator it = childrenOfNode.begin();
                    while (it != childrenOfNode.end()) {
                        TreeNode<SelectableNodeDescriptor> *child = (*it++);
                        modifyRenderingConfiguration(child);
                    }
                }
            }

            void EnvironmentViewerGLWidget::nextContainer(Container &c) {
                static int nextID = 1000;
                if (c.getDataType() == Container::USER_DATA_0) {
                    passed &= (c.getDataType() == nextID++);
                }
                if (c.getDataType() == Container::USER_DATA_1) {
                    passed &= (c.getDataType() == nextID++);
                    packetNr++;
                    cout<<"Received "<<packetNr<<" packets!"<<endl;
                }
                if (c.getDataType() == Container::USER_DATA_2) {
                    // Here, we have a valid packet.
                    //cout<<"Get a valid packet"<<endl;
//                    m_readFlag=false;
                    passed &= (c.getDataType() == nextID);
                    nextID = 1001;
                    if(packetNr>=400)//We only store data from the first 400 packets
                    {
                        cout<<"Enough!"<<endl;
                        cout<<"Frame:"<<frameIndex<<", Number of points: "<<pointIndex<<endl;
                        return;
                    }
                    //Decode Velodyne data
                    pcap::Packet packet = c.getData<pcap::Packet>();
                    pcap::PacketHeader packetHeader = packet.getHeader();
                    if(packetHeader.getIncl_len()==1248)
                    {
                        const string payload = packet.getPayload();
                        string dataToDecode=payload.substr(42);
                    
                        //A packet consists of 12 blocks with 100 bytes each. Decode each block separately.
                        int firstByte,secondByte,dataValue;
                        for(int index=0;index<12;index++)
                        {   
                            //Decode header information: 2 bytes                    
                            firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                            secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                            dataValue=ntohs(firstByte*256+secondByte);
                            //cout<<"Sensor block ID: "<<hex<<dataValue<<endl;
                            if(dataValue==0xddff)
                            {
                                upperBlock=false;
                                //cout<<"Lower block"<<endl;
                            }
                            else
                            {
                                upperBlock=true;
                                //cout<<"Upper block"<<endl;
                            }
                            dataToDecode=dataToDecode.substr(2);

                            //Decode rotational information: 2 bytes
                            firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                            secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                            dataValue=ntohs(firstByte*256+secondByte);                        
                            double rotation=static_cast<double>(dataValue/100.00);
                            //cout << "R = " << rotation << ", p = " << previousAzimuth << endl;
                            if(rotation<previousAzimuth)
                            {
                                  //m_readFlag=false;

                                //Visualize one frame based on "pointIndex", intensity[index], 
                                //where index is from 0 to intensity.size(), the same for xData[index],yData[index],zData[index]
                                /*if(frameIndex==1)
                                {
                                    for(unsigned long iii=0;iii<intensity.size();iii++)
                                    {
                                        outputData<<intensity[iii]<<".0,"<<xData[iii]<<","<<yData[iii]<<","<<zData[iii]<<endl;
                                    }
                                }*/
                                if(frameIndex==1)
                                {
                                    m_readFlag=false;
                                    m_velodyne-> deleteAllChildren();
                                    for(unsigned long iii=0;iii<intensity.size();iii++)
                                    {
                                        Point3 myPoint(xData[iii],yData[iii],zData[iii]);
                                        //Point3 color(0, 0, 1);
                                        Point3 color;
                                        if(intensity[iii]<=127){
                                            color.setX(0);
                                            color.setY(intensity[iii]*2);
                                            color.setZ(255-intensity[iii]*2);
                                        }
                                        else{
                                            color.setX((intensity[iii]-127)*2);
                                            color.setY(255-(intensity[iii]-127)*2);
                                            color.setZ(0);
                                        }

                                        hesperia::threeD::models::Point *p = new hesperia::threeD::models::Point(NodeDescriptor("velodyne"), myPoint, color, 1);
                                        m_velodyne->addChild(p);
                                    }
                                    cout<<"Visualize frame:"<<frameIndex<<endl;
                                    m_readFlag=true;

                                }
                                intensity.clear();
                                xData.clear();
                                yData.clear();
                                zData.clear();
                                pointIndex=0;
                                frameIndex++;
                                cout<<rotation<<"/"<<previousAzimuth<<"/Next frame!"<<endl;
                            }
                            previousAzimuth=rotation;
                            dataToDecode=dataToDecode.substr(2);

                            cout.unsetf(ios::hex);
                            //Decode distance information and intensity of each sensor in a block
                            for(int counter=0;counter<32;counter++)
                            {
                                //Decode distance: 2 bytes
                                int sensorID(0);
                                if(upperBlock)
                                    sensorID=counter;
                                else
                                    sensorID=counter+32;
                                firstByte=(unsigned int)(uint8_t)(dataToDecode.at(0));
                                secondByte=(unsigned int)(uint8_t)(dataToDecode.at(1));
                                dataValue=ntohs(firstByte*256+secondByte);
                                distance[counter]=static_cast<double>(dataValue*0.200/100.000);
                                    distance[counter]=distance[counter]+distCorrection[sensorID]/100;
                                double xyDistance=distance[counter]*cos(toRadian(vertCorrection[sensorID]));
                                xData.push_back(xyDistance*sin(toRadian(rotation-rotCorrection[sensorID]))
                                    -horizOffsetCorrection[sensorID]/100.0*cos(toRadian(rotation-rotCorrection[sensorID])));
                                yData.push_back(xyDistance*cos(toRadian(rotation-rotCorrection[sensorID]))
                                    +horizOffsetCorrection[sensorID]/100.0*sin(toRadian(rotation-rotCorrection[sensorID])));
                                zData.push_back(distance[counter]*sin(toRadian(vertCorrection[sensorID]))+vertOffsetCorrection[sensorID]/100.0);
    
                                //Decode intensity: 1 byte
                                intensity.push_back((unsigned int)(uint8_t)(dataToDecode.at(2)));
                                dataToDecode=dataToDecode.substr(3);
                                pointIndex++;
                            }            
                        }
                    }             
                }
                if (c.getDataType() == Container::EGOSTATE) {
                    if (m_egoStateNode != NULL) {
                        while (lidlarStream.good() && m_readFlag) {
                            char cc;
                            lidlarStream.read(&cc, sizeof(uint8_t));
                            stringstream sstr;
                            sstr << cc;
                            string s = sstr.str();
                            m_pcap.nextString(s);
                        }
                        if(!lidlarStream.good())
                            lidlarStream.close();
                    }
                }
                if (c.getDataType() == Container::CONTOUREDOBJECTS) {
                    if (m_contouredObjectsNode != NULL) {
                        Lock l(m_rootMutex);
                        ContouredObjects cos = c.getData<ContouredObjects>();
                        vector<ContouredObject> listOfContouredObjects = cos.getContouredObjects();
                        vector<ContouredObject>::iterator it = listOfContouredObjects.begin();
                        m_contouredObjectsNode->deleteAllChildren();
                        while (it != listOfContouredObjects.end()) {
                            vector<Point3> contour = (*it).getContour();
                            vector<Point3>::iterator jt = contour.begin();
                            while (jt != contour.end()) {
                                m_contouredObjectsNode->addChild(new hesperia::threeD::models::Point(NodeDescriptor("Point"), (*jt), Point3(1, 0, 0), 2));
                                jt++;
                            }
                            it++;
                        }
                    }
                }
                if (c.getDataType() == Container::ROUTE) {
                    if (m_plannedRoute != NULL) {
                        Lock l(m_rootMutex);
                        Route r = c.getData<Route>();
                        vector<Point3> listOfVertices = r.getListOfPoints();
                        const uint32_t SIZE = listOfVertices.size();
                        if (SIZE > 0) {
                            m_plannedRoute->deleteAllChildren();
                            for (uint32_t i = 0; i < SIZE - 1; i++) {
                                Point3 posA = listOfVertices.at(i);
                                posA.setZ(0.05);

                                Point3 posB = listOfVertices.at(i+1);
                                posB.setZ(0.05);

                                m_plannedRoute->addChild(new hesperia::threeD::models::Line(NodeDescriptor(), posA, posB, Point3(0, 1, 0), 6));
                            }
                        }
                    }
                }
                if (c.getDataType() == Container::DRAW_LINE) {
                    if (m_lines != NULL) {
                        Lock l(m_rootMutex);
                        hesperia::data::environment::Line line = c.getData<Line>();

                        Point3 posA = line.getA();
                        posA.setZ(0.05);

                        Point3 posB = line.getB();
                        posB.setZ(0.05);

                        m_lines->addChild(new hesperia::threeD::models::Line(NodeDescriptor(), posA, posB, Point3(1, 0, 0), 6));
                    }
                }
                if (c.getDataType() == Container::OBSTACLE) {
                    if (m_obstaclesRoot != NULL) {
                        Lock l(m_rootMutex);
                        Obstacle obstacle = c.getData<Obstacle>();
                        switch (obstacle.getState()) {
                            case Obstacle::REMOVE:
                            {
                                // Remove obstacle.
                                map<uint32_t, Node*>::iterator result = m_mapOfObstacles.find(obstacle.getID());
                                if (result != m_mapOfObstacles.end()) {
                                    // Remove child from scene graph node.
                                    m_obstaclesRoot->removeChild(result->second);

                                    // Remove entry from map.
                                    m_mapOfObstacles.erase(result);
                                }
                            }
                            break;

                            case Obstacle::UPDATE:
                            {
                                map<uint32_t, Node*>::iterator result = m_mapOfObstacles.find(obstacle.getID());
                                if (result != m_mapOfObstacles.end()) {
                                    // Remove child from scene graph node.
                                    m_obstaclesRoot->removeChild(result->second);

                                    // Remove entry from map.
                                    m_mapOfObstacles.erase(result);
                                }
                                // Update obstacle.
                                TransformGroup *contourTG = new TransformGroup();
                                vector<Point3> contour = obstacle.getPolygon().getVertices();
                                // Close polygons.
                                Point3 p = contour.at(0);
                                contour.push_back(p);
                                for (uint32_t k = 0; k < contour.size() - 1; k++) {
                                    Point3 A = contour.at(k); A.setZ(0.5);
                                    Point3 B = contour.at(k+1); B.setZ(0.5);

                                    contourTG->addChild(new hesperia::threeD::models::Line(NodeDescriptor(), A, B, Point3(0, 1, 0), 2));
                                }
                                m_mapOfObstacles[obstacle.getID()] = contourTG;
                                m_obstaclesRoot->addChild(contourTG);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
} // plugins::environmentviewer
