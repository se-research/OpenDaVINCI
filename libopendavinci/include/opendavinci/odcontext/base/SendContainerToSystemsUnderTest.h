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

#ifndef CONTEXT_BASE_SENDCONTAINERTOSYSTEMSUNDERTEST_H_
#define CONTEXT_BASE_SENDCONTAINERTOSYSTEMSUNDERTEST_H_

#include "opendavinci/odcore/opendavinci.h"

namespace odcore { namespace data { class Container; } }

namespace odcontext {
    namespace base {

        /**
         * This interface provides methods to send data to a
         * ControlledContainerConferenceForSystemsUnderTest.
         */
        class OPENDAVINCI_API SendContainerToSystemsUnderTest {
            public:
                virtual ~SendContainerToSystemsUnderTest();

                /**
                 * This method sends a Container to all created
                 * ControlledContainerConferences and thus to all
                 * running systems under test.
                 *
                 * @param c Container to send.
                 */
                virtual void sendToSystemsUnderTest(odcore::data::Container &c) = 0;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_SENDCONTAINERTOSYSTEMSUNDERTEST_H_*/
