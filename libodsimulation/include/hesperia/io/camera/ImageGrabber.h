/**
 * hesperia - Simulation environment
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

#ifndef HESPERIA_IO_CAMERA_IMAGEGRABBER_H_
#define HESPERIA_IO_CAMERA_IMAGEGRABBER_H_

#include "core/SharedPointer.h"
// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "hesperia/data/camera/ImageGrabberCalibration.h"
#include "hesperia/data/camera/ImageGrabberID.h"

namespace core { namespace wrapper { class Image; } }

namespace hesperia {
    namespace io {
        namespace camera {

            using namespace std;

            /**
             * This class is the abstract superclass for all image grabbers.
             */
            class OPENDAVINCI_API ImageGrabber {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ImageGrabber(const ImageGrabber &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ImageGrabber& operator=(const ImageGrabber &);

                public:
                    /**
                     * Constructor.
                     *
                     * @param imageGrabberID Identifier for this image grabber.
                     * @param imageGrabberCalibration Calibration information for this grabber.
                     */
                    ImageGrabber(const data::camera::ImageGrabberID &imageGrabberID, const data::camera::ImageGrabberCalibration &imageGrabberCalibration);

                    virtual ~ImageGrabber();

                    /**
                     * This method returns the next image from this image grabber.
                     *
                     * @return Next available image.
                     */
                    virtual core::SharedPointer<core::wrapper::Image> getNextImage() = 0;

                    /**
                     * This methods delays the image acquisition.
                     */
                    virtual void delay() = 0;

                    /**
                     * This method returns the imageGrabberID for this image grabber.
                     *
                     * @return imageGrabberID for this image grabber.
                     */
                    const data::camera::ImageGrabberID getImageGrabberID() const;

                    /**
                     * This method returns the calibration for this image grabber.
                     *
                     * @return Calibration for this image grabber.
                     */
                    const data::camera::ImageGrabberCalibration getImageGrabberCalibration() const;

                private:
                    data::camera::ImageGrabberID m_imageGrabberID;
                    data::camera::ImageGrabberCalibration m_imageGrabberCalibration;
            };

        }
    }
} // hesperia::io::camera

#endif /*HESPERIA_IO_CAMERA_IMAGEGRABBER_H_*/
