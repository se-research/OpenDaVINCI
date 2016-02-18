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

#ifndef HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_
#define HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_

#include <sstream>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/Container.h"

#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/planning/Route.h"

namespace opendlv {
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
                void toStringStream(const opendlv::data::environment::EgoState &es);

                /**
                 * This method draws the planned Route.
                 *
                 * @param r Planned route to be drawn.
                 */
                void toStringStream(const opendlv::data::planning::Route &r);

            private:
                stringstream &m_sstr;
        };

    }
} // opendlv::decorator

#endif /*HESPERIA_CORE_DECORATOR_DATA2STRINGSTREAM_H_*/
