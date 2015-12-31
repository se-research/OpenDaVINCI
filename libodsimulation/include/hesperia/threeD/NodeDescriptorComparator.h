/**
 * hesperia - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef HESPERIA_CORE_THREED_NODEDESCRIPTORCOMPARATOR_H_
#define HESPERIA_CORE_THREED_NODEDESCRIPTORCOMPARATOR_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"
#include "hesperia/threeD/NodeDescriptor.h"

namespace hesperia {
    namespace threeD {

        using namespace std;

        /**
         * This class compares NodeDescriptors for sorting.
         */
        class OPENDAVINCI_API NodeDescriptorComparator {
            public:
                NodeDescriptorComparator();

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                NodeDescriptorComparator(const NodeDescriptorComparator &obj);

                virtual ~NodeDescriptorComparator();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                NodeDescriptorComparator& operator=(const NodeDescriptorComparator &obj);

                /**
                 * This method returns nd1.getName().compare(nd2.getName()).
                 *
                 * @return nd1.getName().compare(nd2.getName()) < 0.
                 */
                bool operator()(const NodeDescriptor &nd1, const NodeDescriptor &nd2) const;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_NODEDESCRIPTORCOMPARATOR_H_*/
