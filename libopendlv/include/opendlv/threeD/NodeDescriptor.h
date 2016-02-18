/**
 * OpenDLV - Simulation environment
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

#ifndef HESPERIA_CORE_THREED_NODEDESCRIPTOR_H_
#define HESPERIA_CORE_THREED_NODEDESCRIPTOR_H_

#include <string>

#include "opendavinci/core/opendavinci.h"

namespace opendlv {
    namespace threeD {

        using namespace std;

        /**
         * This class provides a description for the current node.
         */
        class OPENDAVINCI_API NodeDescriptor {
            public:
                NodeDescriptor();

                /**
                 * Constructor.
                 *
                 * @param name Name of this node descriptor.
                 */
                NodeDescriptor(const string &name);

                /**
                 * Copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                NodeDescriptor(const NodeDescriptor &obj);

                virtual ~NodeDescriptor();

                /**
                 * Assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                NodeDescriptor& operator=(const NodeDescriptor &obj);

                /**
                 * This method returns the name of this node.
                 *
                 * @return Name of this node.
                 */
                const string getName() const;

            private:
                string m_name;
        };

    }
} // opendlv::threeD

#endif /*HESPERIA_CORE_THREED_NODEDESCRIPTOR_H_*/
