/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic push
# endif
# pragma GCC diagnostic ignored "-Weffc++"
#endif
    #include "jpgd.h"
    #include "jpge.h"
#ifndef WIN32
# if !defined(__OpenBSD__) && !defined(__NetBSD__)
#  pragma GCC diagnostic pop
# endif
#endif

#include "core/wrapper/jpg/JPG.h"

namespace core {
    namespace wrapper {
        namespace jpg {

            using namespace std;

            JPG::JPG() {}

            JPG::~JPG() {}

            bool JPG::compress(void *dest, int &destSize, const uint32_t &width, const uint32_t &height, const uint32_t &bytesPerPixel, const uint8_t *rawImageData, const uint32_t &quality) {
                bool retVal = false;
                if ( (dest != NULL) &&
                     (destSize > 0) &&
                     (width > 0) &&
                     (height > 0) &&
                     (bytesPerPixel > 0) &&
                     (rawImageData != NULL) &&
                     (quality >= 1) &&
                     (quality <= 100) ) {
                    void *buffer = ::malloc(width * height * bytesPerPixel);

                    // Setup the specified image quality.
                    jpge::params p;
                    p.m_quality = quality;
                    p.m_subsampling = (bytesPerPixel == 1) ? jpge::Y_ONLY : jpge::H2V2;

                    // Size of the buffer as the compressed image is at most as large as the raw image.
                    destSize = width * height * bytesPerPixel;
                    retVal = jpge::compress_image_to_jpeg_file_in_memory(buffer, destSize, width, height, bytesPerPixel, rawImageData, p);

                    // Free pointer to compressed data.
                    OPENDAVINCI_CORE_FREE_POINTER(buffer);
                }

                return retVal;
            }

            unsigned char* JPG::decompress(const unsigned char *src, const uint32_t &srcSize, int *width, int *height, int *actualBytesPerPixel, const uint32_t &requestedBytesPerPixel) {
                unsigned char* imageData = NULL;

                if ( (src != NULL) && 
                     (srcSize > 0) && 
                     (requestedBytesPerPixel > 0) ) {
                    imageData = jpgd::decompress_jpeg_image_from_memory(src, srcSize, width, height, actualBytesPerPixel, requestedBytesPerPixel);
                }
                return imageData;
            }

        }
    }
} // core::wrapper::jpg

