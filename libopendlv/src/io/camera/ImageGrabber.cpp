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

#include "opendlv/io/camera/ImageGrabber.h"

namespace hesperia {
    namespace io {
        namespace camera {

            using namespace data::camera;

            ImageGrabber::ImageGrabber(const ImageGrabberID &imageGrabberID, const ImageGrabberCalibration &imageGrabberCalibration) :
                    m_imageGrabberID(imageGrabberID),
                    m_imageGrabberCalibration(imageGrabberCalibration) {}

            ImageGrabber::~ImageGrabber() {}

            const ImageGrabberID ImageGrabber::getImageGrabberID() const {
                return m_imageGrabberID;
            }

            const ImageGrabberCalibration ImageGrabber::getImageGrabberCalibration() const {
                return m_imageGrabberCalibration;
            }

        }
    }
} // hesperia::io::camera
