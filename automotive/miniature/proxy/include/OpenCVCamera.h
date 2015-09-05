/**
 * proxy - Sample application to encapsulate HW/SW interfacing with embedded systems.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef OPENCVCAMERA_H_
#define OPENCVCAMERA_H_

#include "opencv2/highgui/highgui.hpp"

#include "Camera.h"

namespace automotive {
    namespace miniature {

        using namespace std;

        /**
         * This class wraps an OpenCV camera and captures its data into a shared memory segment.
         */
        class OpenCVCamera : public Camera {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                OpenCVCamera(const OpenCVCamera &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                OpenCVCamera& operator=(const OpenCVCamera &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of the shared memory segment.
                 * @param id OpenCVCamera identifier.
                 * @param width
                 * @param height
                 * @param bpp
                 */
                OpenCVCamera(const string &name, const uint32_t &id, const uint32_t &width, const uint32_t &height, const uint32_t &bpp);

                virtual ~OpenCVCamera();

            private:
                virtual bool copyImageTo(char *dest, const uint32_t &size);

                virtual bool isValid() const;

                virtual bool captureFrame();

            private:
                CvCapture *m_capture;
                IplImage *m_image;
        };

    }
} // automotive::miniature

#endif /*OPENCVCAMERA_H_*/
