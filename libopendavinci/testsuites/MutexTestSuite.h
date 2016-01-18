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

#ifndef CORE_MUTEXTESTSUITE_H_
#define CORE_MUTEXTESTSUITE_H_

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/core/base/Lock.h"             // for Lock
#include "opendavinci/core/base/Mutex.h"            // for Mutex

using namespace std;
using namespace core::base;

class MutexTestDirectLocking : public Mutex {
    public:
        void doLock() {
            Mutex::lock();
        }

        bool doTryLock() {
            return Mutex::tryLock();
        }

        void doUnlock() {
            Mutex::unlock();
        }
};

class MutexTest : public CxxTest::TestSuite {
    public:
        void testTryLock() {
            MutexTestDirectLocking m;
            TS_ASSERT(m.doTryLock());
            TS_ASSERT(!m.doTryLock());
        }

        void testLockAndUnlock() {
            MutexTestDirectLocking m2;
            m2.doLock();
            m2.doUnlock();

            m2.doLock();
            TS_ASSERT(!m2.doTryLock());
            m2.doUnlock();
        }

        void testScopedLock() {
            MutexTestDirectLocking m1;
            {
                core::base::Lock l(m1);
                TS_ASSERT(!m1.doTryLock());
            }
            TS_ASSERT(m1.doTryLock());
            TS_ASSERT(!m1.doTryLock());
        }
};

#endif /*CORE_MUTEXTESTSUITE_H_*/
