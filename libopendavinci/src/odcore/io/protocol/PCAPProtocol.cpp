/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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
#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

namespace odcore {
    namespace io {
        namespace protocol {

            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::io::conference;
            using namespace odcore::data;

            PCAPProtocol::PCAPProtocol() :
                AbstractProtocol(),
                ContainerObserver(),
                m_containerListenerMutex(),
                m_containerListener(NULL),
                m_partialDataMutex(),
                m_partialData() {}

            PCAPProtocol::~PCAPProtocol() {
                setContainerListener(NULL);
            }

            void PCAPProtocol::setContainerListener(ContainerListener* listener) {
                Lock l(m_containerListenerMutex);
                m_containerListener = listener;
            }

            void PCAPProtocol::nextString(const string &s) {
                Lock l(m_partialDataMutex);

                m_partialData.seekp(0, ios_base::end);
                m_partialData.write(s.c_str(), s.length());

                while (tryConsumingData());
            }

            bool PCAPProtocol::tryConsumingData() {
                static bool SWAP_VALUES = false;
                static pcap::PacketHeader ph;

                // State machine variables.
                static bool foundHeader = false;
                static bool foundPacketHeader = false;

                // Sizes.
                const uint32_t SIZE_GLOBAL_HEADER = 24;
                const uint32_t SIZE_PACKET_HEADER = 16;

                // Get size of stringstream
                m_partialData.seekg(0, ios_base::end);
                const uint32_t streamSize = m_partialData.tellg();
                m_partialData.seekg(0, ios_base::beg);

                // State 1: Consume global header (once!).
                if (!foundHeader) {
                    // Did we receive at least the global header?
                    if (streamSize >= SIZE_GLOBAL_HEADER) {
                        // Consume global header.
                        uint32_t magic_number = 0; m_partialData.read((char*)&magic_number, sizeof(uint32_t));
                        SWAP_VALUES = (0xa1b2c3d4 != magic_number);

                        uint16_t version_major = 0; m_partialData.read((char*)&version_major, sizeof(uint16_t)); if (SWAP_VALUES) version_major = ntohs(version_major);
                        uint16_t version_minor = 0; m_partialData.read((char*)&version_minor, sizeof(uint16_t)); if (SWAP_VALUES) version_minor = ntohs(version_minor);
                        int32_t thiszone = 0; m_partialData.read((char*)&thiszone, sizeof(int32_t)); if (SWAP_VALUES) thiszone = ntohl(thiszone);
                        uint32_t sigfigs = 0; m_partialData.read((char*)&sigfigs, sizeof(uint32_t)); if (SWAP_VALUES) sigfigs = ntohl(sigfigs);
                        uint32_t snaplen = 0; m_partialData.read((char*)&snaplen, sizeof(uint32_t)); if (SWAP_VALUES) snaplen = ntohl(snaplen);
                        uint32_t network = 0; m_partialData.read((char*)&network, sizeof(uint32_t)); if (SWAP_VALUES) network = ntohl(network);

                        // Remove consumed part.
                        m_partialData.str(m_partialData.str().substr(SIZE_GLOBAL_HEADER));
                        foundHeader = true;

                        pcap::GlobalHeader gh(magic_number, version_major, version_minor, thiszone, sigfigs, snaplen, network);

                        Container c(gh);
                        invokeContainerListener(c);

                        return foundHeader;
                    }
                }

                // State 2: Consume packet header.
                if (foundHeader && !foundPacketHeader) {
                    // Did we receive at least the global header?
                    if (streamSize >= SIZE_PACKET_HEADER) {
                        // Consume packet header.
                        uint32_t ts_sec = 0; m_partialData.read((char*)&ts_sec, sizeof(uint32_t)); if (SWAP_VALUES) ts_sec = ntohl(ts_sec);
                        uint32_t ts_usec = 0; m_partialData.read((char*)&ts_usec, sizeof(uint32_t)); if (SWAP_VALUES) ts_usec = ntohl(ts_usec);
                        uint32_t incl_len = 0; m_partialData.read((char*)&incl_len, sizeof(uint32_t)); if (SWAP_VALUES) incl_len = ntohl(incl_len);
                        uint32_t orig_len = 0; m_partialData.read((char*)&orig_len, sizeof(uint32_t)); if (SWAP_VALUES) orig_len = ntohl(orig_len);

                        // Remove consumed part.
                        m_partialData.str(m_partialData.str().substr(SIZE_PACKET_HEADER));
                        foundPacketHeader = true;

                        ph = pcap::PacketHeader(ts_sec, ts_usec, incl_len, orig_len);

                        Container c(ph);
                        invokeContainerListener(c);

                        return foundPacketHeader;
                    }
                }

                // State 3: Consume packet's payload.
                if (foundPacketHeader && (ph.getIncl_len() > 0) && (streamSize >= ph.getIncl_len())) {
                    string payload(ph.getIncl_len(), '\0');

                    // Get pointer to the beginning of the string to store the data.
                    char* begin = &(*payload.begin());
                    m_partialData.read(begin, ph.getIncl_len());

                    // Remove consumed part.
                    m_partialData.str(m_partialData.str().substr(ph.getIncl_len()));

                    // Create packet.
                    pcap::Packet p(ph, payload);

                    // Create packet with the header and the payload.
                    Container c(p);
                    invokeContainerListener(c);

                    // Reset states.
                    ph = pcap::PacketHeader();
                    foundPacketHeader = false;

                    // Start over.
                    return !foundPacketHeader;
                }

                // Default: Nothing found.
                return false;
            }

            void PCAPProtocol::invokeContainerListener(Container &c) {
                Lock l(m_containerListenerMutex);
                if (m_containerListener != NULL) {
                    m_containerListener->nextContainer(c);
                }
            }

        }
    }
}

