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

#ifndef CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCEFACTORY_H_
#define CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCEFACTORY_H_

#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcontext/base/ControlledContainerConference.h"

namespace odcore { namespace data { class Container; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace odcontext {
    namespace base {

class BlockableContainerReceiver;
class ContainerDeliverer;

        using namespace std;

        /**
         * This class provides controlled ContainerConferences.
         */
        class OPENDAVINCI_API ControlledContainerConferenceFactory : public odcore::io::conference::ContainerConferenceFactory, public ControlledContainerConference, public odcore::io::conference::ContainerListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ControlledContainerConferenceFactory(const ControlledContainerConferenceFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ControlledContainerConferenceFactory& operator=(const ControlledContainerConferenceFactory &);

            public:
                ControlledContainerConferenceFactory();

                virtual ~ControlledContainerConferenceFactory();

                /**
                 * This method returns a new ContainerConference.
                 *
                 * @param address Use address for joining.
                 * @param port Use port for joining.  If omitted, MULTICAST_PORT will be used.
                 * @return ContainerConference or NULL.
                 */
                virtual odcore::SharedPointer<odcore::io::conference::ContainerConference> getContainerConference(const string &address, const uint32_t &port = odcore::io::conference::ContainerConferenceFactory::MULTICAST_PORT);

                virtual void sendToSystemsUnderTest(odcore::data::Container &c);

                virtual void add(odcore::io::conference::ContainerListener *cl);

                // This method is called by BlockableContainerReceiver to send data FROM a specific System Under Test to all SystemParts.
                // Furthermore, every container send from a System Under Test is also dispatched to all Systems Under Test using sendToSystemsUnderTest
                virtual void nextContainer(odcore::data::Container &c);

            private:
                /**
                 * This method sends the given container to all systems under test
                 * without modifying the sent timestamp.
                 *
                 * @param c Container to send.
                 */
                void sendToSUD(odcore::data::Container &c);

                /**
                 * This method sends the given container to all SystemContextComponents
                 * without modifying the sent timestamp.
                 *
                 * @param c Container to send.
                 */
                void sendToSCC(odcore::data::Container &c);

            private:
                odcore::base::Mutex m_listOfContainerListenersToReceiveContainersFromSystemsUnderTestMutex;
                vector<odcore::io::conference::ContainerListener*> m_listOfContainerListenersToReceiveContainersFromSystemsUnderTest;

                // Using ContainerDeliverers, synchronous communication is enforced.
                odcore::base::Mutex m_listOfContainerDelivererToSystemUnderTestMutex;
                vector<ContainerDeliverer*> m_listOfContainerDelivererToSystemUnderTest;

                odcore::base::Mutex m_listOfContainerDelivererFromSystemUnderTestMutex;
                vector<BlockableContainerReceiver*> m_listOfContainerDelivererFromSystemUnderTest;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_CONTROLLEDCONTAINERCONFERENCEFACTORY_H_*/
