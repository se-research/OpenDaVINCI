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

#ifdef HAVE_UEYE

#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "uEyeCamera.h"

namespace automotive {
    namespace miniature {

        uEyeCamera::uEyeCamera(const string &name, const uint32_t &id, const uint32_t &width, const uint32_t &height, const uint32_t &bpp) :
            Camera(name, id, width, height, bpp),
            m_capture(0),
            m_imageMemory(NULL),
            m_ueyeImagePtr(NULL),
            m_pid(0),
            m_image(NULL) {

            int retVal = is_InitCamera(&m_capture, NULL);

            is_AllocImageMem(m_capture, width, height, bpp, &m_imageMemory, &m_pid);
            is_SetImageMem(m_capture, m_imageMemory, m_pid);
            is_SetDisplayMode(m_capture, IS_SET_DM_DIB);
            is_SetColorMode(m_capture, IS_CM_MONO8);

            int pnCol, pnColMode;
            is_GetColorDepth(m_capture, &pnCol , &pnColMode);

            is_CaptureVideo(m_capture, IS_WAIT);

            if (retVal != IS_SUCCESS) {
                if (retVal == IS_STARTER_FW_UPLOAD_NEEDED) {
                    m_capture = m_capture | IS_ALLOW_STARTER_FW_UPLOAD;
                    retVal = is_InitCamera(&m_capture, NULL);
                }
                cerr << "proxy: Could not open camera '" << name << "' with ID: " << id << ", returned value: " << retVal << endl;

                m_capture = 0;
            }
            else {
                m_image = cvCreateImageHeader(cvSize(m_width, m_height), IPL_DEPTH_8U, m_bpp);
            }
        }

        uEyeCamera::~uEyeCamera() {
            // Free the allocated memory.
            is_FreeImageMem(m_capture, m_imageMemory, m_pid);

            // Try to deinitialize camera.
            if (is_ExitCamera(m_capture) != IS_SUCCESS) {
                cerr << "proxy: Could not exit camera '" << m_name << "' with ID: " << m_id << endl;
            }
        }

        bool uEyeCamera::isValid() const {
            return (m_capture > 0);
        }

        bool uEyeCamera::captureFrame() {
            bool retVal = false;
            m_ueyeImagePtr = NULL;
            if (m_capture > 0) {
                if (is_GetImageMem(m_capture, (void**)&(m_ueyeImagePtr)) == IS_SUCCESS) {
                    retVal = true;
                }
            }

            return retVal;
        }

        bool uEyeCamera::copyImageTo(char *dest, const uint32_t &size) {
            bool retVal = false;

            if ( (dest != NULL) && (size > 0) && (m_image != NULL) && (m_ueyeImagePtr != NULL) ) {
                ::memcpy(dest, m_ueyeImagePtr, size);
                m_image->imageData = (char*)m_ueyeImagePtr;

                cvShowImage("WindowShowImage", m_image);
                cvWaitKey(10);

                retVal = true;
            }

            return retVal;
        }

    }
} // automotive::miniature

#endif /*HAVE_UEYE*/

