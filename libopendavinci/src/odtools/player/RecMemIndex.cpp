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
#include <string>
#include <thread>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/GeneratedHeaders_OpenDaVINCI.h>

#include <opendavinci/odtools/player/RecMemIndex.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;

        ////////////////////////////////////////////////////////////////////////

        RawMemoryBufferEntry::RawMemoryBufferEntry() :
            m_container(),
            m_rawMemoryBuffer(NULL),
            m_lengthOfRawMemoryBuffer(0) {}

        RawMemoryBufferEntry::~RawMemoryBufferEntry() {
            if ((NULL != m_rawMemoryBuffer) && (m_lengthOfRawMemoryBuffer > 0)) {
                OPENDAVINCI_CORE_FREE_POINTER(m_rawMemoryBuffer);
            }
            m_rawMemoryBuffer = NULL;
            m_lengthOfRawMemoryBuffer = 0;
        }

        RawMemoryBufferEntry::RawMemoryBufferEntry(const RawMemoryBufferEntry &obj) :
            m_container(obj.m_container),
            m_rawMemoryBuffer(obj.m_rawMemoryBuffer),
            m_lengthOfRawMemoryBuffer(obj.m_lengthOfRawMemoryBuffer) {}

        RawMemoryBufferEntry& RawMemoryBufferEntry::operator=(const RawMemoryBufferEntry &obj) {
            m_container = obj.m_container;
            m_rawMemoryBuffer = obj.m_rawMemoryBuffer;
            m_lengthOfRawMemoryBuffer = obj.m_lengthOfRawMemoryBuffer;
            return *this;
        }

        ////////////////////////////////////////////////////////////////////////

        RecMemIndex::RecMemIndex(const URL &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments) :
            m_url(url),
            m_recMemFile(),
            m_recMemFileValid(false),
            m_indexMutex(),
            m_index(),
            m_rawMemoryBufferFillingThreadIsRunningMutex(),
            m_rawMemoryBufferFillingThreadIsRunning(false),
            m_rawMemoryBufferFillingThread(),
            m_rawMemoryBuffer() {
cout << "Acquiring " << numberOfMemorySegments << " of " << memorySegmentSize << " bytes." << endl;
            initializeIndex();

            // Start concurrent thread to manage the cache for shared memory dumps.
            setRawMemoryBufferFillingRunning(true);
            m_rawMemoryBufferFillingThread = std::thread(&RecMemIndex::manageRawMemoryBuffer, this);
        }

        RecMemIndex::~RecMemIndex() {
cout << "Closing RecMemIndex" << endl;
            // Stop concurrent thread to manage cache.
            setRawMemoryBufferFillingRunning(false);
            m_rawMemoryBufferFillingThread.join();

            m_recMemFile.close();
        }

        void RecMemIndex::initializeIndex() {
            if (m_url.getResource().find(".rec.mem") != string::npos) {
                m_recMemFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
                m_recMemFileValid = m_recMemFile.good();

                // Determine file size to display progress.
                m_recMemFile.seekg(0, m_recMemFile.end);
                int64_t fileLength = m_recMemFile.tellg();
                m_recMemFile.seekg(0, m_recMemFile.beg);

                // Read complete file and store file positions to containers
                // preceding the shared memory dumps to create an index of
                // available data. The actual reading of shared memory
                // dumps is deferred.
                uint64_t totalBytesRead = 0;
                const TimeStamp BEFORE;
                {
                    int32_t oldPercentage = -1;
                    while (m_recMemFile.good()) {
                        const uint64_t POS_BEFORE = m_recMemFile.tellg();
                            Container c;
                            m_recMemFile >> c;
                        const uint64_t POS_AFTER = m_recMemFile.tellg();

                        if (!m_recMemFile.eof()) {
                            totalBytesRead += (POS_AFTER - POS_BEFORE);

                            // Skip the binary dump of the shared memory segment
                            // directly following the Container.
                            uint64_t bytesToSkip = 0;
                            if (c.getDataType() == odcore::data::SharedData::ID()) {
                                bytesToSkip = c.getData<odcore::data::SharedData>().getSize();
                            }
                            if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                                bytesToSkip = c.getData<odcore::data::image::SharedImage>().getSize();
                            }
                            if (c.getDataType() == odcore::data::SharedPointCloud::ID()) {
                                bytesToSkip = c.getData<odcore::data::SharedPointCloud>().getSize();
                            }
                            const uint64_t CURRENT_POSITION_IN_RECMEM_FILE = m_recMemFile.tellg();
                            m_recMemFile.seekg(CURRENT_POSITION_IN_RECMEM_FILE + bytesToSkip);
                            totalBytesRead += bytesToSkip;

//                            // Store mapping .rec file position --> index entry.
//                            m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(),
//                                                           RecMemIndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));

                            const int32_t percentage = static_cast<int32_t>(static_cast<float>(m_recMemFile.tellg()*100.0)/static_cast<float>(fileLength));
                            if ( (percentage % 5 == 0) && (percentage != oldPercentage) ) {
                                clog << "[odtools::player::RecMemIndex]: Indexed " << percentage << "% from " << m_url.toString() << "." << endl;
                                oldPercentage = percentage;
                            }
                        }
                    }
                }
                const TimeStamp AFTER;

                // Reset pointer to beginning of the .rec.mem file.
                if (m_recMemFileValid) {
                    clog << "[odtools::player::RecMemIndex]: " << m_url.getResource()
//                                          << " contains " << m_index.size() << " entries; "
                                          << "read " << totalBytesRead << " bytes "
                                          << "took " << (AFTER-BEFORE).toMicroseconds()/(1000.0*1000.0) << "s." << endl;
                }
            }
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
//                        m_nextEntryToReadFromRecFile->second.m_available = m_rawMemoryBuffer.emplace(std::make_pair(m_nextEntryToReadFromRecFile->second.m_filePosition, c)).second;
//                    }

//                    m_nextEntryToReadFromRecFile++;
//                    entriesReadFromFile++;
//                }
            }

            return entriesReadFromFile;
        }

        ////////////////////////////////////////////////////////////////////////

        void RecMemIndex::setRawMemoryBufferFillingRunning(const bool &running) {
            Lock l(m_rawMemoryBufferFillingThreadIsRunningMutex);
            m_rawMemoryBufferFillingThreadIsRunning = running;
        }

        bool RecMemIndex::isRawMemoryBufferFillingRunning() const {
            Lock l(m_rawMemoryBufferFillingThreadIsRunningMutex);
            return m_rawMemoryBufferFillingThreadIsRunning;
        }

        void RecMemIndex::manageRawMemoryBuffer() {
//            uint32_t numberOfEntries = 0;
            while (isRawMemoryBufferFillingRunning()) {
//                {
//                    Lock l(m_indexMutex);
//                    numberOfEntries = m_rawMemoryBuffer.size();
//                }
//                // If filling level is around 25%, pour in 1.25 times the amount.
//                if (numberOfEntries < 0.25*m_desiredInitialLevel) {
//                    const uint32_t entriesReadFromFile = fillContainerCache(1.25 * m_desiredInitialLevel);
//                    if (entriesReadFromFile > 0) {
//                        clog << "[odtools::player::RecMemIndex]: Number of entries in cache: "  << numberOfEntries << ". " << entriesReadFromFile << " added to cache. " << m_rawMemoryBuffer.size() << " entries available." << endl;
//                    }
//                }
                // Manage cache at 10 Hz.
                Thread::usleepFor(100 * RecMemIndex::ONE_MILLISECOND_IN_MICROSECONDS);
            }
        }

    } // player
} // tools
