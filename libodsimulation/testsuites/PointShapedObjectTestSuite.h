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

#ifndef HESPERIA_POINTSHAPEDOBJECTTESTSUITE_H_
#define HESPERIA_POINTSHAPEDOBJECTTESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <sstream>

#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/PointShapedObject.h"

using namespace std;
using namespace hesperia::data;
using namespace hesperia::data::environment;
using namespace hesperia::data::environment;

class PointShapedObjectTest : public CxxTest::TestSuite {
    public:
        void testPointShapedObject() {
            Point3 position(1, 2, 3);
            Point3 rotation(4, 5, 6);
            Point3 velocity(7, 8, 9);
            Point3 acceleration(10, 11, 12);

            PointShapedObject pso;
            pso.setPosition(position);
            pso.setRotation(rotation);
            pso.setVelocity(velocity);
            pso.setAcceleration(acceleration);

            stringstream s;
            s << pso;
            s.flush();

            PointShapedObject pso2;
            s >> pso2;

            TS_ASSERT(pso.toString() == pso2.toString());
        }
};

#endif /*HESPERIA_POINTSHAPEDOBJECTTESTSUITE_H_*/
