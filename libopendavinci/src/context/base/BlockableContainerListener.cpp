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
#include "context/base/BlockableContainerListener.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;

        BlockableContainerListener::BlockableContainerListener() :
            m_nextContainerAllowedMutex(),
            m_nextContainerAllowed(false) {}

        BlockableContainerListener::~BlockableContainerListener() {
            // Break blocking.
            setNextContainerAllowed(true);
        }

        void BlockableContainerListener::setNextContainerAllowed(const bool &allowed) {
            {
                Lock l(m_nextContainerAllowedMutex);
                m_nextContainerAllowed = allowed;
            }
        }

        bool BlockableContainerListener::isNextContainerAllowed() const {
            bool retVal = false;
            {
                Lock l(m_nextContainerAllowedMutex);
                retVal = m_nextContainerAllowed;
            }
            return retVal;
        }

    }
} // context::base
