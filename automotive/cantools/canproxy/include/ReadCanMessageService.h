/**
 * canproxy - Tool wrapping a CAN interface.
 * Copyright (C) 2015 Christian Berger
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

#ifndef READCANMESSAGESERVICE_H_
#define READCANMESSAGESERVICE_H_

#include <libpcan.h>

#include <core/base/Service.h>

#include "GenericCANMessageListener.h"

namespace automotive {

    using namespace std;

    /**
     * This class encapsulates the service for reading low-level CAN message to be
     * wrapped into a GenericCANMessage.
     */
    class ReadCanMessageService : public core::base::Service {
       private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            ReadCanMessageService(const ReadCanMessageService &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            ReadCanMessageService& operator=(const ReadCanMessageService &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param handle Handle referring to a successully opened CAN device.
             * @param listener Listener that will received wrapped GenericCANMessages.
             */
            ReadCanMessageService(HANDLE handle, GenericCANMessageListener &listener);

            virtual ~ReadCanMessageService();

            virtual void beforeStop();

            virtual void run();

        private:
            HANDLE m_handle;
            GenericCANMessageListener &m_listener;
    };

} // automotive

#endif /*READCANMESSAGESERVICE_H_*/
