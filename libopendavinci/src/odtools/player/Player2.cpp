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
#include <future>
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
            m_filePosition(0),
            m_available(false) {}

        IndexEntry::IndexEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition) :
            m_sampleTimeStamp(sampleTimeStamp),
            m_filePosition(filePosition),
            m_available(false) {}

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

            // Read complete file and store file positions to containers to
            // create index of available data.
            // The actual reading of Containers is deferred.
            uint32_t totalBytesRead = 0;
            const TimeStamp BEFORE;
            {
                while (m_recFile.good()) {
                    const uint32_t POS_BEFORE = m_recFile.tellg();
                    Container c;
                    m_recFile >> c;

                    if (!m_recFile.eof()) {
                        const uint32_t POS_AFTER = m_recFile.tellg();
                        const uint32_t SIZE = (POS_AFTER - POS_BEFORE);
                        totalBytesRead += SIZE;

                        // Store mapping .rec file position --> index entry.
                        m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(), IndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));
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

                const uint8_t LOOK_AHEAD_IN_S = 10;

//cout << "beg = " << smallestSampleTimePoint << ", end = " << largestSampleTimePoint << ", need to read " << ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY << " entries/s for realtime playback." << endl;

                clog << "[Player2]: Reading " << ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * LOOK_AHEAD_IN_S << " entries initially." << endl;

                fillContainerCache(ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * LOOK_AHEAD_IN_S);
            }
        }


        void Player2::fillContainerCache(const uint32_t &maxNumberOfEntriesToReadFromFile) {
            if (m_recFileValid) {
cout << "[Player2]: Request to read " << maxNumberOfEntriesToReadFromFile << endl;
                Lock l(m_indexMutex);

                // Reset any fstream's error states.
                m_recFile.clear();

                uint32_t entriesReadFromFile = 0;
                while ( (m_nextEntryToReadFromFile != m_index.end())
                     && (entriesReadFromFile < maxNumberOfEntriesToReadFromFile) ) {
                    // Move to corresponding position in the .rec file.
                    m_recFile.seekg(m_nextEntryToReadFromFile->second.m_filePosition);

                    // Read the corresponding container.
                    Container c;
                    m_recFile >> c;

                    // Store the container in the container cache.
                    const bool SUCCESSFULLY_INSERTED = m_containerCache.emplace(std::make_pair(m_nextEntryToReadFromFile->second.m_filePosition, c)).second;
                    m_nextEntryToReadFromFile->second.m_available = SUCCESSFULLY_INSERTED;

                    m_nextEntryToReadFromFile++;
                    entriesReadFromFile++;
                }
                m_numberOfAvailableEntries += entriesReadFromFile;
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
                    fillContainerCache(m_containerReplayThroughput * LOOK_AHEAD_IN_S);
                }

                // TODO: Erase played entries.
            }


            Lock l(m_indexMutex);
            const Container &retVal = m_containerCache[m_currentContainerToReplay->second.m_filePosition];
            m_delay = retVal.getSampleTimeStamp().toMicroseconds() - m_containerCache[m_previousContainerAlreadyReplayed->second.m_filePosition].getSampleTimeStamp().toMicroseconds();
            m_previousContainerAlreadyReplayed = m_currentContainerToReplay++;

            m_numberOfReturnedContainersInTotal++;
            m_numberOfAvailableEntries--;

            const uint64_t ELAPSED = (thisTimePointCallingThisMethod - m_firstTimePointReturningAContainer).toMicroseconds();
            m_containerReplayThroughput = std::ceil(m_numberOfReturnedContainersInTotal*1000.0*1000.0/ELAPSED);


if (++callCounter%1000 == 0) {
    cout << "Throughput = " << m_containerReplayThroughput << endl;
    callCounter = 0;
}

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

//////////////////////////

//            if (!m_currentContainerToReplay->second.m_available) {
//                auto handle = std::async(std::launch::async, &Player2::readEntryAsynchronously, this, m_currentContainerToReplay->second.m_filePosition);
//                Container c = handle.get();

//                auto it = m_containerCache.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(), c));
//                m_currentContainerToReplay->second.m_entry = it;
//                m_currentContainerToReplay->second.m_available = true;
//            }


/*
                    if (entries <= INITIAL_ENTRIES) {
                        auto it = m_containerCache.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(), c));
                        // Using map::insert(hint, ...) to have amortized constant complexity.
                        m_currentContainerToReplay = m_index.emplace_hint(m_currentContainerToReplay, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), IndexEntry(c.getSampleTimeStamp().toMicroseconds(), posBefore, true, it)));
                    }
                    else {
                        // Using map::insert(hint, ...) to have amortized constant complexity.
                        m_currentContainerToReplay = m_index.emplace_hint(m_currentContainerToReplay, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), IndexEntry(c.getSampleTimeStamp().toMicroseconds(), posBefore)));
                    }

*/


//////////////////////////

    } // player
} // tools
