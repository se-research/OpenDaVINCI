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

#include "core/base/module/AbstractCIDModule.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/POSIX/POSIXThread.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            /**
             * This method encapsulates the runnable.
             */
            void *threadRunner(void *v) {
                pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
                Runnable *runnable = static_cast<Runnable*>(v);

                try {
                    runnable->run();
                } catch (string &s) {
                    CLOG3 << "[core::wrapper::POSIXThread] Exception caught: " << s << endl;
                    throw;
                } catch (...) {
                    CLOG3 << "[core::wrapper::POSIXThread] Unknown exception caught." << endl;
                    throw;
                }

                // The pthread_exit sys call terminates this thread to allow a clean join.
                pthread_exit(NULL);
                return NULL;
            }

            POSIXThread::POSIXThread(Runnable &r) :
                m_threadStateMutex(NULL),
                m_threadState(INITIALIZED),
                m_runnable(r),
                m_threadWrapper() {
                // Create mutex.
                m_threadStateMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_threadStateMutex.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::POSIXThread] Error creating mutex: " << strerror(errno);
                    throw s.str();
                }
            }

            POSIXThread::~POSIXThread() {
                stop();
            }

            bool POSIXThread::start() {
                m_threadStateMutex->lock();
                {
                    if (m_threadState == INITIALIZED) {
                        pthread_create(&m_threadWrapper, NULL, threadRunner, &m_runnable);
                        m_threadState = RUNNING;
                    }
                }
                m_threadStateMutex->unlock();

                return isRunning();
            }

            bool POSIXThread::stop() {
                bool doJoin = false;
                m_threadStateMutex->lock();
                {
                    if (m_threadState == RUNNING) {
                        doJoin = true;
                        m_threadState = STOPPED;
                    }
                }
                m_threadStateMutex->unlock();

                if (doJoin) {
                    void *retVal = NULL;
                    pthread_join(m_threadWrapper, &retVal);
                }

                return !isRunning();
            }

            bool POSIXThread::isRunning() const {
                bool retVal = false;
                m_threadStateMutex->lock();
                {
                    retVal = (m_threadState == RUNNING);
                }
                m_threadStateMutex->unlock();

                return retVal;
            }

        }
    }
} // core::wrapper::POSIX
