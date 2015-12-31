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

#ifndef HESPERIA_CORE_DATA_SITUATION_SITUATIONVISITOR_H_
#define HESPERIA_CORE_DATA_SITUATION_SITUATIONVISITOR_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace hesperia {
    namespace data {
        namespace situation {

            /**
             * This interface allows the use of visitors for transforming
             * the situation data structure.
             */
class SituationNode;

            class OPENDAVINCI_API SituationVisitor {
                public:
                    virtual ~SituationVisitor();

                    /**
                     * This method visits a node.
                     *
                     * @param node Node to be visited.
                     */
                    virtual void visit(SituationNode &node) = 0;
            };

        }
    }
} // hesperia::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_SITUATIONVISITOR_H_*/
