/**
 * libvehiclecontext - Models for simulating automotive systems.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <ctime>
#include <iostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcontext/base/SendContainerToSystemsUnderTest.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/generated/coredata/image/SharedImage.h"
#include "opendlv/data/camera/ImageGrabberCalibration.h"
#include "opendlv/data/camera/ImageGrabberID.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/vehiclecontext/model/CameraModel.h"
#include "opendlv/vehiclecontext/model/OpenGLGrabber.h"

namespace odcore { namespace wrapper { class Time; } }

namespace opendlv { namespace vehiclecontext {
    namespace model {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;
        using namespace odcontext::base;
        using namespace opendlv::data;
        using namespace opendlv::data::camera;
        using namespace opendlv::data::environment;

        CameraModel* CameraModel::m_singleton = NULL;

        void display_func() {
            CameraModel::getInstance().display();
        }

        void resize_func(int32_t w, int32_t h) {
            CameraModel::getInstance().resize(w, h);
            glutPostRedisplay();
        }

        void idle_func() {
            glutPostRedisplay();
        }

        CameraModel::CameraModel(const string &configuration) :
            m_kvc(),
            m_freq(0),
            m_renderWindow(0),
            m_egoState(),
            m_grabber(NULL),
            m_image(),
            m_sharedImage(),
            m_translationX(0),
            m_translationY(0),
            m_scale(1),
            m_phi(0),
            m_theta(0),
            m_height(0),
            m_mouseX(0),
            m_mouseY(0),
            m_mouseButton(0) {

            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        CameraModel::CameraModel(const float &freq, const string &configuration) :
            m_kvc(),
            m_freq(freq),
            m_renderWindow(0),
            m_egoState(),
            m_grabber(NULL),
            m_image(),
            m_sharedImage(),
            m_translationX(0),
            m_translationY(0),
            m_scale(1),
            m_phi(0),
            m_theta(0),
            m_height(0),
            m_mouseX(0),
            m_mouseY(0),
            m_mouseButton(0) {
            // Create configuration object.
            stringstream sstrConfiguration;
            sstrConfiguration.str(configuration);
            m_kvc.readFrom(sstrConfiguration);
        }

        CameraModel::~CameraModel() {}

        CameraModel& CameraModel::getInstance() {
            return *m_singleton;
        }

        float CameraModel::getFrequency() const {
            return m_freq;
        }

        void CameraModel::setup() {
            CameraModel::m_singleton = this;

            string argv0("odsimcamera");
            int32_t argc = 1;
            char **argv;
            argv = new char*[1];
            argv[0] = const_cast<char*>(argv0.c_str());
            glutInit(&argc, argv);

            initGlut();
            initGL();

            ImageGrabberID id("Test");
            ImageGrabberCalibration calibration;

            m_grabber = new OpenGLGrabber(m_kvc, id, calibration);
        }

        void CameraModel::tearDown() {
            // Leave glut main loop.
            glutLeaveMainLoop();

            OPENDAVINCI_CORE_DELETE_POINTER(m_grabber);

            glutDestroyWindow(m_renderWindow);
        }

        void CameraModel::initGlut() {
            glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGB);
            glutInitWindowPosition(50, 50);
            glutInitWindowSize(640, 480);
            m_renderWindow = glutCreateWindow("odsimcamera");
            glutDisplayFunc(display_func);
            glutIdleFunc(idle_func);
            glutReshapeFunc(resize_func);
        }

        void CameraModel::initGL() {
            glEnable(GL_DEPTH_TEST);
            glClearColor(0, 0, 0, 0);
        }

        void CameraModel::drawScene() {
            static uint32_t frameCounter = 0;
            static clock_t start = clock();

            // Render next image.
            m_image = m_grabber->getNextImage();

            frameCounter++;

            // Share information about this image.
            if (m_image.isValid()) {
                m_sharedImage.setWidth(m_image->getWidth());
                m_sharedImage.setHeight(m_image->getHeight());
                // TODO: Refactor me!
                m_sharedImage.setBytesPerPixel(3);
                m_sharedImage.setName("odsimcamera");
            }

            if ((frameCounter % 20) == 0) {
                clock_t end = clock();
                clock_t duration = end - start;
                double seconds = (1000.0 * duration) / CLOCKS_PER_SEC;
                seconds /= 1000.0;
                cerr << "FPS: " << (frameCounter / seconds) << endl;
                frameCounter = 0;
                start = clock();
            }

            m_grabber->delay();
        }

        void CameraModel::display() {
            glClearColor(0, 0.58, 0.78, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glLoadIdentity();

            Point3 dir = m_egoState.getRotation();
            Point3 target(15, 0, 0);
            target.rotateZ(dir.getAngleXY());
            target += m_egoState.getPosition();

//            cerr << "Look from: " << m_egoState.getPosition().toString() << "/angle: " << dir.getAngleXY() << endl;
//            cerr << "Look to: " << target.toString() << endl << endl;

            gluLookAt(m_egoState.getPosition().getX(), m_egoState.getPosition().getY(), 2.8,
                      target.getX(), target.getY(), 0,
                      0, 0, 1);


            // First, apply the translation.
            glTranslatef(m_translationX, m_translationY, 0);

            // Second, rotate the model.
            glRotatef(m_theta, 1, 0, 0);
            glRotatef(m_phi, 0, 1, 0);

            // Third, scale the model.
            glScalef(m_scale, m_scale, m_scale);

            glPushMatrix();
                drawScene();
            glPopMatrix();

            glutSwapBuffers();
        }

        void CameraModel::resize(int32_t w, int32_t h) {
            h = (h == 0) ? 1 : h;
            m_height = h;
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60, w/h, 1, 20);
            glMatrixMode(GL_MODELVIEW);
        }

        void CameraModel::step(const odcore::wrapper::Time &t, SendContainerToSystemsUnderTest &sender) {
            (void)sender;
            cerr << "[CameraModel] Call for t = " << t.getSeconds() << "." << t.getPartialMicroseconds() << ", containing " << getFIFO().getSize() << " containers." << endl;

            // Get last EgoState.
            bool hasEgoState = false;
            const uint32_t SIZE = getFIFO().getSize();
            for (uint32_t i = 0; i < SIZE; i++) {
                Container c = getFIFO().leave();
                cerr << "[CameraModel] Received: " << c.toString() << endl;
                if (c.getDataType() == Container::EGOSTATE) {
                    m_egoState = c.getData<EgoState>();
                    hasEgoState = true;
                }
            }

            ////////////////////////////////////////////////////////////////////

            if (hasEgoState) {
                // Trigger event processing.
                glutMainLoopEvent();

                // Trigger a repaint event.
                glutPostRedisplay();

                // Send next image.
                Container c(Container::SHARED_IMAGE, m_sharedImage);
                sender.sendToSystemsUnderTest(c);
            }
        }

    }
} } // opendlv::vehiclecontext::model
