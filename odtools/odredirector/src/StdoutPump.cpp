/**
 * odredirector - Tool for dumping data to stdout or reading back from stdin
 * Copyright (C) 2015 Christian Berger
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

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/image/CompressedImage.h"
#include "opendavinci/odcore/wrapper/jpg/JPG.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include "StdoutPump.h"

namespace odredirector {

    using namespace std;
    using namespace odcore;
    using namespace odcore::base;
    using namespace odcore::data;

    StdoutPump::StdoutPump(const int32_t &jpegQuality) :
        m_jpegQuality(jpegQuality) {}

    StdoutPump::~StdoutPump() {}

    void StdoutPump::add(const odcore::data::Container &container) {
        // SharedImages are transformed into compressed images using JPEG compression.
        if (container.getDataType() == odcore::data::image::SharedImage::ID()) {
            odcore::data::image::SharedImage si = const_cast<odcore::data::Container&>(container).getData<odcore::data::image::SharedImage>();
            
            if ( (1 == si.getBytesPerPixel()) || 
                 (3 == si.getBytesPerPixel()) ) {
                bool retVal = false;
                int compressedSize = si.getWidth() * si.getHeight() * si.getBytesPerPixel();
                void *buffer = ::malloc(compressedSize);
                if (buffer != NULL) {
                    // As we are transforming a SharedImage into a CompressedImage, attached to the shared memory segment.
                    SharedPointer<odcore::wrapper::SharedMemory> memory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    if (memory->isValid()) {
                        Lock l(memory);
                        retVal = odcore::wrapper::jpg::JPG::compress(buffer, compressedSize, si.getWidth(), si.getHeight(), si.getBytesPerPixel(), static_cast<const unsigned char*>(memory->getSharedMemory()), m_jpegQuality);
                    }

                }
                // Check if the size of the compressed image fits in a UDP packet.
                const int32_t MAX_SIZE_UDP_PAYLOAD = 65000;
                if ( retVal && (compressedSize < MAX_SIZE_UDP_PAYLOAD) ) {
                    // Create the CompressedImage data structure.
                    odcore::data::image::CompressedImage ci(si.getName(), si.getWidth(), si.getHeight(), si.getBytesPerPixel(), compressedSize);
                    ::memcpy(ci.getRawData(), buffer, compressedSize);

                    // Write the CompressedImage container to STDOUT.
                    odcore::data::Container c(ci);
                    c.setSentTimeStamp(container.getSentTimeStamp());
                    c.setReceivedTimeStamp(container.getReceivedTimeStamp());
                    std::cout << c;
                }
                if (compressedSize >= MAX_SIZE_UDP_PAYLOAD) {
                    cerr << "[odredirector]: Warning! Compressed image too large (" << compressedSize << " bytes) to fit in a UDP packet. Image skipped." << std::endl;
                }
                if (!retVal) {
                    cerr << "[odredirector]: Warning! Failed to compress image. Image skipped." << std::endl;
                }
                // Free pointer to compressed data.
                OPENDAVINCI_CORE_FREE_POINTER(buffer);
            }
            else {
                cerr << "[odredirector]: Warning! Color space not supported. Image skipped." << std::endl;
            }
        }
        else {
            std::cout << container;
        }

        std::cout.rdbuf()->pubsync();
        std::cout.flush();
    }

    void StdoutPump::clear() {}

    uint32_t StdoutPump::getSize() const {
        return 0;
    }

    bool StdoutPump::isEmpty() const {
        return true;
    }

} // odredirector

