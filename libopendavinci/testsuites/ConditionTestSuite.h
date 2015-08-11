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

#ifndef CORE_CONDITIONTESTSUITE_H_
#define CORE_CONDITIONTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <string>
#include <iostream>

#include "core/base/Condition.h"
#include "core/base/Lock.h"
#include "core/base/Service.h"
#include "core/base/Thread.h"

using namespace std;
using namespace core::base;

class WaitOnSignalService : public Service {
    public:
        WaitOnSignalService(string name, Condition &myCondition, Condition &otherCondition):
                m_name(name),
                m_myCondition(myCondition),
                m_otherCondition(otherCondition),
                m_inLoopMutex(),
                m_inLoop(false),
                m_waiting(false) {}

        virtual void beforeStop() {}

        bool isInLoop() {
            Lock l(m_inLoopMutex);
            return m_inLoop;
        }

        bool isWaiting() {
            //Lock l(m_myCondition);
            return m_waiting;
        }

    protected:
        virtual void run() {
            serviceReady();
            clog << "A" << endl;
            {
                Lock l(m_myCondition);
                m_waiting = true;

                // Wait for new events.
                m_myCondition.waitOnSignal();
            }

            clog << "B" << endl;
            {
                Lock l(m_inLoopMutex);
                m_inLoop = true;
            }

            clog << "C" << endl;
            // Let the test case fall asleep.
            Thread::usleepFor(1000);

            // Awake buddy thread.
            clog << "D" << endl;
            {
                Lock l(m_otherCondition);
                m_otherCondition.wakeAll();
            }

            while (isRunning()) {
                // Do something quite useful.
                Thread::usleepFor(100);
            }
            clog << "E" << endl;
        }

    private:
        string m_name;
        Condition &m_myCondition;
        Condition &m_otherCondition;

        Mutex m_inLoopMutex;
        bool m_inLoop;

        bool m_waiting;
};

class ConditionTest : public CxxTest::TestSuite {
    public:
        void testLocking() {
            clog << endl << "ConditionTest::testLocking" << endl;
            bool failed = true;
            try {
                Condition c;
                {
                    Lock l(c);
                }
                failed = false;
            } catch (...) {}
            TS_ASSERT(!failed)
        }

        void testWakeOne() {
            clog << endl << "ConditionTest::testWakeOne" << endl;
            Condition conditionForThread1;
            Condition conditionForThread2;
            WaitOnSignalService service1("Service 1", conditionForThread1, conditionForThread2);
            WaitOnSignalService service2("Service 2", conditionForThread2, conditionForThread1);

            // Start both threads.
            service1.start();
            service2.start();

            // Wait until they signalled each other their readiness.
            while ( !service1.isWaiting() || !service2.isWaiting() ) {
                Thread::usleepFor(1000);
            }

            // Awake thread 1 that awakes thread 2.
            {
                Lock l(conditionForThread1);
                conditionForThread1.wakeOne();
            }

            // Let thread 2 awake ourselves by sleeping on the same condition as thread 1.
            {
                Lock l(conditionForThread1);
                conditionForThread1.waitOnSignal();
            }


            // Both threads are in the loop.
            TS_ASSERT(service1.isInLoop() && service2.isInLoop());

            service1.stop();
            service2.stop();
        }

        void testWakeAll() {
            clog << endl << "ConditionTest::testWakeAll" << endl;
            Condition firstCondition;
            Condition secondCondition;
            Condition thirdCondition;
            WaitOnSignalService service1("Service 1", firstCondition, secondCondition);
            WaitOnSignalService service2("Service 2", firstCondition, thirdCondition);

            // Start both threads.
            service1.start();
            service2.start();

            clog << "1" << endl;

            while (!service1.isWaiting() || !service2.isWaiting()) {
                Thread::usleepFor(1000);
            }

            clog << "2" << endl;
            {
                Lock l(firstCondition);
                firstCondition.wakeAll();
            }

            clog << "3" << endl;
            // Let thread 2 awake ourselves by sleeping on the same condition as itself.
            {
                Lock l(thirdCondition);
                clog << "3.1" << endl;
                thirdCondition.waitOnSignal();
                clog << "3.2" << endl;
            }

            clog << "4" << endl;
            TS_ASSERT(service1.isInLoop() && service2.isInLoop());

            service1.stop();
            service2.stop();
        }

        void testTimeCondition() {
            clog << endl << "ConditionTest::testTimeCondition" << endl;
            Condition condition;
            Lock l(condition);

            TS_ASSERT(condition.waitOnSignalWithTimeout(100) == false);

        }
};

#endif /*CORE_CONDITIONTESTSUITE_H_*/
