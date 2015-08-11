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

#ifndef MOCKS_FUNCTIONCALLWAITER_H
#define MOCKS_FUNCTIONCALLWAITER_H

#include "core/base/Lock.h"
#include "core/base/Condition.h"

namespace mocks {

    /**
     * FunctionCallWaiter is a helper class that eases the implementation
     * of mocks that hava to check if a specific method was called.
     */
    class FunctionCallWaiter
    {
        public:
            FunctionCallWaiter() :
				m_called(false),
				m_condition()
			{}

            bool wait() {
            	core::base::Lock lock(m_condition);
                if (!m_called) {
                    return m_condition.waitOnSignalWithTimeout(2000);
                }

                return true;
            }

            bool wasCalled() {
            	core::base::Lock lock(m_condition);
                return m_called;
            }

            void called() {
            	core::base::Lock lock(m_condition);
                m_called = true;
                m_condition.wakeAll();
            }

            void reset() {
                core::base::Lock lock(m_condition);
                m_called = false;
            }

        private:
            bool m_called;
            core::base::Condition m_condition;
    };
}

#endif
