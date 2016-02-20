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
#include <sstream>

#include "opendavinci/odcontext/base/SuperComponent.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/dmcp/connection/ModuleConnection.h"
#include "opendavinci/odcore/dmcp/connection/Server.h"
#include "opendavinci/odcore/dmcp/discoverer/Server.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/generated/odcore/data/dmcp/Constants.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::io;
        using namespace odcore::io::conference;
        using namespace odcore::dmcp;
        using namespace odcore::data::dmcp;

        SuperComponent::SuperComponent(const string &multicastGroup, const uint32_t &CID, const KeyValueConfiguration &configuration) :
            m_configurationMutex(),
            m_configuration(configuration),
            m_discovererServer(NULL),
            m_connectionServer(NULL),
            m_conference(NULL),
            m_listOfModuleConnections() {
            // Run locally.
            ServerInformation serverInformation("127.0.0.1", odcore::data::dmcp::Constants::CONNECTIONSERVER_PORT_BASE + CID, ServerInformation::ML_NONE);

            clog << "(context::base::SuperComponent) Server information: " << serverInformation.toString() << endl;
            clog << "(context::base::SuperComponent) Creating discoverer server..." << endl;
            vector<string> noModulesToIgnore;
            m_discovererServer = auto_ptr<odcore::dmcp::discoverer::Server>(new discoverer::Server(serverInformation, multicastGroup, odcore::data::dmcp::Constants::BROADCAST_PORT_SERVER, odcore::data::dmcp::Constants::BROADCAST_PORT_CLIENT, noModulesToIgnore));
            m_discovererServer->startResponding();

            clog << "(context::base::SuperComponent) Creating connection server..." << endl;
            m_connectionServer = auto_ptr<odcore::dmcp::connection::Server>(new connection::Server(serverInformation, *this));
            m_connectionServer->setConnectionHandler(this);

            clog << "(context::base::SuperComponent) Creating ContainerConference..." << endl;
            m_conference = ContainerConferenceFactory::getInstance().getContainerConference(multicastGroup);
        }

        SuperComponent::~SuperComponent() {
            m_listOfModuleConnections.clear();
        }

        ContainerConference& SuperComponent::getContainerConference() {
            return *m_conference;
        }

        KeyValueConfiguration SuperComponent::getConfiguration(const odcore::data::dmcp::ModuleDescriptor& md) {
            Lock l(m_configurationMutex);

             if (md.getName() == "Cockpit") {
                 return m_configuration;
             }

             // Determine subset of configuration for this client.
             KeyValueConfiguration globalConfiguration = m_configuration.getSubsetForSection("global.");

             stringstream module;
             module << md.getName() << ".";
             KeyValueConfiguration privateConfigurationBasedOnModuleName = m_configuration.getSubsetForSection(module.str());

             KeyValueConfiguration privateConfigurationBasedOnModuleIdentifier;
             if (md.getIdentifier() != "") {
                 stringstream moduleIdentifier;
                 moduleIdentifier << md.getName() << ":" << md.getIdentifier() << ".";
                 KeyValueConfiguration privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier;
                 privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier = m_configuration.getSubsetForSection(moduleIdentifier.str());

                 // Remove string ":" + md.getIdentifier().
                 const vector<string> keys = privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier.getListOfKeys();
                 vector<string>::const_iterator it = keys.begin();
                 stringstream moduleIdentifierPart;
                 moduleIdentifierPart << ":" << md.getIdentifier() << ".";
                 stringstream sstrPrivateConfigurationWithoutModuleIdentifier;
                 while (it != keys.end()) {
                     string key = (*it++);

                     stringstream modifiedKey;
                     modifiedKey << key.substr(0, key.find(moduleIdentifierPart.str())) << "." << key.substr(key.find(moduleIdentifierPart.str()) + moduleIdentifierPart.str().length());

                     sstrPrivateConfigurationWithoutModuleIdentifier << modifiedKey.str() << "=" << privateConfigurationBasedOnModuleIdentiferIncludingModuleIdentifier.getValue<string>(key) << endl;
                 }
                 if (sstrPrivateConfigurationWithoutModuleIdentifier.str().length() > 0) {
                     privateConfigurationBasedOnModuleIdentifier.readFrom(sstrPrivateConfigurationWithoutModuleIdentifier);
                 }
             }

             // Prepare configuration.
             stringstream configurationForClient;
             globalConfiguration.writeTo(configurationForClient);
             configurationForClient << endl;

             privateConfigurationBasedOnModuleName.writeTo(configurationForClient);
             configurationForClient << endl;

             privateConfigurationBasedOnModuleIdentifier.writeTo(configurationForClient);
             configurationForClient << endl;

             KeyValueConfiguration clientKeyValueConfiguration;
             clientKeyValueConfiguration.readFrom(configurationForClient);

             // Set up configuration object.
             return clientKeyValueConfiguration;
        }

        KeyValueConfiguration SuperComponent::getGlobalConfiguration() const {
            return m_configuration;
        }

        void SuperComponent::onNewModule(SharedPointer<odcore::dmcp::connection::ModuleConnection> mc) {
            if (mc.isValid()) {
                clog << "(context::base::SuperComponent) Got new connection from " << mc->getModuleDescriptor().toString() << endl;

                m_listOfModuleConnections.push_back(mc);
            }
        }

        void SuperComponent::handleChangeState(const odcore::data::dmcp::ModuleDescriptor& md, const odcore::data::dmcp::ModuleStateMessage::ModuleState &ms) {
            switch (ms) {
                case odcore::data::dmcp::ModuleStateMessage::NOT_RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to NOT_RUNNING." << endl;
                break;

                case odcore::data::dmcp::ModuleStateMessage::RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to RUNNING." << endl;
                break;

                case odcore::data::dmcp::ModuleStateMessage::UNDEFINED_STATE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;

                default:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;
            }
        }

        void SuperComponent::handleExitCode(const odcore::data::dmcp::ModuleDescriptor& md, const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me) {
            switch (me) {
                case odcore::data::dmcp::ModuleExitCodeMessage::OKAY:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode OKAY." << endl;
                break;

                case odcore::data::dmcp::ModuleExitCodeMessage::EXCEPTION_CAUGHT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode EXCEPTION_CAUGHT." << endl;
                break;

                case odcore::data::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode SERIOUS_ERROR." << endl;
                break;

                case odcore::data::dmcp::ModuleExitCodeMessage::CONNECTION_LOST:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode CONNECTION_LOST." << endl;
                break;

                case odcore::data::dmcp::ModuleExitCodeMessage::NO_SUPERCOMPONENT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode NO_SUPERCOMPONENT." << endl;
                break;

                case odcore::data::dmcp::ModuleExitCodeMessage::UNDEFINED_EXITCODE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode UNDEFINED_EXITCODE." << endl;
                break;

                default:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;
            }
        }

        void SuperComponent::handleRuntimeStatistics(const odcore::data::dmcp::ModuleDescriptor& md,  const odcore::data::dmcp::RuntimeStatistic& rs) {
            clog << "(context::base::SuperComponent) Received RuntimeStatistics for " << md.toString() << ": " << rs.toString() << endl;
        }

        void SuperComponent::handleConnectionLost(const odcore::data::dmcp::ModuleDescriptor& md) {
            clog << "(context::base::SuperComponent) Lost connection to " << md.toString() << endl;
        }

        void SuperComponent::handleUnkownContainer(const odcore::data::dmcp::ModuleDescriptor& md, const odcore::data::Container& container) {
            clog << "(context::base::SuperComponent) Received unknown container " << container.toString() << "from " << md.toString() << endl;
        }

    }
} // odcontext::base
