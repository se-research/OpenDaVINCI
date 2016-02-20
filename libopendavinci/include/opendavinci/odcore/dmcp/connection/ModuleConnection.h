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

#ifndef OPENDAVINCI_DMCP_CONNECTION_MODULECONNECTION_H_
#define OPENDAVINCI_DMCP_CONNECTION_MODULECONNECTION_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/io/ConnectionErrorListener.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/generated/coredata/dmcp/ModuleDescriptor.h"

namespace coredata { namespace dmcp { class PulseMessage; } }
namespace odcore { namespace dmcp { class ModuleConfigurationProvider; } }
namespace odcore { namespace dmcp { class ModuleStateListener; } }

namespace odcore {
    namespace dmcp {
        namespace connection {

            using namespace std;

            class OPENDAVINCI_API ModuleConnection : protected odcore::io::ConnectionErrorListener,
                                                     protected odcore::io::conference::ContainerListener
            {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ModuleConnection(const ModuleConnection &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ModuleConnection& operator=(const ModuleConnection &);

                public:
                    ModuleConnection(odcore::SharedPointer<odcore::io::Connection> connection,
                                     ModuleConfigurationProvider &configProvider);
                    virtual ~ModuleConnection();

                    void setModuleStateListener(ModuleStateListener* listener);

                    void waitForModuleDescription();

                    /**
                     * This method sends a pulse to the connected module.
                     *
                     * @param pm Pulse to be sent.
                     */
                    void pulse(const coredata::dmcp::PulseMessage &pm);

                    /**
                     * This method sends a pulse to the connected module and
                     * requires an ACK confirmation sent from the respective,
                     * dependent module that the PULSE has been processed.
                     *
                     * @param pm Pulse to be sent.
                     * @param timeout Timeout in milliseconds to wait for the ACK message.
                     */
                    void pulse_ack(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout);

                    /**
                     * This method sends a pulse to the connected module and
                     * requires an ACK confirmation sent from the respective,
                     * dependent module that the PULSE has been processed. In
                     * addition to the original pulse_ack method, this one
                     * also receives all newly created containers from the
                     * dependent module to be transferred to supercomponent.
                     *
                     * @param pm Pulse to be sent.
                     * @param timeout Timeout in milliseconds to wait for the ACK message.
                     * @return Containers to be transferred to supercomponent.
                     */
                    vector<odcore::data::Container> pulse_ack_containers(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout);

                    const coredata::dmcp::ModuleDescriptor getModuleDescriptor() const;

                protected:
                    virtual void nextContainer(odcore::data::Container &c);
                    virtual void handleConnectionError();

                    odcore::SharedPointer<odcore::io::Connection> m_connection;
                    ModuleConfigurationProvider& m_configurationProvider;

                    odcore::base::Condition m_descriptorCondition;
                    coredata::dmcp::ModuleDescriptor m_descriptor;
                    bool m_hasDescriptor;

                    odcore::base::Condition m_pulseAckCondition;
                    bool m_hasReceivedPulseAck;

                    odcore::base::Condition m_pulseAckContainersCondition;
                    bool m_hasReceivedPulseAckContainers;

                    odcore::base::Mutex m_connectionLostMutex;
                    bool m_connectionLost;

                    ModuleStateListener* m_stateListener;
                    odcore::base::Mutex m_stateListenerMutex;

                    vector<odcore::data::Container> m_containersToBeTransferredToSupercomponent;
            };
        }
    }
} // odcore::dmcp

#endif /*OPENDAVINCI_DMCP_CONNECTION_MODULECONNECTION_H_*/
