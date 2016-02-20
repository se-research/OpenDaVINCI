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

#include "opendavinci/context/base/SuperComponent.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/data/Container.h"
#include "opendavinci/core/dmcp/connection/ModuleConnection.h"
#include "opendavinci/core/dmcp/connection/Server.h"
#include "opendavinci/core/dmcp/discoverer/Server.h"
#include "opendavinci/core/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/generated/coredata/dmcp/Constants.h"
#include "opendavinci/generated/coredata/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/coredata/dmcp/ServerInformation.h"

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::io;
        using namespace core::io::conference;
        using namespace core::dmcp;
        using namespace coredata::dmcp;

        SuperComponent::SuperComponent(const string &multicastGroup, const uint32_t &CID, const KeyValueConfiguration &configuration) :
            m_configurationMutex(),
            m_configuration(configuration),
            m_discovererServer(NULL),
            m_connectionServer(NULL),
            m_conference(NULL),
            m_listOfModuleConnections() {
            // Run locally.
            ServerInformation serverInformation("127.0.0.1", coredata::dmcp::Constants::CONNECTIONSERVER_PORT_BASE + CID, ServerInformation::ML_NONE);

            clog << "(context::base::SuperComponent) Server information: " << serverInformation.toString() << endl;
            clog << "(context::base::SuperComponent) Creating discoverer server..." << endl;
            vector<string> noModulesToIgnore;
            m_discovererServer = auto_ptr<core::dmcp::discoverer::Server>(new discoverer::Server(serverInformation, multicastGroup, coredata::dmcp::Constants::BROADCAST_PORT_SERVER, coredata::dmcp::Constants::BROADCAST_PORT_CLIENT, noModulesToIgnore));
            m_discovererServer->startResponding();

            clog << "(context::base::SuperComponent) Creating connection server..." << endl;
            m_connectionServer = auto_ptr<core::dmcp::connection::Server>(new connection::Server(serverInformation, *this));
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

        KeyValueConfiguration SuperComponent::getConfiguration(const coredata::dmcp::ModuleDescriptor& md) {
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

        void SuperComponent::onNewModule(SharedPointer<core::dmcp::connection::ModuleConnection> mc) {
            if (mc.isValid()) {
                clog << "(context::base::SuperComponent) Got new connection from " << mc->getModuleDescriptor().toString() << endl;

                m_listOfModuleConnections.push_back(mc);
            }
        }

        void SuperComponent::handleChangeState(const coredata::dmcp::ModuleDescriptor& md, const coredata::dmcp::ModuleStateMessage::ModuleState &ms) {
            switch (ms) {
                case coredata::dmcp::ModuleStateMessage::NOT_RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to NOT_RUNNING." << endl;
                break;

                case coredata::dmcp::ModuleStateMessage::RUNNING:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to RUNNING." << endl;
                break;

                case coredata::dmcp::ModuleStateMessage::UNDEFINED_STATE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;

                default:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;
            }
        }

        void SuperComponent::handleExitCode(const coredata::dmcp::ModuleDescriptor& md, const coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode &me) {
            switch (me) {
                case coredata::dmcp::ModuleExitCodeMessage::OKAY:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode OKAY." << endl;
                break;

                case coredata::dmcp::ModuleExitCodeMessage::EXCEPTION_CAUGHT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode EXCEPTION_CAUGHT." << endl;
                break;

                case coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode SERIOUS_ERROR." << endl;
                break;

                case coredata::dmcp::ModuleExitCodeMessage::CONNECTION_LOST:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode CONNECTION_LOST." << endl;
                break;

                case coredata::dmcp::ModuleExitCodeMessage::NO_SUPERCOMPONENT:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode NO_SUPERCOMPONENT." << endl;
                break;

                case coredata::dmcp::ModuleExitCodeMessage::UNDEFINED_EXITCODE:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " exited with exitcode UNDEFINED_EXITCODE." << endl;
                break;

                default:
                    clog << "(context::base::SuperComponent) Module " << md.toString() << " changed state to UNDEFINED_STATE." << endl;
                break;
            }
        }

        void SuperComponent::handleRuntimeStatistics(const coredata::dmcp::ModuleDescriptor& md,  const coredata::dmcp::RuntimeStatistic& rs) {
            clog << "(context::base::SuperComponent) Received RuntimeStatistics for " << md.toString() << ": " << rs.toString() << endl;
        }

        void SuperComponent::handleConnectionLost(const coredata::dmcp::ModuleDescriptor& md) {
            clog << "(context::base::SuperComponent) Lost connection to " << md.toString() << endl;
        }

        void SuperComponent::handleUnkownContainer(const coredata::dmcp::ModuleDescriptor& md, const core::data::Container& container) {
            clog << "(context::base::SuperComponent) Received unknown container " << container.toString() << "from " << md.toString() << endl;
        }

    }
} // odcontext::base
