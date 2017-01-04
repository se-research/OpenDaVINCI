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
#include <iostream>
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

        Player2::Player2(const URL &url, const bool &autoRewind) :
            m_autoRewind(autoRewind),
            m_cacheMutex(),
            m_cache(),
            m_before(m_cache.begin()),
            m_current(m_cache.begin()),
            m_delay(0) {
            fillCache(url.getResource());
        }

        Player2::~Player2() {}

        void Player2::fillCache(const string &resource) {
            Lock l(m_cacheMutex);

            fstream fin;
            fin.open(resource.c_str(), ios_base::in|ios_base::binary);

            uint64_t size = 0;
            while (fin.good()) {
                const uint32_t posBefore = fin.tellg();
                Container c;
                fin >> c;

                if (!fin.eof()) {
                    const uint32_t posAfter = fin.tellg();
                    size += (posAfter - posBefore);
                    // Using map::insert(hint, ...) to have amortized constant complexity.
                    m_current = m_cache.insert(m_current, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), c));
                }
            }

            // Point to first entry.
            m_before = m_current = m_cache.begin();

            clog << "[Player2]: " << resource << " contains " << m_cache.size() << " entries; read " << size << " bytes." << endl;
        }

        Container Player2::getNextContainerToBeSent() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            return getNextContainerToBeSentNoCopy();
        }

        const odcore::data::Container& Player2::getNextContainerToBeSentNoCopy() throw (odcore::exceptions::ArrayIndexOutOfBoundsException) {
            // If at "EOF", either throw exception of autorewind.
            if (m_current == m_cache.end()) {
                if (!m_autoRewind) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(ArrayIndexOutOfBoundsException, "m_current != m_cache.end() failed.");
                }
                else {
                    rewind();
                }
            }

            Lock l(m_cacheMutex);
            const Container &retVal = m_current->second;
            m_delay = m_current->second.getSampleTimeStamp().toMicroseconds() - m_before->second.getSampleTimeStamp().toMicroseconds();
            m_before = m_current++;
            return retVal;
        }

        uint32_t Player2::getDelay() const {
            return m_delay;
        }

        void Player2::rewind() {
            Lock l(m_cacheMutex);
            m_before = m_current = m_cache.begin();
        }

        bool Player2::hasMoreData() const {
            Lock l(m_cacheMutex);
            return (m_autoRewind || (m_current != m_cache.end()));
        }

    } // player
} // tools
