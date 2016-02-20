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

#include <cstdlib>
#include <iostream>
#include <sstream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/ConditionFactory.h"
#include "opendavinci/odcore/wrapper/Disposable.h"
#include "opendavinci/odcore/wrapper/DisposalService.h"
#include "opendavinci/odcore/wrapper/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/odcore/wrapper/Thread.h"

namespace odcore {
    namespace wrapper {

        // Initialization of the singleton instance.
        auto_ptr<Mutex> DisposalService::m_singletonMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
        DisposalService* DisposalService::m_singleton = NULL;

        DisposalService::DisposalService() :
            m_queueCondition(NULL),
            m_finalRemovalMutex(NULL),
            m_queueMutex(NULL),
            m_queueForRegularRemoval(),
            m_queueForFinalRemoval(),
            m_thread(NULL),
            m_queueCleaner(NULL) {

            m_queueCondition = ConditionFactory::createCondition();
            if (!m_queueCondition.isValid()) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating condition.";
                throw s.str();
            }

            m_finalRemovalMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_finalRemovalMutex.get() == NULL) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating mutex.";
                throw s.str();
            }

            m_queueMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_queueMutex.get() == NULL) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating mutex.";
                throw s.str();
            }

            m_queueCleaner = new DisposalService::QueueCleaner(m_queueCondition, *m_finalRemovalMutex, *m_queueMutex, m_queueForRegularRemoval);
            if (m_queueCleaner == NULL) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating queue cleaner.";
                throw s.str();
            }

            m_queueCleaner->setRunning(true);

            // Create thread for encapsulating string distribution.
            m_thread = auto_ptr<Thread>(ConcurrencyFactory::createThread(*m_queueCleaner));
            if (m_thread.get() == NULL) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating thread.";
                throw s.str();
            }

            // Start thread.
            m_thread->start();
        }

        DisposalService::~DisposalService() {
            // Stop runnable.
            m_queueCleaner->setRunning(false);

            // Wake awaiting threads before destructing.
            m_queueCondition->wakeAll();

            // Stop thread.
            m_thread->stop();

            // Clean up finally.
            cleanUpFinally();

            // Destroy distributor.
            if (m_queueCleaner != NULL) {
                delete m_queueCleaner;
            }
            m_queueCleaner = NULL;

            DisposalService::m_singleton = NULL;
        }

        DisposalService& DisposalService::getInstance() {
            DisposalService::m_singletonMutex->lock();
            {
                if (DisposalService::m_singleton == NULL) {
                    DisposalService::m_singleton = new DisposalService();
                }
            }
            DisposalService::m_singletonMutex->unlock();

            return *m_singleton;
        }

        void DisposalService::cleanUpImmediately() {
            m_queueCondition->lock();
            {
                // Wake awaiting threads.
                m_queueCondition->wakeAll();
            }
            m_queueCondition->unlock();
        }

        void DisposalService::cleanUpFinally() {
            m_finalRemovalMutex->lock();
            {
                deque<Disposable**>::iterator it;

                CLOG2 << "[core::wrapper::DisposalServer] Cleaning up regular removal queue... ";
                // Clean up regular removal queue.
                it = m_queueForRegularRemoval.begin();
                while (it != m_queueForRegularRemoval.end()) {
                    Disposable **disposable = (*it++);
                    CLOG2 << *disposable << " ";
                    OPENDAVINCI_CORE_FREE_POINTER(*disposable);
                }
                m_queueForRegularRemoval.clear();
                CLOG2 << "done." << endl;

                CLOG2 << "[core::wrapper::DisposalServer] Cleaning up final removal queue... ";
                // Clean up regular removal queue.
                it = m_queueForFinalRemoval.begin();
                while (it != m_queueForFinalRemoval.end()) {
                    Disposable **disposable = (*it++);
                    CLOG2 << *disposable << " ";
                    OPENDAVINCI_CORE_FREE_POINTER(*disposable);
                }
                m_queueForFinalRemoval.clear();
                CLOG2 << "done." << endl;
            }
            m_finalRemovalMutex->unlock();
        }

        void DisposalService::addDisposableForRegularRemoval(Disposable **d) {
            if (d != NULL) {
                m_queueCondition->lock();
                {
                    // Enter new data.
                    m_queueMutex->lock();
                    m_queueForRegularRemoval.push_back(d);
                    m_queueMutex->unlock();

                    // Wake awaiting threads.
                    m_queueCondition->wakeAll();
                }
                m_queueCondition->unlock();
            }
        }

        void DisposalService::addDisposableForFinalRemoval(Disposable **d) {
            if (d != NULL) {
                // Enter new data.
                m_queueForFinalRemoval.push_back(d);
            }
        }

        DisposalService::QueueCleaner::QueueCleaner(SharedPointer<Condition> condition, Mutex &finalRemovalMutex, Mutex &mutex, deque<Disposable**> &queue) :
            m_queueCondition(condition),
            m_finalRemovalMutex(finalRemovalMutex),
            m_queueMutex(mutex),
            m_queue(queue),
            m_threadStateMutex(NULL),
            m_threadState(false) {
            m_threadStateMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
            if (m_threadStateMutex.get() == NULL) {
                stringstream s;
                s << "[core::wrapper::DisposalServer] Error while creating mutex.";
                throw s.str();
            }
        }

        DisposalService::QueueCleaner::~QueueCleaner() {}

        void DisposalService::QueueCleaner::run() {
            while (isRunning()) {
                m_queueCondition->lock();
                    m_queueCondition->waitOnSignal();
                m_queueCondition->unlock();

                // Delay removal.
                ConcurrencyFactory::usleepFor(1000);

                if (isRunning()) {
                    uint32_t numberOfEntries = 0;

                    // Determine the amount of current entries.
                    m_queueMutex.lock();
                    {
                        numberOfEntries = static_cast<uint32_t>(m_queue.size());
                    }
                    m_queueMutex.unlock();

                    if (numberOfEntries > 0) {
                        // Lock final removal method.
                        m_finalRemovalMutex.lock();

                        // Read all entries and clean up.
                        Disposable **disposable = NULL;
                        for (uint32_t i = 0; i < numberOfEntries; i++) {
                            // Acquire next entry.
                            m_queueMutex.lock();
                            {
                                disposable = m_queue.front();
                            }
                            m_queueMutex.unlock();

                            // Remove entry.
                            OPENDAVINCI_CORE_DELETE_POINTER(*disposable);

                            // Delay removal.
                            ConcurrencyFactory::usleepFor(5);

                            // Remove processed entry.
                            m_queueMutex.lock();
                            {
                                m_queue.pop_front();
                            }
                            m_queueMutex.unlock();
                        }

                        m_finalRemovalMutex.unlock();
                    }
                }
            }
        }

        void DisposalService::QueueCleaner::setRunning(const bool &b) {
            m_threadStateMutex->lock();
            {
                m_threadState = b;
            }
            m_threadStateMutex->unlock();
        }

        bool DisposalService::QueueCleaner::isRunning() {
            bool retVal = false;
            m_threadStateMutex->lock();
            {
                retVal = m_threadState;
            }
            m_threadStateMutex->unlock();

            return retVal;
        }

    }
} // odcore::wrapper
