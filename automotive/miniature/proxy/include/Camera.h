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

#ifndef CAMERA_H_
#define CAMERA_H_

#include <stdint.h>
#include <string>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

namespace automotive {
    namespace miniature {

        using namespace std;

        /**
         * This class wraps a camera and captures its data into a shared memory segment.
         */
        class Camera {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Camera(const Camera &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Camera& operator=(const Camera &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of the shared memory segment.
                 * @param id Camera identifier.
                 * @param width
                 * @param height
                 * @param bpp
                 */
                Camera(const string &name, const uint32_t &id, const uint32_t &width, const uint32_t &height, const uint32_t &bpp);

                virtual ~Camera();

                /**
                 * @return Meta information about the image.
                 */
                odcore::data::image::SharedImage capture();

            protected:
                /**
                 * This method is responsible to copy the image from the
                 * specific camera driver to the shared memory.
                 *
                 * @param dest Pointer where to copy the data.
                 * @param size Number of bytes to copy.
                 * @return true if the data was successfully copied.
                 */
                virtual bool copyImageTo(char *dest, const uint32_t &size) = 0;

                virtual bool captureFrame() = 0;

                virtual bool isValid() const = 0;

                const string getName() const;

                uint32_t getID() const;

                uint32_t getWidth() const;

                uint32_t getHeight() const;

                uint32_t getBPP() const;

                uint32_t getSize() const;

            private:
                odcore::data::image::SharedImage m_sharedImage;
                odcore::SharedPointer<odcore::wrapper::SharedMemory> m_sharedMemory;
                
            protected:
                string m_name;
                uint32_t m_id;
                uint32_t m_width;
                uint32_t m_height;
                uint32_t m_bpp;
                uint32_t m_size;
        };

    }
} // automotive::miniature

#endif /*CAMERA_H_*/
