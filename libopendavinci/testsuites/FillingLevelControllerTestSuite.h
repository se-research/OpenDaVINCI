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

#ifndef CORE_FILLINGLEVELCONTROLLERTESTSUITE_H_
#define CORE_FILLINGLEVELCONTROLLERTESTSUITE_H_

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include <cstdlib>
#include <ctime>

#include <iostream>
#include <deque>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Condition.h"        // for Condition
#include "opendavinci/odcore/base/Lock.h"             // for Lock
#include "opendavinci/odcore/base/Mutex.h"            // for Mutex
#include "opendavinci/odcore/base/Service.h"          // for Service
#include "opendavinci/odcore/base/Thread.h"

using namespace std;
using namespace odcore::base;

class Cache {
    public:
        Cache() :
            m_cacheMutex(),
            m_cache() {}

        int size() {
            Lock l(m_cacheMutex);
            return m_cache.size();
        }

        void enter(const int &v) {
            Lock l(m_cacheMutex);
            m_cache.push_front(v);
        }

        int leave() {
            Lock l(m_cacheMutex);
            int e = m_cache.back();
            m_cache.pop_back();
            return e;
        }

    private:
        odcore::base::Mutex m_cacheMutex;
        deque<int> m_cache;
};

class ProducerService : public Service {
    public:
        ProducerService(Cache &c) :
            m_cache(c) {
            std::srand(std::time(0)); // use current time as seed for random generator
        }

        void beforeStop() {}

        void run() {
            int32_t i = 0;
            serviceReady();
            cout << "Producer: Started." << endl;
            while (isRunning()) {
                if (i == 10) {
                    break;
                }
                i++;

                int v = (std::rand()/(RAND_MAX*1.0f))*10;
                m_cache.enter(v);

                // Yield other threads.
                Thread::usleepFor(0.5*1000*1000);
            }
            cout << "Producer: Finished." << endl;
        }

    private:
        Cache &m_cache;
};

class ConsumerService : public Service {
    public:
        ConsumerService(Cache &c) :
            m_cache(c) {}

        void beforeStop() {}

        void run() {
            int32_t i = 0;
            serviceReady();
            cout << "Consumer: Started." << endl;
            while (isRunning()) {
                if (i == 10) {
                    break;
                }
                i++;

                cout << "CS: size = " << m_cache.size();
                cout << " v = " <<  m_cache.leave() << endl;

                // Yield other threads.
                Thread::usleepFor(0.9*1000*1000);
            }
            cout << "Consumer: Finished." << endl;
        }

    private:
        Cache &m_cache;
};

class FillingLevelControllerTest : public CxxTest::TestSuite {
    public:
        void testService() {
            Cache cache;

            ProducerService ps(cache);
            ConsumerService cs(cache);

            cout << endl;

            ps.start();
            cs.start();

            Thread::usleepFor(10* 1000 * 1000);

            cs.stop();
            ps.stop();
        }

};

#endif /*CORE_FILLINGLEVELCONTROLLERTESTSUITE_H_*/
