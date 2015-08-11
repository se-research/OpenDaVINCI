/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include "core/base/module/ManagedClientModuleContainerConference.h"
#include "core/data/TimeStamp.h"

namespace core {
    namespace base {
        namespace module {

            using namespace core::data;

            ManagedClientModuleContainerConference::ManagedClientModuleContainerConference() :
                m_listOfContainersToBeDelivered() {}

            ManagedClientModuleContainerConference::~ManagedClientModuleContainerConference() {}

            void ManagedClientModuleContainerConference::send(core::data::Container &container) const {
                // Put container to be sent into our list of data to be distributed.
                container.setSentTimeStamp(TimeStamp());

                // The const cast is required as the method signature is designed to be const...
                const_cast<ManagedClientModuleContainerConference*>(this)->m_listOfContainersToBeDelivered.push_back(container);
            }

            vector<core::data::Container> ManagedClientModuleContainerConference::getListOfContainers() const {
                return m_listOfContainersToBeDelivered;
            }

            void ManagedClientModuleContainerConference::clearListOfContainers() {
                m_listOfContainersToBeDelivered.clear();
            }

            void ManagedClientModuleContainerConference::receiveFromLocal(core::data::Container &c) {
                // Delegate call to super class.
                receive(c);
            }

        }
    }
} // core::base

