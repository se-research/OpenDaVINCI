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
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>

#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>
#include <opendavinci/odcore/wrapper/SharedMemoryFactory.h>

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
            return (*this);
        }

        ////////////////////////////////////////////////////////////////////////

        RecMemIndex::RecMemIndex(const URL &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
            m_url(url),
            m_recMemFile(),
            m_recMemFileValid(false),
            m_indexMutex(),
            m_index(),
            m_nextEntryToPlayBack(),
            m_nextEntryToReadFromRecMemFile(),
            m_hasMoreData(false),
            m_rawMemoryBuffer(),
            m_unusedEntriesFromRawMemoryBuffer(),
            m_allEntriesFromRawMemoryBuffer(),
            m_mapOfPointersToSharedMemorySegments(),
            m_rawMemoryBufferFillingThreadIsRunningMutex(),
            m_rawMemoryBufferFillingThreadIsRunning(false),
            m_rawMemoryBufferFillingThread() {
            clog << "[odtools::player::RecMemIndex]: Acquiring " << numberOfMemorySegments << " memory segments of " << memorySegmentSize << " bytes...";
            for(uint16_t id = 0; id < numberOfMemorySegments; id++) {
                shared_ptr<RawMemoryBufferEntry> e = shared_ptr<RawMemoryBufferEntry>(new RawMemoryBufferEntry());
                e->m_rawMemoryBuffer = static_cast<char*>(::malloc(memorySegmentSize));
                e->m_lengthOfRawMemoryBuffer = memorySegmentSize;
                m_unusedEntriesFromRawMemoryBuffer.push_back(e);

                // This vector holds all entries for reuse.
                m_allEntriesFromRawMemoryBuffer.push_back(e);
            }
            clog << "done." << endl;

            initializeIndex();

            // Fill raw buffer.
            manageRawMemoryBuffer();

            if (m_threading) {
                // Start concurrent thread to manage the cache for shared memory dumps.
                setRawMemoryBufferFillingRunning(true);
                m_rawMemoryBufferFillingThread = std::thread(&RecMemIndex::manageRawMemoryBuffer, this);
            }
        }

        RecMemIndex::~RecMemIndex() {
            if (m_threading) {
                // Stop concurrent thread to manage cache.
                setRawMemoryBufferFillingRunning(false);
                m_rawMemoryBufferFillingThread.join();
            }

            m_recMemFile.close();

            clog << "[odtools::player::RecMemIndex]: Clearing " << m_allEntriesFromRawMemoryBuffer.size() << " entries from buffer...";
                // Entries will be automatically freed due to the shared_ptr<...>.
                m_unusedEntriesFromRawMemoryBuffer.clear();
                m_index.clear();
                m_allEntriesFromRawMemoryBuffer.clear();
            clog << "done." << endl;

            // Release shared memory segments.
            m_mapOfPointersToSharedMemorySegments.clear();
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
                            string nameOfSharedMemorySegment = "";
                            if (c.getDataType() == odcore::data::SharedData::ID()) {
                                odcore::data::SharedData sd = c.getData<odcore::data::SharedData>();
                                bytesToSkip = sd.getSize();
                                nameOfSharedMemorySegment = sd.getName();
                            }
                            if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                                odcore::data::image::SharedImage si = c.getData<odcore::data::image::SharedImage>();
                                bytesToSkip = (si.getSize() > 0) ? si.getSize() : (si.getWidth() * si.getHeight() * si.getBytesPerPixel());
                                nameOfSharedMemorySegment = si.getName();
                            }
                            if (c.getDataType() == odcore::data::SharedPointCloud::ID()) {
                                odcore::data::SharedPointCloud spc = c.getData<odcore::data::SharedPointCloud>();
                                bytesToSkip = spc.getSize();
                                nameOfSharedMemorySegment = spc.getName();
                            }
                            const uint64_t CURRENT_POSITION_IN_RECMEM_FILE = m_recMemFile.tellg();
                            m_recMemFile.seekg(CURRENT_POSITION_IN_RECMEM_FILE + bytesToSkip);
                            totalBytesRead += bytesToSkip;

                            // Store pointer to Container in m_recMemFile ordered by sample time stamp.
                            m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(),
                                                           IndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE, nameOfSharedMemorySegment, bytesToSkip)));

                            const int32_t percentage = static_cast<int32_t>(static_cast<float>(m_recMemFile.tellg()*100.0)/static_cast<float>(fileLength));
                            if ( (percentage % 5 == 0) && (percentage != oldPercentage) ) {
                                clog << "[odtools::player::RecMemIndex]: Indexed " << percentage << "% from " << m_url.toString() << "." << endl;
                                oldPercentage = percentage;
                            }
                        }
                    }
                }
                const TimeStamp AFTER;

                if (m_recMemFileValid) {
                    // Reset pointer to beginning of the .rec.mem file.
                    m_nextEntryToPlayBack
                        = m_nextEntryToReadFromRecMemFile
                        = m_index.begin();

                    clog << "[odtools::player::RecMemIndex]: " << m_url.getResource()
                                          << " contains " << m_index.size() << " entries; "
                                          << "read " << totalBytesRead << " bytes "
                                          << "took " << (AFTER-BEFORE).toMicroseconds()/(1000.0*1000.0) << "s." << endl;
                }
            }
        }

        bool RecMemIndex::hasMoreData() const {
            Lock l(m_indexMutex);
            return m_hasMoreData;
        }

        void RecMemIndex::rewind() {
            if (m_threading) {
                // Stop concurrent thread to manage cache.
                setRawMemoryBufferFillingRunning(false);
                m_rawMemoryBufferFillingThread.join();
            }

            // Reset pointer to beginning of the .rec.mem file.
            m_nextEntryToPlayBack
                = m_nextEntryToReadFromRecMemFile
                = m_index.begin();

            // Clear caches to rebuild it.
            m_rawMemoryBuffer.clear();
            m_unusedEntriesFromRawMemoryBuffer.clear();

            // Make raw buffer entries available again.
            for(auto entry = m_allEntriesFromRawMemoryBuffer.begin();
                entry != m_allEntriesFromRawMemoryBuffer.end();
                entry++) {
                m_unusedEntriesFromRawMemoryBuffer.push_back(*entry);
            }

            // Fill raw buffer.
            manageRawMemoryBuffer();

            if (m_threading) {
                // Start concurrent thread to manage the cache for shared memory dumps.
                setRawMemoryBufferFillingRunning(true);
                m_rawMemoryBufferFillingThread = std::thread(&RecMemIndex::manageRawMemoryBuffer, this);
            }
        }

        int64_t RecMemIndex::peekNextSampleTimeToPlayBack() const {
            Lock l(m_indexMutex);
            return m_nextEntryToPlayBack->first;
        }

        odcore::data::Container RecMemIndex::makeNextRawMemoryEntryAvailable() {
            odcore::data::Container retVal;
            {
                Lock l(m_indexMutex);
                if ( (m_nextEntryToPlayBack->second.m_available) &&
                     (1 == m_rawMemoryBuffer.count(m_nextEntryToPlayBack->second.m_filePosition)) ) {
                    // Load Container from cache to be distributed into container conference.
                    retVal = m_rawMemoryBuffer[m_nextEntryToPlayBack->second.m_filePosition]->m_container;

                    // Transfer raw memory available to shared memory.
                    const string NAME_OF_SHARED_MEMORY_SEGMENT = m_nextEntryToPlayBack->second.m_nameOfSharedMemorySegment;
                    if (0 == m_mapOfPointersToSharedMemorySegments.count(NAME_OF_SHARED_MEMORY_SEGMENT)) {
                        // A shared memory segment has not been acquired for this container.
                        std::shared_ptr<odcore::wrapper::SharedMemory> sp = odcore::wrapper::SharedMemoryFactory::createSharedMemory(NAME_OF_SHARED_MEMORY_SEGMENT, m_nextEntryToPlayBack->second.m_sizeOfSharedMemorySegment);
                        m_mapOfPointersToSharedMemorySegments[NAME_OF_SHARED_MEMORY_SEGMENT] = sp;
                    }

                    if ( (0 < m_mapOfPointersToSharedMemorySegments.count(NAME_OF_SHARED_MEMORY_SEGMENT)) &&
                         (m_mapOfPointersToSharedMemorySegments[NAME_OF_SHARED_MEMORY_SEGMENT]->isValid()) ) {
                        Lock l2(m_mapOfPointersToSharedMemorySegments[NAME_OF_SHARED_MEMORY_SEGMENT]);
                        // Copy data from raw memory buffer into shared memory.
                        ::memcpy(m_mapOfPointersToSharedMemorySegments[NAME_OF_SHARED_MEMORY_SEGMENT]->getSharedMemory(),
                                 m_rawMemoryBuffer[m_nextEntryToPlayBack->second.m_filePosition]->m_rawMemoryBuffer,
                                 /* Limit the amount of data to be copied to the maximum length of the shared memory. */
                                 std::min(m_rawMemoryBuffer[m_nextEntryToPlayBack->second.m_filePosition]->m_lengthOfRawMemoryBuffer, 
                                          m_nextEntryToPlayBack->second.m_sizeOfSharedMemorySegment));
                    }

                    // Mark entry as available.
                    m_nextEntryToReadFromRecMemFile->second.m_available = false;
                    // Remove entry from map of used rawMemoryBuffers.
                    m_unusedEntriesFromRawMemoryBuffer.push_front(m_rawMemoryBuffer[m_nextEntryToPlayBack->second.m_filePosition]);
                }

                // Move to next entry for playback and enable auto-rewind by default.
                m_nextEntryToPlayBack++;
                if (m_nextEntryToPlayBack == m_index.end()) {
                    m_nextEntryToPlayBack = m_index.begin();

                    // We have come to the end of our available containers.
                    m_hasMoreData = false;
                }
            }

            // If not threading, handle cache regularly.
            if (!m_threading) {
                // Fill raw buffer.
                manageRawMemoryBuffer();
            }

            return retVal;
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
            m_hasMoreData = true;
            do {
                if (m_recMemFileValid) {
                    Lock l(m_indexMutex);

                    if (!m_unusedEntriesFromRawMemoryBuffer.empty()) {
                        // Clear any error flags.
                        m_recMemFile.clear();
                    }

                    // TODO: Avoid re-reading the same contaiers.
                    while (!m_unusedEntriesFromRawMemoryBuffer.empty()) {
                        // Always auto-rewind.
                        if (m_nextEntryToReadFromRecMemFile == m_index.end()) {
                            m_nextEntryToReadFromRecMemFile = m_index.begin();
                        }

                        // Find entry in .rec.mem file.
                        m_recMemFile.seekg(m_nextEntryToReadFromRecMemFile->second.m_filePosition);

                        // Get and remove next available entry from unsedRawBuffer.
                        shared_ptr<RawMemoryBufferEntry> entry = m_unusedEntriesFromRawMemoryBuffer.back();
                        m_unusedEntriesFromRawMemoryBuffer.pop_back();

                        // Read data from .rec.mem file.
                        m_recMemFile >> entry->m_container;

                        // Read raw memory dump.
                        m_recMemFile.read(entry->m_rawMemoryBuffer,
                                          std::min(m_nextEntryToReadFromRecMemFile->second.m_sizeOfSharedMemorySegment, entry->m_lengthOfRawMemoryBuffer));

                        // Make entry available in map filePosition -> shared_ptr<RawMemoryBufferEntry>.
                        m_rawMemoryBuffer[m_nextEntryToReadFromRecMemFile->second.m_filePosition] = entry;

                        // Mark this entry as available.
                        m_nextEntryToReadFromRecMemFile->second.m_available = true;

                        // Move forward to read next entry from file.
                        m_nextEntryToReadFromRecMemFile++;
                    }
                }

                // Manage cache at 10 Hz.
                Thread::usleepFor(100 * RecMemIndex::ONE_MILLISECOND_IN_MICROSECONDS);
            } while (isRawMemoryBufferFillingRunning());
        }

    } // player
} // tools
