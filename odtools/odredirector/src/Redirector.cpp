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

#include "core/platform.h"

#include "jpeglib.h"

#include "core/data/Container.h"
#include "core/base/CommandLineParser.h"
#include "core/wrapper/SharedMemory.h"
#include "core/wrapper/SharedMemoryFactory.h"
#include "core/data/image/CompressedImage.h"

#include "GeneratedHeaders_CoreData.h"

#include "Redirector.h"
#include "StdoutPump.h"

namespace odredirector {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Redirector::Redirector(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odredirector"),
        m_fromstdin(false),
        m_tostdout(false),
        m_jpegQuality(5),
        m_mapOfSharedMemories() {
        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);
    }

    Redirector::~Redirector() {
        m_mapOfSharedMemories.clear();
    }

    void Redirector::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("fromstdin");
        cmdParser.addCommandLineArgument("tostdout");
        cmdParser.addCommandLineArgument("jpegquality");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentFROMSTDIN = cmdParser.getCommandLineArgument("fromstdin");
        CommandLineArgument cmdArgumentTOSTDOUT = cmdParser.getCommandLineArgument("tostdout");
        CommandLineArgument cmdArgumentJPEGQUALITY = cmdParser.getCommandLineArgument("jpegquality");

        if (cmdArgumentFROMSTDIN.isSet()) {
            m_fromstdin = cmdArgumentFROMSTDIN.getValue<int>() == 1;
        }

        if (cmdArgumentTOSTDOUT.isSet()) {
            m_tostdout = cmdArgumentTOSTDOUT.getValue<int>() == 1;
        }

        if (cmdArgumentJPEGQUALITY.isSet()) {
            m_jpegQuality = cmdArgumentJPEGQUALITY.getValue<int32_t>();

            if (m_jpegQuality < 1 || m_jpegQuality > 100) {
                clog << "Value for parameter --jpegquality must be between 1 and 100; using default value 5." << endl;
                m_jpegQuality = 5;
            }
        }
    }

    void Redirector::setUp() {}

    void Redirector::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode Redirector::body() {
        // Enforce synchronized behavior with C STDIN and STDOUT.
        cin.sync_with_stdio(true);
        cout.sync_with_stdio(true);

        // Create a stdout pump.
        StdoutPump stdoutPump(m_jpegQuality);

        if (m_tostdout) {
            // ...that is called automagically whenever we receive data from the UDP multicast session.
            addDataStoreFor(stdoutPump);
        }

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            if (m_fromstdin) {
                while (cin.good()) {
                    Container c;
                    cin >> c;

                    // Please note that reading from stin does not evaluate sending latencies.

                    // Compressed images are transformed into regular shared images again.
                    if (c.getDataType() == Container::COMPRESSED_IMAGE) {
                        core::data::image::CompressedImage ci = c.getData<core::data::image::CompressedImage>();

                        // Check, whether a shared memory was already created for this SharedImage; otherwise, create it and save it for later.
                        map<string, core::SharedPointer<core::wrapper::SharedMemory> >::iterator it = m_mapOfSharedMemories.find(ci.getName());
                        if (it == m_mapOfSharedMemories.end()) {
                            core::SharedPointer<core::wrapper::SharedMemory> sp = core::wrapper::SharedMemoryFactory::createSharedMemory(ci.getName(), ci.getSize());
                            m_mapOfSharedMemories[ci.getName()] = sp;
                        }

                        // Get the shared memory to put the uncompressed image into.
                        core::SharedPointer<core::wrapper::SharedMemory> sp = m_mapOfSharedMemories[ci.getName()];

                        // Set up the actual JPEG decompressor.
                        struct jpeg_decompress_struct cinfo;

                        // Set up the error reporting for JPEG decompression.
                        struct jpeg_error_mgr jerr;
                        cinfo.err = jpeg_std_error(&jerr);

                        // Create the decompressor structure.
                        jpeg_create_decompress(&cinfo);

                        // Set up the data source for decompression; in our case, use the data from CompressedImage.
                        jpeg_mem_src(&cinfo, ci.getRawData(), ci.getCompressedSize());

                        // Read the JPEG header.
                        (void) jpeg_read_header(&cinfo, TRUE);

                        // Start the decompressor.
                        (void) jpeg_start_decompress(&cinfo);

                        // Actual width of a row in the image: number of pixel per row * number of bytes per pixel.
                        int row_stride = cinfo.output_width * cinfo.output_components;

                        // Pointer to the buffer where to read the compressed image data from.
                        JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

                        // Lock shared memory to store the uncompressed data.
                        if (sp->isValid()) {
                            sp->lock();
                            int rowCounter = 0;
                            while (cinfo.output_scanline < cinfo.output_height) {
                                // Read next line from JPEG and decompress it.
                                (void) jpeg_read_scanlines(&cinfo, buffer, 1);
                                // Put the line to shared memory segmet.
                                ::memcpy(static_cast<uint8_t*>(sp->getSharedMemory()) + (rowCounter * row_stride), buffer[0], row_stride);
                                // Increase the row counter.
                                rowCounter++;
                            }
                            sp->unlock();
                        }
                        // Finalize the decompression.
                        (void) jpeg_finish_decompress(&cinfo);

                        // Free the decompressor.
                        jpeg_destroy_decompress(&cinfo);

                        // As we have now the decompressed image data in memory, create a SharedMemory data structure to describe it.
                        coredata::image::SharedImage si;
                        si.setName(ci.getName());
                        si.setWidth(ci.getWidth());
                        si.setHeight(ci.getHeight());
                        si.setBytesPerPixel(ci.getBytesPerPixel());

                        // Distribute the SharedImage information in the UDP multicast session.
                        Container c2(Container::SHARED_IMAGE, si);
                        getConference().send(c2);
                    }
                    else {
                        getConference().send(c);
                    }
                }
            }
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // odredirector

