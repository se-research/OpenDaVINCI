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

#include <fstream>
#include <iostream>
#include <utility>

#include <opendavinci/odcore/base/module/AbstractCIDModule.h>
#include <opendavinci/odtools/player/Player2.h>

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

namespace odtools {
    namespace player {

        using namespace std;
        using namespace odcore::base::module;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;

        Player2::Player2(const URL &url) :
            m_cache(),
            m_current(m_cache.end()) {
            fillCache(url.getResource());
        }

        Player2::~Player2() {}

        void Player2::fillCache(const string &resource) {
            clog << "[Player2]: Reading from " << resource << "." << endl;

            fstream fin;
            fin.open(resource.c_str(), ios_base::in|ios_base::binary);

            while (fin.good()) {
                Container c;
                fin >> c;

                // Using map::insert(hint, ...) to have amortized constant complexity.
                m_current = m_cache.insert(m_current, std::make_pair(c.getSampleTimeStamp().toMicroseconds(), c));
            }

            // Point to first entry.
            m_current = m_cache.begin();
            if (m_current->second.getSampleTimeStamp().toMicroseconds() == (m_current->second.getDataType() == 0)) {
                // The first element is "surprisingly" unusable.
                m_current = m_cache.erase(m_current);
            }

            clog << "[Player2]: Stored " << m_cache.size() << " entries." << endl;
        }

        Container Player2::getNextContainerToBeSent() {
            return getNextContainerToBeSentNoCopy();
        }

        const odcore::data::Container& Player2::getNextContainerToBeSentNoCopy() {
            const Container &retVal = m_current->second;
            m_current++;
            return retVal;
        }

        uint32_t Player2::getDelay() const {
            return 0;
        }

        bool Player2::hasMoreData() const {
            return m_current != m_cache.end();
        }

    } // player
} // tools
