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

#ifndef CORE_SERVICETESTSUITE_H_
#define CORE_SERVICETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <iostream>

#include "core/base/Condition.h"
#include "core/base/Lock.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"

using namespace std;
using namespace core::base;

class ServiceTestSuiteService : public Service {
    public:
        ServiceTestSuiteService(Condition &c):
                m_c(c) {}

        void beforeStop() {}

        void run() {
            int32_t i = 600;
            serviceReady();
            while (isRunning()) {
                if (i-- == 400) {
                    Lock l(m_c);
                    m_c.wakeAll();
                }
                // Yield other threads.
                Thread::usleepFor(1000);
            }
        }

    private:
        Condition &m_c;
};

class ServiceCounter {
    public:
        virtual ~ServiceCounter() {};
        virtual void inc() = 0;
};

class SimpleServiceTestSuiteService : public Service {
    public:
        SimpleServiceTestSuiteService(ServiceCounter &sc, int32_t boundary, Condition &c):
                m_counter(sc),
                m_boundary(boundary),
                m_c(c) {}

        void beforeStop() {}

        void run() {
            int32_t i = 2000;
            serviceReady();
            while (isRunning()) {
                if (i == 500) {
                    Lock l(m_c);
                    m_c.wakeAll();
                }
                if (i == m_boundary) {
                    m_counter.inc();
                }
                i--;
                // Yield other threads.
                Thread::usleepFor(1000);
            }
        }

    private:
        ServiceCounter &m_counter;
        int32_t m_boundary;
        Condition &m_c;
};

class ServiceTest : public CxxTest::TestSuite, public virtual ServiceCounter {
    private:
        Mutex m_mutexCounter;
        int32_t m_counter;
        Condition m_complete;

    public:
        ServiceTest() : m_mutexCounter(), m_counter(0), m_complete() {};
        void inc() {
            Lock l(m_mutexCounter);
            m_counter++;
            {
                Lock ll(m_complete);
                if (m_counter == 5) {
                    m_complete.wakeAll();
                }
            }
        }

        void testService() {
            bool failed = true;
            try {
                Condition c;
                ServiceTestSuiteService s(c);
                s.start();

                {
                    Lock l(c);
                    c.waitOnSignal();
                }

                s.stop();

                failed = false;
            } catch (...) {}
            TS_ASSERT(!failed);
        }

        void testSeveralServices() {
            bool failed = true;
            try {
                Condition c;
                m_counter = 0;
                SimpleServiceTestSuiteService s1(dynamic_cast<ServiceCounter&>(*this), 500, c);
                SimpleServiceTestSuiteService s2(dynamic_cast<ServiceCounter&>(*this), 400, c);
                SimpleServiceTestSuiteService s3(dynamic_cast<ServiceCounter&>(*this), 300, c);
                SimpleServiceTestSuiteService s4(dynamic_cast<ServiceCounter&>(*this), 200, c);
                SimpleServiceTestSuiteService s5(dynamic_cast<ServiceCounter&>(*this), 100, c);

                {
                    Lock l(c);
                    s1.start();
                    c.waitOnSignal();
                }

                {
                    Lock l(c);
                    s2.start();
                    c.waitOnSignal();
                }

                {
                    Lock l(c);
                    s3.start();
                    c.waitOnSignal();
                }

                {
                    Lock l(c);
                    s4.start();
                    c.waitOnSignal();
                }

                {
                    Lock l(c);
                    s5.start();
                    c.waitOnSignal();
                }

                {
                    Lock l (m_complete);
                    m_complete.waitOnSignal();
                }

                s1.stop();
                s2.stop();
                s3.stop();
                s4.stop();
                s5.stop();

                failed = false;
            } catch (...) {}
            TS_ASSERT(!failed);
        }
};

#endif /*CORE_SERVICETESTSUITE_H_*/
