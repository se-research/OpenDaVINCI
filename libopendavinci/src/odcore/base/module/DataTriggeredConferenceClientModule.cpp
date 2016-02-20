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

#include "opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h"
#include "opendavinci/generated/coredata/dmcp/ModuleStateMessage.h"

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;

            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::exceptions;

            DataTriggeredConferenceClientModule::DataTriggeredConferenceClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException) :
                    AbstractConferenceClientModule(argc, argv, name) {}

            DataTriggeredConferenceClientModule::~DataTriggeredConferenceClientModule() {}

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode DataTriggeredConferenceClientModule::body() {
                while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                    // Do nothing.
                    //
                    // This empty implementation is required to ensure proper scheduling.
                }

                return coredata::dmcp::ModuleExitCodeMessage::OKAY;
            }

        }
    }
} // odcore::base
