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

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/PointShapedObject.h"
#include "opendlv/data/environment/Position.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace opendlv::data::environment;

            PointShapedObject::PointShapedObject() :
                    Position(Point3(0, 0, 0), Point3(0, 0, 0)),
                    m_velocity(Point3(0, 0, 0)),
                    m_acceleration(Point3(0, 0, 0)) {}

            PointShapedObject::PointShapedObject(const Point3 &position, const Point3 &rotation,
                                                 const Point3 &velocity, const Point3 &acceleration) :
                    Position(position, rotation),
                    m_velocity(velocity),
                    m_acceleration(acceleration) {}

            PointShapedObject::PointShapedObject(const PointShapedObject &obj) :
                    Position(obj),
                    m_velocity(obj.getVelocity()),
                    m_acceleration(obj.getAcceleration()) {}

            PointShapedObject::~PointShapedObject() {}

            PointShapedObject& PointShapedObject::operator=(const PointShapedObject &obj) {
                Position::operator=(obj);
                setVelocity(obj.getVelocity());
                setAcceleration(obj.getAcceleration());

                return (*this);
            }

            const Point3 PointShapedObject::getVelocity() const {
                return m_velocity;
            }

            void PointShapedObject::setVelocity(const Point3 &velocity) {
                m_velocity = velocity;
            }

            const Point3 PointShapedObject::getAcceleration() const {
                return m_acceleration;
            }

            void PointShapedObject::setAcceleration(const Point3 &acceleration) {
                m_acceleration = acceleration;
            }

            int32_t PointShapedObject::getID() const {
                return 37;
            }

            const string PointShapedObject::getShortName() const {
                return "PointShapedObject";
            }

            const string PointShapedObject::getLongName() const {
                return "hesperia.data.environment.PointShapedObject";
            }

            const string PointShapedObject::toString() const {
                stringstream s;
                s << Position::toString() << "@" << getVelocity().toString() << " with " << getAcceleration().toString();
                return s.str();
            }

            ostream& PointShapedObject::operator<<(ostream &out) const {
                // Serializer super class.
                Position::operator<<(out);

                // Serialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_velocity);

                s->write(2, m_acceleration);

                return out;
            }

            istream& PointShapedObject::operator>>(istream &in) {
                // Deserializer super class.
                Position::operator>>(in);

                // Deserialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_velocity);

                d->read(2, m_acceleration);

                return in;
            }

        }
    }
} // opendlv::data::environment
