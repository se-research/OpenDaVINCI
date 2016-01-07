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

#include <Qt/qevent.h>
#include <Qt/qtimer.h>
#include <qpainter.h>
#include <qpen.h>
#include <qrect.h>
#include <qtransform.h>

#include <sstream>
#include <string>
#include <vector>

#include "core/opendavinci.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "core/base/TreeNode.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "generated/cartesian/Constants.h"
#include "hesperia/data/environment/Obstacle.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Polygon.h"
#include "hesperia/data/planning/Route.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/scenegraph/SceneNode.h"
#include "hesperia/scenegraph/models/SimpleCar.h"
#include "hesperia/scenegraph/models/XYAxes.h"
#include "hesperia/scenegraph/models/Grid.h"
#include "hesperia/scenegraph/primitives/Line.h"
#include "hesperia/scenegraph/primitives/Polygon.h"
#include "hesperia/scenegraph/renderer/SceneNodeRenderingConfiguration.h"
#include "hesperia/scenegraph/transformation/SceneGraphFactory.h"
#include "plugins/PlugIn.h"
#include "plugins/birdseyemap/BirdsEyeMapMapWidget.h"
#include "plugins/birdseyemap/BirdsEyeMapRenderer.h"
#include "plugins/birdseyemap/CameraAssignableNodesListener.h"
#include "plugins/birdseyemap/SelectableNodeDescriptor.h"
#include "plugins/birdseyemap/TreeNodeVisitor.h"

namespace hesperia { namespace scenario { class SCNXArchive; } }

namespace cockpit {
    namespace plugins {
        namespace birdseyemap {

            using namespace core::base;
            using namespace core::data;
            using namespace core::exceptions;
            using namespace core::io;
            using namespace hesperia::data::environment;
            using namespace hesperia::data::environment;
            using namespace hesperia::scenegraph;
            using namespace hesperia::scenegraph::models;
            using namespace hesperia::scenegraph::renderer;

            BirdsEyeMapMapWidget::BirdsEyeMapMapWidget(const PlugIn &plugIn, QWidget *prnt, CameraAssignableNodesListener &canl, SelectableNodeDescriptorTreeListener &sndtl) :
                QWidget(prnt),
                m_plugIn(plugIn),
                m_renderingConfiguration(),
                m_selectableNodeDescriptorTree(NULL),
                m_selectableNodeDescriptorTreeListener(sndtl),
                m_cameraAssignableNodesListener(canl),
                m_listOfCameraAssignableNodes(),
                m_cameraAssignedNodeDescriptor(),
                m_timer(NULL),
                m_rootMutex(),
                m_root(new SceneNode()),
                m_scales(new SceneNode()),
                m_stationaryElements(new SceneNode()),
                m_dynamicElements(new SceneNode()),
                m_measurements(new SceneNode()),
                m_scaleFactor(9.99995),
                m_centerOfMap(),
                m_mouseOld(-1, -1, 0),
                m_numberOfReceivedEgoStates(0),
                m_egoState(),
                m_lastEgoState(),
                m_egoCar(NULL),
                m_egoCarTrace(NULL),
                m_obstaclesRoot(NULL),
                m_mapOfObstacles(),
                m_plannedRoute(NULL) {

                m_root->addChild(m_scales);
                m_root->addChild(m_stationaryElements);
                m_root->addChild(m_dynamicElements);
                m_root->addChild(m_measurements);

                createSceneGraph();

                // Setup selectable scene graph.
                m_selectableNodeDescriptorTree = new TreeNode<SelectableNodeDescriptor>();
                TreeNode<SelectableNodeDescriptor> *scalesElements = new TreeNode<SelectableNodeDescriptor>();
                scalesElements->setValue(SelectableNodeDescriptor(SceneNodeDescriptor("Scales"), false));
                m_selectableNodeDescriptorTree->addChild(scalesElements);

                TreeNode<SelectableNodeDescriptor> *stationaryElements = new TreeNode<SelectableNodeDescriptor>();
                stationaryElements->setValue(SelectableNodeDescriptor(SceneNodeDescriptor("Stationary Elements"), false));
                m_selectableNodeDescriptorTree->addChild(stationaryElements);

                TreeNode<SelectableNodeDescriptor> *dynamicElements = new TreeNode<SelectableNodeDescriptor>();
                dynamicElements->setValue(SelectableNodeDescriptor(SceneNodeDescriptor("Dynamic Elements"), false));
                m_selectableNodeDescriptorTree->addChild(dynamicElements);

                TreeNode<SelectableNodeDescriptor> *measuredData = new TreeNode<SelectableNodeDescriptor>();
                measuredData->setValue(SelectableNodeDescriptor(SceneNodeDescriptor("Measured Data"), false));
                m_selectableNodeDescriptorTree->addChild(measuredData);

                // Collect data from scene graph using a visitor.
                TreeNodeVisitor tnvScaleElements(m_renderingConfiguration, scalesElements);
                m_scales->accept(tnvScaleElements);

                TreeNodeVisitor tnvStationaryElements(m_renderingConfiguration, stationaryElements);
                m_stationaryElements->accept(tnvStationaryElements);

                TreeNodeVisitor tnvDynamicElements(m_renderingConfiguration, dynamicElements);
                m_dynamicElements->accept(tnvDynamicElements);

                TreeNodeVisitor tnvMeasuredData(m_renderingConfiguration, measuredData);
                m_measurements->accept(tnvMeasuredData);

                // Inform listener about selectable SceneNodeDescriptors.
                m_selectableNodeDescriptorTreeListener.update(m_selectableNodeDescriptorTree);

                // Inform listener about assignable nodes.
                m_cameraAssignableNodesListener.updateListOfCameraAssignableNodes(m_listOfCameraAssignableNodes);

                // Timer repaint.
                m_timer = new QTimer(this);
                connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
                m_timer->start(50);
            }

            BirdsEyeMapMapWidget::~BirdsEyeMapMapWidget() {
                m_timer->stop();
                OPENDAVINCI_CORE_DELETE_POINTER(m_root);
            }

            void BirdsEyeMapMapWidget::createSceneGraph() {
                // Setup surroundings.
                const URL urlOfSCNXFile(m_plugIn.getKeyValueConfiguration().getValue<string>("global.scenario"));
                if (urlOfSCNXFile.isValid()) {
                    hesperia::scenario::SCNXArchive &scnxArchive = hesperia::scenario::SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

                    // Read scnxArchive and transform it into renderable scene graph.
                    SceneNode *surroundings = hesperia::scenegraph::transformation::SceneGraphFactory::getInstance().transform(scnxArchive);

                    if (surroundings != NULL) {
                        surroundings->setSceneNodeDescriptor(SceneNodeDescriptor("Surroundings"));
                        m_stationaryElements->addChild(surroundings);
                    }
                }

                // Setup scales.
                m_scales->addChild(new Grid(SceneNodeDescriptor("Grid")));
                m_scales->addChild(new XYAxes(SceneNodeDescriptor("X/Y-Axes"), Point3(1, 1, 1), 2));

                ///////////////////////////////////////////////////////////////

                // Setup egoCar.
                SceneNodeDescriptor egoStateNodeDescriptor("EgoCar");
                m_egoCar = new SimpleCar(egoStateNodeDescriptor, 4, 2, Point3(), 0, Point3(1, 0.84, 0), 2);
                m_dynamicElements->addChild(m_egoCar);

                m_egoCarTrace = new SceneNode(SceneNodeDescriptor("EgoCar (Trace)"));
                m_dynamicElements->addChild(m_egoCarTrace);

                m_plannedRoute = new SceneNode(SceneNodeDescriptor("Planned Route"));
                m_dynamicElements->addChild(m_plannedRoute);

                // EgoCar is assignable.
                m_listOfCameraAssignableNodes.push_back(egoStateNodeDescriptor);

                ///////////////////////////////////////////////////////////////

                // Measurements.
                m_obstaclesRoot = new SceneNode(SceneNodeDescriptor("Obstacles"));
                m_measurements->addChild(m_obstaclesRoot);
            }

            void BirdsEyeMapMapWidget::setZoomLevel(float val) {
                Lock l(m_rootMutex);
                if ((val < 1.0) && (val > 0)) {
                    const double scaleMax = 20;
                    const double scaleMin = 0.0001;

                    m_scaleFactor = (scaleMax - scaleMin) * val;
                }
            }

            void BirdsEyeMapMapWidget::assignCameraTo(const SceneNodeDescriptor &snd) {
                Lock l(m_rootMutex);
                m_cameraAssignedNodeDescriptor = snd;
            }

            void BirdsEyeMapMapWidget::mouseReleaseEvent(QMouseEvent */*evnt*/) {
                m_mouseOld.setX(-1);
                m_mouseOld.setY(-1);
            }

            void BirdsEyeMapMapWidget::mouseMoveEvent(QMouseEvent *evnt) {
                if (this->rect().contains(evnt->pos())) {

                    if ((m_mouseOld.getX() > -1) && (m_mouseOld.getY() > 0)) {
                        int deltaX = (evnt->x() - m_mouseOld.getX());
                        int deltaY = (evnt->y() - m_mouseOld.getY());

                        {
                            Lock l(m_rootMutex);
                            m_centerOfMap += Point3(deltaX, deltaY, 0);
                        }
                    }

                    m_mouseOld.setX(evnt->x());
                    m_mouseOld.setY(evnt->y());
                 }
            }

            void BirdsEyeMapMapWidget::paintEvent(QPaintEvent *evt) {
                Lock l(m_rootMutex);
                const double scaleMax = 20;
                const double scaleMin = 0.0001;

                if (m_scaleFactor < scaleMin) {
                    m_scaleFactor = scaleMin;
                } else if (m_scaleFactor > scaleMax) {
                    m_scaleFactor = scaleMax;
                }

                QPainter painter(this);
                painter.setRenderHint(QPainter::Antialiasing);

                // White background.
                painter.fillRect(evt->rect(), QBrush(Qt::darkGray));

                QPen pen;

                // Define image coordinates: +Y = 6am, -Y = 12am, -X = 9am, +X = 3am, (0, 0) = upper left corner.
                QTransform imageCoordinates;
                imageCoordinates.translate(0, 0);
                imageCoordinates.scale(1, 1);
                imageCoordinates.rotate(0);

                // Define cartesian coordinates: +Y = 12am, -Y = 6am, -X = 9am, +X = 3am, (0, 0) = image center, scaling = 1px=1mm=0.001m
                QTransform cartesianCoordinates;

                if (m_cameraAssignedNodeDescriptor.getName() == "EgoCar") {
                    // This applies map translation wrt. vehicle-fixed orientation.
                    cartesianCoordinates.translate((evt->rect().width() / 2) + m_egoState.getPosition().getX()*10, (evt->rect().height() / 2) + m_egoState.getPosition().getY()*10);
                    cartesianCoordinates.rotateRadians(m_egoState.getRotation().getAngleXY()+(-90*cartesian::Constants::DEG2RAD));
                }
                else {
                    // Fixed translation to center of window.
//                    cartesianCoordinates.translate(evt->rect().width() / 2, evt->rect().height() / 2);

                    // This applies map translation based on user configuration.
                    cartesianCoordinates.rotate(0);
                    cartesianCoordinates.translate((evt->rect().width() / 2) + m_centerOfMap.getX(), (evt->rect().height() / 2) + m_centerOfMap.getY());
                }

                // Ensure pixelsPerMeter.
                cartesianCoordinates.scale(0.001, -0.001);

                // This defines the scaling.
                QTransform magnify;
                magnify.scale(m_scaleFactor, m_scaleFactor);

                // This transformation scales the cartesian coordinate system.
                QTransform scaledCartesianCoordinates;
                scaledCartesianCoordinates = magnify * cartesianCoordinates;

                {
                    // Update position of ego car and renderer it.
                    m_egoCar->setPosition(m_egoState.getPosition(), m_egoState.getRotation().getAngleXY());

                    // Now, draw everything in the scaled cartesian coordinate frame.
                    painter.setTransform(scaledCartesianCoordinates);

                    // Create a renderer for the scene graph.
                    BirdsEyeMapRenderer renderer(&painter, m_renderingConfiguration);

                    // Render m_root and all its children.
                    m_root->accept(renderer);
                }

                painter.end();
            }

            void BirdsEyeMapMapWidget::update(TreeNode<SelectableNodeDescriptor> *node) {
                Lock l(m_rootMutex);
                if (node != NULL) {
                    modifyRenderingConfiguration(node);
                }
            }

            void BirdsEyeMapMapWidget::resetEgoTrace() {
                Lock l(m_rootMutex);
                if (m_egoCarTrace != NULL) {
                    m_egoCarTrace->deleteAllChildren();
                }
            }

            void BirdsEyeMapMapWidget::modifyRenderingConfiguration(TreeNode<SelectableNodeDescriptor> *node) {
                if (node != NULL) {
                    SceneNodeDescriptor snd = node->getValue().getSceneNodeDescriptor();
                    SceneNodeRenderingConfiguration snrc = m_renderingConfiguration.getSceneNodeRenderingConfiguration(snd);
                    snrc.setParameter(SceneNodeRenderingConfiguration::ENABLED, node->getValue().isSelected());
                    m_renderingConfiguration.setSceneNodeRenderingConfiguration(snd, snrc);

                    vector<TreeNode<SelectableNodeDescriptor>* > childrenOfNode = node->getChildren();
                    vector<TreeNode<SelectableNodeDescriptor>* >::iterator it = childrenOfNode.begin();
                    while (it != childrenOfNode.end()) {
                        TreeNode<SelectableNodeDescriptor> *child = (*it++);
                        modifyRenderingConfiguration(child);
                    }
                }
            }

            void BirdsEyeMapMapWidget::nextContainer(Container &c) {
                if (c.getDataType() == Container::EGOSTATE) {
                    Lock l(m_rootMutex);
                    m_egoState = c.getData<EgoState>();
                    m_numberOfReceivedEgoStates++;

                    if ( (m_numberOfReceivedEgoStates % 10) == 0 ) {
                        hesperia::scenegraph::primitives::Line *line = new hesperia::scenegraph::primitives::Line(m_egoCarTrace->getSceneNodeDescriptor(), m_lastEgoState.getPosition(), m_egoState.getPosition(), Point3(1, 0.84, 0), 2);
                        m_egoCarTrace->addChild(line);

                        m_lastEgoState = m_egoState;
                    }
                }

                if (c.getDataType() == Container::ROUTE) {
                    if (m_plannedRoute != NULL) {
                        Lock l(m_rootMutex);
                        hesperia::data::planning::Route r = c.getData<hesperia::data::planning::Route>();
                        vector<Point3> listOfVertices = r.getListOfPoints();
                        const uint32_t SIZE = listOfVertices.size();
                        if (SIZE > 0) {
                            m_plannedRoute->deleteAllChildren();
                            for (uint32_t i = 0; i < SIZE - 1; i++) {
                                Point3 posA = listOfVertices.at(i);
                                posA.setZ(0.05);

                                Point3 posB = listOfVertices.at(i+1);
                                posB.setZ(0.05);

                                m_plannedRoute->addChild(new hesperia::scenegraph::primitives::Line(m_plannedRoute->getSceneNodeDescriptor(), posA, posB, Point3(0.84, 1, 1), 4));
                            }
                        }
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
                                map<uint32_t, SceneNode*>::iterator result = m_mapOfObstacles.find(obstacle.getObstacleID());
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
                                map<uint32_t, SceneNode*>::iterator result = m_mapOfObstacles.find(obstacle.getObstacleID());
                                if (result != m_mapOfObstacles.end()) {
                                    // Remove child from scene graph node.
                                    m_obstaclesRoot->removeChild(result->second);

                                    // Remove entry from map.
                                    m_mapOfObstacles.erase(result);
                                }
                                stringstream contourName;
                                contourName << "Obstacles";
                                hesperia::scenegraph::primitives::Polygon *contour = new hesperia::scenegraph::primitives::Polygon(SceneNodeDescriptor(contourName.str()), obstacle.getPolygon().getVertices(), Point3(0, 1, 0), 2);
                                m_mapOfObstacles[obstacle.getObstacleID()] = contour;
                                m_obstaclesRoot->addChild(contour);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
} // plugins::birdseyemap
