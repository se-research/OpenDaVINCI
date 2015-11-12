/**
 * proxy - Sample application to encapsulate HW/SW interfacing with embedded systems.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <iostream>

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "core/wrapper/SharedMemoryFactory.h"

#include "Camera.h"

namespace automotive {
    namespace miniature {

        Camera::Camera(const string &name, const uint32_t &id, const uint32_t &width, const uint32_t &height, const uint32_t &bpp) :
            m_sharedImage(),
            m_sharedMemory(),
            m_name(name),
            m_id(id),
            m_width(width),
            m_height(height),
            m_bpp(bpp),
            m_size(0) {

            m_sharedMemory = core::wrapper::SharedMemoryFactory::createSharedMemory(name, width * height * bpp);

            m_sharedImage.setName(name);
            m_sharedImage.setWidth(width);
            m_sharedImage.setHeight(height);
            m_sharedImage.setBytesPerPixel(bpp);

            m_size = width * height * bpp;
            m_sharedImage.setSize(m_size);
        }

        Camera::~Camera() {}

        const string Camera::getName() const {
            return m_name;
        }

        uint32_t Camera::getID() const {
            return m_id;
        }

        uint32_t Camera::getWidth() const {
            return m_width;
        }

        uint32_t Camera::getHeight() const {
            return m_height;
        }

        uint32_t Camera::getBPP() const {
            return m_bpp;
        }

        uint32_t Camera::getSize() const {
            return m_size;
        }

        coredata::image::SharedImage Camera::capture() {
            if (isValid()) {
                if (captureFrame()) {
                    if (m_sharedMemory.isValid() && m_sharedMemory->isValid()) {
                        m_sharedMemory->lock();
                            copyImageTo((char*)m_sharedMemory->getSharedMemory(), m_size);
                        m_sharedMemory->unlock();
                    }
                }
            }

            return m_sharedImage;
        }

    }
} // automotive::miniature

