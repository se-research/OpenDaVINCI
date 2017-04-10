/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2017 Christian Berger
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

#ifndef OPENDAVINCI_TOOLS_PLAYER_RECMEMINDEX_H_
#define OPENDAVINCI_TOOLS_PLAYER_RECMEMINDEX_H_

#include <deque>
#include <fstream>
#include <map>
#include <thread>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/io/URL.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>

#include <opendavinci/odtools/player/Player.h>
#include <opendavinci/odtools/player/PlayerListener.h>

namespace odtools {
    namespace player {

        using namespace std;

        class RawMemoryBufferEntry {
            public:
                RawMemoryBufferEntry();
                virtual ~RawMemoryBufferEntry();
                RawMemoryBufferEntry(const RawMemoryBufferEntry &obj);
                RawMemoryBufferEntry& operator=(const RawMemoryBufferEntry &obj);

            public:
                odcore::data::Container m_container;
                char *m_rawMemoryBuffer;
                uint32_t m_lengthOfRawMemoryBuffer;
        };

        /**
         * This class reads a corresponding .rec.mem file belonging to a .rec
         * file that holds the shared memory dumps.
         */
        class OPENDAVINCI_API RecMemIndex {
            private:
                enum {
                    ONE_MILLISECOND_IN_MICROSECONDS = 1000,
                };

            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                RecMemIndex(const RecMemIndex &/*obj*/) = delete;

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                RecMemIndex& operator=(const RecMemIndex &/*obj*/) = delete;

            public:
                /**
                 * Constructor.
                 *
                 * @param url Resource to play.
                 * @param memorySegmentSize Size of the memory segment to be used for buffering.
                 * @param numberOfMemorySegments Number of memory segments to be used for buffering.
                 * @param threading If set to true, RecMemIndex will load new containers from the .rec.mem file in background.
                 */
                RecMemIndex(const odcore::io::URL &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading);

                virtual ~RecMemIndex();

                /**
                 * This method returns true if there is more data to replay.
                 *
                 * @return true if there is more data to replay.
                 */
                bool hasMoreData() const;

                /**
                 * This method rewinds the iterators.
                 */
                void rewind();

                /**
                 * This method returns the sample time stamp of the
                 * next Shared*-container to be replayed without
                 * actually returning it.
                 *
                 * @return sampleTimeStamp in microseconds of the next container in line.
                 */
                int64_t peekNextSampleTimeToPlayBack() const;

                /**
                 * This method returns the next Shared*-container to be replayed
                 * and copies the raw memory into the corresponding shared memory.
                 *
                 * @return The next container to be replayed.
                 */
                odcore::data::Container makeNextRawMemoryEntryAvailable();

            private:
                /**
                 * This method initializes the global index where the sample
                 * time stamps are sorted chronologically and mapped to the 
                 * corresponding entries (like containers) in the corresponding
                 * recording files.
                 */
                void initializeIndex();

            private: // File handle for the RecMemIndex.
                bool m_threading;

                odcore::io::URL m_url;

                // Handle to .rec.mem file.
                fstream m_recMemFile;
                bool m_recMemFileValid;

            private: // Index and cache management.
                mutable odcore::base::Mutex m_indexMutex;
                multimap<int64_t, IndexEntry> m_index;
                multimap<int64_t, IndexEntry>::iterator m_nextEntryToPlayBack;
                multimap<int64_t, IndexEntry>::iterator m_nextEntryToReadFromRecMemFile;
                bool m_hasMoreData;

                // Mapping of pos_type (within .rec.mem file) --> meta-entry describing tupel (Container, raw memory).
                map<uint64_t, shared_ptr<RawMemoryBufferEntry> > m_rawMemoryBuffer;
                deque<shared_ptr<RawMemoryBufferEntry> > m_unusedEntriesFromRawMemoryBuffer;
                vector<shared_ptr<RawMemoryBufferEntry> > m_allEntriesFromRawMemoryBuffer;

                map<string, std::shared_ptr<odcore::wrapper::SharedMemory> > m_mapOfPointersToSharedMemorySegments;

            private:
                /**
                 * This method set the state of the containerCacheFilling thread.
                 *
                 * @param running False if the thread to fill the container cache shall be joined.
                 */
                void setRawMemoryBufferFillingRunning(const bool &running);
                bool isRawMemoryBufferFillingRunning() const;

                /**
                 * This method manages the raw buffer for shared memory dumps.
                 */
                void manageRawMemoryBuffer();

            private:
                mutable odcore::base::Mutex m_rawMemoryBufferFillingThreadIsRunningMutex;
                bool m_rawMemoryBufferFillingThreadIsRunning;
                std::thread m_rawMemoryBufferFillingThread;
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_RECMEMINDEX_H_*/
