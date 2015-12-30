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

#ifndef HESPERIA_CORE_WRAPPER_MATRIXFACTORY_H_
#define HESPERIA_CORE_WRAPPER_MATRIXFACTORY_H_

#include "core/platform.h"
#include "core/wrapper/Disposable.h"

namespace core {
    namespace wrapper {

class Matrix;
class Mutex;

        using namespace std;

        /**
         * Abstract factory for handling matrices using a
         * native library (i.e. OpenCV).
         *
         * It can be used as follows:
         *
         * @code
         * Matrix *m = MatrixFactory::getInstance().getMatrix(3, 4);
         * m[2][1] = 7.0;
         *
         * ...
         *
         * if (m != NULL) {
         *     delete m;
         * }
         *
         * @endcode
         */
        class OPENDAVINCI_API MatrixFactory : public Disposable {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                MatrixFactory(const MatrixFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                MatrixFactory& operator=(const MatrixFactory &);

            protected:
                MatrixFactory();

            public:
                virtual ~MatrixFactory();

                /**
                 * Singleton getter.
                 *
                 * @return Instance of the concrete factory.
                 */
                static MatrixFactory& getInstance();

                /**
                 * This method creates a new matrix.
                 *
                 * @param in The stream to be used to create the image.
                 * @return time based on the type of instance this factory is.
                 */
                virtual Matrix* createMatrix(const uint32_t &dimensionX, const uint32_t &dimensionY) = 0;

            private:
                static Mutex *m_singletonMutex;
                static MatrixFactory *m_singleton;
        };

    }
} // core::wrapper

#endif /*HESPERIA_CORE_WRAPPER_MATRIXFACTORY_H_*/
