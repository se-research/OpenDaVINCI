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

#include <memory>
#include <ostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/StopType.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            StopType::StopType() :
                    m_type(StopType::UNDEFINED) {}

            StopType::StopType(const StopType &obj) :
                    SerializableData(),
                    m_type(obj.getType()) {}

            StopType::~StopType() {}

            StopType& StopType::operator=(const StopType &obj) {
                setType(obj.getType());
                return (*this);
            }

            enum StopType::STOPTYPE StopType::getType() const {
                return m_type;
            }

            void StopType::setType(const enum StopType::STOPTYPE &type) {
                m_type = type;
            }

            int32_t StopType::getID() const {
                return 858;
            }

            const string StopType::getShortName() const {
                return "StopType";
            }

            const string StopType::getLongName() const {
                return "hesperia.data.situation.StopType";
            }

            const string StopType::toString() const {
                stringstream s;
                s << "Type: " << static_cast<uint32_t>(m_type);
                return s.str();
            }

            ostream& StopType::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, static_cast<uint32_t>(m_type));

                return out;
            }

            istream& StopType::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                uint32_t type = 0;
                d->read(1, type);

                m_type = static_cast<enum StopType::STOPTYPE>(type);

                return in;
            }

        }
    }
} // opendlv::data::situation
