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

#include <sstream>

#include <memory>
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/base/module/AbstractConferenceClientModule.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/odcore/opendavinci.h"

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;
            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::io;
            using namespace odcore::io::conference;
            using namespace odcore::exceptions;

            AbstractConferenceClientModule::AbstractConferenceClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException) :
                    ManagedClientModule(argc, argv, name) {
                std::shared_ptr<ContainerConference> containerConference = ContainerConferenceFactory::getInstance().getContainerConference(getMultiCastGroup());
                if (!containerConference.get()) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "ContainerConference invalid!");
                }
                setContainerConference(containerConference);

                SerializationFactory::getInstance();
            }

            AbstractConferenceClientModule::~AbstractConferenceClientModule() {
                if (getContainerConference().get()) {
                    getContainerConference()->setContainerListener(NULL);
                }
            }

            ContainerConference& AbstractConferenceClientModule::getConference() {
                return *(getContainerConference());
            }

            void AbstractConferenceClientModule::toLogger(const odcore::data::LogMessage::LogLevel &logLevel, const string &msg) {
                odcore::data::LogMessage logMessage;

                logMessage.setComponentName(getName());

                if (getIdentifier().size() > 0) {
                    stringstream componentName;
                    componentName << getName() << "-" << getIdentifier();
                    logMessage.setComponentName(componentName.str());
                }

                logMessage.setLogMessage(msg);
                logMessage.setLogLevel(logLevel);

                Container c(logMessage);
                getConference().send(c);
            }

        }
    }
} // odcore::base::module
