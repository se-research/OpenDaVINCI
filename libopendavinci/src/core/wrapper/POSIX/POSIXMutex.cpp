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

#include "core/wrapper/POSIX/POSIXMutex.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXMutex::POSIXMutex() : m_mutex() {
                // Initialize mutex based on pthread.
                if (pthread_mutex_init(&m_mutex, NULL) != 0) {
                    stringstream s;
                    s << "[core::wrapper::POSIXMutex] Error while creating mutex at " << __FILE__ << ": " << __LINE__ << ": " << strerror(errno);
                    throw s.str();
                }
            }

            POSIXMutex::~POSIXMutex() {
                pthread_mutex_destroy(&m_mutex);
            }

            void POSIXMutex::lock() {
                pthread_mutex_lock(&m_mutex);
            }

            bool POSIXMutex::tryLock() {
                return (pthread_mutex_trylock(&m_mutex) != EBUSY);
            }

            void POSIXMutex::unlock() {
                pthread_mutex_unlock(&m_mutex);
            }

            pthread_mutex_t& POSIXMutex::getNativeMutex() {
                return m_mutex;
            }
        }
    }
} // core::wrapper::POSIX
