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
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Shape.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            Shape::Shape() :
                    m_name(""),
                    m_type(Shape::POLYGON) {}

            Shape::Shape(const Shape &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_type(obj.m_type) {}

            Shape::~Shape() {}

            Shape& Shape::operator=(const Shape &obj) {
                setName(obj.getName());
                setType(obj.getType());
                return (*this);
            }

            const string Shape::getName() const {
                return m_name;
            }

            void Shape::setName(const string &name) {
                m_name = name;
            }

            enum Shape::SHAPETYPE Shape::getType() const {
                return m_type;
            }

            void Shape::setType(const enum Shape::SHAPETYPE &type) {
                m_type = type;
            }

            int32_t Shape::getID() const {
                return 846;
            }

            const string Shape::getShortName() const {
                return "Shape";
            }

            const string Shape::getLongName() const {
                return "hesperia.data.scenario.Shape";
            }

            const string Shape::toString() const {
                stringstream s;
                s << "Name: '" << m_name << "', Type: " << static_cast<uint32_t>(m_type);
                return s.str();
            }

            ostream& Shape::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_name);

                s->write(2, static_cast<uint32_t>(m_type));

                return out;
            }

            istream& Shape::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_name);

                uint32_t type = 0;
                d->read(2, type);

                m_type = static_cast<enum Shape::SHAPETYPE>(type);

                return in;
            }

        }
    }
} // opendlv::data::scenario
