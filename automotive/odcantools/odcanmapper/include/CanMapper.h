/**
 * odcanmapper - Tool for mapping GenericCANMessages to
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

#ifndef CANMAPPER_H_
#define CANMAPPER_H_

#include <core/base/module/DataTriggeredConferenceClientModule.h>
#include <stdint.h>

#include "GeneratedHeaders_CANMessageMapping.h"

namespace core { namespace data { class Container; } }

namespace automotive {
    namespace odcantools {

        using namespace std;

        /**
         * This class can be used to map GenericCANMessages to high-level C++ messages.
         */
        class CanMapper : public core::base::module::DataTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                CanMapper(const CanMapper &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                CanMapper& operator=(const CanMapper &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                CanMapper(const int32_t &argc, char **argv);

                virtual ~CanMapper();

                virtual void nextContainer(core::data::Container &c);

            private:
                virtual void setUp();

                virtual void tearDown();

                /**
                 * This method prints the payload of the low-level CAN message
                 * to STDOUT for debug purposes.
                 *
                 * @param data to be printed.
                 */
                void printPayload(uint64_t payload) const;

            private:
                canmapping::CanMapping m_canMapping;
        };

    } // odcantools
} // automotive

#endif /*CANMAPPER_H_*/
