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
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendavinci/core/base/Thread.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/wrapper/SharedMemoryFactory.h"
#include "opendlv/core/wrapper/ImageFactory.h"
#include "opendlv/data/camera/ImageGrabberID.h"
#include "opendlv/threeD/decorator/DecoratorFactory.h"
#include "opendlv/io/camera/ImageGrabber.h"
#include "opendlv/scenario/SCNXArchiveFactory.h"
#include "opendlv/vehiclecontext/model/OpenGLGrabber.h"
#include "opendlv/threeD/models/CheckerBoard.h"
#include "opendlv/threeD/models/Grid.h"
#include "opendlv/threeD/models/XYZAxes.h"
#include "opendlv/threeD/RenderingConfiguration.h"

namespace core { namespace wrapper { class Image; } }
namespace hesperia { namespace data { namespace camera { class ImageGrabberCalibration; } } }
namespace hesperia { namespace scenario { class SCNXArchive; } }

namespace vehiclecontext {
    namespace model {

        using namespace std;
        using namespace core::base;
        using namespace core::io;
        using namespace hesperia::data::camera;
        using namespace hesperia::data::environment;
        using namespace hesperia::scenario;
        using namespace hesperia::threeD;
        using namespace hesperia::threeD::decorator;
        using namespace hesperia::threeD::models;

        OpenGLGrabber::OpenGLGrabber(const KeyValueConfiguration &kvc, const ImageGrabberID &imageGrabberID, const ImageGrabberCalibration &imageGrabberCalibration) :
            ImageGrabber(imageGrabberID, imageGrabberCalibration),
            m_kvc(kvc),
            m_image(),
            m_sharedMemory(),
            m_root() {

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
        }

        OpenGLGrabber::~OpenGLGrabber() {}

        void OpenGLGrabber::delay() {
            Thread::usleepFor(1000 * 10);
        }

        core::SharedPointer<core::wrapper::Image> OpenGLGrabber::getNextImage() {
            if ( (m_sharedMemory.isValid()) && (m_sharedMemory->isValid()) ) {
                m_sharedMemory->lock();
                    RenderingConfiguration r = RenderingConfiguration();
                    m_root->render(r);

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

    }
} // vehiclecontext::model
