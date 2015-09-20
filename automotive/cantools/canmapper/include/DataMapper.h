/**
 * canmapper - Tool for mapping GenericCANMessages to
 *             high-level C++ data structures and vice-versa
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

#ifndef DATAMAPPER_H_
#define DATAMAPPER_H_

#include <core/data/Container.h>

#include "GeneratedHeaders_AutomotiveData.h"

namespace automotive {

    using namespace std;

    /**
     * This class can be used to map GenericCANMessages to high-level C++ messages.
     */
    class DataMapper {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            DataMapper(const DataMapper &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            DataMapper& operator=(const DataMapper &/*obj*/);

        public:
            DataMapper();

            virtual ~DataMapper();

            /**
             * This method adds the given GenericCANMessage to the internal
             * CAN message decoder. If this message could be decoded (or
             * including the previous sequence, this method returns a valid
             * Container (ie. Container::UNDEFINEDDATA).
             *
             * @param gcm Next GenericCANMessage.
             * @return Container, where the type needs to be checked to determine invalidity (i.e. !Container::UNDEFINEDDATA).
             */
            core::data::Container mapNext(const GenericCANMessage &gcm);

        private:
            /**
             * This method prints the payload of the low-level CAN message
             * to STDOUT for debug purposes.
             *
             * @param data to be printed.
             */
            void printPayload(uint64_t payload) const;

            // This method is an example to demonstrate the steps that are needed
            // to decode from a GenericCANMessage to a valid Container with a
            // named high-level message as payload.
            core::data::Container decodeWheelSpeed(const GenericCANMessage &gcm);
    };

} // automotive

#endif /*DATAMAPPER_H_*/
