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

#ifndef HESPERIA_CORE_DATA_SCENARIO_SCENARIONODE_H_
#define HESPERIA_CORE_DATA_SCENARIO_SCENARIONODE_H_

#include "opendavinci/core/opendavinci.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            // Forward declaration to prevent circular dependencies.
            class ScenarioVisitor;

            /**
             * This interface allows the use of visitors for transforming
             * the scenario data structure.
             */
            class OPENDAVINCI_API ScenarioNode {
                public:
                    virtual ~ScenarioNode();

                    /**
                     * This method accepts a visitor for traversing the scenario
                     * to build graphs or 3D scenes.
                     *
                     * @param visitor Visitor to be accepted.
                     */
                    virtual void accept(ScenarioVisitor &visitor) = 0;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_SCENARIONODE_H_*/
