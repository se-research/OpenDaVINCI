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

#ifndef OPENDAVINCI_CORE_WRAPPER_JPG_JPG_H_
#define OPENDAVINCI_CORE_WRAPPER_JPG_JPG_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

namespace core {
    namespace wrapper {
        namespace jpg {

            /**
             * This class provides static methods to compress and decompress
             * data in JPG format.
             */
            class OPENDAVINCI_API JPG {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    JPG(const JPG &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    JPG& operator=(const JPG &);

                    JPG();
                    
                public:
                    virtual ~JPG();

                    /**
                     * This method compresses raw image data using a JPG compressor.
                     *
                     * @param dest Pointer to destination buffer to receive the compressed image data.
                     * @param destSize Size of destination buffer that will be set to the actual amount of bytes used thereof.
                     * @param width Raw image's width.
                     * @param height Raw image's height.
                     * @param bytesPerPixel Raw image's bytes per pixel (channels).
                     * @param rawImageDate Raw image data.
                     * @param quality Compression rate (must be between 1 and 100).
                     * @return true if the compression succeeded.
                     */
                    static bool compress(void *dest, int &destSize, const uint32_t &width, const uint32_t &height, const uint32_t &bytesPerPixel, const uint8_t *rawImageData, const uint32_t &quality);

                    /**
                     * This method decompresses a JPG compressed image.
                     *
                     * @param src Pointer to a buffer containing the compressed image data.
                     * @param srctSize Size of buffer.
                     * @param width Decompressed image's width.
                     * @param height Decompressed image's height.
                     * @param actualBytesPerPixel Decompressed image's bytes per pixel (channels).
                     * @param requestedBytesPerPixel Expected decompressed image's bytes per pixel (channels).
                     * @return Pointer to the decompressed image that MUST be released by the callee or NULL in the case of an error.
                     */
                    static unsigned char* decompress(const unsigned char *src, const uint32_t &srcSize, int *width, int *height, int *actualBytesPerPixel, const uint32_t &requestedBytesPerPixel);
            };

        }
    }
} // core::wrapper::jpg

#endif /*OPENDAVINCI_CORE_WRAPPER_JPG_JPG_H_*/
