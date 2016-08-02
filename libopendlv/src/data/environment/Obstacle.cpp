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
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/environment/Obstacle.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/PointShapedObject.h"
#include "opendlv/data/environment/Polygon.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace opendlv::data::environment;

            Obstacle::Obstacle() :
                    PointShapedObject(Point3(0, 0, 0), Point3(0, 0, 0), Point3(0, 0, 0), Point3(0, 0, 0)),
                    m_obstacleid(0),
                    m_state(Obstacle::REMOVE),
                    m_classification(Obstacle::UNKNOWN),
                    m_polygon() {}

            Obstacle::Obstacle(const uint32_t &id, const enum Obstacle::STATE &state) :
                   PointShapedObject(Point3(0, 0, 0), Point3(0, 0, 0), Point3(0, 0, 0), Point3(0, 0, 0)),
                   m_obstacleid(id),
                   m_state(state),
                   m_classification(Obstacle::UNKNOWN),
                   m_polygon() {}

            Obstacle::Obstacle(const uint32_t &id, const enum Obstacle::STATE &state, const enum Obstacle::CLASSIFICATION &classification,
                               const Point3 &position, const Point3 &rotation,
                               const Point3 &velocity, const Point3 &acceleration,
                               const Polygon &polygon) :
                   PointShapedObject(position, rotation, velocity, acceleration),
                   m_obstacleid(id),
                   m_state(state),
                   m_classification(classification),
                   m_polygon(polygon) {}

            Obstacle::Obstacle(const Obstacle &obj) :
                    PointShapedObject(obj),
                    m_obstacleid(obj.m_obstacleid),
                    m_state(obj.m_state),
                    m_classification(obj.m_classification),
                    m_polygon(obj.m_polygon) {}

            Obstacle::~Obstacle() {}

            Obstacle& Obstacle::operator=(const Obstacle &obj) {
                PointShapedObject::operator=(obj);

                m_obstacleid = obj.m_obstacleid;
                m_state = obj.m_state;
                m_classification = obj.m_classification;
                m_polygon = obj.m_polygon;

                return (*this);
            }

            uint32_t Obstacle::getObstacleID() const {
                return m_obstacleid;
            }

            void Obstacle::setObstacleID(const uint32_t &id) {
                m_obstacleid = id;
            }

            enum Obstacle::STATE Obstacle::getState() const {
                return m_state;
            }

            void Obstacle::setState(const enum Obstacle::STATE &s) {
                m_state = s;
            }

            enum Obstacle::CLASSIFICATION Obstacle::getClassification() const {
                return m_classification;
            }

            void Obstacle::setClassification(const enum Obstacle::CLASSIFICATION &c) {
                m_classification = c;
            }

            void Obstacle::setPolygon(const Polygon &p) {
                m_polygon = p;
            }

            const Polygon Obstacle::getPolygon() const {
                return m_polygon;
            }

            int32_t Obstacle::ID() {
                return 35;
            }

            int32_t Obstacle::getID() const {
                return 35;
            }

            const string Obstacle::getShortName() const {
                return "Obstacle";
            }

            const string Obstacle::getLongName() const {
                return "hesperia.data.environment.Obstacle";
            }

            const string Obstacle::toString() const {
                stringstream s;
                s << PointShapedObject::toString() << "/" << m_polygon.toString() << ", state: " << m_state << ", classification: " << m_classification;
                return s.str();
            }

            ostream& Obstacle::operator<<(ostream &out) const {
                // Serializer super class.
                PointShapedObject::operator<<(out);

                // Serialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, static_cast<uint32_t>(m_obstacleid));

                s->write(2, static_cast<uint32_t>(m_state));

                s->write(3, static_cast<uint32_t>(m_classification));

                s->write(4, m_polygon);

                return out;
            }

            istream& Obstacle::operator>>(istream &in) {
                // Deserializer super class.
                PointShapedObject::operator>>(in);

                // Deserialize this class.
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_obstacleid);

                uint32_t v = 0;
                d->read(2, v);
                m_state = static_cast<Obstacle::STATE>(v);

                v = 0;
                d->read(3, v);
                m_classification = static_cast<Obstacle::CLASSIFICATION>(v);

                d->read(4, m_polygon);

                return in;
            }

        }
    }
} // opendlv::data::environment
