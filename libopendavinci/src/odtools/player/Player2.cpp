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
#include <opendavinci/odcore/io/URL.h>

#include <opendavinci/odtools/player/Player2.h>
#include <opendavinci/odtools/player/PlayerDelegate.h>
#include <opendavinci/odtools/player/RecMemIndex.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::io;

        IndexEntry::IndexEntry() :
            IndexEntry(0, 0) {}

        IndexEntry::IndexEntry(const int64_t &sampleTimeStamp, const uint64_t &filePosition) :
            IndexEntry(sampleTimeStamp, filePosition, "", 0) {}

        IndexEntry::IndexEntry(const int64_t &sampleTimeStamp, const uint64_t &filePosition, const string &nameOfSharedMemorySegment, const uint32_t &sizeOfSharedMemorySegment) :
            m_sampleTimeStamp(sampleTimeStamp),
            m_filePosition(filePosition),
            m_nameOfSharedMemorySegment(nameOfSharedMemorySegment),
            m_sizeOfSharedMemorySegment(sizeOfSharedMemorySegment),
            m_available(false) {}

        ////////////////////////////////////////////////////////////////////////

        Player2::Player2(const URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
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
            m_desiredInitialLevel(0),
            m_firstTimePointReturningAContainer(),
            m_numberOfReturnedContainersInTotal(0),
            m_delay(0),
            m_correctedDelay(0),
            m_containerCacheFillingThreadIsRunningMutex(),
            m_containerCacheFillingThreadIsRunning(false),
            m_containerCacheFillingThread(),
            m_containerCache(),
            m_recMemIndex(),
            m_mapOfPlayerDelegatesMutex(),
            m_mapOfPlayerDelegates(),
            m_playerListenerMutex(),
            m_playerListener() {
            initializeIndex();
            computeInitialCacheLevelAndFillCache();

            if (m_threading) {
                // Start concurrent thread to manage cache.
                setContainerCacheFillingRunning(true);
                m_containerCacheFillingThread = std::thread(&Player2::manageCache, this);
            }

            // Try reading accompanying .rec.mem file.
            if (m_recFileValid && ((memorySegmentSize * numberOfMemorySegments) > 0)) {
                URL recMemFile("file://" + m_url.getResource() + ".mem");
                bool recMemFileAvailable = false;
                {
                    ifstream checkForRecMemFile(recMemFile.getResource());
                    recMemFileAvailable = checkForRecMemFile.good();
                }
                if (recMemFileAvailable) {
                    m_recMemIndex = unique_ptr<RecMemIndex>(new RecMemIndex(recMemFile, memorySegmentSize, numberOfMemorySegments, m_threading));
                }
            }
        }

        Player2::~Player2() {
            if (m_threading) {
                // Stop concurrent thread to manage cache.
                setContainerCacheFillingRunning(false);
                m_containerCacheFillingThread.join();
            }

            // Free the map of cached container entries.
            m_recMemIndex.reset();

            m_recFile.close();
        }

        ////////////////////////////////////////////////////////////////////////

        void Player2::setPlayerListener(PlayerListener *pl) {
            Lock l(m_playerListenerMutex);
            m_playerListener = pl;
        }

        void Player2::registerPlayerDelegate(const uint32_t &containerID, PlayerDelegate *pd) {
            Lock l(m_mapOfPlayerDelegatesMutex);

            // First, check if we have registered an existing PlayerDelegate for the given ID.
            auto delegate = m_mapOfPlayerDelegates.find(containerID);
            if (delegate != m_mapOfPlayerDelegates.end()) {
                m_mapOfPlayerDelegates.erase(delegate);
            }

            if (NULL != pd) {
                m_mapOfPlayerDelegates[containerID] = pd;
            }
        }

        ////////////////////////////////////////////////////////////////////////

        void Player2::initializeIndex() {
            m_recFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
            m_recFileValid = m_recFile.good();

            // Determine file size to display progress.
            m_recFile.seekg(0, m_recFile.end);
                int64_t fileLength = m_recFile.tellg();
            m_recFile.seekg(0, m_recFile.beg);

            // Read complete file and store file positions to containers to create
            // index of available data. The actual reading of Containers is deferred.
            uint64_t totalBytesRead = 0;
            const TimeStamp BEFORE;
            {
                int32_t oldPercentage = -1;
                while (m_recFile.good()) {
                    const uint64_t POS_BEFORE = m_recFile.tellg();
                        Container c;
                        m_recFile >> c;
                    const uint64_t POS_AFTER = m_recFile.tellg();

                    if (!m_recFile.eof()) {
                        totalBytesRead += (POS_AFTER - POS_BEFORE);

                        // Store mapping .rec file position --> index entry.
                        m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(),
                                                       IndexEntry(c.getSampleTimeStamp().toMicroseconds(), POS_BEFORE)));

                        const int32_t percentage = static_cast<int32_t>(static_cast<float>(m_recFile.tellg()*100.0)/static_cast<float>(fileLength));
                        if ( (percentage % 5 == 0) && (percentage != oldPercentage) ) {
                            clog << "[odtools::player::Player2]: Indexed " << percentage << "% from " << m_url.toString() << "." << endl;
                            oldPercentage = percentage;
                        }
                    }
                }
            }
            const TimeStamp AFTER;

            // Reset pointer to beginning of the .rec file.
            if (m_recFileValid) {
                clog << "[odtools::player::Player2]: " << m_url.getResource()
                                      << " contains " << m_index.size() << " entries; "
                                      << "read " << totalBytesRead << " bytes "
                                      << "in " << (AFTER-BEFORE).toMicroseconds()/(1000.0*1000.0) << "s." << endl;
            }
        }

        void Player2::resetCaches() {
            Lock l(m_indexMutex);
            m_delay = m_correctedDelay = 0;
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
                m_desiredInitialLevel = std::max<uint32_t>(ENTRIES_TO_READ_PER_SECOND_FOR_REALTIME_REPLAY * Player2::LOOK_AHEAD_IN_S,
                                                           MIN_ENTRIES_FOR_LOOK_AHEAD);

                clog << "[odtools::player::Player2]: Initializing cache with " << m_desiredInitialLevel << " entries." << endl;

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
            // If at "EOF", either throw exception or autorewind.
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
            static int64_t lastContainersSampleTimeStamp = 0;
            TimeStamp thisTimePointCallingThisMethod;

            // Check if the .rec file is at end but the .rec.mem file has still content to replay.
            bool hasNoMoreDataFromRecFileButFromRecMemFile = false;
            {
                Lock l(m_indexMutex);
                hasNoMoreDataFromRecFileButFromRecMemFile = (!hasMoreDataFromRecFile() && hasMoreDataFromRecMemFile());
            }
            if (hasNoMoreDataFromRecFileButFromRecMemFile) {
                if (NULL != m_recMemIndex.get()) {
                    Container retVal = m_recMemIndex->makeNextRawMemoryEntryAvailable();
                    int64_t currentContainersSampleTimeStamp = retVal.getSampleTimeStamp().toMicroseconds();
                    m_correctedDelay = m_delay = ((lastContainersSampleTimeStamp > 0) ? (currentContainersSampleTimeStamp - lastContainersSampleTimeStamp) : static_cast<int64_t>(Player2::MAX_DELAY_IN_MICROSECONDS));
                    lastContainersSampleTimeStamp = currentContainersSampleTimeStamp;
                    return retVal;
                }
            }

            checkForEndOfIndexAndThrowExceptionOrAutoRewind();

            checkAvailabilityOfNextContainerToBeReplayed();

            Lock l(m_indexMutex);
            Container retVal;
            Container &nextContainer = m_containerCache[m_currentContainerToReplay->second.m_filePosition];

            // Check if the next Container + shared memory comes from the .rec.mem file.
            const int64_t recContainerSampleTime = nextContainer.getSampleTimeStamp().toMicroseconds();
            bool replayContainerFromRecMem = false;
            if (NULL != m_recMemIndex.get() && hasMoreDataFromRecMemFile()) {
                int64_t recMemContainerSampleTime = m_recMemIndex->peekNextSampleTimeToPlayBack();

                if ((replayContainerFromRecMem = (recContainerSampleTime > recMemContainerSampleTime))) {
                    retVal = m_recMemIndex->makeNextRawMemoryEntryAvailable();
                    m_correctedDelay = m_delay = retVal.getSampleTimeStamp().toMicroseconds() - m_previousContainerAlreadyReplayed->first;
                }
            }

            // Playback from .rec file.
            if (!replayContainerFromRecMem) {
                // Check if there is a PlayerDelegate registered for this container
                // to handle, for instance, .h264 decoding.
                {
                    Lock l2(m_mapOfPlayerDelegatesMutex);
                    auto delegate = m_mapOfPlayerDelegates.find(nextContainer.getDataType());
                    if (delegate != m_mapOfPlayerDelegates.end()) {
                        // Replace m_actual with the replacement Container.
                        retVal = delegate->second->process(nextContainer);
                    }
                    else {
                        // Use original container.
                        retVal = nextContainer;
                    }
                }

                m_correctedDelay = m_delay = m_currentContainerToReplay->first - m_previousContainerAlreadyReplayed->first;

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

                // Use ELAPSED to compensate for internal data processing.
                const uint64_t ELAPSED = (thisTimePointCallingThisMethod - m_firstTimePointReturningAContainer).toMicroseconds();
                m_correctedDelay -= (m_correctedDelay > ELAPSED) ? ELAPSED : 0;
            }

            // If Player2 is non-threaded, manage cache regularly.
            if (!m_threading) {
                float refillMultiplicator = 1.1;
                checkRefillingCache(m_index.size(), refillMultiplicator);
            }

            // Store sample time stamp as int64 to avoid unnecessary copying of Containers.
            lastContainersSampleTimeStamp = retVal.getSampleTimeStamp().toMicroseconds();
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
                    Thread::usleepFor(10 * Player2::ONE_MILLISECOND_IN_MICROSECONDS);
                }
            }
            while (0 == numberOfEntries);
        }

        ////////////////////////////////////////////////////////////////////////

        uint32_t Player2::getTotalNumberOfContainersInRecFile() const {
            Lock l(m_indexMutex);
            return m_index.size();
        }

        uint32_t Player2::getDelay() const {
            Lock l(m_indexMutex);
            // Make sure that delay is not exceeding the specified maximum delay.
            return std::min<uint32_t>(m_delay, Player2::MAX_DELAY_IN_MICROSECONDS);
        }

        uint32_t Player2::getCorrectedDelay() const {
            Lock l(m_indexMutex);
            // Make sure that delay is not exceeding the specified maximum delay.
            return std::min<uint32_t>(m_correctedDelay, Player2::MAX_DELAY_IN_MICROSECONDS);
        }

        void Player2::rewind() {
            if (m_threading) {
                // Stop concurrent thread.
                setContainerCacheFillingRunning(false);
                m_containerCacheFillingThread.join();
            }

            computeInitialCacheLevelAndFillCache();

            if (m_threading) {
                // Re-start concurrent thread.
                setContainerCacheFillingRunning(true);
                m_containerCacheFillingThread = std::thread(&Player2::manageCache, this);
            }

            // Propagate rewind to .rec.mem file.
            if (NULL != m_recMemIndex.get()) {
                m_recMemIndex->rewind();
            }
        }

        bool Player2::hasMoreData() const {
            Lock l(m_indexMutex);
            // Check both, the status of the .rec file and the .rec.mem file.
            return ( hasMoreDataFromRecFile() || hasMoreDataFromRecMemFile() );
        }

        bool Player2::hasMoreDataFromRecFile() const {
            // File must be successfully opened AND
            //  the Player must be configured as m_autoRewind OR
            //  some entries are left to replay.
            return (m_recFileValid && (m_autoRewind || (m_currentContainerToReplay != m_index.end())));
        }

        bool Player2::hasMoreDataFromRecMemFile() const {
            return ((NULL != m_recMemIndex.get()) && (m_recMemIndex->hasMoreData()));
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
            uint8_t statisticsCounter = 0;
            float refillMultiplicator = 1.1;
            uint32_t numberOfEntries = 0;
            uint32_t numberOfEntriesInIndex = 0;
            {
                Lock l(m_indexMutex);
                numberOfEntriesInIndex = m_index.size();
            }

            while (isContainerCacheFillingRunning()) {
                {
                    Lock l(m_indexMutex);
                    numberOfEntries = m_containerCache.size();
                }

                // Check if refilling of the cache is needed.
                refillMultiplicator = checkRefillingCache(numberOfEntries, refillMultiplicator);

                // Manage cache at 10 Hz.
                Thread::usleepFor(100 * Player2::ONE_MILLISECOND_IN_MICROSECONDS);

                // Publish some statistics at 1 Hz.
                if ( 0 == ((++statisticsCounter) % 10) ) {
                    uint32_t numberOfReturnedContainersInTotal = 0;
                    {
                        // m_numberOfReturnedContainersInTotal is modified in a different thread.
                        Lock l(m_indexMutex);
                        numberOfReturnedContainersInTotal = m_numberOfReturnedContainersInTotal;
                    }
                    {
                        Lock l(m_playerListenerMutex);
                        if (NULL != m_playerListener) {
                            m_playerListener->percentagePlayedBack(numberOfReturnedContainersInTotal/static_cast<float>(numberOfEntriesInIndex));
                        }
                    }
                    statisticsCounter = 0;
                }
            }
        }

        float Player2::checkRefillingCache(const uint32_t &numberOfEntries, float refillMultiplicator) {
            // If filling level is around 35%, pour in more from the recording.
            if (numberOfEntries < 0.35*m_desiredInitialLevel) {
                const uint32_t entriesReadFromFile = fillContainerCache(refillMultiplicator * m_desiredInitialLevel);
                if (entriesReadFromFile > 0) {
                    clog << "[odtools::player::Player2]: Number of entries in cache: "  << numberOfEntries << ". " << entriesReadFromFile << " added to cache. " << m_containerCache.size() << " entries available." << endl;
                    refillMultiplicator *= 1.25;
                }
            }
            return refillMultiplicator;
        }

    } // player
} // tools
