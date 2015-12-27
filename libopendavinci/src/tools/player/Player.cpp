/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include <stddef.h>
#include <string>

#include "core/base/module/AbstractCIDModule.h"
#include "core/data/Container.h"
#include "core/data/TimeStamp.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/StreamFactory.h"
#include "core/io/URL.h"
#include "core/macros.h"
#include "tools/player/Player.h"
#include "tools/player/PlayerCache.h"

namespace tools {
    namespace player {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;

        Player::Player(const URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
            m_threading(threading),
            m_autoRewind(autoRewind),
            m_inFile(NULL),
            m_inSharedMemoryFile(NULL),
            m_playerCache(NULL),
            m_actual(),
            m_successor(),
            m_successorProcessed(true),
            m_seekToTheBeginning(true),
            m_noMoreData(false),
            m_delay(0) {

            // Get the stream using the StreamFactory with the given URL.
            m_inFile = StreamFactory::getInstance().getInputStream(url);

            // Try to load the data storage for data from the shared memory.
            if (url.getResource().compare("/dev/stdin") != 0) {
                URL urlSharedMemoryFile("file://" + url.getResource() + ".mem");
                try {
                    m_inSharedMemoryFile = StreamFactory::getInstance().getInputStream(urlSharedMemoryFile);
                    CLOG1 << "Player: Found shared memory dump file '" << urlSharedMemoryFile.toString() << "'" << endl;
                }
                catch (const core::exceptions::InvalidArgumentException &iae) {
                    clog << "Player: Warning: " << iae.toString() << endl;
                } 
            }

            // Setup cache.
            m_playerCache = auto_ptr<PlayerCache>(new PlayerCache(numberOfMemorySegments, memorySegmentSize, m_autoRewind, m_inFile, m_inSharedMemoryFile));
            if (m_playerCache.get() != NULL) {
                // First, fill the cache...
                m_playerCache->updateCache();

                if (m_threading) {
                    // ...and if running concurrently, start the thread.
                    m_playerCache->start();
                }
            }
        }

        Player::~Player() {
            if ( (m_playerCache.get() != NULL) && (m_threading) ) {
                m_playerCache->stop();
            }
        }

        Container Player::getNextContainerToBeSent() {
            Container retVal;

            // Update cache in the sychronous case.
            if ( (m_playerCache.get() != NULL) && (!m_threading) ) {
                m_playerCache->updateCache();
            }

            // Check, if we are "at the beginning".
            if (m_seekToTheBeginning) {
                // Read the "actual" (first) container.
                if (m_playerCache->getNumberOfEntries() > 0) {
                    m_actual = m_playerCache->getNextContainer();
                }

                // Disable this state.
                m_seekToTheBeginning = false;

                // Don't skip reading successor.
                m_successorProcessed = true;
            }

            // While there are more containers, read the "successor" of the "actual" container.
            if (m_successorProcessed) {
                if (m_playerCache->getNumberOfEntries() > 0) {
                    m_successor = m_playerCache->getNextContainer();

                    if (m_successor.getDataType() != Container::UNDEFINEDDATA) {
                        // Indicate that the successor needs to be processed.
                        m_successorProcessed = false;
                    }
                    else {
                        // If the container contains undefined data and autorewind is chosen, seek to the beginning.
                        if (m_autoRewind) {
                            // Change internal state to "at the beginning".
                            m_seekToTheBeginning = true;
                        }
                    }
                }
                else {
                    m_noMoreData = true;
                }
            }

            // Here, the time gap between two containers is calculated.
            if ( (m_actual.getDataType() != Container::UNDEFINEDDATA) &&
                 (m_successor.getDataType() != Container::UNDEFINEDDATA) ) {
                TimeStamp delta = m_successor.getReceivedTimeStamp() - m_actual.getReceivedTimeStamp();
                if (!(delta.toMicroseconds() < 0)) {
                    m_delay = static_cast<long>(delta.toMicroseconds());
                }
            }

            // If the actual container is a SHARED_IMAGE then copy next entry into the shared memory before sending the actual container.
            if (m_actual.getDataType() == Container::SHARED_IMAGE) {
                m_playerCache->copyMemoryToSharedMemory(m_actual);
            }

            // If the actual container is a SHARED_IMAGE then copy next entry into the shared memory before sending the actual container.
            if (m_actual.getDataType() == Container::SHARED_DATA) {
                m_playerCache->copyMemoryToSharedMemory(m_actual);
            }

            // Return the m_actual container as retVal;
            retVal = m_actual;

            // Process the "successor" container as the next "actual" one.
            m_actual = m_successor;

            // The actual container has been sent, therefore, the successor becomes the next actual container.
            m_successorProcessed = true;

            return retVal;
        }

        uint32_t Player::getDelay() const {
            return m_delay;
        }

        void Player::rewind() {
            // Clear cache and wait for new data.
            m_playerCache->clearQueueRewindInputStreams();

            // Reset our own states.
            m_seekToTheBeginning = true;
            m_noMoreData = false;
        }

        bool Player::hasMoreData() const {
            return !m_noMoreData;
        }

    } // player
} // tools
