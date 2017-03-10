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
#include "opendavinci/odcore/io/StringListener.h"
#include "opendavinci/odcore/io/udp/UDPReceiver.h"
#include "opendavinci/generated/odcore/data/Packet.h"

namespace odcore { namespace io { class StringListener; } }

namespace odcore {
    namespace io {
        namespace udp {

            using namespace std;
            using namespace odcore::base;

            UDPReceiver::UDPReceiver() :
                m_stringListenerMutex(),
                m_stringListener(NULL),
                m_packetPipeline() {
                m_packetPipeline.start();
            }

            UDPReceiver::~UDPReceiver() {
                m_packetPipeline.stop();
            }

            void UDPReceiver::setStringListener(StringListener *sl) {
                Lock l(m_stringListenerMutex);
                m_stringListener = sl;
            }

            void UDPReceiver::setPacketListener(PacketListener *pl) {
                m_packetPipeline.setPacketListener(pl);
            }

            void UDPReceiver::nextPacket(const odcore::data::Packet &p) {
                Lock l(m_stringListenerMutex);

                // Pass packet either to packet listner or to string listener.
                if (m_stringListener != NULL) {
                    m_stringListener->nextString(p.getData());
                }
                else {
                    m_packetPipeline.nextPacket(p);
                }
            }

        }
    }
} // odcore::io::udp
