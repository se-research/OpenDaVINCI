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

#ifndef OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_
#define OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/Connection.h"
#include "opendavinci/odcore/io/ConnectionErrorListener.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/PulseMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcore { namespace data { class Configuration; } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace dmcp { class SupercomponentStateListener; } }

namespace odcore {
    namespace dmcp {
        namespace connection {

            using namespace std;

            class OPENDAVINCI_API Client : protected odcore::io::conference::ContainerListener,
                                           protected odcore::io::ConnectionErrorListener
            {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    Client(const Client &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    Client& operator=(const Client &);

                public:
                    Client(const odcore::data::dmcp::ModuleDescriptor &moduleDescriptor,
                           const odcore::data::dmcp::ServerInformation &serverInformation);

                    virtual ~Client();

                    void initialize();

                    void sendModuleExitCode(const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me);
                    void sendModuleState(const odcore::data::dmcp::ModuleStateMessage::ModuleState &me);
                    void sendStatistics(const odcore::data::dmcp::RuntimeStatistic &rs);

                    odcore::base::KeyValueConfiguration getConfiguration();

                    const odcore::data::dmcp::PulseMessage getPulseMessage();

                    /**
                     * This method sends the PulseAckMessage to supercomponent.
                     */
                    void sendPulseAck();

                    /**
                     * This method sends the PulseAckMessage to supercomponent
                     * including all containers to be sent from this component.
                     *
                     * @param listOfContainers List of containers to be sent.
                     */
                    void sendPulseAckContainers(const vector<odcore::data::Container> &listOfContainers);

                    void setSupercomponentStateListener(SupercomponentStateListener* listener);

                    bool isConnected();

                protected:
                    void sendConfigurationRequest();
                    virtual void nextContainer(odcore::data::Container &c);
                    virtual void handleConnectionError();

                    void handleConfiguration(odcore::data::Configuration &configuration);
                    void waitForConfiguration();
                    bool isConfigured();

                private:
                    odcore::data::dmcp::ModuleDescriptor m_moduleDescriptor;
                    odcore::data::dmcp::ServerInformation m_serverInformation;

                    odcore::io::Connection m_connection;

                    odcore::base::Mutex m_configurationMutex;
                    odcore::base::KeyValueConfiguration m_configuration;

                    bool m_configured;
                    odcore::base::Mutex m_configuredMutex;
                    odcore::base::Condition m_configurationRequestCondition;

                    odcore::base::Mutex m_listenerMutex;
                    SupercomponentStateListener* m_listener;

                    odcore::base::Condition m_pulseCondition;
                    odcore::base::Mutex m_pulseMessageMutex;
                    odcore::data::dmcp::PulseMessage m_pulseMessage;
            };
        }
    }
} // odcore::dmcp

#endif /*OPENDAVINCI_DMCP_CONNECTION_CLIENT_H_*/
