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
#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Lock.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/data/Container.h"
#include "core/dmcp/SuperComponentStateListener.h"
#include "core/dmcp/connection/Client.h"
#include "core/exceptions/Exceptions.h"
#include "core/opendavinci.h"
#include "generated/coredata/Configuration.h"
#include "generated/coredata/dmcp/Constants.h"
#include "generated/coredata/dmcp/PulseAckContainersMessage.h"
#include "generated/coredata/dmcp/PulseAckMessage.h"

namespace core {
    namespace dmcp {
        namespace connection {
            using namespace std;

            using namespace core::base;
            using namespace core::exceptions;
            using namespace core::io;
            using namespace core::data;
            using namespace core::dmcp;
            using namespace coredata::dmcp;

            Client::Client(const ModuleDescriptor& moduleDescriptor, const ServerInformation& serverInformation) :
                m_moduleDescriptor(moduleDescriptor),
                m_serverInformation(serverInformation),
                m_connection(serverInformation.getIP(), serverInformation.getPort()),
                m_configurationMutex(),
                m_configuration(),
                m_configured(false),
                m_configuredMutex(),
                m_configurationRequestCondition(),
                m_listenerMutex(),
                m_listener(NULL),
                m_pulseCondition(),
                m_pulseMessageMutex(),
                m_pulseMessage() {
                m_connection.setContainerListener(this);
                m_connection.setErrorListener(this);
                m_connection.start();
            }

            Client::~Client() {
                m_connection.setContainerListener(NULL);
                m_connection.setErrorListener(NULL);
                m_connection.stop();
            }

            void Client::initialize() {
                sendConfigurationRequest();
                waitForConfiguration();
            }

            void Client::sendModuleExitCode(const coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode& exitCode) {
                Container container(Container::DMCP_MODULEEXITCODEMESSAGE, ModuleExitCodeMessage(exitCode));
                m_connection.send(container);
            }

            void Client::sendModuleState(const coredata::dmcp::ModuleStateMessage::ModuleState& state) {
                Container container(Container::DMCP_MODULESTATEMESSAGE, ModuleStateMessage(state));
                m_connection.send(container);
            }

            void Client::sendStatistics(const coredata::dmcp::RuntimeStatistic& rs) {
                Container container(Container::RUNTIMESTATISTIC, rs);
                m_connection.send(container);
            }

            KeyValueConfiguration Client::getConfiguration() {
                Lock l(m_configurationMutex);
                return m_configuration;
            }

            void Client::setSupercomponentStateListener(SupercomponentStateListener* listener) {
                Lock l(m_listenerMutex);
                m_listener = listener;
            }

            void Client::sendConfigurationRequest() {
                CLOG1 << "(DMCP-ConnectionClient) sending configuration request..." << m_serverInformation.toString() << endl;

                Container container(Container::DMCP_CONFIGURATION_REQUEST, m_moduleDescriptor);
                m_connection.send(container);
            }

            void Client::sendPulseAck() {
                Container container(Container::DMCP_PULSE_ACK_MESSAGE, PulseAckMessage());
                m_connection.send(container);
            }

            void Client::sendPulseAckContainers(const vector<core::data::Container> &listOfContainers) {
                PulseAckContainersMessage pac;
                pac.setListOfContainers(listOfContainers);
                Container container(Container::DMCP_PULSE_ACK_CONTAINERS_MESSAGE, pac);
                m_connection.send(container);
            }

            void Client::nextContainer(Container &c) {
                if (c.getDataType() == Container::CONFIGURATION) {
                    coredata::Configuration configuration = c.getData<coredata::Configuration>();
                    handleConfiguration(configuration);
                }

                if (c.getDataType() == Container::DMCP_PULSE_MESSAGE) {
                    {
                        Lock l(m_pulseMessageMutex);
                        m_pulseMessage = c.getData<PulseMessage>();
                    }

                    {
                        Lock l(m_pulseCondition);
                        m_pulseCondition.wakeAll();
                    }
                }
            }

            const coredata::dmcp::PulseMessage Client::getPulseMessage() {
                PulseMessage pm;

                {
                    Lock l(m_pulseCondition);
                    m_pulseCondition.waitOnSignal();
                }

                {
                    Lock l(m_pulseMessageMutex);
                    pm = m_pulseMessage;
                }

                return pm;
            }

            void Client::handleConnectionError() {
                // Awake any sleeping modules.
                {
                    Lock l(m_pulseCondition);
                    m_pulseCondition.wakeAll();
                }

                {
                    Lock l(m_listenerMutex);
                    if (m_listener) {
                        m_listener->handleConnectionLost();
                    }
                }
            }

            void Client::handleConfiguration(coredata::Configuration& configuration) {
                Lock l(m_configurationRequestCondition);
                CLOG1 << "(DMCP-Client) Received Configuration" << endl;

                try {
                    KeyValueConfiguration kvc = configuration.getKeyValueConfiguration();
                    CLOG2 << configuration.toString() << endl;

                    {
                        Lock ll(m_configurationMutex);
                        m_configuration = kvc;
                    }

                } catch (...) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(DMCPClientConfigurationException,
                                                  "Received configuration is invalid");
                }

                m_configured = true;
                m_configurationRequestCondition.wakeAll();
            }

            void Client::waitForConfiguration() {
                Lock l(m_configurationRequestCondition);
                if ( !isConfigured() ) {
                    m_configurationRequestCondition.waitOnSignalWithTimeout(coredata::dmcp::Constants::CONFIGURATION_TIMEOUT);
                }

                if ( !isConfigured() ) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(DMCPClientConfigurationException,
                                                  "Timeout while waiting for Configuration");
                }
            }

            bool Client::isConfigured() {
                Lock l(m_configuredMutex);
                return m_configured;
            }

            bool Client::isConnected() {
                return m_connection.isConnected();
            }

        }
    }
}
