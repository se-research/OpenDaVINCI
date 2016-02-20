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

#ifndef CORE_WRAPPER_TCPGATHERERTESTSUITE_H_
#define CORE_WRAPPER_TCPGATHERERTESTSUITE_H_

#include <ostream>                      // for stringstream, basic_ostream, etc
#include <string>                       // for string, allocator, etc

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/opendavinci.h"
#include "mocks/ConnectionListenerMock.h"
#include "mocks/StringListenerMock.h"
#include "mocks/TCPAcceptorListenerMock.h"
#ifdef WIN32
	#include "opendavinci/odcore/wrapper/WIN32/WIN32TCPFactoryWorker.h"
#endif

#include "opendavinci/odcore/io/tcp/TCPConnection.h"  // for TCPConnection

using namespace std;
using namespace odcore;
using namespace odcore::base;

class TCPGathererTestSuite : public CxxTest::TestSuite, public odcore::io::tcp::TCPConnection
{
    public:
		TCPGathererTestSuite() :
			m_sentData("") {}

        virtual void sendImplementation(const string& data) {
            m_sentData = data;
        }

        virtual void start()
        {}

        virtual void stop()
        {}

        /**
         * 1. Test Case: Received data corresponds to an entire packet.
         */
        void testNoGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testNoGathering" << endl;
            const string testData = createTestData("The test data");

			mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem("The test data");
            mockListener.VALUES_nextString.prepare();

            receivedString(testData);

            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }

        /**
         * 2. Case: Data is split into two parts.
         */
        void testGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testGathering" << endl;
            const string testData = createTestData("The test data");

            // Prepare StringListenerMock
            mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem("The test data");
            mockListener.VALUES_nextString.prepare();

            const string dataString1 = testData.substr(0, testData.length()/2);
            const string dataString2 = testData.substr(testData.length()/2);

            receivedString(dataString1);
            TS_ASSERT( !mockListener.CALLWAITER_nextString.wait() );

            receivedString(dataString2);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }

        /**
         * 3. Test case: Test data is split and mixed.
         */
        void testMixedGathering()
        {
            clog << endl << "TCPConnectionTestSuite::testMixedGathering" << endl;
            stringstream dataStream;

            const string data1("The first test data");
            const string data2("The second test data");

            const string testData1 = createTestData(data1);
            const string testData2 = createTestData(data2);

            // Prepare StringListenerMock
            mocks::StringListenerMock mockListener;
            setStringListener(&mockListener);
            mockListener.VALUES_nextString.addItem(data1);
            mockListener.VALUES_nextString.addItem(data2);
            mockListener.VALUES_nextString.prepare();

            const string dataString1 = testData1 + testData2.substr(0, testData2.length()/2);
            const string dataString2 = testData2.substr(testData2.length()/2);

            receivedString(dataString1);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled());
            mockListener.CALLWAITER_nextString.reset();

            receivedString(dataString2);
            TS_ASSERT( mockListener.CALLWAITER_nextString.wait() );
            TS_ASSERT( mockListener.correctCalled() );
        }


	    unsigned long my_htonl(uint32_t n)
	    {
                unsigned char *s = (unsigned char *)&n;
                return (unsigned long)(s[0] << 24 | s[1] << 16 | s[2] << 8 | s[3]);
	    }

        string createTestData(const string& data)
        {
            const uint32_t dataSize = my_htonl(data.length());
            stringstream dataStream;
            dataStream.write(reinterpret_cast<const char*>(&dataSize), sizeof(uint32_t));
            dataStream << data;

            return dataStream.str();
        }

    private:
        string m_sentData;
};

#endif /*CORE_WRAPPER_TCPGATHERERTESTSUITE_H_*/
