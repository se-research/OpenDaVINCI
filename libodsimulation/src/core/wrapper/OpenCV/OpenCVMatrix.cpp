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

#include <cstdio>
#include <iostream>

#include "core/wrapper/OpenCV/OpenCVMatrix.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            using namespace std;

            OpenCVMatrix::OpenCVMatrix(const uint32_t &dimensionX, const uint32_t &dimensionY) :
                    m_rawMatrix(NULL) {
                if ((dimensionX * dimensionY) > 0) {
                    // BEWARE! cvMatrix expects (rows, cols)!!
                    m_rawMatrix = cvCreateMat(dimensionY, dimensionX, CV_32F);
                    cvZero(m_rawMatrix);
                }
            }

            OpenCVMatrix::~OpenCVMatrix() {
                if (m_rawMatrix != NULL) {
                    cvReleaseMat(&m_rawMatrix);
                }
                m_rawMatrix = NULL;
            }

            float OpenCVMatrix::get(const uint32_t &x, const uint32_t &y) const throw (string) {
                if ( (x > (getWidth() - 1)) || (y > (getHeight() - 1)) ) {
                    throw string("Array index out of bounds exception.");
                }
                // BEWARE! cvMatrix expects (rows, cols)!!
                return static_cast<float>(cvmGet(m_rawMatrix, y, x));
            }

            void OpenCVMatrix::set(const uint32_t &x, const uint32_t &y, const float &value) const throw (string) {
                if ( (x > (getWidth() - 1)) || (y > (getHeight() - 1)) ) {
                    throw string("Array index out of bounds exception.");
                }
                // BEWARE! cvMatrix expects (rows, cols)!!
                return cvmSet(m_rawMatrix, y, x, value);
            }

            uint32_t OpenCVMatrix::getWidth() const {
                return (m_rawMatrix != NULL) ? static_cast<uint32_t>(m_rawMatrix->cols) : 0;
            }

            uint32_t OpenCVMatrix::getHeight() const {
                return (m_rawMatrix != NULL) ? static_cast<uint32_t>(m_rawMatrix->rows) : 0;
            }

            void* OpenCVMatrix::getPointerToRawMatrix() const {
                return m_rawMatrix;
            }

            Matrix* OpenCVMatrix::operator+(const Matrix &other) const {
                OpenCVMatrix *matrix = new OpenCVMatrix(getWidth(), getHeight());

                cvAdd(m_rawMatrix, other.getRawMatrix<CvMat*>(), matrix->getRawMatrix<CvMat*>());

                return matrix;
            }

            Matrix& OpenCVMatrix::operator+=(const Matrix &other) {
                Matrix *result = operator+(other);

                // Swap matrices.
                cvReleaseMat(&m_rawMatrix);
                m_rawMatrix = static_cast<CvMat*>(cvClone(result->getRawMatrix<CvMat*>()));
                delete result;

                return (*this);
            }

            Matrix* OpenCVMatrix::operator-(const Matrix &other) const {
                OpenCVMatrix *matrix = new OpenCVMatrix(getWidth(), getHeight());

                cvSub(m_rawMatrix, other.getRawMatrix<CvMat*>(), matrix->getRawMatrix<CvMat*>());

                return matrix;
            }

            Matrix& OpenCVMatrix::operator-=(const Matrix &other) {
                Matrix *result = operator-(other);

                // Swap matrices.
                cvReleaseMat(&m_rawMatrix);
                m_rawMatrix = static_cast<CvMat*>(cvClone(result->getRawMatrix<CvMat*>()));
                delete result;

                return (*this);
            }

            Matrix* OpenCVMatrix::operator*(const double &a) const {
                CvMat *nullMat = cvCreateMat(getHeight(), getWidth(), CV_32F);
                cvSetZero(nullMat);

                OpenCVMatrix *matrix = new OpenCVMatrix(getWidth(), getHeight());

                cvScaleAdd(m_rawMatrix, cvRealScalar(a), nullMat, matrix->getRawMatrix<CvMat*>());

                cvReleaseMat(&nullMat);

                return matrix;
            }

            Matrix& OpenCVMatrix::operator*=(const double &a) {
                Matrix *result = operator*(a);

                // Swap matrices.
                cvReleaseMat(&m_rawMatrix);
                m_rawMatrix = static_cast<CvMat*>(cvClone(result->getRawMatrix<CvMat*>()));
                delete result;

                return (*this);
            }

            Matrix* OpenCVMatrix::operator*(const Matrix &m) const {
                OpenCVMatrix *matrix = new OpenCVMatrix(getWidth(), getHeight());

                // Calculate: 1.0 * m_rawMatrix * m->getRawMatrix<CvMat*>() + 0 * NULL.
                cvGEMM(m_rawMatrix, m.getRawMatrix<CvMat*>(), 1.0, NULL, 0, matrix->getRawMatrix<CvMat*>(), 0);

                return matrix;
            }

            Matrix& OpenCVMatrix::operator*=(const Matrix &m) {
                Matrix *result = operator*(m);

                // Swap matrices.
                cvReleaseMat(&m_rawMatrix);
                m_rawMatrix = static_cast<CvMat*>(cvClone(result->getRawMatrix<CvMat*>()));
                delete result;

                return (*this);
            }

            Matrix& OpenCVMatrix::transpose() {
                // BEWARE! Change width and height due to transposition.
                CvMat *temp = cvCreateMat(getWidth(), getHeight(), CV_32F);
                cvTranspose(m_rawMatrix, temp);

                // Swap matrices.
                cvReleaseMat(&m_rawMatrix);
                m_rawMatrix = temp;

                return (*this);
            }

        }
    }
} // core::wrapper::OpenCV
