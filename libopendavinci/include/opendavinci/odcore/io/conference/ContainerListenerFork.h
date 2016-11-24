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

#ifndef CONTAINERLISTENERFORK_H_
#define CONTAINERLISTENERFORK_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"

namespace odcore {
    namespace io {
        namespace conference {

            using namespace std;

            /**
             * This class forks as ContainerListener incoming Containers to multiple registered ContainerListeners.
             */
            class OPENDAVINCI_API ContainerListenerFork : public ContainerListener {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ContainerListenerFork(const ContainerListenerFork &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ContainerListenerFork& operator=(const ContainerListenerFork &/*obj*/);

                public:
                    /**
                     * Constructor.
                     */
                    ContainerListenerFork();

                    virtual ~ContainerListenerFork();

                    virtual void addContainerListener(odcore::io::conference::ContainerListener *containerListener);

                    virtual void removeContainerListener(odcore::io::conference::ContainerListener *containerListener);

                    virtual void nextContainer(odcore::data::Container &c);

                private:
                    odcore::base::Mutex m_listOfContainerListenersMutex;
                    vector<odcore::io::conference::ContainerListener*> m_listOfContainerListeners;
            };

        }
    }
} // odcore::io::conference

#endif /*CONTAINERLISTENERFORK_H_*/

