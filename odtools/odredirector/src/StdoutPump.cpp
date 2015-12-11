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

#include <iostream>
#include <sstream>

#include "core/platform.h"

#include "jpeglib.h"

#include "core/SharedPointer.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "core/data/image/CompressedImage.h"

#include "GeneratedHeaders_CoreData.h"

#include "StdoutPump.h"

namespace odredirector {

    using namespace std;
    using namespace core;

    StdoutPump::StdoutPump(const int32_t &jpegQuality) :
        m_jpegQuality(jpegQuality) {}

    StdoutPump::~StdoutPump() {}

    void StdoutPump::add(const core::data::Container &container) {
        stringstream sstr;
        // SharedImages are transformed into compressed images using JPEG compression.
        if (container.getDataType() == core::data::Container::SHARED_IMAGE) {
            coredata::image::SharedImage si = const_cast<core::data::Container&>(container).getData<coredata::image::SharedImage>();
            
            if (si.getBytesPerPixel()==1 || si.getBytesPerPixel()==3) {
                // Set up the actual JPEG compressor.
                struct jpeg_compress_struct cinfo;

                // Set up the error reporting for JPEG compression.
                struct jpeg_error_mgr jerr;
                cinfo.err = jpeg_std_error(&jerr);

                // Create the compressor structure.
                jpeg_create_compress(&cinfo);

                // Define the image parameters.
                cinfo.image_width = si.getWidth();
                cinfo.image_height = si.getHeight();
                cinfo.input_components = si.getBytesPerPixel();

                // Set correct color space.                
                cinfo.in_color_space = (si.getBytesPerPixel() == 1) ? JCS_GRAYSCALE : JCS_RGB;
                
                jpeg_set_defaults(&cinfo);

                // Set up the compression ratio.
                const int quality = m_jpegQuality;
                jpeg_set_quality(&cinfo, quality, TRUE /* limit to baseline-JPEG values */);

                // Define where to store the compression data; in our case in memory.
                unsigned char *mem = NULL;
                unsigned long mem_size = 0;
                jpeg_mem_dest(&cinfo, &mem, &mem_size);

                // Start compression (i.e. create the JPEG header).
                jpeg_start_compress(&cinfo, TRUE);

                // As we are transforming a SharedImage into a CompressedImage, attached to the shared memory segment.
                SharedPointer<core::wrapper::SharedMemory> memory = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
                if (memory->isValid()) {
                    memory->lock();
                        // Pointer to store the compressed image data per row.
                        JSAMPROW row_pointer[1];

                        // Actual width of a row in the image: number of pixel per row * number of bytes per pixel.
                        int row_stride = si.getWidth() * si.getBytesPerPixel();

                        while (cinfo.next_scanline < cinfo.image_height) {
                            row_pointer[0] = & (static_cast<JSAMPROW>(memory->getSharedMemory()))[cinfo.next_scanline * row_stride];
                            (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
                        }
                    memory->unlock();
                }

                // Close the image compression.
                jpeg_finish_compress(&cinfo);

                // Check if the size of the compressed image fits in a UDP packet.
                const uint32_t MAX_SIZE_UDP_PAYLOAD = 65000;
                if (mem_size < MAX_SIZE_UDP_PAYLOAD) {
                    // Create the CompressedImage data structure.
                    core::data::image::CompressedImage ci(si.getName(), si.getWidth(), si.getHeight(), si.getBytesPerPixel(), mem_size);
                    ::memcpy(ci.getRawData(), mem, mem_size);

                    // Free the compressor.
                    jpeg_destroy_compress(&cinfo);

                    // Free pointer to compressed data.
                    OPENDAVINCI_CORE_FREE_POINTER(mem);

                    // Write the CompressedImage container to STDOUT.
                    core::data::Container c(core::data::Container::COMPRESSED_IMAGE, ci);
                    sstr << c;
                }
                else {
                    cerr << "[odredirector]: Warning! Compressed image to large to fit in a UDP packet. Image skipped." << std::endl;
                }
            }
            else {
                cerr << "[odredirector]: Warning! Color space not supported. Image skipped." << std::endl;
            }
        }
        else {
            sstr << container;
        }
        string s = sstr.str();

        const uint32_t dataSize = htonl(s.length());
        std::cout.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
        std::cout << s;

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

