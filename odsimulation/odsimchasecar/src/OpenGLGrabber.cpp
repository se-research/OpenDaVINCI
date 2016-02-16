/**
 * chasecar - Render video from chasing the ego car
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

#include <GL/gl.h>
#include <GL/glut.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "OpenGLGrabber.h"
#include "core/base/FIFOQueue.h"
#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "core/wrapper/ImageFactory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/environment/Obstacle.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/Polygon.h"
#include "hesperia/data/environment/Position.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/decorator/DecoratorFactory.h"
#include "hesperia/threeD/loaders/OBJXArchive.h"
#include "hesperia/threeD/loaders/OBJXArchiveFactory.h"
#include "hesperia/threeD/models/Grid.h"
#include "hesperia/threeD/models/Line.h"
#include "hesperia/threeD/models/XYZAxes.h"

namespace hesperia { namespace data { namespace camera { class ImageGrabberCalibration; } } }
namespace hesperia { namespace scenario { class SCNXArchive; } }
namespace hesperia { namespace threeD { class Node; } }

namespace chasecar {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::camera;
    using namespace hesperia::data::environment;
    using namespace core::io;
    using namespace hesperia::scenario;
    using namespace hesperia::threeD;
    using namespace hesperia::threeD::decorator;
    using namespace hesperia::threeD::models;
    using namespace hesperia::threeD::loaders;

    OpenGLGrabber::OpenGLGrabber(const KeyValueConfiguration &kvc, const ImageGrabberID &imageGrabberID, const ImageGrabberCalibration &imageGrabberCalibration, hesperia::data::environment::EgoState &egoState, core::base::FIFOQueue &obstacles) :
            ImageGrabber(imageGrabberID, imageGrabberCalibration),
            m_render(OpenGLGrabber::IN_CAR),
            m_kvc(kvc),
            m_image(),
            m_sharedMemory(),
            m_root(),
            m_car(),
            m_sensors(),
            m_mapOfObstacles(),
            m_egoState(egoState),
            m_FIFO_Obstacles(obstacles) {

        const URL urlOfSCNXFile(m_kvc.getValue<string>("global.scenario"));
        const bool SHOW_GRID = (m_kvc.getValue<uint8_t>("global.showgrid") == 1);
        if (urlOfSCNXFile.isValid()) {
            m_root = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());
            m_car = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());
            m_sensors = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());

            SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

            // Read scnxArchive and decorate it for getting displayed in an OpenGL scene.
            const bool SHOW_LANE_CONNECTORS = false;
            m_root->addChild(DecoratorFactory::getInstance().decorate(scnxArchive, SHOW_LANE_CONNECTORS));
            if (SHOW_GRID) {
                m_root->addChild(new XYZAxes(NodeDescriptor("XYZAxes")));
                m_root->addChild(new Grid(NodeDescriptor("Grid"), 10, 2));
            }

            const URL urlOfCar(m_kvc.getValue<string>("global.car"));
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
                        m_car->addChild(objxArchive->createTransformGroup(NodeDescriptor("Car")));
                    }
                }
            }

            m_sharedMemory = core::wrapper::SharedMemoryFactory::createSharedMemory("ChaseCar", 640 * 480 * 3);

            m_image = core::SharedPointer<core::wrapper::Image>(core::wrapper::ImageFactory::getInstance().getImage(640, 480, core::wrapper::Image::BGR_24BIT, static_cast<char*>(m_sharedMemory->getSharedMemory())));

            if (m_image.isValid()) {
                cerr << "OpenGLGrabber initialized." << endl;
            }
        }
    }

    OpenGLGrabber::~OpenGLGrabber() {}

    void OpenGLGrabber::delay() {
        Thread::usleepFor(1000 * 10);
    }

    core::SharedPointer<core::wrapper::Image> OpenGLGrabber::getNextImage() {
        if ( (m_sharedMemory.isValid()) && (m_sharedMemory->isValid()) ) {
            m_sharedMemory->lock();

            // Render the image right before grabbing it.
            switch (m_render) {
                case  OpenGLGrabber::IN_CAR:
                    renderNextImageInCar();

                    m_FIFO_Obstacles.clear();
                break;
                case  OpenGLGrabber::CHASE_CAR:
                    renderNextImageChaseCar();

                    m_FIFO_Obstacles.clear();
                break;
                case  OpenGLGrabber::CHASE_CAR_SENSORS:
                {
                    const uint32_t size = m_FIFO_Obstacles.getSize();
                    for(uint32_t i = 0; i < size; i++) {
                        Container c = m_FIFO_Obstacles.leave();
                        if (c.getDataType() == Obstacle::ID()) {
                            Obstacle obstacle = c.getData<Obstacle>();

                            // Check if sensor FOV-"Obstacle":
                            if (obstacle.getObstacleID() >= 9000) {
                                switch (obstacle.getState()) {
                                    case Obstacle::REMOVE:
                                    {
                                        // Remove obstacle.
                                        map<uint32_t, Node*>::iterator result = m_mapOfObstacles.find(obstacle.getObstacleID());
                                        if (result != m_mapOfObstacles.end()) {
                                            // Remove child from scene graph node.
                                            m_sensors->removeChild(result->second);

                                            // Remove entry from map.
                                            m_mapOfObstacles.erase(result);
                                        }
                                    }
                                    break;

                                    case Obstacle::UPDATE:
                                    {
                                        map<uint32_t, Node*>::iterator result = m_mapOfObstacles.find(obstacle.getObstacleID());
                                        if (result != m_mapOfObstacles.end()) {
                                            // Remove child from scene graph node.
                                            m_sensors->removeChild(result->second);

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
                                        m_mapOfObstacles[obstacle.getObstacleID()] = contourTG;

                                        m_sensors->addChild(contourTG);
                                    }
                                    break;
                                }
                            }
                        }
                    }

                    renderNextImageChaseCarSensors();
                }
                break;
            }

            // TODO Read pixels using BGRA!!!
            glReadBuffer(GL_BACK);
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            glReadPixels(0, 0, m_image->getWidth(), m_image->getHeight(), GL_BGR, GL_UNSIGNED_BYTE, m_sharedMemory->getSharedMemory());

            // Flip the image horizontally.
            m_image->flipHorizontally();

            m_sharedMemory->unlock();
        }

        return m_image;
    }

    void OpenGLGrabber::renderNextImageInCar() {
        RenderingConfiguration r = RenderingConfiguration();
        m_root->render(r);
    }

    void OpenGLGrabber::renderNextImageChaseCar() {
        renderNextImageChaseCarSensors(false);
    }

    void OpenGLGrabber::renderNextImageChaseCarSensors() {
        renderNextImageChaseCarSensors(true);
    }

    void OpenGLGrabber::renderNextImageChaseCarSensors(bool renderSensors) {
        Position assignedNode = m_egoState;
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
            RenderingConfiguration r = RenderingConfiguration();
            m_root->render(r);

            // Update ego position.
            Point3 dir(0, 0, m_egoState.getRotation().getAngleXY());
            m_car->setRotation(dir);
            m_car->setTranslation(m_egoState.getPosition());
            m_car->render(r);

            if (renderSensors) {
                // Render sensor FOVs
                m_sensors->render(r);
            }

        glPopMatrix();
    }

} // chasecar
