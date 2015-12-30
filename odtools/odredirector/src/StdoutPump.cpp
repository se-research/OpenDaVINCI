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
<<<<<<< HEAD
#include <cstring>
=======
>>>>>>> master
#include <iostream>
#include <sstream>

#include "core/platform.h"

#include "core/SharedPointer.h"
#include "core/base/Lock.h"
#include "core/data/TimeStamp.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "core/wrapper/jpg/JPG.h"
#include "core/data/image/CompressedImage.h"

#include "GeneratedHeaders_CoreData.h"

#include "StdoutPump.h"

namespace odredirector {

    using namespace std;
    using namespace core;
    using namespace core::base;
    using namespace core::data;

    StdoutPump::StdoutPump(const int32_t &jpegQuality) :
        m_jpegQuality(jpegQuality) {}

    StdoutPump::~StdoutPump() {}

    void StdoutPump::add(const core::data::Container &container) {
        // SharedImages are transformed into compressed images using JPEG compression.
        if (container.getDataType() == core::data::Container::SHARED_IMAGE) {
            coredata::image::SharedImage si = const_cast<core::data::Container&>(container).getData<coredata::image::SharedImage>();
            
            if ( (1 == si.getBytesPerPixel()) || 
                 (3 == si.getBytesPerPixel()) ) {
                bool retVal = false;
                int compressedSize = si.getWidth() * si.getHeight() * si.getBytesPerPixel();
                void *buffer = ::malloc(compressedSize);
                if (buffer != NULL) {
                    // As we are transforming a SharedImage into a CompressedImage, attached to the shared memory segment.
                    SharedPointer<core::wrapper::SharedMemory> memory = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                    if (memory->isValid()) {
                        Lock l(memory);
                        retVal = core::wrapper::jpg::JPG::compress(buffer, compressedSize, si.getWidth(), si.getHeight(), si.getBytesPerPixel(), static_cast<const unsigned char*>(memory->getSharedMemory()), m_jpegQuality);
                    }

                }
                // Check if the size of the compressed image fits in a UDP packet.
                const int32_t MAX_SIZE_UDP_PAYLOAD = 65000;
                if ( retVal && (compressedSize < MAX_SIZE_UDP_PAYLOAD) ) {
                    // Create the CompressedImage data structure.
                    core::data::image::CompressedImage ci(si.getName(), si.getWidth(), si.getHeight(), si.getBytesPerPixel(), compressedSize);
                    ::memcpy(ci.getRawData(), buffer, compressedSize);

                    // Write the CompressedImage container to STDOUT.
                    core::data::Container c(core::data::Container::COMPRESSED_IMAGE, ci);
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

