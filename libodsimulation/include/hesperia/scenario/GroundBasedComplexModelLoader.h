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

#ifndef HESPERIA_SCENARIO_GROUNDBASEDCOMPLEXMODELLOADER_H_
#define HESPERIA_SCENARIO_GROUNDBASEDCOMPLEXMODELLOADER_H_

#include "core/opendavinci.h"

#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/threeD/TransformGroup.h"

namespace hesperia {
    namespace scenario {

        using namespace std;

        /**
         * This class traverses the list of ground based complex
         * models and returns a renderable tranformation group.
         */
        class OPENDAVINCI_API GroundBasedComplexModelLoader {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                GroundBasedComplexModelLoader(const GroundBasedComplexModelLoader &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                GroundBasedComplexModelLoader& operator=(const GroundBasedComplexModelLoader &);

            public:
                GroundBasedComplexModelLoader();

                virtual ~GroundBasedComplexModelLoader();

                threeD::TransformGroup* getGroundBasedComplexModels(const scenario::SCNXArchive &scnxArchive) const;
        };

    }
} // hesperia::scenario

#endif /*HESPERIA_SCENARIO_GROUNDBASEDCOMPLEXMODELLOADER_H_*/
