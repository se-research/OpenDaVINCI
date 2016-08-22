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

#ifndef HESPERIA_EGOSTATETESTSUITE_H_
#define HESPERIA_EGOSTATETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <sstream>

#include "opendavinci/odcore/data/Container.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/EgoState.h"

using namespace std;
using namespace odcore::data;
using namespace opendlv::data;
using namespace opendlv::data::environment;
using namespace opendlv::data::environment;

class EgoStateTest : public CxxTest::TestSuite {
    public:
        void testEgoState() {
            Point3 position(1, 2, 3);
            Point3 rotation(4, 5, 6);
            Point3 velocity(7, 8, 9);
            Point3 acceleration(10, 11, 12);

            EgoState es(position, rotation, velocity, acceleration);

            stringstream s;
            s << es;
            s.flush();

            EgoState es2;
            s >> es2;

            TS_ASSERT(es.toString() == es2.toString());
        }

        void testEgoStateContainer() {
            Point3 position(1, 2, 3);
            Point3 rotation(4, 5, 6);
            Point3 velocity(7, 8, 9);
            Point3 acceleration(10, 11, 12);

            EgoState es(position, rotation, velocity, acceleration);

            Container c(es);

            stringstream s;
            s << c;
            s.flush();

            Container c2;
            s >> c2;
            TS_ASSERT(c2.getDataType() == EgoState::ID());

            EgoState es2 = c2.getData<EgoState>();
            TS_ASSERT(es.toString() == es2.toString());
        }
};

#endif /*HESPERIA_EGOSTATETESTSUITE_H_*/
