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

#ifndef CONNECTIONHANDLERMOCK_H_
#define CONNECTIONHANDLERMOCK_H_

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/dmcp/connection/ConnectionHandler.h"
#include "opendavinci/core/dmcp/connection/ModuleConnection.h"
#include "FunctionCallWaiter.h"

namespace mocks {

    class ConnectionHandlerMock : public core::dmcp::connection::ConnectionHandler {
        public:
            ConnectionHandlerMock() :
                connection(NULL),
                WAITER()
            {};

            virtual ~ConnectionHandlerMock() {};

            virtual void onNewModule(core::SharedPointer<core::dmcp::connection::ModuleConnection> mc)
            {
                connection = mc;
                WAITER.called();
            }

            core::SharedPointer<core::dmcp::connection::ModuleConnection> connection;
            FunctionCallWaiter WAITER;
        private:
            ConnectionHandlerMock(const ConnectionHandlerMock &);
            ConnectionHandlerMock& operator=(const ConnectionHandlerMock &);
    };
}
#endif /* CONNECTIONHANDLERMOCK_H_ */
