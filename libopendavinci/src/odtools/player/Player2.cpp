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
#include <opendavinci/odcore/base/Thread.h>

#include <opendavinci/odtools/player/Player2.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::io;

        IndexEntry::IndexEntry() : IndexEntry(0, 0) {}

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
            m_previousPreviousContainerAlreadyReplayed(m_index.end()),
            m_previousContainerAlreadyReplayed(m_index.begin()),
            m_currentContainerToReplay(m_index.begin()),
            m_nextEntryToReadFromRecFile(m_index.begin()),
            m_containerReadFromFileThroughput(0),
            m_desiredInitialLevel(0),
            m_firstTimePointReturningAContainer(),
            m_numberOfReturnedContainersInTotal(0),
            m_containerReplayThroughput(0),
            m_delay(0),
            m_containerCacheFillingThreadIsRunningMutex(),
            m_containerCacheFillingThreadIsRunning(false),
            m_containerCacheFillingThread(),
            m_containerCache() {
            initializeIndex();
            computeInitialCacheLevelAndFillCache();

            // Start concurrent thread to manage cache.
            setContainerCacheFillingRunning(true);
            m_containerCacheFillingThread = std::thread(&Player2::manageCache, this);
        }

        Player2::~Player2() {
            // Stop concurrent thread to manage cache.
            setContainerCacheFillingRunning(false);
            m_containerCacheFillingThread.join();

            m_recFile.close();
        }

        void Player2::initializeIndex() {
            m_recFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
            m_recFileValid = m_recFile.good();

            // Determine file size to display progress.
            m_recFile.seekg(0, m_recFile.end);
            int32_t fileLength = m_recFile.tellg();
            m_recFile.seekg(0, m_recFile.beg);

            // Read complete file and store file positions to containers to create
            // index of available data. The actual reading of Containers is deferred.
            uint32_t totalBytesRead = 0;
            const TimeStamp BEFORE;
            {
                int32_t oldPercentage = -1;
                while (m_recFile.good()) {
                    const uint32_t POS_BEFORE = m_recFile.tellg();
                        Container c;
                        m_recFile >> c;
                    const uint32_t POS_AFTER = m_recFile.tellg();

                    if (!m_recFile.eof()) {
                        totalBytesRead += (POS_AFTER - POS_BEFORE);

                        // Store mapping .rec file position --> index entry.
                        m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(),
                                                       IndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));

                        const int32_t percentage = static_cast<int32_t>(static_cast<float>(m_recFile.tellg()*100.0)/static_cast<float>(fileLength));
                        if ( (percentage % 5 == 0) && (percentage != oldPercentage) ) {
                            clog << "[Player2]: Indexed " << percentage << "%." << endl;
                            oldPercentage = percentage;
                        }
                    }
                }
            }
            const TimeStamp AFTER;

            // Reset pointer to beginning of the .rec file.
            if (m_recFileValid) {
                // Compute throughput for reading from file.
                m_containerReadFromFileThroughput = std::ceil(m_index.size()*static_cast<float>(Player2::ONE_SECOND_IN_MICROSECONDS)/(AFTER-BEFORE).toMicroseconds());

                clog << "[Player2]: " << m_url.getResource()
                                      << " contains " << m_index.size() << " entries; "
                                      << "read " << totalBytesRead << " bytes ("
                                      << m_containerReadFromFileThroughput << " entries/s)." << endl;
            }
        }

        void Player2::resetCaches() {
            Lock l(m_indexMutex);
            m_delay = 0;
            m_containerCache.clear();
        }

        void Player2::resetIterators() {
            Lock l(m_indexMutex);
            // Point to first entry in index.
            m_nextEntryToReadFromRecFile
                = m_previousContainerAlreadyReplayed
                = m_currentContainerToReplay
                = m_index.begin();
            // Invalidate iterator for erasing entries point.
            m_previousPreviousContainerAlreadyReplayed = m_index.end();
        }

        void Player2::computeInitialCacheLevelAndFillCache() {
            if (m_recFileValid && (m_index.size() > 0) ) {
                int64_t smallestSampleTimePoint = numeric_limits<int64_t>::max();
                int64_t largestSampleTimePoint = numeric_limits<int64_t>::min();
                for (auto it = m_index.begin(); it != m_index.end(); it++) {
                    smallestSampleTimePoint = std::min(smallestSampleTimePoint, it->first);
                    largestSampleTimePoint = std::max(largestSampleTimePoint, it->first);
                }

                const uint32_t ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY = std::ceil(m_index.size()*(static_cast<float>(Player2::ONE_SECOND_IN_MICROSECONDS))/(largestSampleTimePoint - smallestSampleTimePoint));
                m_desiredInitialLevel = ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * Player2::LOOK_AHEAD_IN_S;

                clog << "[Player2]: Initializing cache with " << m_desiredInitialLevel << " entries." << endl;

                resetCaches();
                resetIterators();
                fillContainerCache(m_desiredInitialLevel);
            }
        }

        uint32_t Player2::fillContainerCache(const uint32_t &maxNumberOfEntriesToReadFromFile) {
            uint32_t entriesReadFromFile = 0;
            if (m_recFileValid && (maxNumberOfEntriesToReadFromFile > 0)) {
                // Reset any fstream's error states.
                m_recFile.clear();

                while ( (m_nextEntryToReadFromRecFile != m_index.end())
                     && (entriesReadFromFile < maxNumberOfEntriesToReadFromFile) ) {
                    // Move to corresponding position in the .rec file.
                    m_recFile.seekg(m_nextEntryToReadFromRecFile->second.m_filePosition);

                    // Read the corresponding container.
                    Container c;
                    m_recFile >> c;

                    // Store the container in the container cache.
                    {
                        Lock l(m_indexMutex);
                        m_nextEntryToReadFromRecFile->second.m_available = m_containerCache.emplace(std::make_pair(m_nextEntryToReadFromRecFile->second.m_filePosition, c)).second;
                    }

                    m_nextEntryToReadFromRecFile++;
                    entriesReadFromFile++;
                }
            }

            return entriesReadFromFile;
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
            TimeStamp thisTimePointCallingThisMethod;

            checkForEndOfIndexAndThrowExceptionOrAutoRewind();

            checkAvailabilityOfNextContainerToBeReplayed();

            Lock l(m_indexMutex);
            const Container &retVal = m_containerCache[m_currentContainerToReplay->second.m_filePosition];
            m_delay = m_currentContainerToReplay->first - m_previousContainerAlreadyReplayed->first;

            // TODO: Delegate deleting into own thread.
            if (m_previousPreviousContainerAlreadyReplayed != m_index.end()) {
                auto it = m_containerCache.find(m_previousContainerAlreadyReplayed->second.m_filePosition);
                if (it != m_containerCache.end()) {
                    m_containerCache.erase(it);
                }
            }

            m_previousPreviousContainerAlreadyReplayed = m_previousContainerAlreadyReplayed;
            m_previousContainerAlreadyReplayed = m_currentContainerToReplay++;

            m_numberOfReturnedContainersInTotal++;

            const uint64_t ELAPSED = (thisTimePointCallingThisMethod - m_firstTimePointReturningAContainer).toMicroseconds();
            m_containerReplayThroughput = std::ceil(m_numberOfReturnedContainersInTotal*static_cast<float>(Player2::ONE_SECOND_IN_MICROSECONDS)/ELAPSED);

            return retVal;
        }

        void Player2::checkAvailabilityOfNextContainerToBeReplayed() {
            int32_t numberOfEntries = 0;
            do {
                {
                    Lock l(m_indexMutex);
                    numberOfEntries = m_containerCache.size();
                }
                if (0 == numberOfEntries) {
                    Thread::usleepFor(10 * 1000);
                }
            }
            while (0 == numberOfEntries);
        }

        uint32_t Player2::getDelay() const {
            Lock l(m_indexMutex);
            // Make sure that delay is not exceeding 10s.
            return std::min<uint32_t>(m_delay, Player2::MAX_DELAY_IN_MICROSECONDS);
        }

        void Player2::rewind() {
            // Stop concurrent thread.
            setContainerCacheFillingRunning(false);
            m_containerCacheFillingThread.join();

            computeInitialCacheLevelAndFillCache();

            // Re-start concurrent thread.
            setContainerCacheFillingRunning(true);
            m_containerCacheFillingThread = std::thread(&Player2::manageCache, this);
        }

        bool Player2::hasMoreData() const {
            Lock l(m_indexMutex);
            // File must be successfully opened AND
            //  the Player must be configured as m_autoRewind OR
            //  some entries are left to replay.
            return (m_recFileValid && (m_autoRewind || (m_currentContainerToReplay != m_index.end())));
        }

        ////////////////////////////////////////////////////////////////////////

        void Player2::setContainerCacheFillingRunning(const bool &running) {
            Lock l(m_containerCacheFillingThreadIsRunningMutex);
            m_containerCacheFillingThreadIsRunning = running;
        }

        bool Player2::isContainerCacheFillingRunning() const {
            Lock l(m_containerCacheFillingThreadIsRunningMutex);
            return m_containerCacheFillingThreadIsRunning;
        }

        void Player2::manageCache() {
            // Constants for controller.
            const float Kp = 1.1;
            const float Ki = 1.7;

            // Target value to control for.
            const int32_t W = m_desiredInitialLevel;

            // Controller variables.
            int32_t X = 0;
            int32_t I = 0;
            int32_t E_old = 0;
            TimeStamp previousCycleTimeStamp;

            while (isContainerCacheFillingRunning()) {
                TimeStamp currentCycleTimeStamp;
                {
                    Lock l(m_indexMutex);
                    X = m_containerCache.size();
                }
                const float deltaT = (currentCycleTimeStamp - previousCycleTimeStamp).toMicroseconds()/(1.0*Player2::ONE_SECOND_IN_MICROSECONDS);
                previousCycleTimeStamp = currentCycleTimeStamp;

                // Compute error.
                const int32_t E = W - X;
                const int32_t deltaE = (E - E_old);
                E_old = E;

                // Compute PID values.
                const int32_t P = E;
                I += deltaE * deltaT;

                const int32_t Y = Kp*P + Ki*I;
                const uint32_t entriesReadFromFile = fillContainerCache(std::max(Y, 0));
                if (entriesReadFromFile > 0) {
//                    clog << "[Player2]: " << entriesReadFromFile << " entries added to cache." << " P = " << P << ", I = " << I << ", S = " << m_containerCache.size() << endl;
                }

                // Manage cache at 4 Hz.
                Thread::usleepFor(250 * 1000);
            }
        }

    } // player
} // tools
