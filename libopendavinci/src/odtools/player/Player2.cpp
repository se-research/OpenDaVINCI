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

#include <opendavinci/odcore/base/module/AbstractCIDModule.h>
#include <opendavinci/odcore/base/Lock.h>

#include <opendavinci/odtools/player/Player2.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::io;

        IndexEntry::IndexEntry() :
            m_sampleTimeStamp(0),
            m_filePosition(0) {}

        IndexEntry::IndexEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition) :
            m_sampleTimeStamp(sampleTimeStamp),
            m_filePosition(filePosition) {}

        ////////////////////////////////////////////////////////////////////////

        Player2::Player2(const URL &url, const bool &autoRewind) :
            m_url(url),
            m_recFile(),
            m_recFileValid(false),
            m_autoRewind(autoRewind),
            m_indexMutex(),
            m_index(),
            m_previousContainerAlreadyReplayed(m_index.begin()),
            m_currentContainerToReplay(m_index.begin()),
            m_numberOfAvailableEntries(0),
            m_nextEntryToReadFromFile(m_index.begin()),
            m_containerReadFromFileThroughput(0),
            m_firstTimePointReturningAContainer(),
            m_numberOfReturnedContainersInTotal(0),
            m_containerReplayThroughput(0),
            m_readingRequested(false),
            handle(),
            m_delay(0),
            m_containerCache() {
            initializeIndex();
            computeInitialCacheLevelAndFillCache();
        }

        Player2::~Player2() {
            m_recFile.close();
        }

        void Player2::initializeIndex() {
            m_recFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
            m_recFileValid = m_recFile.good();

            // Determine file size to display progress.
            m_recFile.seekg(0, m_recFile.end);
            int32_t fileLength = m_recFile.tellg();
            m_recFile.seekg(0, m_recFile.beg);

            // Read complete file and store file positions to containers to
            // create index of available data.
            // The actual reading of Containers is deferred.
            uint32_t totalBytesRead = 0;
            int32_t oldPercentage = -1;
            const TimeStamp BEFORE;
            {
                while (m_recFile.good()) {
                    const uint32_t POS_BEFORE = m_recFile.tellg();
                    Container c;
                    m_recFile >> c;

                    if (!m_recFile.eof()) {
                        const uint32_t POS_AFTER = m_recFile.tellg();
                        totalBytesRead += (POS_AFTER - POS_BEFORE);

                        // Store mapping .rec file position --> index entry.
                        m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(), IndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));

                        {
                            float percentage = (float)(m_recFile.tellg()*100.0)/(float)fileLength;
                            if ( (static_cast<int32_t>(percentage) % 5 == 0) && (static_cast<int32_t>(percentage) != oldPercentage) ) {
                                clog << "[Player2]: Processed " << static_cast<int32_t>(percentage) << "%." << endl;
                                oldPercentage = static_cast<int32_t>(percentage);
                            }
                        }
                    }
                }
            }
            const TimeStamp AFTER;

            // Reset pointer to beginning of the .rec file.
            if (m_recFileValid) {
                m_recFile.clear();
                m_recFile.seekg(0, ios::beg);

                // Point to first entry.
                m_nextEntryToReadFromFile
                    = m_previousContainerAlreadyReplayed
                    = m_currentContainerToReplay
                    = m_index.begin();

                // Compute throughput for reading from file.
                m_containerReadFromFileThroughput = std::ceil(m_index.size()*1000.0*1000.0/(AFTER-BEFORE).toMicroseconds());

                clog << "[Player2]: " << m_url.getResource() << " contains " << m_index.size() << " entries; read " << totalBytesRead << " bytes (" << m_containerReadFromFileThroughput << " entries/s)." << endl;
            }
        }

        void Player2::computeInitialCacheLevelAndFillCache() {
            if (m_recFileValid && (m_index.size() > 0) ) {
                int64_t smallestSampleTimePoint = numeric_limits<int64_t>::max();
                int64_t largestSampleTimePoint = numeric_limits<int64_t>::min();
                {
                    for (auto it = m_index.begin(); it != m_index.end(); it++) {
                        smallestSampleTimePoint = (smallestSampleTimePoint > it->first) ? it->first : smallestSampleTimePoint;
                        largestSampleTimePoint = (largestSampleTimePoint < it->first) ? it->first : largestSampleTimePoint;
                    }
                }
                const uint32_t ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY = std::ceil(m_index.size()*(1000.0*1000.0)/(largestSampleTimePoint - smallestSampleTimePoint));

                const uint8_t LOOK_AHEAD_IN_S = 10 * 3;
                clog << "[Player2]: Reading " << ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * LOOK_AHEAD_IN_S << " entries initially." << endl;

                fillContainerCache(ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * LOOK_AHEAD_IN_S);
            }
        }


        void Player2::fillContainerCache(const uint32_t &maxNumberOfEntriesToReadFromFile) {
            if (m_recFileValid) {
                // Reset any fstream's error states.
                m_recFile.clear();

                uint32_t entriesReadFromFile = 0;
// TODO: Add Auto Rewind
                while ( (m_nextEntryToReadFromFile != m_index.end())
                     && (entriesReadFromFile < maxNumberOfEntriesToReadFromFile) ) {
                    // Move to corresponding position in the .rec file.
                    m_recFile.seekg(m_nextEntryToReadFromFile->second.m_filePosition);

                    // Read the corresponding container.
                    Container c;
                    m_recFile >> c;

                    // Store the container in the container cache.
                    {
                        Lock l(m_indexMutex);
                        m_containerCache.emplace(std::make_pair(m_nextEntryToReadFromFile->second.m_filePosition, c)).second;
                    }

                    m_nextEntryToReadFromFile++;
                    entriesReadFromFile++;
                }

                {
                    Lock l(m_indexMutex);
                    m_numberOfAvailableEntries += entriesReadFromFile;
                }

                if (entriesReadFromFile > 0) {
                    clog << "[Player2]: " << entriesReadFromFile << " entries read." << endl;
                }
            }

            {
                Lock l(m_indexMutex);
                m_readingRequested = false;
            }
        }

        void Player2::checkForEndOfIndexAndThrowExceptionOrAutoRewind() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            // If at "EOF", either throw exception of autorewind.
            if (m_currentContainerToReplay == m_index.end()) {
                if (!m_autoRewind) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(ArrayIndexOutOfBoundsException, "m_currentContainerToReplay != m_index.end() failed.");
                }
                else {
                    rewind();
                }
            }
        }

        Container Player2::getNextContainerToBeSent() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            return getNextContainerToBeSentNoCopy();
        }

        const odcore::data::Container& Player2::getNextContainerToBeSentNoCopy() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            static uint8_t callCounter = 0;
            TimeStamp thisTimePointCallingThisMethod;

            checkForEndOfIndexAndThrowExceptionOrAutoRewind();

            {
                // TODO: Cache management.
                const uint8_t LOOK_AHEAD_IN_S = 10;
                if ( (m_containerReplayThroughput * LOOK_AHEAD_IN_S) > m_numberOfAvailableEntries) {
                    Lock l(m_indexMutex);
                    if (!m_readingRequested) {
                        m_readingRequested = true;
                        handle = std::async(std::launch::async, &Player2::fillContainerCache, this, m_containerReplayThroughput * LOOK_AHEAD_IN_S * 3);
                    }

//                    fillContainerCache(m_containerReplayThroughput * LOOK_AHEAD_IN_S * 3);
                }
            }


            Lock l(m_indexMutex);
            const Container &retVal = m_containerCache[m_currentContainerToReplay->second.m_filePosition];
            m_delay = retVal.getSampleTimeStamp().toMicroseconds() - m_containerCache[m_previousContainerAlreadyReplayed->second.m_filePosition].getSampleTimeStamp().toMicroseconds();

            // Make sure that delay is not exceeding 10s.
            m_delay = std::min<uint32_t>(m_delay, 10*1000*1000);

// TODO: Delete here.

            m_previousContainerAlreadyReplayed = m_currentContainerToReplay++;

            m_numberOfReturnedContainersInTotal++;
            m_numberOfAvailableEntries--;

            const uint64_t ELAPSED = (thisTimePointCallingThisMethod - m_firstTimePointReturningAContainer).toMicroseconds();
            m_containerReplayThroughput = std::ceil(m_numberOfReturnedContainersInTotal*1000.0*1000.0/ELAPSED);

/*<REMOVE ME>*/
if (++callCounter%1000 == 0) {
    cout << "Throughput = " << m_containerReplayThroughput << " containers/s." << endl;
    callCounter = 0;
}
/*</REMOVE ME>*/

            return retVal;
        }

        uint32_t Player2::getDelay() const {
            Lock l(m_indexMutex);
            return m_delay;
        }

        void Player2::rewind() {
            Lock l(m_indexMutex);
            m_previousContainerAlreadyReplayed = m_currentContainerToReplay = m_index.begin();
        }

        bool Player2::hasMoreData() const {
            Lock l(m_indexMutex);
            // File must be successfully opened AND
            //  the Player must be configured as m_autoRewind OR
            //  some entries are left to replay.
            return (m_recFileValid && (m_autoRewind || (m_currentContainerToReplay != m_index.end())));
        }

    } // player
} // tools
