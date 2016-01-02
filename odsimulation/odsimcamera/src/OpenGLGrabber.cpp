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

#include <GL/gl.h>
#include <GL/glut.h>

#include <cstring>
#include <iostream>
#include <string>

#include "core/opendavinci.h"
#include "core/platform.h"
#include "OpenGLGrabber.h"
#include "core/base/Thread.h"
#include "core/io/URL.h"
#include "core/wrapper/ImageFactory.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/threeD/RenderingConfiguration.h"
#include "hesperia/threeD/TransformGroup.h"
#include "hesperia/threeD/decorator/DecoratorFactory.h"
#include "hesperia/threeD/models/CheckerBoard.h"
#include "hesperia/threeD/models/Grid.h"
#include "hesperia/threeD/models/XYZAxes.h"

namespace core { namespace wrapper { class Image; } }
namespace hesperia { namespace data { namespace camera { class ImageGrabberCalibration; } } }
namespace hesperia { namespace data { namespace environment { class EgoState; } } }
namespace hesperia { namespace scenario { class SCNXArchive; } }

namespace camgen {

    using namespace std;
    using namespace core::base;
    using namespace hesperia::data::camera;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;
    using namespace core::io;
    using namespace hesperia::scenario;
    using namespace hesperia::threeD;
    using namespace hesperia::threeD::decorator;
    using namespace hesperia::threeD::models;

    OpenGLGrabber::OpenGLGrabber(const KeyValueConfiguration &kvc, const ImageGrabberID &imageGrabberID, const ImageGrabberCalibration &imageGrabberCalibration, hesperia::data::environment::EgoState &egoState) :
            ImageGrabber(imageGrabberID, imageGrabberCalibration),
            m_render(OpenGLGrabber::WORLD),
            m_kvc(kvc),
            m_image(),
            m_sharedMemory(),
            m_root(),
            m_extrinsicCalibrationRoot(),
            m_intrinsicCalibrationRoot(),
            m_egoState(egoState) {

        const URL urlOfSCNXFile(m_kvc.getValue<string>("global.scenario"));
        const bool SHOW_GRID = (m_kvc.getValue<uint8_t>("global.showgrid") == 1);
        if (urlOfSCNXFile.isValid()) {
            m_root = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());
            SCNXArchive &scnxArchive = SCNXArchiveFactory::getInstance().getSCNXArchive(urlOfSCNXFile);

            // Read scnxArchive and decorate it for getting displayed in an OpenGL scene.
            const bool SHOW_LANE_CONNECTORS = false;
            m_root->addChild(DecoratorFactory::getInstance().decorate(scnxArchive, SHOW_LANE_CONNECTORS));
            if (SHOW_GRID) {
                m_root->addChild(new XYZAxes(NodeDescriptor("XYZAxes")));
                m_root->addChild(new Grid(NodeDescriptor("Grid"), 10, 2));
            }

            m_sharedMemory = core::wrapper::SharedMemoryFactory::createSharedMemory("odsimcamera", 640 * 480 * 3);

            m_image = core::SharedPointer<core::wrapper::Image>(core::wrapper::ImageFactory::getInstance().getImage(640, 480, core::wrapper::Image::BGR_24BIT, static_cast<char*>(m_sharedMemory->getSharedMemory())));

            if (m_image.isValid()) {
                cerr << "OpenGLGrabber initialized." << endl;
            }
        }

        m_intrinsicCalibrationRoot = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());
        m_intrinsicCalibrationRoot->addChild(new XYZAxes(NodeDescriptor("XYZAxes")));
        m_intrinsicCalibrationRoot->addChild(new CheckerBoard(NodeDescriptor("CheckerBoard")));
        m_intrinsicCalibrationRoot->setTranslation(Point3(2.5, 0, 1));

        m_extrinsicCalibrationRoot = core::SharedPointer<TransformGroup>(new hesperia::threeD::TransformGroup());
        m_extrinsicCalibrationRoot->addChild(new XYZAxes(NodeDescriptor("XYZAxes")));
        m_extrinsicCalibrationRoot->addChild(new CheckerBoard(NodeDescriptor("CheckerBoard")));
        m_extrinsicCalibrationRoot->setTranslation(Point3(2.3, 0, 0));
        m_extrinsicCalibrationRoot->setRotation(Point3(cartesian::Constants::PI/2, cartesian::Constants::PI/2, 0));
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
                case  OpenGLGrabber::WORLD:
                    renderNextImageFromRealWord();
                break;
                case  OpenGLGrabber::INTRINSIC_PATTERN:
                    renderNextImageFromIntrinsicCalibrationBody();
                break;
                case  OpenGLGrabber::EXTRINSIC_PATTERN:
                    renderNextImageFromExtrinsicCalibrationBody();
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

    void OpenGLGrabber::renderNextImageFromRealWord() {
//        cerr << m_egoState.toString() << endl;

//                gluLookAt(0, -8, 1,
//                          0, 0,  0,
//                          0, 0,  1); // -1 is necessary to rotate the entire model by PI around the y-axis.

//        Point3 dir = m_egoState.getRotation();
//        Point3 target(15, 0, 0);
//        target.rotateZ(dir.getAngleXY());
//        target += m_egoState.getPosition();
//
//        gluLookAt(m_egoState.getPosition().getX(), m_egoState.getPosition().getY(), 1.65,
//                  target.getX(), target.getY(), 0,
//                  0, 0, -1);

//                glLoadIdentity();
//                gluLookAt(0, 0, 3,
//                          0, 3,  0,
//                          0, 0,  -1); // -1 is necessary to rotate the entire model by PI around the y-axis.

        RenderingConfiguration r = RenderingConfiguration();
        m_root->render(r);
    }

    void OpenGLGrabber::renderNextImageFromIntrinsicCalibrationBody() {
        glClearColor(0.5, 0.5, 0.5, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderingConfiguration r = RenderingConfiguration();
        m_intrinsicCalibrationRoot->render(r);
    }

    void OpenGLGrabber::renderNextImageFromExtrinsicCalibrationBody() {
        glClearColor(0.5, 0.5, 0.5, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        RenderingConfiguration r = RenderingConfiguration();
        m_extrinsicCalibrationRoot->render(r);
/*
        double *m_model = new double[16];
        double *m_projection = new double[16];
        int32_t *m_view = new int[4];

        // Get actual projection values.
        glGetDoublev(GL_MODELVIEW_MATRIX, m_model);
        glGetDoublev(GL_PROJECTION_MATRIX, m_projection);
        glGetIntegerv(GL_VIEWPORT, m_view);

        cerr << "MV: " << endl;
        for(uint32_t row = 0; row < 4; row++) {
            for(uint32_t col = 0; col < 4; col++) {
                cerr << m_model[row * 4 + col] << " ";
            }
            cerr << endl;
        }

        cerr << "P: " << endl;
        for(uint32_t row = 0; row < 4; row++) {
            for(uint32_t col = 0; col < 4; col++) {
                cerr << m_projection[row * 4 + col] << " ";
            }
            cerr << endl;
        }

        cerr << "V: " << endl;
        for(uint32_t row = 0; row < 4; row++) {
            cerr << m_view[row] << " ";
        }
        cerr << endl;

        HESPERIA_CORE_DELETE_ARRAY(m_model);
        HESPERIA_CORE_DELETE_ARRAY(m_projection);
        HESPERIA_CORE_DELETE_ARRAY(m_view);
*/
    }

} // camgen
