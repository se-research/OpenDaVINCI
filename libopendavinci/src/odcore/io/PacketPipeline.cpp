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

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/io/PacketPipeline.h"

namespace odcore {
    namespace io {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;

        PacketPipeline::PacketPipeline() :
            Service(),
            PacketObserver(),
            PacketListener(),
            m_queueCondition(),
            m_queueMutex(),
            m_queue(),
            m_packetListenerMutex(),
            m_packetListener(NULL) {}

        PacketPipeline::~PacketPipeline() {
            // Stop the queue.
            stop();
        }

        void PacketPipeline::setPacketListener(PacketListener *pl) {
            Lock l(m_packetListenerMutex);

            // Prevent listening by ourselves!
            if (pl != this) {
                m_packetListener = pl;
            }
        }

        void PacketPipeline::nextPacket(const Packet &s) {
            Lock l(m_queueCondition);

            // Enter new data.
            {
                Lock l2(m_queueMutex);
                m_queue.push(s);
            }

            // Wake awaiting threads.
            m_queueCondition.wakeAll();
        }

        void PacketPipeline::processQueue() {
            uint32_t numberOfEntries = 0;

            // Determine the amount of current entries.
            {
                Lock l(m_queueMutex);
                numberOfEntries = static_cast<uint32_t>(m_queue.size());
            }

            Packet entry;
            for (uint32_t i = 0; i < numberOfEntries; i++) {
                // Acquire and remove next entry.
                {
                    Lock l2(m_queueMutex);
                    entry = m_queue.front();
                    m_queue.pop();
                }

                // Read all entries and distribute using the packetListener.
                {
                    Lock l(m_packetListenerMutex);
                    if (m_packetListener != NULL) {
                        // Distribute entry to connected listeners while NOT locking the queue.
                        m_packetListener->nextPacket(entry);
                    }
                }
            }
        }

        void PacketPipeline::beforeStop() {
            // Wake awaiting threads.
            Lock l(m_queueCondition);
            m_queueCondition.wakeAll();
        }

        void PacketPipeline::run() {
            serviceReady();

            while (isRunning()) {
                Lock l(m_queueCondition);
                m_queueCondition.waitOnSignal();

                if (isRunning()) {
                    processQueue();
                }
            }

            // Procee the queue to release any further waiting entries before shutting down.
            processQueue();
        }

    }
} // odcore::io
