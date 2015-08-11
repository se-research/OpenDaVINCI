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

#include "core/base/Lock.h"
#include "core/base/Thread.h"
#include "context/base/RunModuleBreakpoint.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;

        RunModuleBreakpoint::RunModuleBreakpoint(BlockableContainerListener &bcl) :
            m_blockableContainerListener(bcl),
            m_reachedMutex(),
            m_reached(false),
            m_continueMutex(),
            m_continue(false) {}

        RunModuleBreakpoint::~RunModuleBreakpoint() {}

        void RunModuleBreakpoint::reached() {
            // Disable sending BEFORE reaching the breakpoint (since RuntimeControl would increment time after reaching the breakpoint).
            m_blockableContainerListener.setNextContainerAllowed(false);

            // Indicate the outer thread that the inner thread has reached its breakpoint.
            {
                Lock l1(m_reachedMutex);
                m_reached = true;
            }

            // Wait for continue.
            while (!hasContinue()) {
                Thread::usleepFor(1000);
            }

            // Enable sending.
            m_blockableContainerListener.setNextContainerAllowed(true);

            // Consume continue.
            {
                Lock l3(m_continueMutex);
                m_continue = false;
            }
        }

        void RunModuleBreakpoint::setFinallyReaching() {
            Lock l1(m_reachedMutex);
            m_reached = true;
        }

        bool RunModuleBreakpoint::hasReached() const {
            bool retVal = false;
            {
                Lock l(m_reachedMutex);
                retVal = m_reached;
            }
            return retVal;
        }

        bool RunModuleBreakpoint::hasContinue() const {
            bool retVal = false;
            {
                Lock l1(m_continueMutex);
                retVal = m_continue;
            }
            return retVal;
        }

        void RunModuleBreakpoint::continueExecution() {
            // Prepare reached for next execution.
            {
                Lock l1(m_reachedMutex);
                m_reached = false;
            }

            // Continue execution.
            {
                Lock l2(m_continueMutex);
                m_continue = true;
            }
        }

    }
} // context::base
