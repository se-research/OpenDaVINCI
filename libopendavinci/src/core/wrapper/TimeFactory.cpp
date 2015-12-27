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

#include <stddef.h>

#include "core/wrapper/Mutex.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/Time.h"
#include "core/wrapper/TimeFactory.h"

namespace core {
    namespace wrapper {

        // Set up TimeFactory that can be exchanged on runtime.
        TimeFactory* TimeFactory::instance = NULL;
        TimeFactory* TimeFactory::controlledInstance = NULL;
        auto_ptr<Mutex> TimeFactory::m_singletonMutex = auto_ptr<Mutex>(MutexFactory::createMutex());

        SystemTimeFactory::worker_type SystemTimeFactory::instance = SystemTimeFactory::worker_type();
        
        TimeFactory::TimeFactory() {
            if (TimeFactory::instance == NULL) {
                TimeFactory::instance = this;
            }
        }

        TimeFactory::~TimeFactory() {}

        TimeFactory& TimeFactory::getInstance() {
        	TimeFactory::m_singletonMutex->lock();
            if (TimeFactory::instance == NULL) {
                TimeFactory::instance = new TimeFactory();
            }
            TimeFactory::m_singletonMutex->unlock();

            if (TimeFactory::controlledInstance != NULL) {
                return *(TimeFactory::controlledInstance);
            }

            return *(TimeFactory::instance);
        }

        core::SharedPointer<core::wrapper::Time> TimeFactory::now() {
        	core::SharedPointer<core::wrapper::Time> t;

        	TimeFactory::m_singletonMutex->lock();
                if (TimeFactory::controlledInstance == NULL) {
                    t = core::SharedPointer<Time>(SystemTimeFactory::getInstance().now());
                }
            TimeFactory::m_singletonMutex->unlock();

            // Otherwise, use this time factory (might be overwritten in sub classes).
			if (!t.isValid()) {
				t = TimeFactory::getInstance().now();
			}
            return t;
        }

        void TimeFactory::setSingleton(TimeFactory *tf) {
        	TimeFactory::m_singletonMutex->lock();
            	TimeFactory::controlledInstance = tf;
            TimeFactory::m_singletonMutex->unlock();
        }  

    }
} // core::wrapper
