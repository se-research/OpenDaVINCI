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

#include <fstream>
#include <iostream>

#include "core/platform.h"
#include "core/base/Lock.h"
#include "core/macros.h"
#include "hesperia/threeD/Node.h"
#include "hesperia/threeD/NodeDescriptor.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/TransformGroup.h"
#include "hesperia/threeD/decorator/DecoratorFactory.h"
#include "hesperia/threeD/loaders/OBJXArchiveFactory.h"
#include "hesperia/threeD/models/Grid.h"
#include "hesperia/threeD/models/XYZAxes.h"
#include "plugins/objxviewer/OBJXGLWidget.h"

class QWidget;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace hesperia { namespace threeD { namespace loaders { class OBJXArchive; } } }

namespace cockpit {
    namespace plugins {
        namespace objxviewer {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::threeD;
            using namespace hesperia::threeD::decorator;
            using namespace hesperia::threeD::loaders;
            using namespace hesperia::threeD::models;

            OBJXGLWidget::OBJXGLWidget(const PlugIn &plugIn, QWidget *prnt) :
                    AbstractGLWidget(plugIn, prnt),
                    m_root(NULL),
                    m_modelMutex(),
                    m_model(NULL) {}

            OBJXGLWidget::~OBJXGLWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_root);
            }

            void OBJXGLWidget::setOBJXModel(const string &objxModel) {
                Lock l(m_modelMutex);
                m_model->deleteAllChildren();

                fstream fin(objxModel.c_str(), ios::in | ios::binary);

                if (fin.good()) {
                    OBJXArchive *objxArchive = OBJXArchiveFactory::getInstance().getOBJXArchive(fin);

                    fin.close();

                    if (objxArchive != NULL) {
                        // Decorate objxArchive for getting displayed in an OpenGL scene.
                        Node *n = DecoratorFactory::getInstance().decorate(*objxArchive, NodeDescriptor(objxModel));

                        if (n != NULL) {
                            m_model->addChild(n);
                        } else {
                            cout << "Model could not be loaded." << endl;
                        }

                        OPENDAVINCI_CORE_DELETE_POINTER(objxArchive);
                    }
                } else {
                    cout << "File could not be opened." << endl;
                }
            }

            void OBJXGLWidget::setupOpenGL() {
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

            void OBJXGLWidget::initScene() {
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

            void OBJXGLWidget::drawScene() {
                Lock l(m_modelMutex);
                if (m_root != NULL) {
                    RenderingConfiguration r = RenderingConfiguration();
                    m_root->render(r);
                }
            }
        }
    }
} // cockpit::plugins::objxviewer
