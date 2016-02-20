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

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"

namespace odcore {
    namespace base {

        Mutex::Mutex() :
            m_mutex() {
            m_mutex = SharedPointer<wrapper::Mutex>(wrapper::MutexFactory::createMutex());
        }

        Mutex::~Mutex() {
            // Add the following semantic: Mutexes that are destroyed will be unlocked automatically.
            tryLock();
            unlock();
        }

        void Mutex::lock() {
            m_mutex->lock();
        }

        bool Mutex::tryLock() {
            return m_mutex->tryLock();
        }

        void Mutex::unlock() {
            m_mutex->unlock();
        }

    }
} // odcore::base
