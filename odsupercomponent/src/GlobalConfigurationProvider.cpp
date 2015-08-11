/**
 * odsupercomponent - Configuration and monitoring component for
 *                    distributed software systems
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <vector>

#include "GlobalConfigurationProvider.h"

#include "core/base/Lock.h"

namespace odsupercomponent {

    using namespace core::base;
    using namespace coredata::dmcp;

    GlobalConfigurationProvider::GlobalConfigurationProvider(const KeyValueConfiguration& configurations) :
        m_configuration(configurations),
        m_configurationMutex()
    {}

    GlobalConfigurationProvider::GlobalConfigurationProvider() :
        m_configuration(),
        m_configurationMutex()
    {}

    GlobalConfigurationProvider::GlobalConfigurationProvider(const GlobalConfigurationProvider& configurationProvider) :
	    core::dmcp::ModuleConfigurationProvider(),
        m_configuration(configurationProvider.getGlobalConfiguration()),
        m_configurationMutex()
    {}

    GlobalConfigurationProvider& GlobalConfigurationProvider::operator=(const GlobalConfigurationProvider& configurationProvider) {
        m_configuration = KeyValueConfiguration(configurationProvider.getGlobalConfiguration());
        return *this;
    }

    GlobalConfigurationProvider::~GlobalConfigurationProvider() {}

    KeyValueConfiguration GlobalConfigurationProvider::getConfiguration(const ModuleDescriptor& md) {
        Lock l(m_configurationMutex);

        if ( (md.getName() == "Monitor") || (md.getName() == "Cockpit") ) {
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

    KeyValueConfiguration GlobalConfigurationProvider::getGlobalConfiguration() const {
        return m_configuration;
    }
}
