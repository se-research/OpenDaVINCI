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

#ifndef SUPERCOMPONENT_H_
#define SUPERCOMPONENT_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "ConnectedModules.h"
#include "GlobalConfigurationProvider.h"
#include <memory>
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/base/module/MasterModule.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/dmcp/ModuleStateListener.h"
#include "opendavinci/odcore/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/generated/odcore/data/LogMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStateMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcore { namespace data { namespace dmcp { class ModuleDescriptor; } } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace dmcp { namespace connection { class ModuleConnection; } } }
namespace odcore { namespace dmcp { namespace connection { class Server; } } }
namespace odcore { namespace dmcp { namespace discoverer { class Server; } } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace odsupercomponent {

class ConnectedModule;

    using namespace std;

    class SuperComponent : public odcore::base::module::MasterModule,
                           protected odcore::dmcp::connection::ConnectionHandler,
                           protected odcore::dmcp::ModuleStateListener,
                           protected odcore::io::conference::ContainerListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            SuperComponent(const SuperComponent &);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            SuperComponent& operator=(const SuperComponent &);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            SuperComponent(const int &argc, char **argv);

            virtual ~SuperComponent();

            /**
             * @return Start time of the current execution cycle.
             */
            const odcore::data::TimeStamp getStartOfCurrentCycle() const;

            /**
             * @return End time of the last execution cycle.
             */
            const odcore::data::TimeStamp getStartOfLastCycle() const;

        protected:
            void checkForSuperComponent();

            virtual odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            virtual void onNewModule(std::shared_ptr<odcore::dmcp::connection::ModuleConnection> mc);

            virtual void nextContainer(odcore::data::Container &c);

            virtual void handleChangeState(const odcore::data::dmcp::ModuleDescriptor& md,
                                           const odcore::data::dmcp::ModuleStateMessage::ModuleState &ms);

            virtual void handleExitCode(const odcore::data::dmcp::ModuleDescriptor& md,
                                        const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me);

            virtual void handleRuntimeStatistics(const odcore::data::dmcp::ModuleDescriptor& md,
                                                 const odcore::data::dmcp::RuntimeStatistic& rs);

            virtual void handleConnectionLost(const odcore::data::dmcp::ModuleDescriptor& md);

            virtual void handleUnkownContainer(const odcore::data::dmcp::ModuleDescriptor& md,
                                               const odcore::data::Container& container);

            ConnectedModule* moveToShutdownModules(const odcore::data::dmcp::ModuleDescriptor& md);

            odcore::base::KeyValueConfiguration m_configuration;

            GlobalConfigurationProvider m_configurationProvider;
            odcore::dmcp::discoverer::Server* m_discovererServer;
            odcore::dmcp::connection::Server* m_connectionServer;

            std::shared_ptr<odcore::io::conference::ContainerConference> m_conference;

            ConnectedModules m_modules;
            ConnectedModules m_shutdownModules;

            odcore::base::Mutex m_moduleStatisticsMapMutex;
            map<string, odcore::data::dmcp::ModuleStatistic> m_moduleStatisticsMap;

            odcore::data::dmcp::ServerInformation::ManagedLevel m_managedLevel;

        private:
            /**
             * This method will check for an additional command line parameter
             * --configuration=... to specify which configuration file to use
             * for the current session.
             *
             * If this parameter is omitted, a configuration file in the current
             * working directory is returned.
             *
             * @param argc argc from command line
             * @param argv argv from command line
             * @return configuration file to be used
             */
            const string checkForCommandLinePassedConfigurationFileOrDefaultConfigurationFile(const int &argc, char **argv);

            void parseAdditionalCommandLineParameters(const int &argc, char **argv);

            odcore::data::TimeStamp m_startOfCurrentCycle;
            odcore::data::TimeStamp m_startOfLastCycle;
            odcore::data::TimeStamp m_lastCycle;
            uint64_t m_lastWaitTime;
            uint32_t m_shiftMicroseconds;
            uint32_t m_timeoutACKMilliseconds;
            uint32_t m_yieldMicroseconds;

            vector<string> m_modulesToIgnore;
            odcore::data::LogMessage::LogLevel m_logLevel;
            fstream *m_logFile;
    };
}

#endif /*SUPERCOMPONENT_H_*/
