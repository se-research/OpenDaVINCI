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

#include "opendlv/data/situation/Immediately.h"
#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/StartType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            Immediately::Immediately() :
                    StartType() {
                setType(StartType::IMMEDIATELY);
            }

            Immediately::Immediately(const Immediately &obj) :
                    StartType(obj) {}

            Immediately::~Immediately() {}

            Immediately& Immediately::operator=(const Immediately &obj) {
                StartType::operator=(obj);
                return (*this);
            }

            void Immediately::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            int32_t Immediately::getID() const {
                return 868;
            }

            const string Immediately::getShortName() const {
                return "Immediately";
            }

            const string Immediately::getLongName() const {
                return "hesperia.data.situation.Immediately";
            }

            const string Immediately::toString() const {
                stringstream s;
                s << getType();
                return s.str();
            }

            ostream& Immediately::operator<<(ostream &out) const {
                // Serializer super class.
                StartType::operator<<(out);

//
//                SerializationFactory& sf=SerializationFactory::getInstance();
//
//                std::shared_ptr<Serializer> s = sf.getSerializer(out);
//
//                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
//                        static_cast<uint32_t>(m_type));

                return out;
            }

            istream& Immediately::operator>>(istream &in) {
                // Deserializer super class.
                StartType::operator>>(in);

//                SerializationFactory& sf=SerializationFactory::getInstance();
//
//                std::shared_ptr<Deserializer> d = sf.getDeserializer(in);
//
//                uint32_t type = 0;
//                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
//                       type);
//
//                m_type = static_cast<enum Immediately::BEHAVIORTYPE>(type);

                return in;
            }

        }
    }
} // opendlv::data::situation
