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

#ifndef CONTEXT_BASE_RUNTIMECONTROLINTERFACE_H_
#define CONTEXT_BASE_RUNTIMECONTROLINTERFACE_H_

#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"

namespace odcontext {
    namespace base {

        using namespace std;

        /**
         * This interface provides information for the RuntimeControl.
         */
        class OPENDAVINCI_API RuntimeControlInterface {
            public:
                virtual ~RuntimeControlInterface();

                /**
                 * This method returns the configuration to be used for the
                 * SystemContext.
                 *
                 * @return KeyValueConfiguration to be used.
                 */
                virtual const core::base::KeyValueConfiguration getConfiguration() const = 0;

                /**
                 * This method returns the multicast group to be used.
                 *
                 * @return Multicast group.
                 */
                virtual const string getMulticastGroup() const = 0;

                /**
                 * This method returns the conference ID (CID).
                 *
                 * @return CID.
                 */
                virtual uint32_t getCID() const = 0;

                /**
                 * This method returns true if the RuntimeControl should
                 * be verbose.
                 *
                 * @return true if the RuntimeControl should be verbose.
                 */
                virtual bool isVerbose() const = 0;

                /**
                 * This method returns true if the RuntimeControl should
                 * provide supercomponent-functionality.
                 *
                 * @return true if the RuntimeControl should provide supercomponent functionality.
                 */
                virtual bool isSupercomponent() const = 0;
        };

    }
} // odcontext::base

#endif /*CONTEXT_BASE_RUNTIMECONTROLINTERFACE_H_*/
