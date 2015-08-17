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

#include "core/wrapper/OpenCV/OpenCVImage.h"
#include "core/wrapper/OpenCV/OpenCVImageFactory.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            OpenCVImageFactory::OpenCVImageFactory() {}

            OpenCVImageFactory::~OpenCVImageFactory() {}

            Image* OpenCVImageFactory::getImage(istream &in) {
                Image *img = new OpenCVImage(in);
                return img;
            }

            Image* OpenCVImageFactory::getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format) {
                if ( ((width * height) == 0) || (format == Image::INVALID) ) {
                    return NULL;
                }
                return new OpenCVImage(width, height, format);
            }

            Image* OpenCVImageFactory::getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format, char *ptr) {
                if ( ((width * height) == 0) || (ptr == NULL) || (format == Image::INVALID) ) {
                    return NULL;
                }
                return new OpenCVImage(width, height, format, ptr);
            }
        }
    }
} // core::wrapper::OpenCV
