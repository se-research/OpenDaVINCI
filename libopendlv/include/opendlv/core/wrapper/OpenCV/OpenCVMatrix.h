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

#ifndef HESPERIA_CORE_WRAPPER_OPENCV_OPENCVMATRIX_H_
#define HESPERIA_CORE_WRAPPER_OPENCV_OPENCVMATRIX_H_

#include <string>

#include <opencv/cv.h>

#include "opendlv/core/wrapper/Matrix.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            using namespace std;


            /**
             * This class implements an abstract object containing
             * the raw data of a matrix.
             *
             * @See Matrix.
             */
            class OpenCVMatrix : public Matrix {
                private:
                    friend class OpenCVMatrixFactory;

                    /**
                     * Constructor.
                     *
                     * @param dimensionX Size of the new matrix in X-direction.
                     * @param dimensionY Size of the new matrix in Y-direction.
                     */
                    OpenCVMatrix(const uint32_t &dimensionX, const uint32_t &dimensionY);

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OpenCVMatrix(const OpenCVMatrix &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OpenCVMatrix& operator=(const OpenCVMatrix &);

                public:
                    virtual ~OpenCVMatrix();

                    virtual uint32_t getWidth() const;

                    virtual uint32_t getHeight() const;

                    virtual float get(const uint32_t &x, const uint32_t &y) const throw (std::string);

                    virtual void set(const uint32_t &x, const uint32_t &y, const float &value) const throw (std::string);

                    virtual void* getPointerToRawMatrix() const;

                    virtual Matrix* operator+(const Matrix &other) const;

                    virtual Matrix& operator+=(const Matrix &other);

                    virtual Matrix* operator-(const Matrix &other) const;

                    virtual Matrix& operator-=(const Matrix &other);

                    virtual Matrix* operator*(const double &a) const;

                    virtual Matrix& operator*=(const double &a);

                    virtual Matrix* operator*(const Matrix &m) const;

                    virtual Matrix& operator*=(const Matrix &m);

                    virtual Matrix& transpose();

                private:
                    CvMat *m_rawMatrix;
            };

        }
    }
} // core::wrapper::OpenCV

#endif /*HESPERIA_CORE_WRAPPER_OPENCV_OPENCVMATRIX_H_*/
