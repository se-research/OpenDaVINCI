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
#include "opendlv/data/situation/Shape.h"
#include "opendlv/data/situation/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            Shape::Shape() :
                    m_name(""),
                    m_type(Shape::UNDEFINED),
                    m_front() {}

            Shape::Shape(const Shape &obj) :
                    SerializableData(),
                    m_name(obj.getName()),
                    m_type(obj.getType()),
                    m_front(obj.getFront()) {}

            Shape::~Shape() {}

            Shape& Shape::operator=(const Shape &obj) {
                setName(obj.getName());
                setType(obj.getType());
                setFront(obj.getFront());
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

            const Vertex3 Shape::getFront() const {
                return m_front;
            }

            void Shape::setFront(const Vertex3 f) {
                m_front = f;
            }

            int32_t Shape::getID() const {
                return 859;
            }

            const string Shape::getShortName() const {
                return "Shape";
            }

            const string Shape::getLongName() const {
                return "hesperia.data.situation.Shape";
            }

            const string Shape::toString() const {
                stringstream s;
                s << "Name: '" << m_name << "', Type: " << static_cast<uint32_t>(m_type) << ", front: " << m_front.toString();
                return s.str();
            }

            ostream& Shape::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_name);

                s->write(2, static_cast<uint32_t>(m_type));

                s->write(3, m_front);

                return out;
            }

            istream& Shape::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_name);

                uint32_t type = 0;
                d->read(2, type);

                m_type = static_cast<enum Shape::SHAPETYPE>(type);

                d->read(3, m_front);

                return in;
            }

        }
    }
} // opendlv::data::situation
