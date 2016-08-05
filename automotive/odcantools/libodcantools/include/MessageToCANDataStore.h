/**
 * libodcantools - Library to wrap a CAN interface.
 * Copyright (C) 2015 Christian Berger
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

#ifndef MESSAGETOCANDATASTORE_H_
#define MESSAGETOCANDATASTORE_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/AbstractDataStore.h"

namespace odcore { namespace data { class Container; } }

namespace automotive {
    namespace odcantools {

        using namespace std;

        // Forward declaration due to circular dependency.
        class CANDevice;

        /**
         * This class is waiting for Containers to be written to a CAN bus.
         */
        class MessageToCANDataStore : public odcore::base::AbstractDataStore {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                MessageToCANDataStore(const MessageToCANDataStore &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                MessageToCANDataStore& operator=(const MessageToCANDataStore &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param canDevice Reference to the CAN device used for sending the data.
                 */
                MessageToCANDataStore(shared_ptr<CANDevice> canDevice);

                virtual ~MessageToCANDataStore();

                /**
                 * The default behavior for the MessageToCANDataStore is
                 * to simply relay all Containers of type GenericCANMessage::ID
                 * directly to the CANDevice.
                 *
                 * This method _can_ be overwritten in subclasses to realize a
                 * different behavior; for instance by selecting high-level
                 * messages and transform them into GenericCANMessages.
                 */
                virtual void add(odcore::data::Container &container);

                virtual void clear();

                virtual uint32_t getSize() const;

                virtual bool isEmpty() const;

            protected:
                shared_ptr<CANDevice> m_canDevice;
        };

    } // odcantools
} // automotive

#endif /*MESSAGETOCANDATASTORE_H_*/
