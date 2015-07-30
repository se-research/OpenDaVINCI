/**
 * lanedetector - Application skeleton for detecting lane markings.
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
#include <memory>

#include <opencv/cv.h>
#include <opencv/highgui.h>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "core/data/Container.h"
#include "core/wrapper/SharedMemoryFactory.h"

#include "tools/player/Player.h"

#include "GeneratedHeaders_CoreData.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "LaneDetector.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace core::base;
        using namespace core::base::module;
        using namespace core::data;
        using namespace coredata::image;
        using namespace tools::player;
        using namespace automotive;

        LaneDetector::LaneDetector(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "LaneDetector"),
            m_hasAttachedToSharedImageMemory(false),
            m_sharedImageMemory(),
            m_image(NULL),
            m_debug(false) {}

        LaneDetector::~LaneDetector() {}

        void LaneDetector::setUp() {
	        // This method will be called automatically _before_ running body().

            // If in debug mode, display the image from the camera feed.
	        if (m_debug) {
		        cvNamedWindow("Camera Feed Image", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("Camera Feed Image", 300, 100);
	        }
        }

        void LaneDetector::tearDown() {
	        // This method will be called automatically _after_ return from body().
	        if (m_image != NULL) {
		        cvReleaseImage(&m_image);
	        }

	        if (m_debug) {
		        cvDestroyWindow("Camera Feed Image");
	        }
        }

        bool LaneDetector::readSharedImage(Container &c) {
	        bool retVal = false;

	        if (c.getDataType() == Container::SHARED_IMAGE) {
		        SharedImage si = c.getData<SharedImage> ();

		        // Check if we have already attached to the shared memory containing the image from the virtual camera.
		        if (!m_hasAttachedToSharedImageMemory) {
			        m_sharedImageMemory = core::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
		        }

		        // Check if we could successfully attach to the shared memory.
		        if (m_sharedImageMemory->isValid()) {
			        // Lock the memory region to gain exclusive access using a scoped lock.
                    Lock l(m_sharedImageMemory);

			        if (m_image == NULL) {
				        m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, si.getBytesPerPixel());
			        }

			        // Example: Simply copy the image into our process space.
			        if (m_image != NULL) {
				        memcpy(m_image->imageData, m_sharedImageMemory->getSharedMemory(), si.getWidth() * si.getHeight() * si.getBytesPerPixel());
			        }

			        // Mirror the image.
			        cvFlip(m_image, 0, -1);

			        retVal = true;
		        }
	        }
	        return retVal;
        }

        // This method is called to process an image described by the SharedImage data structure.
        void LaneDetector::processImage() {
            // Example: Show the image.
            if (m_debug) {
                if (m_image != NULL) {
                    cvShowImage("Camera Feed Image", m_image);
                    cvWaitKey(10);
                }
            }



            // 1. Do something with the image m_image here, for example: find lane marking features, optimize quality, ...



            // 2. Calculate desired steering commands from the image features.



            // Here, you see an example of how to send the data structure SteeringData to the ContainerConference.
            // This data structure will be received by all running components. In our example, it will be processed
            // by a potential component to "drive" the car.
            SteeringData sd;
            sd.setExampleData(1234.56);

            // Create container for finally sending the data.
            Container c(Container::USER_DATA_1, sd);
            // Send container.
            getConference().send(c);
        }

        // This method will do the main data processing job.
        // Therefore, it tries to open the real camera first. If that fails, the virtual camera images from camgen are used.
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode LaneDetector::body() {
	        // Get configuration data.
	        KeyValueConfiguration kv = getKeyValueConfiguration();
	        m_debug = kv.getValue<int32_t> ("lanedetector.debug") == 1;

            auto_ptr<Player> player;
/*
            // Lane-detector can also directly read the data from file. This might be interesting to inspect the algorithm step-wisely.
            core::io::URL url("file://recording.rec");

            // Size of the memory buffer.
            const uint32_t MEMORY_SEGMENT_SIZE = kv.getValue<uint32_t>("global.buffer.memorySegmentSize");

            // Number of memory segments.
            const uint32_t NUMBER_OF_SEGMENTS = kv.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

            // If AUTO_REWIND is true, the file will be played endlessly.
            const bool AUTO_REWIND = true;

            // We do not want player to run in parallel but we want to process frame by frame sequentially.
            const bool THREADING = false;

            // Construct the player.
            player = auto_ptr<Player>(new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
*/

            // Main data processing loop.
	        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
		        bool has_next_frame = false;

		        // Use the shared memory image.
                Container c;
                if (player.get() != NULL) {
		            // Read the next container from file.
                    c = player->getNextContainerToBeSent();
                }
                else {
		            // Get the most recent available container for a SHARED_IMAGE.
		            c = getKeyValueDataStore().get(Container::SHARED_IMAGE);
                }                

		        if (c.getDataType() == Container::SHARED_IMAGE) {
			        // Example for processing the received container.
			        has_next_frame = readSharedImage(c);
		        }

		        // Process the read image.
		        if (true == has_next_frame) {
			        processImage();
		        }
	        }

	        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    } // miniature
} // automotive

