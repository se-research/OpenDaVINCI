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

#ifndef CONTEXT_BASE_SYSTEMCONTEXTCOMPONENT_H_
#define CONTEXT_BASE_SYSTEMCONTEXTCOMPONENT_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/FIFOQueue.h"
#include "opendavinci/odcore/base/KeyValueDataStore.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcontext/base/Runner.h"

namespace odcore { namespace data { class Container; } }

namespace odcontext {
    namespace base {

        using namespace std;

        /**
         * This class can be used to compute data for system's parts
         * which can be either feedback or reporting components.
         */
        class OPENDAVINCI_API SystemContextComponent : public Runner, public odcore::io::conference::ContainerListener {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SystemContextComponent(const SystemContextComponent&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SystemContextComponent& operator=(const SystemContextComponent&);

            protected:
                /**
                 * Protected constructor to enforce subclasses.
                 */
                SystemContextComponent();

            public:
                virtual ~SystemContextComponent();

                /**
                 * This method is called to setup this component.
                 */
                virtual void setup() = 0;

                /**
                 * This method is called to tear down this component.
                 */
                virtual void tearDown() = 0;

                virtual void nextContainer(odcore::data::Container &c);

                /**
                 * This method returns the FIFO containing received containers.
                 *
                 * @return FIFO containing received containers.
                 */
                odcore::base::FIFOQueue& getFIFO();

                /**
                 * This method returns the key/value-data store.
                 *
                 * @return Key/value-datastore.
                 */
                odcore::base::KeyValueDataStore& getKeyValueDataStore();

            private:
                odcore::base::FIFOQueue m_fifo;
                odcore::SharedPointer<odcore::base::KeyValueDataStore> m_keyValueDataStore;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_SYSTEMCONTEXTCOMPONENT_H_*/
