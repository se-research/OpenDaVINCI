/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "opendavinci/odcontext/base/PlaybackContainer.h"
#include "opendavinci/odcontext/base/SendContainerToSystemsUnderTest.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odtools/player/Player2.h"

namespace odcore { namespace wrapper { class Time; } }

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace odcore::data;
        using namespace odtools::player;

        PlaybackContainer::PlaybackContainer(const float &freq, const string &urlFileName, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments) :
            m_freq(freq),
            m_urlFileName(urlFileName),
            m_memorySegmentSize(memorySegmentSize),
            m_numberOfSegments(numberOfSegments),
            m_player() {
        }

        PlaybackContainer::~PlaybackContainer() {}

        void PlaybackContainer::setup() {
            if (m_urlFileName != "") {
                // We can use the sychronous player as we are running in a deterministic simulation anyways.
                const bool THREADING = false;
                const bool AUTO_REWIND = false;
                m_player = unique_ptr<Player2>(new Player2(m_urlFileName, AUTO_REWIND, m_memorySegmentSize, m_numberOfSegments, THREADING));
            }
        }

        void PlaybackContainer::tearDown() {}

        void PlaybackContainer::step(const odcore::wrapper::Time &/*t*/, SendContainerToSystemsUnderTest &sender) {
            if (m_player.get() != NULL) {
                // TODO: Check if the delta between two captures frames matches the t and replay more than one frame potentially.
                Container c;
                if (m_player->hasMoreData()) {
                    c = m_player->getNextContainerToBeSent();
                    sender.sendToSystemsUnderTest(c);
                }
            }

            // Discard all received containers.
            getFIFO().clear();
        }

        float PlaybackContainer::getFrequency() const {
            return m_freq;
        }

    }
} // odcontext::base
