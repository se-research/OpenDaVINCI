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

#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/Stop.h"
#include "opendlv/data/situation/StopType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            Stop::Stop() :
                    StopType() {
                setType(StopType::STOP);
            }

            Stop::Stop(const Stop &obj) :
                    StopType(obj) {}

            Stop::~Stop() {}

            Stop& Stop::operator=(const Stop &obj) {
                StopType::operator=(obj);
                return (*this);
            }

            void Stop::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            int32_t Stop::getID() const {
                return 861;
            }

            const string Stop::getShortName() const {
                return "Stop";
            }

            const string Stop::getLongName() const {
                return "hesperia.data.situation.Stop";
            }

            const string Stop::toString() const {
                stringstream s;
                s << getType();
                return s.str();
            }

            ostream& Stop::operator<<(ostream &out) const {
                // Serializer super class.
                StopType::operator<<(out);

//
//                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();
//
//                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);
//
//                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
//                        static_cast<uint32_t>(m_type));

                return out;
            }

            istream& Stop::operator>>(istream &in) {
                // Deserializer super class.
                StopType::operator>>(in);

//                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();
//
//                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);
//
//                uint32_t type = 0;
//                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
//                       type);
//
//                m_type = static_cast<enum Stop::BEHAVIORTYPE>(type);

                return in;
            }

        }
    }
} // opendlv::data::situation
