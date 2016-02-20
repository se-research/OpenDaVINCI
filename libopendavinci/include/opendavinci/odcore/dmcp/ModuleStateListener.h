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

#ifndef OPENDAVINCI_DMCP_MODULESTATELISTENER_H_
#define OPENDAVINCI_DMCP_MODULESTATELISTENER_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/Container.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

namespace odcore {
    namespace dmcp {

        using namespace std;

        class OPENDAVINCI_API ModuleStateListener {
            public:
                virtual ~ModuleStateListener() {};

                virtual void handleChangeState(const odcore::data::dmcp::ModuleDescriptor &md,
                                               const odcore::data::dmcp::ModuleStateMessage::ModuleState &ms) = 0;

                virtual void handleExitCode(const odcore::data::dmcp::ModuleDescriptor &md,
                                            const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me) = 0;

                virtual void handleRuntimeStatistics(const odcore::data::dmcp::ModuleDescriptor &md,
                                                     const odcore::data::dmcp::RuntimeStatistic &rs) = 0;

                virtual void handleConnectionLost(const odcore::data::dmcp::ModuleDescriptor &md) = 0;

                virtual void handleUnkownContainer(const odcore::data::dmcp::ModuleDescriptor &md,
                                                   const odcore::data::Container& container) = 0;
        };
    }
} // odcore::dmcp

#endif /* OPENDAVINCI_DMCP_MODULESTATELISTENER_H_ */
