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

#include <iostream>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/wrapper/DisposalService.h"
#include "opendlv/scenario/SCNXArchiveFactory.h"
#include "opendlv/threeD/Node.h"
#include "opendlv/threeD/NodeDescriptor.h"
#include "opendlv/threeD/RenderingConfiguration.h"
#include "opendlv/threeD/TransformGroup.h"
#include "opendlv/threeD/decorator/DecoratorFactory.h"
#include "opendlv/threeD/models/Grid.h"
#include "opendlv/threeD/models/XYZAxes.h"
#include "plugins/scnxviewer/SCNXGLWidget.h"

class QWidget;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace opendlv { namespace scenario { class SCNXArchive; } }

namespace cockpit {
    namespace plugins {
        namespace scnxviewer {

            using namespace std;
            using namespace core::base;
            using namespace core::io;
            using namespace opendlv::scenario;
            using namespace opendlv::threeD;
            using namespace opendlv::threeD::decorator;
            using namespace opendlv::threeD::models;

            SCNXGLWidget::SCNXGLWidget(const PlugIn &plugIn, QWidget *prnt) :
                    AbstractGLWidget(plugIn, prnt),
                    m_root(NULL),
                    m_modelMutex(),
                    m_model(NULL) {}

            SCNXGLWidget::~SCNXGLWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_root);
            }

            void SCNXGLWidget::setSCNXModel(const string &scnxModel) {
                Lock l(m_modelMutex);
                m_model->deleteAllChildren();

                // Cleanup right now.
                core::wrapper::DisposalService::getInstance().cleanUpImmediately();
                Thread::usleepFor(1000*1000);

                URL scnxFile("file://" + scnxModel);

                SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(scnxFile);

                // Decorate scnxArchive for getting displayed in an OpenGL scene.
                Node *n = DecoratorFactory::getInstance().decorate(scnxArchive);
                if (n != NULL) {
                    m_model->addChild(n);
                }
                else {
                    cout << "Model could not be loaded." << endl;
                }
            }

            void SCNXGLWidget::setupOpenGL() {
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

            void SCNXGLWidget::initScene() {
                Lock l(m_modelMutex);

                // Initialize.
                m_model = new TransformGroup();

                TransformGroup *tg = new TransformGroup();
                // Add model to be shown.
                tg->addChild(m_model);

                tg->addChild(new XYZAxes(NodeDescriptor("XYZAxes"), 1, 12));
                tg->addChild(new Grid(NodeDescriptor("Grid"), 10, 1));

                m_root = tg;
            }

            void SCNXGLWidget::drawScene() {
                Lock l(m_modelMutex);
                if (m_root != NULL) {
                    RenderingConfiguration r = RenderingConfiguration();
                    m_root->render(r);
                }
            }

        }
    }
} // plugins::scnxviewer
