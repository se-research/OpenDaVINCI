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

#ifndef LANEDETECTOR_H_
#define LANEDETECTOR_H_

#include <opencv/cv.h>

#include <memory>
#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace automotive {
    namespace miniature {

        using namespace std;

        /**
         * This class is an exemplary skeleton for processing video data with OpenDaVINCI.
         */
        class LaneDetector: public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
	            /**
	             * "Forbidden" copy constructor. Goal: The compiler should warn
	             * already at compile time for unwanted bugs caused by any misuse
	             * of the copy constructor.
	             *
	             * @param obj Reference to an object of this class.
	             */
	            LaneDetector(const LaneDetector &/*obj*/);

	            /**
	             * "Forbidden" assignment operator. Goal: The compiler should warn
	             * already at compile time for unwanted bugs caused by any misuse
	             * of the assignment operator.
	             *
	             * @param obj Reference to an object of this class.
	             * @return Reference to this instance.
	             */
	            LaneDetector& operator=(const LaneDetector &/*obj*/);

            public:
	            /**
	             * Constructor.
	             *
	             * @param argc Number of command line arguments.
	             * @param argv Command line arguments.
	             */
	            LaneDetector(const int32_t &argc, char **argv);

	            virtual ~LaneDetector();

	            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            protected:
	            /**
	             * This method is called to process an incoming container.
	             *
	             * @param c Container to process.
	             * @return true if c was successfully processed.
	             */
	            bool readSharedImage(odcore::data::Container &c);

            private:
	            bool m_hasAttachedToSharedImageMemory;
	            std::shared_ptr<odcore::wrapper::SharedMemory> m_sharedImageMemory;
	            IplImage *m_image;
                bool m_debug;

	            virtual void setUp();

	            virtual void tearDown();

                void processImage();
        };

    } // miniature
} // automotive

#endif /*LANEDETECTOR_H_*/
