/**
 * camgen - Camera stream generator (part of simulation environment)
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

#include <ctime>

#include <iostream>

#include <GL/gl.h>
#include <GL/freeglut.h>

#include <opencv/highgui.h>
#include <opencv/cxcore.h>

#include "core/macros.h"
#include "core/base/Thread.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "GeneratedHeaders_AutomotiveData.h"
#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/camera/ImageGrabberCalibration.h"
#include "hesperia/data/camera/ImageGrabberID.h"
#include "GeneratedHeaders_CoreData.h"

#include "CamGen.h"

namespace camgen {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data;
    using namespace hesperia::data::camera;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;

    CamGen* CamGen::m_singleton = NULL;

    void exit_func() {
        CamGen::getInstance().tearDown();
    }

    void display_func() {
        CamGen::getInstance().display();
    }

    void resize_func(int32_t w, int32_t h) {
        CamGen::getInstance().resize(w, h);
        glutPostRedisplay();
    }

    void idle_func() {
        glutPostRedisplay();
    }

    void keyboard_func(unsigned char key, int32_t x, int32_t y) {
        CamGen::getInstance().processKey(key, x, y);
    }

    void mousemotion_func(int32_t x, int32_t y) {
        CamGen::getInstance().processMouseMotion(x, y);
    }

    void mouseevent_func(int32_t button, int32_t state, int32_t x, int32_t y) {
        CamGen::getInstance().processMouseEvent(button, state, x, y);
    }

    CamGen::CamGen(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimcamera"),
        m_egoState(),
        m_grabber(NULL),
        m_image(),
        m_translationX(0),
        m_translationY(0),
        m_scale(1),
        m_phi(0),
        m_theta(0),
        m_height(0),
        m_mouseX(0),
        m_mouseY(0),
        m_mouseButton(0) {

        CamGen::m_singleton = this;

        int32_t ac = argc;
        glutInit(&ac, argv);
    }

    CamGen::~CamGen() {
        OPENDAVINCI_CORE_DELETE_POINTER(m_grabber);
    }

    CamGen& CamGen::getInstance() {
        return *m_singleton;
    }

    void CamGen::setUp() {
        // Catch system exit.
        atexit(exit_func);

        initGlut();
        initGL();

        // Setup grabber.
        KeyValueConfiguration kvc = getKeyValueConfiguration();

        ImageGrabberID id("Test");
        ImageGrabberCalibration calibration;

        m_grabber = new OpenGLGrabber(kvc, id, calibration, m_egoState);
    }

    void CamGen::tearDown() {}

    void CamGen::initGlut() {
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE| GLUT_RGB);
        glutInitWindowPosition(50, 50);
        glutInitWindowSize(640, 480);
        glutCreateWindow("odsimcamera");
        glutDisplayFunc(display_func);
        glutIdleFunc(idle_func);
        glutReshapeFunc(resize_func);
        glutKeyboardFunc(keyboard_func);
        glutMotionFunc(mousemotion_func);
        glutMouseFunc(mouseevent_func);
    }

    void CamGen::initGL() {
        glEnable(GL_DEPTH_TEST);
        glClearColor(0, 0, 0, 0);
    }

    void CamGen::drawScene() {
        static uint32_t frameCounter = 0;
        static clock_t start = clock();

        Container container = getKeyValueDataStore().get(Container::EGOSTATE);
        m_egoState = container.getData<hesperia::data::environment::EgoState>();
        m_image = m_grabber->getNextImage();

        frameCounter++;

        // Share information about this image.
        if (m_image.isValid()) {
            coredata::image::SharedImage si;
            si.setWidth(m_image->getWidth());
            si.setHeight(m_image->getHeight());
            // TODO: Refactor me!
            si.setBytesPerPixel(3);
            si.setName("odsimcamera");

            Container c(si);
            getConference().send(c);
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

    void CamGen::processMouseMotion(int32_t x, int32_t y) {
        // Left mouse button pressed.
        if (m_mouseButton == GLUT_LEFT_BUTTON) {
            // Rotation around the X-axis.
            m_theta += 0.2f * (m_mouseY - y);

            // Rotation around the Y-axis.
            m_phi += 0.2f * (m_mouseX - x);
        }

        // Right mouse button pressed.
        if (m_mouseButton == GLUT_RIGHT_BUTTON) {
            // Scaling into the scene.
            m_scale *= exp(2.0 * (y - m_mouseY)/m_height);
        }

        // Save mouse position for later usage.
        m_mouseX = x;
        m_mouseY = y;
    }

    void CamGen::processMouseEvent(int32_t button, int32_t state, int32_t x, int32_t y) {
        if (state == GLUT_DOWN) {
            m_mouseButton = button;
            m_mouseX = x;
            m_mouseY = y;
        }
        else {
            m_mouseButton = 0;
        }
    }

    void CamGen::processKey(unsigned char key, int32_t /*x*/, int32_t /*y*/) {
        if (key == 'w') {
            m_translationY += 0.5f;
        }
        if (key == 's') {
            m_translationY -= 0.5f;
        }
        if (key == 'a') {
            m_translationX -= 0.5f;
        }
        if (key == 'd') {
            m_translationX += 0.5f;
        }

        if (key == '1') {
            m_grabber->m_render = OpenGLGrabber::INTRINSIC_PATTERN;
        }
        if (key == '2') {
            m_grabber->m_render = OpenGLGrabber::EXTRINSIC_PATTERN;
        }
        if (key == '3') {
            m_grabber->m_render = OpenGLGrabber::WORLD;
        }

        glutPostRedisplay();
    }

    void CamGen::display() {
        glClearColor(0, 0.58, 0.78, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        Point3 dir = m_egoState.getRotation();
        Point3 target(15, 0, 0);
        target.rotateZ(dir.getAngleXY());
        target += m_egoState.getPosition();

//        cerr << "Look from: " << m_egoState.getPosition().toString() << "/angle: " << dir.getAngleXY() << endl;
//        cerr << "Look to: " << target.toString() << endl << endl;

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

    void CamGen::resize(int32_t w, int32_t h) {
        h = (h == 0) ? 1 : h;
        m_height = h;
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, w/h, 1, 20);
        glMatrixMode(GL_MODELVIEW);
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CamGen::body() {
        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Trigger event processing.
            glutMainLoopEvent();

            // Trigger a repaint event.
            glutPostRedisplay();
        }

        // Leave glut main loop.
        glutLeaveMainLoop();

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // camgen
