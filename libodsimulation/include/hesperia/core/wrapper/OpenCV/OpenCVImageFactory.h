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

#ifndef HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGEFACTORY_H_
#define HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGEFACTORY_H_

#include <iosfwd>

#include "opendavinci/core/opendavinci.h"
#include "hesperia/core/wrapper/Image.h"
#include "hesperia/core/wrapper/ImageFactory.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            /**
             * This class is a concrete derivative for the abstract
             * factory ImageFactory.
             *
             * @See ImageFactory
             */
            class OpenCVImageFactory : public ImageFactory {
                protected:
                    friend class ImageFactory;

                    OpenCVImageFactory();

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OpenCVImageFactory(const OpenCVImageFactory &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OpenCVImageFactory& operator=(const OpenCVImageFactory &);

                public:
                    virtual ~OpenCVImageFactory();

                    virtual Image* getImage(istream &in);

                    virtual Image* getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format);

                    virtual Image* getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format, char *ptr);
            };

        }
    }
} // core::wrapper::OpenCV

#endif /*HESPERIA_CORE_WRAPPER_OPENCV_OPENCVIMAGEFACTORY_H_*/
