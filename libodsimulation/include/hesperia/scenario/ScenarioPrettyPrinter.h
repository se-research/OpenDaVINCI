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

#ifndef HESPERIA_SCENARIO_SCENARIOPRETTYPRINTER_H_
#define HESPERIA_SCENARIO_SCENARIOPRETTYPRINTER_H_

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/data/SerializableData.h"

#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace scenario {

        using namespace std;

        /**
         * This class pretty prints the Scenario data structure.
         */
        class OPENDAVINCI_API ScenarioPrettyPrinter : public data::scenario::ScenarioVisitor {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ScenarioPrettyPrinter(const ScenarioPrettyPrinter &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ScenarioPrettyPrinter& operator=(const ScenarioPrettyPrinter &);

            public:
                ScenarioPrettyPrinter();

                virtual ~ScenarioPrettyPrinter();

                virtual void visit(data::scenario::ScenarioNode &node);
        };

    }
} // hesperia::scenario

#endif /*HESPERIA_SCENARIO_SCENARIOPRETTYPRINTER_H_*/
