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

#ifndef OPENDAVINCI_TOOLS_PLAYER_PLAYER2_H_
#define OPENDAVINCI_TOOLS_PLAYER_PLAYER2_H_

#include <fstream>
#include <map>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/io/URL.h>
#include "opendavinci/odcore/exceptions/Exceptions.h"

namespace odtools {
    namespace player {

        using namespace std;

        /**
         * This class can be used to read previously recorded
         * data from a given URL.
         */
        class Player2CacheEntry {
            public:
                Player2CacheEntry();
                Player2CacheEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition);
                Player2CacheEntry(const int64_t &sampleTimeStamp, const uint32_t &filePosition, const bool &available, const multimap<int64_t, odcore::data::Container>::iterator &entry);

            public:
                int64_t m_sampleTimeStamp;
                uint32_t m_filePosition;
                bool m_available;
                multimap<int64_t, odcore::data::Container>::iterator m_entry;
        };

        class OPENDAVINCI_API Player2 {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Player2(const Player2 &/*obj*/) = delete;

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Player2& operator=(const Player2 &/*obj*/) = delete;

            public:
                /**
                 * Constructor.
                 *
                 * @param url Resource to play.
                 * @param autoRewind True if the file should be rewind at EOF.
                 */
                Player2(const odcore::io::URL &url, const bool &autoRewind);

                virtual ~Player2();

                /**
                 * This method returns the next container to be replayed.
                 *
                 * @return Next container to be replayed.
                 */
                odcore::data::Container getNextContainerToBeSent() throw (odcore::exceptions::ArrayIndexOutOfBoundsException);

                /**
                 * This method returns the next container to be replayed.
                 *
                 * @return Next container to be replayed.
                 */
                const odcore::data::Container& getNextContainerToBeSentNoCopy() throw (odcore::exceptions::ArrayIndexOutOfBoundsException);

                /**
                 * This method returns the delay to be waited before the next container should be delivered.
                 *
                 * @return delay to the next container in real time microseconds (us).
                 */
                uint32_t getDelay() const;

                /**
                 * This method returns true if there is more data to replay.
                 *
                 * @return true if there is more data to replay.
                 */
                bool hasMoreData() const;

                /**
                 * This method restarts the player.
                 */
                void rewind();

            private:
                void fillMetaCache(const string &resource);

                odcore::data::Container readEntryAsynchronously(const uint32_t &position);

            private:
                fstream m_fin;
                bool m_autoRewind;
                mutable odcore::base::Mutex m_cacheMutex;

                multimap<int64_t, Player2CacheEntry> m_metaCache;
                multimap<int64_t, Player2CacheEntry>::iterator m_before;
                multimap<int64_t, Player2CacheEntry>::iterator m_current;

                multimap<int64_t, odcore::data::Container> m_containerCache;

//                multimap<int64_t, odcore::data::Container> m_cache;
//                multimap<int64_t, odcore::data::Container>::const_iterator m_before;
//                multimap<int64_t, odcore::data::Container>::const_iterator m_current;
                uint32_t m_delay;
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_PLAYER2_H_*/
