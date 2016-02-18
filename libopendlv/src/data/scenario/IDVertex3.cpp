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

#include <ostream>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

            IDVertex3::IDVertex3() :
                    Vertex3(),
                    m_id(0) {}

            IDVertex3::IDVertex3(const IDVertex3 &obj) :
                    Vertex3(obj),
                    m_id(obj.getID()) {}

            IDVertex3::~IDVertex3() {}

            IDVertex3& IDVertex3::operator=(const IDVertex3 &obj) {
                Vertex3::operator=(obj);
                setID(obj.getID());

                return (*this);
            }

            void IDVertex3::accept(ScenarioVisitor &visitor) {
                Vertex3::accept(visitor);
                visitor.visit(*this);
            }

            uint32_t IDVertex3::getID() const {
                return m_id;
            }

            void IDVertex3::setID(const uint32_t &id) {
                m_id = id;
            }

            const string IDVertex3::toString() const {
                stringstream s;
                s << "ID: " << getID() << ": " << Vertex3::toString();
                return s.str();
            }

            ostream& IDVertex3::operator<<(ostream &out) const {
                // Serializer super class.
                Vertex3::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                return out;
            }

            istream& IDVertex3::operator>>(istream &in) {
                // Deserializer super class.
                Vertex3::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                return in;
            }

        }
    }
} // hesperia::data::scenario
