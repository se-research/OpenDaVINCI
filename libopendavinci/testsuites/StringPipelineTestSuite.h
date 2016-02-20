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

#ifndef CORE_STRINGPIPELINETESTSUITE_H_
#define CORE_STRINGPIPELINETESTSUITE_H_

#include <string>
#include <vector>

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/io/StringListener.h"
#include "opendavinci/odcore/io/StringPipeline.h"

using namespace std;
using namespace odcore::base;
using namespace odcore::io;

class StringPipelineTest : public CxxTest::TestSuite, StringListener {
    private:
        vector<string> m_receivedData;

    public:
        StringPipelineTest() : m_receivedData() {}

        void nextString(const string &s) {
            m_receivedData.push_back(s);
        }

        void testRegisterReceiverBeforeSendingData() {
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);

            StringPipeline spl;
            spl.setStringListener(this);

            spl.start();
            spl.nextString("String1");
            Thread::usleepFor(1000); // Allow thread scheduling.
            spl.nextString("String2");
            Thread::usleepFor(1000); // Allow thread scheduling.
            spl.nextString("String3");
            Thread::usleepFor(1000); // Allow thread scheduling.
            spl.stop();
            TS_ASSERT(m_receivedData.size() == 3);

            spl.setStringListener(NULL);
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);
        }

        void testRegisterReceiverAfterDataWasSent() {
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);

            StringPipeline spl;
            spl.start();
            spl.nextString("String1");
            Thread::usleepFor(5000); // Allow thread scheduling.
            spl.nextString("String2");
            Thread::usleepFor(5000); // Allow thread scheduling.
            spl.nextString("String3");
            Thread::usleepFor(5000); // Allow thread scheduling.
            // At this point, no data should be received.
            spl.setStringListener(this);
            TS_ASSERT(m_receivedData.size() == 0);
            spl.stop();
            TS_ASSERT(m_receivedData.size() == 0);

            spl.setStringListener(NULL);
            m_receivedData.clear();
            TS_ASSERT(m_receivedData.size() == 0);
        }
};

#endif /*CORE_STRINGPIPELINETESTSUITE_H_*/
