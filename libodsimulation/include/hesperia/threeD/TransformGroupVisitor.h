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

#ifndef HESPERIA_CORE_THREED_TRANSFORMGROUPVISITOR_H_
#define HESPERIA_CORE_THREED_TRANSFORMGROUPVISITOR_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

namespace hesperia {
    namespace threeD {

class Node;

        /**
         * This interface can be implemented to traverse  a NodeTree built by TransformGroups.
         */
        class OPENDAVINCI_API TransformGroupVisitor {
            public:
                virtual ~TransformGroupVisitor();

                virtual void visit(Node *nd) = 0;
        };

    }
} // hesperia::threeD

#endif /*HESPERIA_CORE_THREED_TRANSFORMGROUPVISITOR_H_*/
