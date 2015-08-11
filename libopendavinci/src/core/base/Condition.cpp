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

#include "core/base/Condition.h"
#include "core/wrapper/ConditionFactory.h"

namespace core {
    namespace base {

        Condition::Condition() :
            m_condition() {
            m_condition = core::wrapper::ConditionFactory::createCondition();
        }

        Condition::~Condition() {}

        void Condition::waitOnSignal() {
            m_condition->waitOnSignal();
        }

        bool Condition::waitOnSignalWithTimeout(const unsigned long& ms) {
            return m_condition->waitOnSignalWithTimeout(ms);
        }

        void Condition::wakeOne() {
            m_condition->wakeOne();
        }

        void Condition::wakeAll() {
            m_condition->wakeAll();
        }

        void Condition::lock() {
            m_condition->lock();
        }

        bool Condition::tryLock() {
            return m_condition->tryLock();
        }

        void Condition::unlock() {
            m_condition->unlock();
        }

    }
} // core::base
