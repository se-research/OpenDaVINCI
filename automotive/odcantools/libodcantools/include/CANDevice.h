/**
 * libodcantools - Library to wrap a CAN interface.
 * Copyright (C) 2017 Christian Berger
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

#ifndef CANDEVICE_H_
#define CANDEVICE_H_

#include <opendavinci/odcore/base/Service.h>

namespace automotive { class GenericCANMessage; }

namespace automotive {
    namespace odcantools {

        using namespace std;

        /**
         * This interface encapsulates the methods to be implemented by deriving
         * implementations for handling CAN devices.
         */
        class CANDevice : public odcore::base::Service {
            public:
                virtual ~CANDevice();

                /**
                 * This method returns true if the device was successfully initialized.
                 *
                 * @return true if the device could be successfully openend.
                 */
                virtual bool isOpen() const = 0;

                /**
                 * This methods writes a GenericCANMessage to the device.
                 *
                 * @param gcm GenericCANMessage to be written.
                 * @return error code from the low level sytem call.
                 */
                virtual int write(const GenericCANMessage &gcm) = 0;
        };

    } // odcantools
} // automotive

#endif /*CANDEVICE_H_*/
