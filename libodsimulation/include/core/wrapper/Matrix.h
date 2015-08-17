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

#ifndef HESPERIA_CORE_WRAPPER_MATRIX_H_
#define HESPERIA_CORE_WRAPPER_MATRIX_H_

// core/platform.h must be included to setup platform-dependent header files and configurations.
#include "core/platform.h"

#include <string>
#include <exception>

namespace core {
    namespace wrapper {

        /**
         * This interface encapsulates a matrix data structure.
         *
         * @See MatrixFactory
         */
        class Matrix {
            public:
                virtual ~Matrix();

                /**
                 * This method returns the matrix' dimension in x-direction.
                 *
                 * @return Dimension in x-direction.
                 */
                virtual uint32_t getWidth() const = 0;

                /**
                 * This method returns the matrix' dimension in y-direction.
                 *
                 * @return Dimension in y-direction.
                 */
                virtual uint32_t getHeight() const = 0;

                /**
                 * This method returns the value at index (x, y).
                 *
                 * @return Value at index (x, y).
                 * @throws std::string if x or y are out of boundaries.
                 */
                virtual float get(const uint32_t &x, const uint32_t &y) const throw (std::string) = 0;

                /**
                 * This method set the value at index (x, y).
                 *
                 * @param value Value at index (x, y).
                 * @throws std::string if x or y are out of boundaries.
                 */
                virtual void set(const uint32_t &x, const uint32_t &y, const float &value) const throw (std::string) = 0;

                /**
                 * This operator adds the other matrix with this instance
                 * to a new object of this class.
                 *
                 * @param other Other coordinate.
                 * @return New object.
                 */
                virtual Matrix* operator+(const Matrix &other) const = 0;

                /**
                 * This operator adds the other matrix to this instance.
                 *
                 * @param other Other coordinate.
                 * @return Modified instance.
                 */
                virtual Matrix& operator+=(const Matrix &other) = 0;

                /**
                 * This operator subtracts the other matrix with this
                 * instance to a new object of this class.
                 *
                 * @param other Other coordinate.
                 * @return New object.
                 */
                virtual Matrix* operator-(const Matrix &other) const = 0;

                /**
                 * This operator subtracts the other matrix from this instance.
                 *
                 * @param other Other coordinate.
                 * @return Modified instance.
                 */
                virtual Matrix& operator-=(const Matrix &other) = 0;

                /**
                 * This operator scales this matrix and returns
                 * a new instance.
                 *
                 * @param a Scaling factor.
                 * @return New object.
                 */
                virtual Matrix* operator*(const double &a) const = 0;

                /**
                 * This operator scales this matrix and returns
                 * a the modified instance.
                 *
                 * @param a Scaling factor.
                 * @return Modified instance.
                 */
                virtual Matrix& operator*=(const double &a) = 0;

                /**
                 * This operator multiplies this matrix with anouther matrix
                 * and returns a new instance.
                 *
                 * @param m Another matrix.
                 * @return New object.
                 */
                virtual Matrix* operator*(const Matrix &m) const = 0;

                /**
                 * This operator multiplies this matrix with anouther matrix
                 * and returns a the modified instance.
                 *
                 * @param m Another matrix.
                 * @return Modified instance.
                 */
                virtual Matrix& operator*=(const Matrix &m) = 0;

                /**
                 * This method transposes this matrix.
                 *
                 * @return Reference to this instance.
                 */
                virtual Matrix& transpose() = 0;

                /**
                 * This method returns a pointer to the raw containing
                 * matrix data structure.
                 *
                 * @return Pointer to the raw matrix data structure.
                 */
                template<class T>
                inline T getRawMatrix() const {
                    return static_cast<T>(getPointerToRawMatrix());
                }

            protected:
                /**
                 * This method returns a void pointer to the raw matrix
                 * data structure.
                 *
                 * @return void pointer to the raw matrix data structure.
                 */
                virtual void* getPointerToRawMatrix() const = 0;
        };

    }
} // core::wrapper

#endif /*HESPERIA_CORE_WRAPPER_MATRIX_H_*/
