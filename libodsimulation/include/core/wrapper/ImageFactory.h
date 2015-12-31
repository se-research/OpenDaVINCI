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

#ifndef HESPERIA_CORE_WRAPPER_IMAGEFACTORY_H_
#define HESPERIA_CORE_WRAPPER_IMAGEFACTORY_H_

#include <iostream>

#include "core/platform.h"
#include "core/wrapper/Disposable.h"
#include "core/wrapper/Image.h"

namespace core {
    namespace wrapper {

class Mutex;

        using namespace std;

        /**
         * Abstract factory for handling matrices using a
         * native library (i.e. OpenCV).
         *
         * It can be used as follows:
         *
         * @code
         * fstream fin("image.png", ios::binary|ios::in);
         * Image *i = ImageFactory::getInstance().getImage(fin);
         * fin.close();
         *
         * ...
         *
         * if (i != NULL) {
         *     delete i;
         * }
         *
         * @endcode
         */
        class OPENDAVINCI_API ImageFactory : public Disposable {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ImageFactory(const ImageFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ImageFactory& operator=(const ImageFactory &);

            protected:
                ImageFactory();

            public:
                virtual ~ImageFactory();

                /**
                 * Singleton getter.
                 *
                 * @return Instance of the concrete factory.
                 */
                static ImageFactory& getInstance();

                /**
                 * This method returns an image read from the given istream.
                 *
                 * @param in The stream to be used to create the image.
                 * @return time based on the type of instance this factory is.
                 */
                virtual Image* getImage(istream &in) = 0;

                /**
                 * This method returns an empty image.
                 *
                 * @param width Width of the image.
                 * @param height Height of the image.
                 * @param format Image's format.
                 * @return Wrapped image or NULL.
                 */
                virtual Image* getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format) = 0;

                /**
                 * This method returns an image for an already existing
                 * memory based image without copying it.
                 *
                 * @param width Width of the image.
                 * @param height Height of the image.
                 * @param format Image's format.
                 * @param ptr Pointer to the raw data area.
                 * @return Wrapped image or NULL.
                 */
                virtual Image* getImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format, char *ptr) = 0;

            private:
                static Mutex *m_singletonMutex;
                static ImageFactory *m_singleton;
        };

    }
} // core::wrapper

#endif /*HESPERIA_CORE_WRAPPER_IMAGEFACTORY_H_*/
