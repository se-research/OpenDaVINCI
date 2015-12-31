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

#include "context/base/ContainerDeliverer.h"
#include "core/base/Lock.h"

namespace core { namespace data { class Container; } }

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;
        using namespace core::data;
        using namespace core::io;

        ContainerDeliverer::ContainerDeliverer() :
            m_containerListenerMutex(),
            m_containerListener(NULL) {}

        ContainerDeliverer::~ContainerDeliverer() {}

        void ContainerDeliverer::setContainerListener(ContainerListener *cl) {
            Lock l(m_containerListenerMutex);
            m_containerListener = cl;
        }

        void ContainerDeliverer::nextContainer(Container &c) {
            Lock l(m_containerListenerMutex);
            if (m_containerListener != NULL) {
                m_containerListener->nextContainer(c);
            }
        }

    }
} // context::base
