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

#ifndef CORE_STRINGPROTOCOLTESTSUITE_H_
#define CORE_STRINGPROTOCOLTESTSUITE_H_

#include <iostream>                     // for stringstream, basic_ostream, etc
#include <string>                       // for string, operator<<

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "core/platform.h"
#include "core/io/StringListener.h"     // for StringListener
#include "core/io/StringSender.h"       // for StringSender
#include "core/io/protocol/StringProtocol.h"  // for StringProtocol

using namespace std;

class StringProtocolTest : public CxxTest::TestSuite, public core::io::StringListener, public core::io::StringSender {
    private:
        string m_receivedData;
        string m_dataToBeSent;

    public:
        StringProtocolTest() :
            m_receivedData(""),
            m_dataToBeSent("") {}

        void send(const string& data) {
            m_dataToBeSent = data;
        }

        void nextString(const string &s) {
            m_receivedData = s;
        }

        void testStringProtocolSend() {
            core::io::protocol::StringProtocol sp;
            sp.setStringListener(this);
            sp.setStringSender(this);

            m_dataToBeSent = "";
            TS_ASSERT(m_dataToBeSent.length() == 0); 

            string testDataToBeSent("HelloWorldSend!");
            sp.send(testDataToBeSent);

            stringstream sstr;
            const uint32_t dataSize = htonl(testDataToBeSent.length());
            stringstream dataStream;
            dataStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            dataStream << testDataToBeSent;

            TS_ASSERT(m_dataToBeSent.length() > 0); 
            TS_ASSERT(m_dataToBeSent.compare(dataStream.str()) == 0); 
        }

        void testStringProtocolReceive() {
            core::io::protocol::StringProtocol sp;
            sp.setStringListener(this);
            sp.setStringSender(this);

            m_receivedData = "";
            TS_ASSERT(m_receivedData.length() == 0); 

            string testDataToBeSent("HelloWorldReceive!");

            stringstream sstr;
            const uint32_t dataSize = htonl(testDataToBeSent.length());
            stringstream dataStream;
            dataStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            dataStream << testDataToBeSent;

            sp.nextString(dataStream.str());

            TS_ASSERT(m_receivedData.length() > 0); 
            TS_ASSERT(m_receivedData.compare(testDataToBeSent) == 0); 
        }
};

#endif /*CORE_STRINGPROTOCOLTESTSUITE_H_*/
