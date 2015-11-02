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

#include "hesperia/data/environment/EgoState.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace core::base;
            using namespace hesperia::data::environment;

            EgoState::EgoState() :
                    PointShapedObject() {}

            EgoState::EgoState(const Point3 &position, const Point3 &rotation,
                               const Point3 &velocity, const Point3 &acceleration) :
                    PointShapedObject(position, rotation, velocity, acceleration) {}

            EgoState::EgoState(const EgoState &obj) :
                    PointShapedObject(obj) {}

            EgoState::~EgoState() {}

            EgoState& EgoState::operator=(const EgoState &obj) {
                PointShapedObject::operator=(obj);

                return (*this);
            }

            int32_t EgoState::getID() const {
                return 32;
            }

            const string EgoState::getShortName() const {
                return "EgoState";
            }

            const string EgoState::getLongName() const {
                return "hesperia.data.environment.EgoState";
            }

            const string EgoState::toString() const {
                stringstream s;
                s << PointShapedObject::toString();
                return s.str();
            }

            ostream& EgoState::operator<<(ostream &out) const {
                // Serializer super class.
                PointShapedObject::operator<<(out);

                // Serialize this class.
//                SerializationFactory& sf=SerializationFactory::getInstance();
//
//                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                // Nothing to be done.

                return out;
            }

            istream& EgoState::operator>>(istream &in) {
                // Deserializer super class.
                PointShapedObject::operator>>(in);

                // Deserialize this class.
//                SerializationFactory& sf=SerializationFactory::getInstance();
//
//                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Nothing to be done.

                return in;
            }

        }
    }
} // hesperia::data::environment
