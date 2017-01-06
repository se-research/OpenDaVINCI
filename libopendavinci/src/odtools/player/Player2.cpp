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

#include <cstdio>

#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

#include <opendavinci/odcore/base/module/AbstractCIDModule.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/data/TimeStamp.h>

#include <opendavinci/odtools/player/Player2.h>

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::io;

        Player2CacheEntry::Player2CacheEntry() :
            m_sampleTimeStamp(0),
            m_filePosition(0),
            m_available(false) {}

        Player2CacheEntry::Player2CacheEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition) :
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
            m_availableEntries(0),
            m_nextEntryToReadFromFile(m_index.begin()),
            m_containerCache(),
            m_delay(0) {
            initializeIndex();
        }

        Player2::~Player2() {
            m_recFile.close();
        }

        void Player2::initializeIndex() {
            m_recFile.open(m_url.getResource().c_str(), ios_base::in|ios_base::binary);
            m_recFileValid = m_recFile.good();

            // Read complete file and store file positions to containers.
            // The actual reading of Containers is deferred.
            uint32_t totalBytesRead = 0;
            while (m_recFile.good()) {
                const uint32_t posBefore = m_recFile.tellg();
                Container c;
                m_recFile >> c;

                if (!m_recFile.eof()) {
                    // Store mapping .rec file position --> index entry.
                    m_index.emplace(std::make_pair(c.getSampleTimeStamp().toMicroseconds(), Player2CacheEntry(c.getSampleTimeStamp().toMicroseconds(), posBefore)));
                    const uint32_t posAfter = m_recFile.tellg();
                    totalBytesRead += (posAfter - posBefore);
                }
            }

            // Reset pointer to beginning of the .rec file.
            if (m_recFileValid) {
                m_recFile.clear();
                m_recFile.seekg(0, ios::beg);

                // Point to first entry.
                m_nextEntryToReadFromFile = 
                    m_previousContainerAlreadyReplayed = 
                    m_currentContainerToReplay = m_index.begin();
                clog << "[Player2]: " << m_url.getResource() << " contains " << m_index.size() << " entries; read " << totalBytesRead << " bytes." << endl;
            }
        }

        void Player2::fillContainerCache(const uint32_t &numberOfEntriesToReadFromFile) {
            if (m_recFileValid) {
                m_recFile.clear();
                uint32_t entriesReadFromFile = 0;
cout << "To read " << numberOfEntriesToReadFromFile << endl;
                while ( (m_nextEntryToReadFromFile != m_index.end()) && (entriesReadFromFile < numberOfEntriesToReadFromFile) ) {
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
cout << "Read " << entriesReadFromFile << endl;
                m_availableEntries += entriesReadFromFile;
            }
        }

        Container Player2::readEntryAsynchronously(const uint32_t &position) {
            m_recFile.clear();
            m_recFile.seekg(position);
            Container retVal;
            m_recFile >> retVal;
            return retVal;
        }

        Container Player2::getNextContainerToBeSent() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            return getNextContainerToBeSentNoCopy();
        }

        const odcore::data::Container& Player2::getNextContainerToBeSentNoCopy() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            // If at "EOF", either throw exception of autorewind.
            if (m_currentContainerToReplay == m_index.end()) {
                if (!m_autoRewind) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(ArrayIndexOutOfBoundsException, "m_currentContainerToReplay != m_index.end() failed.");
                }
                else {
                    rewind();
                }
            }

            {
                // TODO: Cache management.
                if (m_availableEntries == 0) {
                    fillContainerCache(2);
                }

                // TODO: Erase played entries.

            }

            Lock l(m_indexMutex);
            const Container &retVal = m_containerCache[m_currentContainerToReplay->second.m_filePosition];
            m_delay = retVal.getSampleTimeStamp().toMicroseconds() - m_containerCache[m_previousContainerAlreadyReplayed->second.m_filePosition].getSampleTimeStamp().toMicroseconds();
            m_previousContainerAlreadyReplayed = m_currentContainerToReplay++;

            m_availableEntries--;

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
            // the Player must be configured as m_autoRewind OR
            // some entries are left to replay.
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
                        m_currentContainerToReplay = m_index.emplace_hint(m_currentContainerToReplay, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), Player2CacheEntry(c.getSampleTimeStamp().toMicroseconds(), posBefore, true, it)));
                    }
                    else {
                        // Using map::insert(hint, ...) to have amortized constant complexity.
                        m_currentContainerToReplay = m_index.emplace_hint(m_currentContainerToReplay, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), Player2CacheEntry(c.getSampleTimeStamp().toMicroseconds(), posBefore)));
                    }

*/


//////////////////////////

    } // player
} // tools
