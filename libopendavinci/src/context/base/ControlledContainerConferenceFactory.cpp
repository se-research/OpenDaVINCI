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

#include "opendavinci/context/base/BlockableContainerReceiver.h"
#include "opendavinci/context/base/ContainerDeliverer.h"
#include "opendavinci/context/base/ControlledContainerConferenceFactory.h"
#include "opendavinci/context/base/ControlledContainerConferenceForSystemUnderTest.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/data/TimeStamp.h"
#include "opendavinci/core/io/conference/ContainerConference.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;
        using namespace core::io::conference;

        ControlledContainerConferenceFactory::ControlledContainerConferenceFactory() :
            m_listOfContainerListenersToReceiveContainersFromSystemsUnderTestMutex(),
            m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest(),
            m_listOfContainerDelivererToSystemUnderTestMutex(),
            m_listOfContainerDelivererToSystemUnderTest(),
            m_listOfContainerDelivererFromSystemUnderTestMutex(),
            m_listOfContainerDelivererFromSystemUnderTest() {
            ContainerConferenceFactory::setSingleton(this);
        }

        ControlledContainerConferenceFactory::~ControlledContainerConferenceFactory() {
            {
                Lock l1(m_listOfContainerListenersToReceiveContainersFromSystemsUnderTestMutex);
                m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest.clear();
            }

            {
                Lock l2(m_listOfContainerDelivererToSystemUnderTestMutex);
                m_listOfContainerDelivererToSystemUnderTest.clear();
            }

            {
                Lock l3(m_listOfContainerDelivererFromSystemUnderTestMutex);
                m_listOfContainerDelivererFromSystemUnderTest.clear();
            }
        }

        void ControlledContainerConferenceFactory::add(core::io::conference::ContainerListener *cl) {
            if (cl != NULL) {
                Lock l(m_listOfContainerListenersToReceiveContainersFromSystemsUnderTestMutex);
                m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest.push_back(cl);
            }
        }

        void ControlledContainerConferenceFactory::sendToSUD(core::data::Container &c) {
            Lock l(m_listOfContainerDelivererToSystemUnderTestMutex);

            clog << "Distributing '" << c.toString() << "' in ControlledContainerConferenceFactory to all ContainerConferences from Systems Under Test." << endl;

            // Set sent time.
            c.setSentTimeStamp(TimeStamp());

            vector<ContainerDeliverer*>::iterator it = m_listOfContainerDelivererToSystemUnderTest.begin();
            while (it != m_listOfContainerDelivererToSystemUnderTest.end()) {
                ContainerDeliverer *containerDeliverer = (*it++);
                if (containerDeliverer != NULL) {
                    containerDeliverer->nextContainer(c);
                }
            }
        }

        void ControlledContainerConferenceFactory::sendToSCC(core::data::Container &c) {
            Lock l(m_listOfContainerListenersToReceiveContainersFromSystemsUnderTestMutex);

            clog << "Distributing '" << c.toString() << "' in ControlledContainerConferenceFactory to all SystemParts." << endl;

            vector<ContainerListener*>::iterator it = m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest.begin();
            while (it != m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest.end()) {
                ContainerListener *cl = (*it++);
                if (cl != NULL) {
                    cl->nextContainer(c);
                }
            }
        }

        void ControlledContainerConferenceFactory::nextContainer(Container &c) {
            // This method is called by BlockableContainerReceiver to distribute a Container
            // which is sent FROM a SystemUnderTest to all SystemParts AND to all Systems under Tests.
            sendToSCC(c);

            // Additionally, send this Container also to all Systems Under Tests (UDP would do the same).
            sendToSUD(c);
        }

        void ControlledContainerConferenceFactory::sendToSystemsUnderTest(Container &c) {
            // Set sent time.
            c.setSentTimeStamp(TimeStamp());

            // Send to all systems under test.
            sendToSUD(c);

            // Send to all SystemContextComponents.
            sendToSCC(c);
        }

        core::SharedPointer<ContainerConference> ControlledContainerConferenceFactory::getContainerConference(const string &address, const uint32_t &port) {
            // Create a ControlledContainerConference specific synchronous ContainerDeliverer which delivers containers sent TO the system under test.
            ContainerDeliverer *containerDelivererToSystemUnderTest = new ContainerDeliverer();

            // Create a BlockableContainerReceiver which can hold the sending of containers FROM the system under test.
            BlockableContainerReceiver *blockableContainerReceiverFromSystemUnderTest = new BlockableContainerReceiver(*this);

            // Connect the FIFO with a new ControlledContainerConferenceForSystemUnderTest for decoupling it from the factory (the receiving instance will destroy the ControlledContainerConferenceForSystemUnderTest later).
            core::SharedPointer<ContainerConference> ccc(new ControlledContainerConferenceForSystemUnderTest(address, port, *blockableContainerReceiverFromSystemUnderTest, *containerDelivererToSystemUnderTest));

            // Add ContainerDelivererTOSystemUnderTest to list.
            {
                Lock l(m_listOfContainerDelivererToSystemUnderTestMutex);
                m_listOfContainerDelivererToSystemUnderTest.push_back(containerDelivererToSystemUnderTest);
            }

            // Add BlockableContainerReceiverFROMSystemUnderTest to list.
            {
                Lock l(m_listOfContainerDelivererFromSystemUnderTestMutex);
                m_listOfContainerDelivererFromSystemUnderTest.push_back(blockableContainerReceiverFromSystemUnderTest);
            }

            return ccc;
        }

    }
} // context::base
