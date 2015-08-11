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
#include "core/io/conference/ContainerConferenceFactory.h"
#include "core/io/conference/UDPMultiCastContainerConference.h"

namespace core {
    namespace io {
        namespace conference {

            using namespace std;
            using namespace base;

            // Initialize singleton instance.
            Mutex ContainerConferenceFactory::m_singletonMutex;
            ContainerConferenceFactory* ContainerConferenceFactory::m_singleton = NULL;

            ContainerConferenceFactory::ContainerConferenceFactory() {}

            ContainerConferenceFactory::~ContainerConferenceFactory() {
                setSingleton(NULL);
            }

            void ContainerConferenceFactory::setSingleton(ContainerConferenceFactory *singleton) {
                ContainerConferenceFactory::m_singleton = singleton;
            }

            ContainerConferenceFactory& ContainerConferenceFactory::getInstance() {
                {
                    Lock l(ContainerConferenceFactory::m_singletonMutex);
                    if (ContainerConferenceFactory::m_singleton == NULL) {
                        ContainerConferenceFactory::setSingleton(new ContainerConferenceFactory());
                    }
                }

                return (*ContainerConferenceFactory::m_singleton);
            }

            core::SharedPointer<ContainerConference> ContainerConferenceFactory::getContainerConference(const string &address, const uint32_t &port) {
                return core::SharedPointer<ContainerConference>(new UDPMultiCastContainerConference(address, port));
            }

        }
    }
} // core::io::conference
