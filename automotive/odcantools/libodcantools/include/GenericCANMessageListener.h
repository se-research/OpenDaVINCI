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

#ifndef GENERICCANMESSAGELISTENER_H_
#define GENERICCANMESSAGELISTENER_H_

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

        /**
         * This interface is called whenever a low-level CAN message was received and
         * successfully wrapped into a GenericCANMessage.
         */
        class GenericCANMessageListener {
            public:
                virtual ~GenericCANMessageListener();

                /**
                 * This method is called whenever a low-level CAN message was
                 * successfully transformed into a GenericCANMessage.
                 *
                 * @param gcm GenericCANMessage
                 */
                virtual void nextGenericCANMessage(const GenericCANMessage &gcm) = 0;
        };

    } // odcantools
} // automotive

#endif /*GENERICCANMESSAGELISTENER_H_*/
