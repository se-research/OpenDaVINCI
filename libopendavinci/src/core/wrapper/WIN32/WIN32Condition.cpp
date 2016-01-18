/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

// Using c++11 standard.
#include <chrono>

#include "opendavinci/core/wrapper/WIN32/WIN32Condition.h"

namespace core {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32Condition::WIN32Condition() :
                m_condition(),
                m_mutex() {}

            WIN32Condition::~WIN32Condition() {}

            void WIN32Condition::waitOnSignal() {
                // Adopt the lock so that the condition can wait on this native mutex.
                std::unique_lock<std::mutex> l(m_mutex.getNativeMutex(), std::adopt_lock);
                m_condition.wait(l);
                // Release the lock (without unlocking it!) so that the outer scope receives the responsibility to unlock the mutex.
                // Thus, the existing semantics which is compliant with the POSIX implementation is preserved.
                l.release();
            }

            bool WIN32Condition::waitOnSignalWithTimeout(const unsigned long ms) {
                // Adopt the lock so that the condition can wait on this native mutex.
                std::unique_lock<std::mutex> l(m_mutex.getNativeMutex(), std::adopt_lock);
                bool retVal = m_condition.wait_for(l, std::chrono::milliseconds(ms)) == std::cv_status::no_timeout;
                // Release the lock (without unlocking it!) so that the outer scope receives the responsibility to unlock the mutex.
                // Thus, the existing semantics which is compliant with the POSIX implementation is preserved.
                l.release();
                return retVal;
            }

            void WIN32Condition::wakeOne() {
                m_condition.notify_one();
            }

            void WIN32Condition::wakeAll() {
                m_condition.notify_all();
            }

            void WIN32Condition::lock() {
                m_mutex.lock();
            }

            bool WIN32Condition::tryLock() {
                return m_mutex.tryLock();
            }

            void WIN32Condition::unlock() {
                m_mutex.unlock();
            }

        }
    }
} // core::wrapper::WIN32Impl
