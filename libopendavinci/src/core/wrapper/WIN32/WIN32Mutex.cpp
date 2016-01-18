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

#include "opendavinci/core/wrapper/WIN32/WIN32Mutex.h"

namespace core {
    namespace wrapper {
        namespace WIN32Impl {

            using namespace std;

            WIN32Mutex::WIN32Mutex() :
                m_mutex() {}

            WIN32Mutex::~WIN32Mutex() {}

            void WIN32Mutex::lock() {
                m_mutex.lock();
            }

            bool WIN32Mutex::tryLock() {
                return m_mutex.try_lock();
            }

            void WIN32Mutex::unlock() {
                m_mutex.unlock();
            }

            mutex& WIN32Mutex::getNativeMutex() {
                return m_mutex;
            }

        }
    }
} // core::wrapper::WIN32Impl
