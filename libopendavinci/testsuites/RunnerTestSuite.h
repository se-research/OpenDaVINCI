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

#ifndef CONTEXT_RUNNERTESTSUITE_H_
#define CONTEXT_RUNNERTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include "opendavinci/odcontext/base/ControlledTime.h"
#include "opendavinci/odcontext/base/Runner.h"

using namespace std;

using namespace odcontext::base;

class RunnerTestApp : public Runner {
    public:
        RunnerTestApp(const float &freq) :
            m_freq(freq) {}

        virtual float getFrequency() const {
            return m_freq;
        }

    private:
        const float m_freq;
};

class RunnerTest : public CxxTest::TestSuite {
    public:
        void testFrequencies() {
            RunnerTestApp r1(1);
            TS_ASSERT(r1.needsExecution(ControlledTime(0, 0)));
            TS_ASSERT(r1.needsExecution(ControlledTime(1, 0)));
            TS_ASSERT(!r1.needsExecution(ControlledTime(1, 999999)));

            RunnerTestApp r2(2);
            TS_ASSERT(r2.needsExecution(ControlledTime(0, 0)));
            TS_ASSERT(r2.needsExecution(ControlledTime(1, 0)));
            TS_ASSERT(r2.needsExecution(ControlledTime(1, 500000)));
            TS_ASSERT(!r2.needsExecution(ControlledTime(1, 999999)));

            RunnerTestApp r3(0.5);
            TS_ASSERT(r3.needsExecution(ControlledTime(0, 0)));
            TS_ASSERT(!r3.needsExecution(ControlledTime(1, 0)));
            TS_ASSERT(!r3.needsExecution(ControlledTime(1, 500000)));
            TS_ASSERT(!r3.needsExecution(ControlledTime(1, 999999)));
            TS_ASSERT(r3.needsExecution(ControlledTime(2, 0)));
        }
};

#endif /*CONTEXT_RUNNERTESTSUITE_H_*/
