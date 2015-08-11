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

#include "core/base/Lock.h"
#include "core/io/udp/UDPReceiver.h"

namespace core {
    namespace io {
        namespace udp {

            using namespace std;
            using namespace core::base;

            UDPReceiver::UDPReceiver() :
                m_stringPipeline(),
                m_packetListenerMutex(),
                m_packetListener(NULL) {
                m_stringPipeline.start();
            }

            UDPReceiver::~UDPReceiver() {
                m_stringPipeline.stop();
            }

            void UDPReceiver::setPacketListener(PacketListener *pl) {
                Lock l(m_packetListenerMutex);
                m_packetListener = pl;
            }

            void UDPReceiver::nextPacket(const Packet &p) {
                Lock l(m_packetListenerMutex);

                // Pass packet either to packet listner or to string listener.
                if (m_packetListener != NULL) {
                    m_packetListener->nextPacket(p);
                }
                else {
                    m_stringPipeline.nextString(p.getData());
                }
            }

            void UDPReceiver::setStringListener(StringListener *sl) {
                m_stringPipeline.setStringListener(sl);
            }

        }
    }
} // core::io::udp
