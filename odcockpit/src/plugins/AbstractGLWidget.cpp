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
#include <GL/glut.h>

#include <Qt/qevent.h>
#include <Qt/qtimer.h>
#include <qglobal.h>
#include <qnamespace.h>
#include <qpoint.h>

#include <cmath>

#include "core/opendavinci.h"
#include "core/base/Lock.h"
#include "generated/cartesian/Constants.h"
#include "plugins/AbstractGLWidget.h"

class QWidget;

namespace cockpit {
    namespace plugins {

class PlugIn;

        using namespace std;
        using namespace core::base;
        using namespace core::data;

        bool AbstractGLWidget::m_isGLUTinitialized = false;

        AbstractGLWidget::AbstractGLWidget(const PlugIn &plugIn, QWidget *prnt) :
                QGLWidget(prnt),
                m_plugIn(plugIn),
                m_translationX(0),
                m_translationY(0),
                m_translationZ(50),
                m_rotationX(0),
                m_rotationY(0),
                m_rotationZ(0),
                m_pitchX(0),
                m_pitchY(0),
                m_pitchZ(0),
                m_scale(1),
                m_phi(static_cast<float>(-cartesian::Constants::PI)),
                m_theta(static_cast<float>(-cartesian::Constants::PI / 4)),
                m_epsilon(0),
                m_mouseSensitivity(0.03f),
                m_keySensitivity(1.0f),
                m_mouseX(0),
                m_mouseY(0),
                m_mouseButton(0),
                m_backgroundColorMutex(),
                m_backgroundColor() {

            // For using GLUT, the subsystem must be initialized.
            if (!AbstractGLWidget::m_isGLUTinitialized) {
                char **argv = NULL;
                int32_t argc = 0;
                glutInit(&argc, argv);
                AbstractGLWidget::m_isGLUTinitialized = true;
            }

            m_phi = -cartesian::Constants::PI + 0.1;
            emit phiChanged((double)m_phi);
            emit thetaChanged((double)m_theta);
            emit epsilonChanged((double)m_epsilon);

            QTimer *timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
            const uint32_t fps = 25;
            timer->start(1000 / fps);

            setFocusPolicy(Qt::StrongFocus);
        }

        AbstractGLWidget::~AbstractGLWidget() {}

        const PlugIn& AbstractGLWidget::getPlugIn() const {
            return m_plugIn;
        }

        void AbstractGLWidget::setBackgroundColor(const hesperia::data::environment::Point3 &c) {
            Lock l(m_backgroundColorMutex);
            m_backgroundColor = c;
        }

        void AbstractGLWidget::setupOpenGL() {}

        void AbstractGLWidget::initializeGL() {
            {
                Lock l(m_backgroundColorMutex);
                glClearColor(static_cast<float>(m_backgroundColor.getX()), static_cast<float>(m_backgroundColor.getY()), static_cast<float>(m_backgroundColor.getZ()), 0);
            }
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glShadeModel(GL_SMOOTH);
            glEnable(GL_DEPTH_TEST);

            // Perform a special setup from subclasses.
            setupOpenGL();

            // Initialize the scene from subclasses.
            initScene();
        }

        void AbstractGLWidget::paintGL() {
            {
                Lock l(m_backgroundColorMutex);
                glClearColor(static_cast<float>(m_backgroundColor.getX()), static_cast<float>(m_backgroundColor.getY()), static_cast<float>(m_backgroundColor.getZ()), 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            glLoadIdentity();

            m_theta = (m_theta < -cartesian::Constants::PI) ? -cartesian::Constants::PI : m_theta;
            m_theta = (m_theta > -0.01f) ? -0.01f : m_theta;

            m_rotationX = sin(-m_theta) * cos(-m_phi);
            m_rotationY = sin(-m_theta) * sin(-m_phi);
            m_rotationZ = cos(-m_theta);

            m_pitchX = sin(-m_epsilon) * cos(m_theta);
            m_pitchY = sin(-m_epsilon) * sin(m_theta);
            m_pitchZ = cos(-m_epsilon);

            gluLookAt(m_translationX, m_translationY, m_translationZ,
                      m_translationX - m_rotationX, m_translationY - m_rotationY, m_translationZ - m_rotationZ,
                      m_pitchX, m_pitchY, m_pitchZ);

            drawScene();
        }

        void AbstractGLWidget::resizeGL(int32_t w, int32_t h) {
            h = (h == 0) ? 1 : h;
            glViewport(0, 0, w, h);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(60, w / h, 1, 1000);
            glMatrixMode(GL_MODELVIEW);
            updateGL();
        }

        void AbstractGLWidget::keyPressEvent(QKeyEvent *evnt) {
            float denom = sqrt(m_rotationX * m_rotationX + m_rotationY * m_rotationY);
            denom = (abs(denom) < 1e-5) ? 1.0f : denom;
            float norm = 1.0f / denom;

            switch (evnt->key()) {
            case Qt::Key_D:
                m_translationX -= m_keySensitivity * norm * m_rotationY;
                emit translationXChanged((double)m_translationX);
                m_translationY -= m_keySensitivity * -norm * m_rotationX;
                emit translationYChanged((double)m_translationY);
                break;

            case Qt::Key_A:
                m_translationX += m_keySensitivity * norm * m_rotationY;
                emit translationYChanged((double)m_translationY);
                m_translationY += m_keySensitivity * -norm * m_rotationX;
                emit translationXChanged((double)m_translationX);
                break;

            case Qt::Key_S:
                m_translationX += m_keySensitivity * m_rotationX;
                emit translationXChanged((double)m_translationX);
                m_translationY += m_keySensitivity * m_rotationY;
                emit translationYChanged((double)m_translationY);
                m_translationZ += m_keySensitivity * m_rotationZ;
                break;

            case Qt::Key_W:
                m_translationX -= m_keySensitivity * m_rotationX;
                emit translationXChanged((double)m_translationX);
                m_translationY -= m_keySensitivity * m_rotationY;
                emit translationYChanged((double)m_translationY);
                m_translationZ -= m_keySensitivity * m_rotationZ;
                break;

            case Qt::Key_Y:
                m_translationZ -= m_keySensitivity * m_rotationZ;
                emit translationZChanged((double)m_translationZ);
                break;

            case Qt::Key_X:
                m_translationZ += m_keySensitivity * m_rotationZ;
                emit translationZChanged((double)m_translationZ);
                break;
            }

            updateGL();
        }

        void AbstractGLWidget::mousePressEvent(QMouseEvent *evnt) {
            if ( (evnt->buttons() & Qt::LeftButton) == Qt::LeftButton) {
                m_mouseX = evnt->pos().x();
                m_mouseY = evnt->pos().y();
            }

            m_mouseX = evnt->pos().x();
            m_mouseY = evnt->pos().y();
            updateGL();
        }

        void AbstractGLWidget::mouseMoveEvent(QMouseEvent *evnt) {
            // Left mouse button pressed.
            if ( (evnt->buttons() & Qt::LeftButton) == Qt::LeftButton ) {
                // Rotation around the X-axis.
                m_phi -= m_mouseSensitivity *  (m_mouseX - evnt->pos().x());
                emit phiChanged((double)m_phi);

                // Rotation around the Y-axis.
                m_theta -= m_mouseSensitivity *  (m_mouseY - evnt->pos().y());
                emit thetaChanged((double)m_theta);
            }

            // Right mouse button pressed.
            if ( (evnt->buttons() & Qt::RightButton) == Qt::RightButton ) {
                float denom = sqrt(m_rotationX * m_rotationX + m_rotationY * m_rotationY);
                denom = (abs(denom) < 1e-5) ? 1.0f : denom;
                float norm = 1.0f / denom;

                m_translationX += m_mouseSensitivity * (m_mouseX - evnt->pos().x()) * norm * m_rotationY;
                emit translationXChanged((double)m_translationX);
                m_translationY += m_mouseSensitivity * (m_mouseX - evnt->pos().x()) * norm * m_rotationX;
                emit translationYChanged((double)m_translationX);
                m_translationZ += m_mouseSensitivity * (m_mouseY - evnt->pos().y());
                emit translationZChanged((double)m_translationZ);
            }

            m_mouseX = evnt->pos().x();
            m_mouseY = evnt->pos().y();
            updateGL();
        }

        void AbstractGLWidget::setTranslationX(double translationX) {
            m_translationX = translationX;
        }

        void AbstractGLWidget::setTranslationY(double translationY) {
            m_translationY = translationY;
        }

        void AbstractGLWidget::setTranslationZ(double translationZ) {
            m_translationZ = translationZ;
        }

        void AbstractGLWidget::setPhi(double phi) {
            m_phi = phi;

            m_rotationX = sin(-m_theta) * cos(-m_phi);
            m_rotationY = sin(-m_theta) * sin(-m_phi);
            m_rotationZ = cos(-m_theta);
        }

        void AbstractGLWidget::setTheta(double theta) {
            m_theta = theta;

            m_pitchX = sin(-m_epsilon) * cos(-m_theta);
            m_pitchY = sin(-m_epsilon) * sin(-m_theta);
            m_pitchZ = cos(-m_epsilon);
        }

        void AbstractGLWidget::setEpsilon(double epsilon) {
            m_epsilon = epsilon;

            m_pitchX = sin(-m_epsilon) * cos(-m_theta);
            m_pitchY = sin(-m_epsilon) * sin(-m_theta);
            m_pitchZ = cos(-m_epsilon);
        }
    }
} // cockpit::plugins
