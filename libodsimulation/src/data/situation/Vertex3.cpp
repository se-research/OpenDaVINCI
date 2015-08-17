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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/situation/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::data::environment;

            Vertex3::Vertex3() :
                    Point3() {}

            Vertex3::Vertex3(const Vertex3 &obj) :
                    Point3(obj) {}

            Vertex3::~Vertex3() {}

            Vertex3& Vertex3::operator=(const Vertex3 &obj) {
                Point3::operator=(obj);

                return (*this);
            }

            void Vertex3::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

        }
    }
} // hesperia::data::situation
