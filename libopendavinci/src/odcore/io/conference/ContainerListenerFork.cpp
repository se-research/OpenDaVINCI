/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/io/conference/ContainerListenerFork.h"

namespace odcore {
    namespace io {
        namespace conference {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            ContainerListenerFork::ContainerListenerFork() : 
                m_listOfContainerListenersMutex(),
                m_listOfContainerListeners() {}

            ContainerListenerFork::~ContainerListenerFork() {}

            void ContainerListenerFork::addContainerListener(ContainerListener *containerListener) {
                if ( (containerListener != NULL) && (containerListener != this)) {
                    Lock l(m_listOfContainerListenersMutex);
                    m_listOfContainerListeners.push_back(containerListener);
                }
            }

            void ContainerListenerFork::removeContainerListener(ContainerListener *containerListener) {
                if ( (containerListener != NULL) && (containerListener != this)) {
                    Lock l(m_listOfContainerListenersMutex);

                    auto it = m_listOfContainerListeners.begin();
                    while (it != m_listOfContainerListeners.end()) {
                        if (*it == containerListener) {
                            break;
                        }
                        it++;
                    }

                    // Actually remove the container listener.
                    if (it != m_listOfContainerListeners.end()) {
                        m_listOfContainerListeners.erase(it);
                    }
                }
            }

            void ContainerListenerFork::nextContainer(Container &c) {
                Lock l(m_listOfContainerListenersMutex);

                if (m_listOfContainerListeners.size() > 0) {
                    for(auto it : m_listOfContainerListeners) {
                        if (it != NULL) {
                            it->nextContainer(c);
                        }
                    }
                }
            }

        }
    }
} // odcore::io::conference

