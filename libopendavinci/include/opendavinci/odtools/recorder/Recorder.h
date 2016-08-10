/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_TOOLS_RECORDER_RECORDER_H_
#define OPENDAVINCI_TOOLS_RECORDER_RECORDER_H_

#include <map>
#include <memory>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/Mutex.h"

namespace odcore { namespace data { class Container; } }

namespace odtools {
    namespace recorder {

        class RecorderDelegate;
        class SharedDataListener;

        using namespace std;

        /**
         * This class is the interface to use the recorder module from within other modules.s
         */
        class Recorder {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Recorder(const Recorder &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Recorder& operator=(const Recorder &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param url URL of the resource to be used for writing containers to.
                 * @param memorySegmentSize Size of a memory segment for storing shared memory data (like shared images).
                 * @param numberOfSegments Number of segments to be used.
                 * @param threading If true recorder is using a background thread to dump shared memory data.
                 *                  If set to true recorder can be used in real-time required scenarios where
                 *                  it is embedded in user supplied apps; however, there is a risk that if the
                 *                  queue size (numberOfSegments) is chosen too small or the low-level disk I/O
                 *                  containers of type SharedImage or SharedMemory are dropped.
                 * @param dumpSharedData If true, shared images and shared data will be stored as well.
                 */
                Recorder(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData);

                virtual ~Recorder();

                /**
                 * This method records data from the given FIFOQueue.
                 *
                 * @param fifo FIFOQueue to be used for recording data.
                 */
                void recordQueueEntries();

                /**
                 * This method returns the FIFO to be used for all
                 * containers except for shared memory segments.
                 *
                 * @return Reference to queue to be used for queuing Containers.
                 */
                odcore::base::FIFOQueue& getFIFO();

                /**
                 * This method registers a RecorderDelegate to process a specific
                 * Container differently.
                 *
                 * @param containerID Container ID to listen for.
                 * @param r RecorderDelegate.
                 */
                void registerRecorderDelegate(const uint32_t &containerID, RecorderDelegate* r);

                /**
                 * This method returns the data store to be used
                 * for storing shared memory.
                 *
                 * @return Reference to data handler to be used for storing shared memory.
                 */
                SharedDataListener& getDataStoreForSharedData();

                /**
                 * This method stores the given container. Depending on the container
                 * data type, either the FIFO queue is used or the one to handle
                 * shared memory data.
                 *
                 * @param c Container to be recorded.
                 */
                void store(odcore::data::Container c);

            private:
                odcore::base::FIFOQueue m_fifo;
                unique_ptr<SharedDataListener> m_sharedDataListener;
                std::shared_ptr<ostream> m_out;
                std::shared_ptr<ostream> m_outSharedMemoryFile;
                bool m_dumpSharedData;
                odcore::base::Mutex m_mapOfRecorderDelegatesMutex;
                map<int32_t, RecorderDelegate*> m_mapOfRecorderDelegates;
        };

    } // recorder
} // tools

#endif /*OPENDAVINCI_TOOLS_RECORDER_RECORDER_H_*/
