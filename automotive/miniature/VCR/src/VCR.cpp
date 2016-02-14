/**
 * VCR - Application to create a video.
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

#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "GeneratedHeaders_CoreData.h"

#include "VCR.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace coredata::image;

        VCR::VCR(const int32_t &argc, char **argv) : TimeTriggeredConferenceClientModule(argc, argv, "VCR"),
	        m_hasAttachedToSharedImageMemory(false),
            m_sharedImageMemory(),
	        m_image(NULL),
            m_debug(false),
            m_writer(NULL) {}

        VCR::~VCR() {}

        void VCR::setUp() {
	        // This method will be call automatically _before_ running body().

	        if (m_debug) {
		        // Create an OpenCV-window.
		        cvNamedWindow("WindowShowImage", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("WindowShowImage", 300, 100);
	        }
        }

        void VCR::tearDown() {
	        // This method will be call automatically _after_ return from body().

	        if (m_image != NULL) {
		        cvReleaseImage(&m_image);
	        }
	        if (m_writer != NULL) {
		        cvReleaseVideoWriter(&m_writer);
	        }
	        if (m_debug) {
		        cvDestroyWindow("WindowShowImage");
	        }
        }

        bool VCR::readSharedImage(Container &c) {
	        bool retVal = false;

	        if (c.getDataType() == coredata::image::SharedImage::ID()) {
		        SharedImage si = c.getData<SharedImage> ();

		        // Check if we have already attached to the shared memory.
		        if (!m_hasAttachedToSharedImageMemory) {
			        m_sharedImageMemory
					        = core::wrapper::SharedMemoryFactory::attachToSharedMemory(
							        si.getName());
		        }

		        // Check if we could successfully attach to the shared memory.
		        if (m_sharedImageMemory->isValid()) {
			        //cerr << "Got image: LOG 0.2 " << si.toString() << endl;

			        // Lock the memory region to gain exclusive access. REMEMBER!!! DO NOT FAIL WITHIN lock() / unlock(), otherwise, the image producing process would fail.
			        m_sharedImageMemory->lock();
			        {
				        // Here, do something with the image. For example, we simply show the image.

				        const uint32_t numberOfChannels = 3;
				        // For example, simply show the image.
				        if (m_image == NULL) {
					        m_image = cvCreateImage(cvSize(si.getWidth(),
							        si.getHeight()), IPL_DEPTH_8U, numberOfChannels);
				        }

				        // Copying the image data is very expensive...
				        if (m_image != NULL) {
					        memcpy(m_image->imageData,
							        m_sharedImageMemory->getSharedMemory(),
							        si.getWidth() * si.getHeight() * numberOfChannels);
				        }
			        }

			        // Release the memory region so that the image produce (i.e. the camera for example) can provide the next raw image data.
			        m_sharedImageMemory->unlock();

			        // Mirror the image.
			        cvFlip(m_image, 0, -1);

			        retVal = true;
		        }
	        }
	        return retVal;
        }

        void VCR::processImage() {
	        if (m_debug) {
		        // Show the image
		        if (m_image != NULL) {
			        cvShowImage("WindowShowImage", m_image);
			        cvWaitKey(10);

	                if (m_writer != NULL) {
		                cvWriteFrame(m_writer, m_image);
	                }
		        }
	        }
        }

        // This method will do the main data processing job.
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode VCR::body() {
	        // Get configuration data.
	        KeyValueConfiguration kv = getKeyValueConfiguration();
	        m_debug = kv.getValue<int32_t> ("VCR.debug") == 1;

	        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
		        bool has_next_frame = false;

		        // Get the most recent available container for a SharedImage.
		        Container c = getKeyValueDataStore().get(coredata::image::SharedImage::ID());

		        if (c.getDataType() == coredata::image::SharedImage::ID()) {
			        // Example for processing the received container.
			        has_next_frame = readSharedImage(c);
		        }

		        // Process the read image.
		        if ( (true == has_next_frame) && (m_writer == NULL) ) {
                    double fps = getFrequency();
                    CvSize size = cvSize(m_image->width, m_image->height);
                    m_writer = cvCreateVideoWriter("video.mpg", CV_FOURCC('P','I','M','1'), fps, size);
                    if (m_writer != NULL) {
                        cerr << "VideoWriter created." << endl;
                    }
                    else {
                        cerr << "Failed to create VideoWriter." << endl;
                    }
		        }

		        // Process the read image.
		        if (true == has_next_frame) {
			        processImage();
		        }
	        }

	        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

