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

#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/core/dmcp/ModuleStateListener.h"
#include "opendavinci/core/dmcp/connection/ModuleConnection.h"
#include "opendavinci/generated/coredata/Configuration.h"
#include "opendavinci/generated/coredata/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/coredata/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/coredata/dmcp/PulseAckContainersMessage.h"
#include "opendavinci/generated/coredata/dmcp/PulseMessage.h"
#include "opendavinci/generated/coredata/dmcp/RuntimeStatistic.h"

namespace core {
    namespace dmcp {
        namespace connection {

            using namespace std;
            using namespace core::base;
            using namespace core::data;
            using namespace coredata::dmcp;

            ModuleConnection::ModuleConnection(core::SharedPointer<core::io::Connection> connection,
                                               ModuleConfigurationProvider &configProvider) :
                m_connection(connection),
                m_configurationProvider(configProvider),
                m_descriptorCondition(),
                m_descriptor(),
                m_hasDescriptor(),
                m_pulseAckCondition(),
                m_hasReceivedPulseAck(false),
                m_pulseAckContainersCondition(),
                m_hasReceivedPulseAckContainers(false),
                m_connectionLostMutex(),
                m_connectionLost(false),
                m_stateListener(),
                m_stateListenerMutex(),
                m_containersToBeTransferredToSupercomponent() {
                m_connection->setContainerListener(this);
                m_connection->setErrorListener(this);
                m_connection->start();
            }

            ModuleConnection::~ModuleConnection() {
                m_connection->setContainerListener(NULL);
                m_connection->setErrorListener(NULL);
                m_connection->stop();
            }

            void ModuleConnection::setModuleStateListener(ModuleStateListener* listener) {
                Lock l(m_stateListenerMutex);
                m_stateListener = listener;
            }

            void ModuleConnection::waitForModuleDescription() {
                Lock l(m_descriptorCondition);
                if (!m_hasDescriptor) {
                    m_descriptorCondition.waitOnSignal();
                }
            }

            const ModuleDescriptor ModuleConnection::getModuleDescriptor() const {
                return m_descriptor;
            }

            void ModuleConnection::pulse(const coredata::dmcp::PulseMessage &pm) {
                Container c(Container::DMCP_PULSE_MESSAGE, pm);
                m_connection->send(c);
            }

            void ModuleConnection::pulse_ack(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout) {
                // Unfortunately, we cannot prevent code duplication here (cf. pulse_ack_containers)
                // as in this case, the dependent client module will NOT send its containers to using
                // this TCP link but via the regular UDP multicast conference.
                bool connectionLost = true;

                {
                    Lock l(m_connectionLostMutex);
                    connectionLost = m_connectionLost;
                }

                // Only wait for a confirmation from dependent modules when they are still connected.
                if (!connectionLost) {
                    {
                        Lock l(m_pulseAckCondition);
                        m_hasReceivedPulseAck = false;
                    }

                    Container c(Container::DMCP_PULSE_MESSAGE, pm);
                    m_connection->send(c);

                    // Wait for the ACK message from client.
                    {
                        Lock l(m_pulseAckCondition);
                        if (!m_hasReceivedPulseAck) {
                            m_pulseAckCondition.waitOnSignalWithTimeout(timeout);
                        }
                    }
                }
            }

            vector<core::data::Container> ModuleConnection::pulse_ack_containers(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout) {
                // Unfortunately, we cannot prevent code duplication here (cf. pulse_ack)
                // as in this case, the dependent client module will send all its containers
                // via this TCP link and NOT via the regular UDP multicast conference.

                // Assume that we don't receive any further containers.
                m_containersToBeTransferredToSupercomponent.clear();

                bool connectionLost = true;
                {
                    Lock l(m_connectionLostMutex);
                    connectionLost = m_connectionLost;
                }

                // Only wait for a confirmation from dependent modules when they are still connected.
                if (!connectionLost) {
                    {
                        Lock l(m_pulseAckContainersCondition);
                        m_hasReceivedPulseAckContainers = false;
                    }

                    Container c(Container::DMCP_PULSE_MESSAGE, pm);
                    m_connection->send(c);

                    // Wait for the ACK message from client.
                    {
                        Lock l(m_pulseAckContainersCondition);
                        if (!m_hasReceivedPulseAckContainers) {
                            m_pulseAckContainersCondition.waitOnSignalWithTimeout(timeout);
                        }
                    }
                }

                return m_containersToBeTransferredToSupercomponent;
            }

            void ModuleConnection::nextContainer(Container &container) {
                switch (container.getDataType()) {
                    case Container::DMCP_CONFIGURATION_REQUEST:
                    {
                        m_descriptor = container.getData<ModuleDescriptor>();
                        {
                            Lock l(m_descriptorCondition);
                            m_hasDescriptor = true;
                            m_descriptorCondition.wakeAll();
                        }

                        KeyValueConfiguration config = m_configurationProvider.getConfiguration(m_descriptor);

                        Container c(Container::CONFIGURATION, coredata::Configuration(config));
                        m_connection->send(c);
                        break;
                    }

                    case Container::DMCP_MODULESTATEMESSAGE:
                    {
                        ModuleStateMessage msg = container.getData<ModuleStateMessage>();

                        Lock l(m_stateListenerMutex);
                        if (m_stateListener) {
                            m_stateListener->handleChangeState(m_descriptor, msg.getModuleState());
                        }
                        break;
                    }

                    case Container::DMCP_MODULEEXITCODEMESSAGE:
                    {
                        ModuleExitCodeMessage msg = container.getData<ModuleExitCodeMessage>();

                        Lock l(m_stateListenerMutex);
                        if (m_stateListener) {
                            m_stateListener->handleExitCode(m_descriptor, msg.getModuleExitCode());
                        }
                        break;
                    }

                    case Container::RUNTIMESTATISTIC:
                    {
                        coredata::dmcp::RuntimeStatistic rs = container.getData<coredata::dmcp::RuntimeStatistic>();

                        Lock l(m_stateListenerMutex);
                        if (m_stateListener) {
                            m_stateListener->handleRuntimeStatistics(m_descriptor, rs);
                        }
                        break;
                    }

                    case Container::DMCP_PULSE_ACK_MESSAGE:
                    {
                        Lock l(m_pulseAckCondition);
                        m_hasReceivedPulseAck = true;
                        m_pulseAckCondition.wakeAll();
                        break;
                    }

                    case Container::DMCP_PULSE_ACK_CONTAINERS_MESSAGE:
                    {
                        Lock l(m_pulseAckContainersCondition);
                        m_hasReceivedPulseAckContainers = true;

                        // Get containers to be transferred to supercomponent.
                        PulseAckContainersMessage pac = container.getData<PulseAckContainersMessage>();
                        m_containersToBeTransferredToSupercomponent = pac.getListOfContainers();

                        m_pulseAckContainersCondition.wakeAll();
                        break;
                    }

                    default:
                    {
                        Lock l(m_stateListenerMutex);
                        if (m_stateListener) {
                            m_stateListener->handleUnkownContainer(m_descriptor, container);
                        }
                        break;
                    }
                }
            }

            void ModuleConnection::handleConnectionError() {
                // Set connection lost flag.
                {
                    Lock l(m_connectionLostMutex);
                    m_connectionLost = true;
                }

                // Awake any waiting conditions.
                {
                    Lock l(m_pulseAckCondition);
                    m_pulseAckCondition.wakeAll();
                }

                // Awake any waiting conditions.
                {
                    Lock l(m_pulseAckContainersCondition);
                    m_pulseAckContainersCondition.wakeAll();
                }

                // Change module's state.
                {
                    Lock l(m_stateListenerMutex);

                    if (m_stateListener) {
                        m_stateListener->handleConnectionLost(m_descriptor);
                    }
                }
            }

        }
    }
} // core::dmcp
