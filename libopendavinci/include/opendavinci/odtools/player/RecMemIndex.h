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
#include <opendavinci/odcore/data/TimeStamp.h>
#include <opendavinci/odcore/io/URL.h>
#include <opendavinci/odcore/exceptions/Exceptions.h>

#include <opendavinci/odtools/player/PlayerListener.h>

namespace odtools {
    namespace player {

        using namespace std;

        class RecMemIndexEntry {
            public:
                RecMemIndexEntry();
                RecMemIndexEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition);

            public:
                int64_t m_sampleTimeStamp;
                uint32_t m_filePosition;
                bool m_available;
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
                 */
                RecMemIndex(const odcore::io::URL &url);

                virtual ~RecMemIndex();

            private:
                /**
                 * This method initializes the global index where the sample
                 * time stamps are sorted chronocally and mapped to the 
                 * corresponding entries (like containers) in the corresponding
                 * recording files.
                 */
                void initializeIndex();

                /**
                 * This method actually fills the cache by trying to read up
                 * to maxNumberOfEntriesToReadFromFile from the rec file.
                 *
                 * @param maxNumberOfEntriesToReadFromFile Maximum number of entries to be read from file.
                 * @return Number of entries read from file.
                 */
                uint32_t fillContainerCache(const uint32_t &maxNumberOfEntriesToReadFromFile);

            private: // Data for the Player.
                odcore::io::URL m_url;

                // Handle to .rec.mem file.
                fstream m_recMemFile;
                bool m_recMemFileValid;

            private: // Index and cache management.
                // Global index: Mapping SampleTimeStamp --> cache entry (holding the actual content from .rec, .rec.mem, or .h264 file)
                mutable odcore::base::Mutex m_indexMutex;
                multimap<int64_t, RecMemIndexEntry> m_index;

            private:
                /**
                 * This method set the state of the containerCacheFilling thread.
                 *
                 * @param running False if the thread to fill the container cache shall be joined.
                 */
                void setSharedMemoryCacheFillingRunning(const bool &running);
                bool isSharedMemoryCacheFillingRunning() const;

                /**
                 * This method manages the cache for shared memory dumps.
                 */
                void manageSharedMemoryCache();

            private:
                mutable odcore::base::Mutex m_sharedMemoryCacheFillingThreadIsRunningMutex;
                bool m_sharedMemoryCacheFillingThreadIsRunning;
                std::thread m_sharedMemoryCacheFillingThread;

                // Mapping of pos_type (within .rec.mem file) --> raw memory (read from .rec.mem file).
                map<uint32_t, odcore::data::Container> m_sharedMemoryCache;
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_RECMEMINDEX_H_*/
