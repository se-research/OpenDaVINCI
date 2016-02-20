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

#include <ostream>
#include <string>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/CoordinateSystem.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            CoordinateSystem::CoordinateSystem() :
                    m_type(""),
                    m_rotation(0) {}

            CoordinateSystem::CoordinateSystem(const CoordinateSystem &obj) :
                    SerializableData(),
                    m_type(obj.m_type),
                    m_rotation(obj.m_rotation) {}

            CoordinateSystem::~CoordinateSystem() {}

            CoordinateSystem& CoordinateSystem::operator=(const CoordinateSystem &obj) {
                setType(obj.getType());
                setRotation(obj.getRotation());
                return (*this);
            }

            const string CoordinateSystem::getType() const {
                return m_type;
            }

            void CoordinateSystem::setType(const string &type) {
                m_type = type;
            }

            double CoordinateSystem::getRotation() const {
                return m_rotation;
            }

            void CoordinateSystem::setRotation(const double &r) {
                m_rotation = r;
            }

            const string CoordinateSystem::toString() const {
                stringstream s;
                s << "Type: '" << m_type << "', Rotation: " << m_rotation;
                return s.str();
            }

            ostream& CoordinateSystem::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                        m_type);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('r', 'o', 't', 'a', 't', 'i', 'o', 'n') >::RESULT,
                        m_rotation);

                return out;
            }

            istream& CoordinateSystem::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                       m_type);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('r', 'o', 't', 'a', 't', 'i', 'o', 'n') >::RESULT,
                       m_rotation);

                return in;
            }

        }
    }
} // opendlv::data::scenario
