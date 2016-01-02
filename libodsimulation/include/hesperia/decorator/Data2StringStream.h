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

#ifndef HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_
#define HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_

#include <sstream>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/data/Container.h"

#include "hesperia/data/environment/EgoState.h"
#include "hesperia/data/planning/Route.h"

namespace hesperia {
    namespace decorator {

        using namespace std;

        /**
         * This class is renders data to a stringstream using toString of serializable data.
         */
        class OPENDAVINCI_API Data2StringStream {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                Data2StringStream(const Data2StringStream &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuseScenarioRenderer
                 * of the assignment operator.
                 */
                Data2StringStream& operator=(const Data2StringStream &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param sstr StringStream to render data into.
                 */
                Data2StringStream(stringstream &sstr);

                virtual ~Data2StringStream();

                /**
                 * This method tries to draw an arbitrary container.
                 *
                 * @param c Container to draw.
                 */
                void toStringStream(core::data::Container &c);

                /**
                 * This method draws an EgoState.
                 *
                 * @param es EgoState to be drawn.
                 */
                void toStringStream(const hesperia::data::environment::EgoState &es);

                /**
                 * This method draws the planned Route.
                 *
                 * @param r Planned route to be drawn.
                 */
                void toStringStream(const hesperia::data::planning::Route &r);

            private:
                stringstream &m_sstr;
        };

    }
} // hesperia::decorator

#endif /*HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_*/
