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
#include <cstdlib>
#include <fstream>

#ifndef WIN32
  #include <unistd.h>
#endif

#include <opencv/highgui.h>

#include "core/wrapper/OpenCV/OpenCVImage.h"

namespace core {
    namespace wrapper {
        namespace OpenCV {

            using namespace std;

            OpenCVImage::OpenCVImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format) :
                    m_image(NULL),
                    m_rawImage(NULL),
                    m_format(format) {

                const uint32_t channel = 3;
                switch (m_format) {
                case BGR_24BIT:
                case RGB_24BIT:
                    m_image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, channel);
                    cvSetZero(m_image);
                    break;

                case INVALID:
                    break;
                }
            }

            OpenCVImage::OpenCVImage(const uint32_t &width, const uint32_t &height, const enum Image::FORMAT &format, char *ptr) :
                    m_image(NULL),
                    m_rawImage(NULL),
                    m_format(format) {

                const uint32_t CHANNELS = 3;
                switch (m_format) {
                case BGR_24BIT:
                case RGB_24BIT:
                    m_image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, CHANNELS);
                    m_rawImage = m_image->imageData;
                    m_image->imageData = ptr;
                    break;

                case INVALID:
                    break;
                }
            }

            OpenCVImage::OpenCVImage(istream &in) :
                    m_image(NULL),
                    m_rawImage(NULL),
                    m_format(Image::BGR_24BIT) {
                // TODO: OpenCV needs a file to read from. Therefore, we need to buffer the istream...
                char *tempFileName;
#ifdef WIN32
                tempFileName = _tempnam("test", NULL);
#else
		tempFileName = (char*)calloc(50, sizeof(tempFileName));
		strncpy(tempFileName,"/tmp/OpenCVImage-XXXXXX", 23);
		mkstemp(tempFileName);
#endif
                fstream fout(tempFileName, ios::binary | ios::out);
                char c = 0;
                while (in.get(c)) {
                    fout << c;
                }
                fout.flush();
                fout.close();

                // Load image. OpenCV images are stored in BGR format by default.
                // CV_LOAD_IMAGE_COLOR specifies to store graylevel images using 24 bit as well.
                m_image = cvLoadImage(tempFileName, CV_LOAD_IMAGE_COLOR);

#ifdef WIN32
                _unlink(tempFileName);
#else
                unlink(tempFileName);
#endif
                free(tempFileName);
            }

            OpenCVImage::~OpenCVImage() {
                if (m_image != NULL) {
                    // Swap image data since we were constructed from an already existing memory area.
                    if (m_rawImage != NULL) {
                        m_image->imageData = m_rawImage;
                    }

                    cvReleaseImage(&m_image);
                }
            }

            Image::FORMAT OpenCVImage::getFormat() const {
                if (m_image == NULL) {
                    return Image::INVALID;
                }
                return m_format;
            }

            void OpenCVImage::setFormat(const Image::FORMAT &format) {
                m_format = format;
            }

            uint32_t OpenCVImage::getWidth() const {
                uint32_t width = 0;

                if (m_image != NULL) {
                    width = m_image->width;
                }

                return width;
            }

            uint32_t OpenCVImage::getHeight() const {
                uint32_t height = 0;

                if (m_image != NULL) {
                    height = m_image->height;
                }

                return height;
            }

            uint32_t OpenCVImage::getWidthStep() const {
                uint32_t widthStep = 0;
                uint32_t bytesPerPixel = 0;

                if (m_image != NULL) {
                    switch (getFormat()) {
                    case BGR_24BIT:
                    case RGB_24BIT:
                        bytesPerPixel = 3;
                        break;
                    case INVALID:
                        bytesPerPixel = 0;
                    }

                    widthStep = getWidth() * bytesPerPixel;
                }

                return widthStep;
            }

            char* OpenCVImage::getRawData() const {
                if (m_image != NULL) {
                    return m_image->imageData;
                }
                return NULL;
            }

            void OpenCVImage::flipHorizontally() {
                if (m_image != NULL) {
                	cvFlip(m_image, NULL, 1); // Perform an in-place flipping around the Y-axis.
//                    IplImage *flippedImage = cvCloneImage(m_image);
//
//                    cvFlip(m_image, flippedImage, 1); // Flip around Y-axis.
//
//                    // If this images is created using already existing memory,
//                    // copy the rotated image into the memory.
//                    if (m_rawImage != NULL) {
//                        memcpy(m_image->imageData, flippedImage->imageData, (m_image->widthStep / m_image->width) * (m_image->width * m_image->height));
//
//                        // Release rotated image.
//                        cvReleaseImage(&flippedImage);
//                    } else {
//                        // Use rotated image instead of previous image.
//                        cvReleaseImage(&m_image);
//                        m_image = flippedImage;
//                    }
                }
            }

            void OpenCVImage::flipVertically() {
                if (m_image != NULL) {
                	cvFlip(m_image, NULL, 0); // Perform an in-place flipping around the X-axis.
//                    IplImage *flippedImage = cvCloneImage(m_image);
//
//                    cvConvertImage(m_image, flippedImage, CV_CVTIMG_FLIP);
//
//                    // If this images is created using already existing memory,
//                    // copy the rotated image into the memory.
//                    if (m_rawImage != NULL) {
//                        memcpy(m_image->imageData, flippedImage->imageData, (m_image->widthStep / m_image->width) * (m_image->width * m_image->height));
//
//                        // Release rotated image.
//                        cvReleaseImage(&flippedImage);
//                    } else {
//                        // Use rotated image instead of previous image.
//                        cvReleaseImage(&m_image);
//                        m_image = flippedImage;
//                    }
                }
            }

            void OpenCVImage::rotate(const float &rad) {
                if (m_image != NULL) {
                    IplImage *rotatedImage = cvCloneImage(m_image);

                    float m[6];
                    CvMat M = cvMat(2, 3, CV_32F, m);

                    m[0] = static_cast<float>(cos(rad));
                    m[1] = static_cast<float>(sin(rad));
                    m[2] = getWidth() * 0.5f;
                    m[3] = -m[1];
                    m[4] = m[0];
                    m[5] = getHeight() * 0.5f;

                    cvGetQuadrangleSubPix(m_image, rotatedImage, &M);

                    // If this images is created using already existing memory,
                    // copy the rotated image into the memory.
                    if (m_rawImage != NULL) {
                        memcpy(m_image->imageData, rotatedImage->imageData, (m_image->widthStep / m_image->width) * (m_image->width * m_image->height));

                        // Release rotated image.
                        cvReleaseImage(&rotatedImage);
                    } else {
                        // Use rotated image instead of previous image.
                        cvReleaseImage(&m_image);
                        m_image = rotatedImage;
                    }
                }
            }

        }
    }
} // core::wrapper::OpenCV
