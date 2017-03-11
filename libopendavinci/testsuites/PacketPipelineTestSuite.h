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

#ifndef CORE_PACKETPIPELINETESTSUITE_H_
#define CORE_PACKETPIPELINETESTSUITE_H_

#include <string>
#include <vector>

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/io/PacketListener.h"
#include "opendavinci/odcore/io/PacketPipeline.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/generated/odcore/data/Packet.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::io;
using namespace odcore::data;

class PacketPipelineTest : public CxxTest::TestSuite, PacketListener {
    private:
        vector<Packet> m_receivedData;

    public:
        PacketPipelineTest() : m_receivedData() {}

        void nextPacket(const Packet &p) {
            m_receivedData.push_back(p);
        }

        void testRegisterReceiverBeforeSendingData() {
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);

            PacketPipeline ppl;
            ppl.setPacketListener(this);

            ppl.start();
            ppl.nextPacket(Packet("", "Packet1", TimeStamp()));
            Thread::usleepFor(1000); // Allow thread scheduling.
            ppl.nextPacket(Packet("", "Packet2", TimeStamp()));
            Thread::usleepFor(1000); // Allow thread scheduling.
            ppl.nextPacket(Packet("", "Packet3", TimeStamp()));
            Thread::usleepFor(1000); // Allow thread scheduling.
            ppl.stop();
            TS_ASSERT(m_receivedData.size() == 3);

            ppl.setPacketListener(NULL);
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);
        }

        void testRegisterReceiverAfterDataWasSent() {
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);

            PacketPipeline ppl;
            ppl.start();
            ppl.nextPacket(Packet("", "Packet1", TimeStamp()));
            Thread::usleepFor(5000); // Allow thread scheduling.
            ppl.nextPacket(Packet("", "Packet2", TimeStamp()));
            Thread::usleepFor(5000); // Allow thread scheduling.
            ppl.nextPacket(Packet("", "Packet3", TimeStamp()));
            Thread::usleepFor(5000); // Allow thread scheduling.
            // At this point, no data should be received.
            ppl.setPacketListener(this);
            TS_ASSERT(m_receivedData.size() == 0);
            ppl.stop();
            TS_ASSERT(m_receivedData.size() == 0);

            ppl.setPacketListener(NULL);
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);
        }
};

#endif /*CORE_PACKETPIPELINETESTSUITE_H_*/
