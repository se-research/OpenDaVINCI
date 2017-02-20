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

#include <cmath>
#include <cstdio>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <thread>
#include <utility>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>

#include <opendavinci/odtools/player/RecMemIndex.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;

        RecMemIndexEntry::RecMemIndexEntry() : RecMemIndexEntry(0, 0) {}

        RecMemIndexEntry::RecMemIndexEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition) :
            m_sampleTimeStamp(sampleTimeStamp),
            m_filePosition(filePosition),
            m_available(false) {}

        ////////////////////////////////////////////////////////////////////////

        RecMemIndex::RecMemIndex(const URL &url) :
            m_url(url),
            m_recMemFile(),
            m_recMemFileValid(false),
            m_indexMutex(),
            m_index(),
            m_sharedMemoryCacheFillingThreadIsRunningMutex(),
            m_sharedMemoryCacheFillingThreadIsRunning(false),
            m_sharedMemoryCacheFillingThread(),
            m_sharedMemoryCache() {
            initializeIndex();

            // Start concurrent thread to manage the cache for shared memory dumps.
            setSharedMemoryCacheFillingRunning(true);
            m_sharedMemoryCacheFillingThread = std::thread(&RecMemIndex::manageSharedMemoryCache, this);
        }

        RecMemIndex::~RecMemIndex() {
            // Stop concurrent thread to manage cache.
            setSharedMemoryCacheFillingRunning(false);
            m_sharedMemoryCacheFillingThread.join();

            m_recMemFile.close();
        }

        void RecMemIndex::initializeIndex() {
//            m_recMemFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
//            m_recMemFileValid = m_recMemFile.good();

//            // Determine file size to display progress.
//            m_recMemFile.seekg(0, m_recMemFile.end);
//            int32_t fileLength = m_recMemFile.tellg();
//            m_recMemFile.seekg(0, m_recMemFile.beg);

//            // Read complete file and store file positions to containers to create
//            // index of available data. The actual reading of Containers is deferred.
//            uint32_t totalBytesRead = 0;
//            const TimeStamp BEFORE;
//            {
//                int32_t oldPercentage = -1;
//                while (m_recMemFile.good()) {
//                    const uint32_t POS_BEFORE = m_recMemFile.tellg();
//                        Container c;
//                        m_recMemFile >> c;
//                    const uint32_t POS_AFTER = m_recMemFile.tellg();

//                    if (!m_recMemFile.eof()) {
//                        totalBytesRead += (POS_AFTER - POS_BEFORE);

//                        // Store mapping .rec file position --> index entry.
//                        m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(),
//                                                       RecMemIndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));

//                        const int32_t percentage = static_cast<int32_t>(static_cast<float>(m_recMemFile.tellg()*100.0)/static_cast<float>(fileLength));
//                        if ( (percentage % 5 == 0) && (percentage != oldPercentage) ) {
//                            clog << "[odtools::player::RecMemIndex]: Indexed " << percentage << "%." << endl;
//                            oldPercentage = percentage;
//                        }
//                    }
//                }
//            }
//            const TimeStamp AFTER;

//            // Reset pointer to beginning of the .rec file.
//            if (m_recMemFileValid) {
//                // Compute throughput for reading from file.
//                m_containerReadFromFileThroughput = std::ceil(m_index.size()*static_cast<float>(RecMemIndex::ONE_SECOND_IN_MICROSECONDS)/(AFTER-BEFORE).toMicroseconds());

//                clog << "[odtools::player::RecMemIndex]: " << m_url.getResource()
//                                      << " contains " << m_index.size() << " entries; "
//                                      << "read " << totalBytesRead << " bytes ("
//                                      << m_containerReadFromFileThroughput << " entries/s)." << endl;
//            }
        }

        uint32_t RecMemIndex::fillContainerCache(const uint32_t &maxNumberOfEntriesToReadFromFile) {
            uint32_t entriesReadFromFile = 0;
            if (m_recMemFileValid && (maxNumberOfEntriesToReadFromFile > 0)) {
//                // Reset any fstream's error states.
//                m_recMemFile.clear();

//                while ( (m_nextEntryToReadFromRecFile != m_index.end())
//                     && (entriesReadFromFile < maxNumberOfEntriesToReadFromFile) ) {
//                    // Move to corresponding position in the .rec file.
//                    m_recMemFile.seekg(m_nextEntryToReadFromRecFile->second.m_filePosition);

//                    // Read the corresponding container.
//                    Container c;
//                    m_recMemFile >> c;

//                    // Store the container in the container cache.
//                    {
//                        Lock l(m_indexMutex);
//                        m_nextEntryToReadFromRecFile->second.m_available = m_sharedMemoryCache.emplace(std::make_pair(m_nextEntryToReadFromRecFile->second.m_filePosition, c)).second;
//                    }

//                    m_nextEntryToReadFromRecFile++;
//                    entriesReadFromFile++;
//                }
            }

            return entriesReadFromFile;
        }

        ////////////////////////////////////////////////////////////////////////

        void RecMemIndex::setSharedMemoryCacheFillingRunning(const bool &running) {
            Lock l(m_sharedMemoryCacheFillingThreadIsRunningMutex);
            m_sharedMemoryCacheFillingThreadIsRunning = running;
        }

        bool RecMemIndex::isSharedMemoryCacheFillingRunning() const {
            Lock l(m_sharedMemoryCacheFillingThreadIsRunningMutex);
            return m_sharedMemoryCacheFillingThreadIsRunning;
        }

        void RecMemIndex::manageSharedMemoryCache() {
//            uint32_t numberOfEntries = 0;
            while (isSharedMemoryCacheFillingRunning()) {
//                {
//                    Lock l(m_indexMutex);
//                    numberOfEntries = m_sharedMemoryCache.size();
//                }
//                // If filling level is around 25%, pour in 1.25 times the amount.
//                if (numberOfEntries < 0.25*m_desiredInitialLevel) {
//                    const uint32_t entriesReadFromFile = fillContainerCache(1.25 * m_desiredInitialLevel);
//                    if (entriesReadFromFile > 0) {
//                        clog << "[odtools::player::RecMemIndex]: Number of entries in cache: "  << numberOfEntries << ". " << entriesReadFromFile << " added to cache. " << m_sharedMemoryCache.size() << " entries available." << endl;
//                    }
//                }
                // Manage cache at 10 Hz.
                Thread::usleepFor(100 * RecMemIndex::ONE_MILLISECOND_IN_MICROSECONDS);
            }
        }

    } // player
} // tools
