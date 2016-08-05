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

#include <iosfwd>
#include <memory>
#include <string>

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/sensor/LMS291Message.h"

namespace opendlv {
    namespace data {
        namespace sensor {

            using namespace std;
            using namespace odcore::base;

            LMS291Message::LMS291Message() :
                    SerializableData(),
                    m_identifier(),
                    m_message() {}

            LMS291Message::LMS291Message(const LMS291Message &obj) :
                    m_identifier(obj.getIdentifier()),
                    m_message(obj.getMessage()) {}

            LMS291Message::~LMS291Message() {}

            LMS291Message& LMS291Message::operator=(const LMS291Message &obj) {
                setIdentifier(obj.getIdentifier());
                setMessage(obj.getMessage());

                return (*this);
            }

            const string LMS291Message::getIdentifier() const {
                return m_identifier;
            }

            void LMS291Message::setIdentifier(const string &id) {
                m_identifier = id;
            }

            const string LMS291Message::getMessage() const {
                return m_message;
            }

            void LMS291Message::setMessage(const string &msg) {
                m_message = msg;
            }

            int32_t LMS291Message::getID() const {
                return 34;
            }

            const string LMS291Message::getShortName() const {
                return "LMS291Message";
            }

            const string LMS291Message::getLongName() const {
                return "hesperia.data.sensor.LMS291Message";
            }

            const string LMS291Message::toString() const {
                return m_message;
            }

            ostream& LMS291Message::operator<<(ostream &out) const {
                // Serialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_identifier);

                s->write(2, m_message);

                return out;
            }

            istream& LMS291Message::operator>>(istream &in) {
                // Deserialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                d->read(2, m_message);

                return in;
            }

        }
    }
} // opendlv::data::sensor
