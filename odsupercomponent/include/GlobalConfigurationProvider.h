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

#ifndef SUPERCOMPONENT_GLOBALCONFIGURATIONPROVIDER_H_
#define SUPERCOMPONENT_GLOBALCONFIGURATIONPROVIDER_H_

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"

namespace odcore { namespace data { namespace dmcp { class ModuleDescriptor; } } }

namespace odsupercomponent {

    using namespace std;

    class GlobalConfigurationProvider : public odcore::dmcp::ModuleConfigurationProvider {
        public:
            GlobalConfigurationProvider();
            GlobalConfigurationProvider(const odcore::base::KeyValueConfiguration& configurations);
            GlobalConfigurationProvider(const GlobalConfigurationProvider& configurationProvider);
            GlobalConfigurationProvider& operator=(const GlobalConfigurationProvider& configurationProvider);

            virtual ~GlobalConfigurationProvider();

            virtual odcore::base::KeyValueConfiguration getConfiguration(const odcore::data::dmcp::ModuleDescriptor& md);
            virtual odcore::base::KeyValueConfiguration getGlobalConfiguration() const;

        protected:
            odcore::base::KeyValueConfiguration m_configuration;
            odcore::base::Mutex m_configurationMutex;
    };
}

#endif /*SUPERCOMPONENT_GLOBALCONFIGURATIONPROVIDER_H_*/
