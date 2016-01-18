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

#ifndef MOCKS__CONNECTIONERRORLISTENERMOCK_H_
#define MOCKS__CONNECTIONERRORLISTENERMOCK_H_

#include "FunctionCallWaiter.h"
#include "opendavinci/core/io/ConnectionErrorListener.h"

namespace mocks {
    using namespace core;

    class ConnectionErrorListenerMock : public core::io::ConnectionErrorListener {
        public:
            ConnectionErrorListenerMock() :
                CALLWAITER_handleConnectionError()
            {}

            virtual void handleConnectionError() {
                CALLWAITER_handleConnectionError.called();
            }

            mocks::FunctionCallWaiter CALLWAITER_handleConnectionError;
    };
}
#endif
