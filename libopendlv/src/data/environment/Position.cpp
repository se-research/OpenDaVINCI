/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <memory>
#include <ostream>
#include <string>

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/Position.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;

            Position::Position() : m_position(), m_rotation() {}

            Position::Position(const Point3 &position, const Point3 &rotation) :
                m_position(position),
                m_rotation(rotation) {}

            Position::Position(const Position &obj) :
                SerializableData(),
                m_position(obj.getPosition()),
                m_rotation(obj.getRotation()) {}

            Position::~Position() {}

            Position& Position::operator=(const Position &obj) {
                setPosition(obj.getPosition());
                setRotation(obj.getRotation());
                return (*this);
            }

            const Point3 Position::getPosition() const {
                return m_position;
            }

            void Position::setPosition(const Point3 &position) {
                m_position = position;
            }

            const Point3 Position::getRotation() const {
                return m_rotation;
            }

            void Position::setRotation(const Point3 &rotation) {
                m_rotation = rotation;
            }

            bool Position::operator==(const Position& other) const
            {
                return (m_position == other.m_position) && (m_rotation == other.m_rotation);
            }

            bool Position::operator!=(const Position& other) const
            {
                return !operator==(other);
            }

            int32_t Position::getID() const {
                return 15;
            }

            const string Position::getShortName() const {
                return "Position";
            }

            const string Position::getLongName() const {
                return "hesperia.data.environment.Position";
            }

            const string Position::toString() const {
                stringstream sstr;
                sstr  << m_position.toString() << "/" << m_rotation.toString();
                return sstr.str();
            }

            ostream& Position::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_position);

                s->write(2, m_rotation);

                return out;
            }

            istream& Position::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();;

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_position);

                d->read(2, m_rotation);

                return in;
            }

        }
    }
} // opendlv::data::environment
