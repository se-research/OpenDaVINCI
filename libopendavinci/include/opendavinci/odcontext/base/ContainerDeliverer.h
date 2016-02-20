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

#ifndef CONTEXT_BASE_CONTAINERDELIVERER_H_
#define CONTEXT_BASE_CONTAINERDELIVERER_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/io/conference/ContainerObserver.h"
#include "opendavinci/odcore/wrapper/Disposable.h"

namespace odcore { namespace data { class Container; } }

namespace odcontext {
    namespace base {

        /**
         * This class delivers Containers to ControlledContainerConferenceForSystemUnderTest.
         * Every ControlledContainerConferenceForSystemUnderTest has its own
         * ContainerDeliverer to ensure synchronous delivery.
         */
        class OPENDAVINCI_API ContainerDeliverer : public odcore::io::conference::ContainerObserver, public odcore::io::conference::ContainerListener, public odcore::wrapper::Disposable {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ContainerDeliverer(const ContainerDeliverer&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ContainerDeliverer& operator=(const ContainerDeliverer&);

            public:
                ContainerDeliverer();

                virtual ~ContainerDeliverer();

                virtual void setContainerListener(odcore::io::conference::ContainerListener *cl);

                // This method is called by ControlledContainerConferenceFactory to send c to the registered ContainerListener from an app.
                virtual void nextContainer(odcore::data::Container &c);

            private:
                odcore::base::Mutex m_containerListenerMutex;
                odcore::io::conference::ContainerListener *m_containerListener;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_CONTAINERDELIVERER_H_*/
