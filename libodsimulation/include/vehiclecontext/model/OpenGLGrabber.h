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

#ifndef VEHICLECONTEXT_MODEL_OPENGLGRABBER_H_
#define VEHICLECONTEXT_MODEL_OPENGLGRABBER_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "core/SharedPointer.h"
#include "core/base/KeyValueConfiguration.h"
#include "hesperia/core/wrapper/Image.h"
#include "core/wrapper/SharedMemory.h"

#include "hesperia/data/environment/EgoState.h"
#include "hesperia/io/camera/ImageGrabber.h"
#include "hesperia/threeD/TransformGroup.h"

namespace vehiclecontext {
    namespace model {

        using namespace std;

        /**
         * This class implements a grabber providing images from
         * a given OpenGL scene.
         */
        class OpenGLGrabber : public hesperia::io::camera::ImageGrabber {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                OpenGLGrabber(const OpenGLGrabber &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                OpenGLGrabber& operator=(const OpenGLGrabber &);

            public:
                /**
                 * Constructor.
                 *
                 * @param kvc KeyValueConfiguration.
                 * @param imageGrabberID Identifier for this image grabber.
                 * @param imageGrabberCalibration Calibration information for this grabber.
                 * @param egoState Current ego state.
                 */
                OpenGLGrabber(const core::base::KeyValueConfiguration &kvc,
                              const hesperia::data::camera::ImageGrabberID &imageGrabberID,
                              const hesperia::data::camera::ImageGrabberCalibration &imageGrabberCalibration);

                virtual ~OpenGLGrabber();

                virtual void delay();

                virtual core::SharedPointer<core::wrapper::Image> getNextImage();

            private:
                core::base::KeyValueConfiguration m_kvc;
                core::SharedPointer<core::wrapper::Image> m_image;
                core::SharedPointer<core::wrapper::SharedMemory> m_sharedMemory;
                core::SharedPointer<hesperia::threeD::TransformGroup> m_root;
        };

    }
} // vehiclecontext::model

#endif /*VEHICLECONTEXT_MODEL_OPENGLGRABBER_H_*/
