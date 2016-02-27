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

#ifndef CONTEXT_BASE_SUPERCOMPONENT_H_
#define CONTEXT_BASE_SUPERCOMPONENT_H_

#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/dmcp/ModuleConfigurationProvider.h"
#include "opendavinci/odcore/dmcp/ModuleStateListener.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"

namespace odcore { namespace data { namespace dmcp { class ModuleDescriptor; } } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace dmcp { namespace connection { class ModuleConnection; } } }
namespace odcore { namespace dmcp { namespace connection { class Server; } } }
namespace odcore { namespace dmcp { namespace discoverer { class Server; } } }

namespace odcontext {
    namespace base {

        using namespace std;

        /**
         * This class provides supercomponent functionality.
         */
        class OPENDAVINCI_API SuperComponent : protected odcore::dmcp::connection::ConnectionHandler,
                                               protected odcore::dmcp::ModuleStateListener,
                                               public odcore::dmcp::ModuleConfigurationProvider {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SuperComponent(const SuperComponent&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SuperComponent& operator=(const SuperComponent&);

            public:
                /**
                 * Constructor for constructing a supercomponent using REAL UDP/TCP
                 * for the given CID and the given configuration.
                 *
                 * @param multicastGroup Multicast group to create supercomponent for.
                 * @param cid CID for the supercomponent.
                 * @param configuration Global configuration.
                 */
                SuperComponent(const string &multicastGroup, const uint32_t &CID, const odcore::base::KeyValueConfiguration &configuration);

                virtual ~SuperComponent();

                /**
                 * This method returns the real UDPMulticastClientConference.
                 *
                 * @return UDPMulticastClientConference.
                 */
                odcore::io::conference::ContainerConference& getContainerConference();

            protected:
                virtual odcore::base::KeyValueConfiguration getConfiguration(const odcore::data::dmcp::ModuleDescriptor& md);

                virtual odcore::base::KeyValueConfiguration getGlobalConfiguration() const;

                virtual void onNewModule(odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> mc);

                virtual void handleChangeState(const odcore::data::dmcp::ModuleDescriptor& md,
                                               const odcore::data::dmcp::ModuleStateMessage::ModuleState &ms);

                virtual void handleExitCode(const odcore::data::dmcp::ModuleDescriptor& md,
                                            const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me);

                virtual void handleRuntimeStatistics(const odcore::data::dmcp::ModuleDescriptor& md,
                                                     const odcore::data::dmcp::RuntimeStatistic& rs);

                virtual void handleConnectionLost(const odcore::data::dmcp::ModuleDescriptor& md);

                virtual void handleUnkownContainer(const odcore::data::dmcp::ModuleDescriptor& md,
                                                   const odcore::data::Container& container);

            private:
                odcore::base::Mutex m_configurationMutex;
                odcore::base::KeyValueConfiguration m_configuration;

                unique_ptr<odcore::dmcp::discoverer::Server> m_discovererServer;
                unique_ptr<odcore::dmcp::connection::Server> m_connectionServer;

                odcore::SharedPointer<odcore::io::conference::ContainerConference> m_conference;

                vector<odcore::SharedPointer<odcore::dmcp::connection::ModuleConnection> > m_listOfModuleConnections;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_SUPERCOMPONENT_H_*/
