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

#include <iostream>

#include "opendavinci/odcontext/base/BlockableContainerReceiver.h"
#include "opendavinci/odcontext/base/ControlledContainerConferenceForSystemUnderTest.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerObserver.h"

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::io;

        ControlledContainerConferenceForSystemUnderTest::ControlledContainerConferenceForSystemUnderTest(const string &address, const uint32_t &port, BlockableContainerReceiver &bcl, ContainerObserver &receiveFromObserver) :
            m_sendToListener(bcl),
            m_receiveFromObserver(receiveFromObserver) {
            clog << "ControlledContainerConferenceForSystemUnderTest: " << address << ":" << port << endl;

            // Register ourselves as ContainerListener.
            m_receiveFromObserver.setContainerListener(this);
        }

        ControlledContainerConferenceForSystemUnderTest::~ControlledContainerConferenceForSystemUnderTest() {
            // Deregister ourselves as ContainerListener.
            m_receiveFromObserver.setContainerListener(NULL);
        }

        void ControlledContainerConferenceForSystemUnderTest::send(Container &container) const {
            // Set sending time stamp.
            container.setSentTimeStamp(TimeStamp());

            clog << "Sending '" << container.toString() << "' in ControlledContainerConferenceForSystemUnderTest." << endl;

            m_sendToListener.nextContainer(container);
        }

        BlockableContainerReceiver& ControlledContainerConferenceForSystemUnderTest::getBlockableContainerReceiver() {
            return m_sendToListener;
        }

        void ControlledContainerConferenceForSystemUnderTest::nextContainer(Container &c) {
            c.setReceivedTimeStamp(TimeStamp());

            // Actually receive Container.
            receive(c);
        }

    }
} // odcontext::base
