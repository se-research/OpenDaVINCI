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

#include <cerrno>
#include <cstring>

#include "core/wrapper/POSIX/POSIXCondition.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXCondition::POSIXCondition() : 
                m_condition(),
                m_mutex() {
                // Initialize condition based on pthread.
                if (pthread_cond_init(&m_condition, NULL) != 0) {
                    stringstream s;
                    s << "[core::wrapper::POSIXCondition] Error while creating condition: " << strerror(errno);
                    throw s.str();
                }
            }

            POSIXCondition::~POSIXCondition() {
                pthread_cond_destroy(&m_condition);
            }

            void POSIXCondition::waitOnSignal() {
                pthread_cond_wait(&m_condition, &m_mutex.getNativeMutex());
            }

            bool POSIXCondition::waitOnSignalWithTimeout(const unsigned long ms) {
                struct timespec timeout;
#ifdef HAVE_LINUX_RT
                clock_gettime(CLOCK_REALTIME, &timeout);
#else
                struct timeval tv;
                gettimeofday(&tv, NULL);
                timeout.tv_sec = tv.tv_sec;
                timeout.tv_nsec = tv.tv_usec * 1000;
#endif

                uint32_t seconds = 0;
                unsigned long milliseconds = ms;
                while (milliseconds >= 1000) {
                    seconds++;
                    milliseconds -= 1000;
                }
                timeout.tv_sec += seconds;
                timeout.tv_nsec += milliseconds * 1000 * 1000;

                int32_t error = pthread_cond_timedwait(&m_condition, &m_mutex.getNativeMutex(), &timeout);

                return (error == 0);
            }

            void POSIXCondition::wakeOne() {
                pthread_cond_signal(&m_condition);
            }

            void POSIXCondition::wakeAll() {
                pthread_cond_broadcast(&m_condition);
            }

            void POSIXCondition::lock() {
                m_mutex.lock();
            }

            bool POSIXCondition::tryLock() {
                return m_mutex.tryLock();
            }

            void POSIXCondition::unlock() {
                m_mutex.unlock();
            }

        }
    }
} // core::wrapper::POSIX
