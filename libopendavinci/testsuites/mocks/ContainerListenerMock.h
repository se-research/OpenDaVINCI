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

#ifndef MOCKS__CONTAINERLISTENERMOCK_H
#define MOCKS__CONTAINERLISTENERMOCK_H

#include "FunctionCallWaiter.h"
#include "ParameterValueList.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerListener.h"

namespace mocks {

    class ContainerListenerMock : public core::io::conference::ContainerListener {
        public:
            ContainerListenerMock() :
                VALUES_nextContainer(),
                CALLWAITER_nextContainer(),
                currentValue()
            {};

            virtual void nextContainer(core::data::Container &c) {
                currentValue = c;
                CALLWAITER_nextContainer.called();
            }

            ParameterValueList< core::data::Container > VALUES_nextContainer;
            FunctionCallWaiter CALLWAITER_nextContainer;
            core::data::Container currentValue;
    };
}
#endif // MOCKS__CONTAINERLISTENERMOCK_H
