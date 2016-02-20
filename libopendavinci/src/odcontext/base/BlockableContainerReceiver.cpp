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

#include "opendavinci/odcontext/base/BlockableContainerReceiver.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;

        BlockableContainerReceiver::BlockableContainerReceiver(odcore::io::conference::ContainerListener &cl) :
            m_dispatcherForContainersSentFromSystemUnderTest(cl) {}

        BlockableContainerReceiver::~BlockableContainerReceiver() {
            // Break blocking.
            setNextContainerAllowed(true);
        }

        void BlockableContainerReceiver::nextContainer(Container &c) {
            while (!isNextContainerAllowed()) {
                Thread::usleepFor(BlockableContainerReceiver::YIELDING_TIME);
            }

            // Set received TimeStamp.
            c.setReceivedTimeStamp(TimeStamp());

            // Delegate Containter to dispatcher.
            m_dispatcherForContainersSentFromSystemUnderTest.nextContainer(c);
        }

    }
} // odcontext::base
