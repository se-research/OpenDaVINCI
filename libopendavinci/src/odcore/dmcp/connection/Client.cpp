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

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/dmcp/SuperComponentStateListener.h"
#include "opendavinci/odcore/dmcp/connection/Client.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/odcore/data/Configuration.h"
#include "opendavinci/generated/odcore/data/dmcp/Constants.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseAckContainersMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseAckMessage.h"

namespace odcore {
    namespace dmcp {
        namespace connection {
            using namespace std;

            using namespace odcore::base;
            using namespace odcore::exceptions;
            using namespace odcore::io;
            using namespace odcore::data;
            using namespace odcore::dmcp;
            using namespace odcore::data::dmcp;

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

            void Client::sendModuleExitCode(const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode& exitCode) {
                ModuleExitCodeMessage m(exitCode);
                Container container(m);
                m_connection.send(container);
            }

            void Client::sendModuleState(const odcore::data::dmcp::ModuleStateMessage::ModuleState& state) {
                ModuleStateMessage m(state);
                Container container(m);
                m_connection.send(container);
            }

            void Client::sendStatistics(const odcore::data::dmcp::RuntimeStatistic& rs) {
                Container container(rs);
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

                Container container(m_moduleDescriptor, Container::DMCP_CONFIGURATION_REQUEST);
                m_connection.send(container);
            }

            void Client::sendPulseAck() {
                PulseAckMessage p;
                Container container(p);
                m_connection.send(container);
            }

            void Client::sendPulseAckContainers(const vector<odcore::data::Container> &listOfContainers) {
                PulseAckContainersMessage pac;
                pac.setListOfContainers(listOfContainers);
                Container container(pac);
                m_connection.send(container);
            }

            void Client::nextContainer(Container &c) {
                if (c.getDataType() == odcore::data::Configuration::ID()) {
                    odcore::data::Configuration configuration = c.getData<odcore::data::Configuration>();
                    handleConfiguration(configuration);
                }

                if (c.getDataType() == PulseMessage::ID()) {
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

            const odcore::data::dmcp::PulseMessage Client::getPulseMessage() {
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

            void Client::handleConfiguration(odcore::data::Configuration& configuration) {
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
                    m_configurationRequestCondition.waitOnSignalWithTimeout(odcore::data::dmcp::Constants::CONFIGURATION_TIMEOUT);
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
