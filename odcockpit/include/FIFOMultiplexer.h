/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifndef FIFOMULTIPLEXER_H_
#define FIFOMULTIPLEXER_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <vector>

#include "core/base/FIFOQueue.h"
#include "core/base/Mutex.h"
#include "core/base/Service.h"
#include "core/data/Container.h"
#include "core/base/DataStoreManager.h"

#include "ContainerObserver.h"

namespace cockpit {

    using namespace std;

    /**
     * This class implements a simple FIFO for multiplexing incoming containers.
     */
    class FIFOMultiplexer : public core::base::Service, public ContainerObserver {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            FIFOMultiplexer(const FIFOMultiplexer &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            FIFOMultiplexer& operator=(const FIFOMultiplexer &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param dsm DataStoreManager to be used for registering own FIFO.
             */
            FIFOMultiplexer(core::base::DataStoreManager &dsm);

            virtual ~FIFOMultiplexer();

            virtual void addContainerListener(core::io::conference::ContainerListener *containerListener);

            virtual void removeContainerListener(core::io::conference::ContainerListener *containerListener);

        protected:
            virtual void distributeContainer(core::data::Container &c);
            virtual core::data::Container leaveContainer();
            virtual uint32_t getFIFOSize();
            virtual void waitForData();

        private:
            core::base::DataStoreManager &m_dataStoreManager;
            mutable core::base::Mutex m_fifoMutex;
            vector<core::io::conference::ContainerListener*> m_listOfContainerListeners;
            core::base::FIFOQueue m_fifo;

            virtual void beforeStop();

            virtual void run();
    };

} // cockpit

#endif /*FIFOMULTIPLEXER_H_*/

