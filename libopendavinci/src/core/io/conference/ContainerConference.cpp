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

#include "core/base/Lock.h"
#include "core/io/conference/ContainerConference.h"
#include "core/io/conference/ContainerListener.h"

namespace core { namespace data { class Container; } }

namespace core {
    namespace io {
        namespace conference {

            using namespace std;
            using namespace base;
            using namespace data;

            ContainerConference::ContainerConference() :
                m_containerListenerMutex(),
                m_containerListener(NULL) {}

            ContainerConference::~ContainerConference() {}

            void ContainerConference::setContainerListener(ContainerListener *cl) {
                Lock l(m_containerListenerMutex);
                m_containerListener = cl;
            }

            ContainerListener* ContainerConference::getContainerListener() {
                Lock l(m_containerListenerMutex);
                return m_containerListener;
            }

            bool ContainerConference::hasContainerListener() const {
                bool hasListener = false;
                {
                    Lock l(m_containerListenerMutex);
                    hasListener = (m_containerListener != NULL);
                }
                return hasListener;
            }

            void ContainerConference::receive(Container &c) {
                Lock l(m_containerListenerMutex);
                if (m_containerListener != NULL) {
                    m_containerListener->nextContainer(c);
                }
            }

        }
    }
} // core::io::conference
