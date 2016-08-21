/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#ifndef OPENDAVINCI_CORE_REFLECTION_HELPER_H_
#define OPENDAVINCI_CORE_REFLECTION_HELPER_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Visitor.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/reflection/Message.h"

namespace odcore {
    namespace reflection {

        /**
         * This class provides the interface to auto-generated code to transform
         * serialized Containers.
         */
        class OPENDAVINCI_API Helper {
            public:
                virtual ~Helper();

                virtual void delegateVistor(odcore::data::Container &c, odcore::base::Visitor &v, bool &successfullyDelegated) = 0;

                virtual odcore::reflection::Message map(odcore::data::Container &c, bool &successfullyMapped) = 0;
        };

    }
} // odcore::reflection

#endif /*OPENDAVINCI_CORE_REFLECTION_HELPER_H_*/
