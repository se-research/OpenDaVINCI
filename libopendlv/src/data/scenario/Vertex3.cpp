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

#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace opendlv::data::environment;

            Vertex3::Vertex3() :
                    Point3() {}

            Vertex3::Vertex3(const Vertex3 &obj) :
                    Point3(obj) {}

            Vertex3::~Vertex3() {}

            Vertex3& Vertex3::operator=(const Vertex3 &obj) {
                Point3::operator=(obj);

                return (*this);
            }

            void Vertex3::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);
            }

        }
    }
} // opendlv::data::scenario
