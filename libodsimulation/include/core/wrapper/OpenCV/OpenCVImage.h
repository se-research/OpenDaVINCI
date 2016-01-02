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

#ifndef HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGE_H_
#define HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGE_H_

#include <iostream>

#include <opencv/cv.h>

#include "core/opendavinci.h"
#include "core/wrapper/Image.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            using namespace std;


            /**
             * This class implements an abstract object containing
             * the raw data of an image.
             *
             * @See Image.
             */
            class OpenCVImage : public Image {
                private:
                    friend class OpenCVImageFactory;

                    /**
                     * Constructor.
                     *
                     * @param in Stream to be used for reading the contents.
                     */
                    OpenCVImage(istream &in);

                    /**
                     * Constructor for an empty image.
                     *
                     * @param width Width of the image.
                     * @param height Height of the image.
                     * @param format Image's format.
                     */
                    OpenCVImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format);

                    /**
                     * Constructor for an already existing image in memory.
                     * The memory won't get deleted at destruction.
                     *
                     * @param width Width of the image.
                     * @param height Height of the image.
                     * @param format Image's format.
                     * @param ptr Pointer to the raw data area.
                     */
                    OpenCVImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format, char *ptr);

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OpenCVImage(const OpenCVImage &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OpenCVImage& operator=(const OpenCVImage &);

                public:
                    virtual ~OpenCVImage();

                    virtual FORMAT getFormat() const;

                    virtual void setFormat(const FORMAT &format);

                    virtual uint32_t getWidth() const;

                    virtual uint32_t getHeight() const;

                    virtual uint32_t getWidthStep() const;

                    virtual char* getRawData() const;

                    virtual void rotate(const float &rad);

                    virtual void flipHorizontally();

                    virtual void flipVertically();

                private:
                    IplImage *m_image;
                    char *m_rawImage;
                    enum FORMAT m_format;
            };

        }
    }
} // core::wrapper::OpenCV

#endif /*HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGE_H_*/
