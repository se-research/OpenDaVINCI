/**
 * canproxy - Tool wrapping a CAN interface.
 * Copyright (C) 2015 Christian Berger
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

#include <iostream>

#include "core/data/Container.h"

#include "CanProxy.h"

namespace automotive {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    CanProxy::CanProxy(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "canproxy"),
        m_fifo() {}

    CanProxy::~CanProxy() {}

    void CanProxy::setUp() {}

    void CanProxy::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode CanProxy::body() {
        // Add FIFOQueue to spy all data.
        addDataStoreFor(m_fifo);

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            cout << "[CanProxy]" << endl;
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // automotive
