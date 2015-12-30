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

#ifndef HESPERIA_CORE_WRAPPER_IMAGE_H_
#define HESPERIA_CORE_WRAPPER_IMAGE_H_

#include "core/platform.h"

namespace core {
    namespace wrapper {

        /**
         * This interface encapsulates all methods necessary for
         * accessing image data.
         *
         * @See ImageFactory
         */
        class Image {
            public:
                /**
                 * This enum describes the format of the underlying image.
                 */
                enum FORMAT {
                    INVALID,
                    BGR_24BIT,
                    RGB_24BIT
                };

            public:
                virtual ~Image();

                /**
                 * This method returns the image's format.
                 *
                 * @return Image's format.
                 */
                virtual FORMAT getFormat() const = 0;

                /**
                 * This method sets the image's format.
                 *
                 * @param format Image's format.
                 */
                virtual void setFormat(const FORMAT &format) = 0;

                /**
                             * This method returns the image's width.
                             *
                             * @return Image's width.
                             */
                virtual uint32_t getWidth() const = 0;

                /**
                 * This method returns the image's height.
                 *
                 * @return Image's height.
                 */
                virtual uint32_t getHeight() const = 0;

                /**
                 * This method returns the image's width step.
                 *
                 * @return Image's width step.
                 */
                virtual uint32_t getWidthStep() const = 0;

                /**
                 * This method returns the image's raw data:
                 * getWidth()*getHeight()*getWidthStep().
                 *
                 * @return Image's raw data.
                 */
                virtual char* getRawData() const = 0;

                /**
                 * This method rotates the image by the given
                 * angle in RAD.
                 *
                 * @param rad Angle for rotation.
                 */
                virtual void rotate(const float &rad) = 0;

                /**
                 * This method flips the current image horizontally.
                 */
                virtual void flipHorizontally() = 0;

                /**
                 * This method flips the current image vertically.
                 */
                virtual void flipVertically() = 0;
        };

    }
} // core::wrapper

#endif /*HESPERIA_CORE_WRAPPER_IMAGE_H_*/
