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
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/scenario/Cylinder.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            Cylinder::Cylinder() :
                    m_center(),
                    m_radius(0),
                    m_height(0),
                    m_color() {
                Shape::setType(Shape::CYLINDER);
            }

            Cylinder::Cylinder(const Cylinder &obj) :
                    Shape(obj),
                    m_center(obj.m_center),
                    m_radius(obj.m_radius),
                    m_height(obj.m_height),
                    m_color(obj.m_color) {}

            Cylinder::~Cylinder() {}

            Cylinder& Cylinder::operator=(const Cylinder &obj) {
                Shape::operator=(obj);
                setCenter(obj.getCenter());
                setRadius(obj.getRadius());
                setHeight(obj.getHeight());
                setColor(obj.getColor());
                return (*this);
            }

            void Cylinder::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_center.accept(visitor);
                m_color.accept(visitor);
            }

            const Vertex3& Cylinder::getCenter() const {
                return m_center;
            }

            void Cylinder::setCenter(const Vertex3 &c) {
                m_center = c;
            }

            double Cylinder::getRadius() const {
                return m_radius;
            }

            void Cylinder::setRadius(const double &r) {
                if (!(r > 0)) {
                    m_radius = 0.1;
                } else {
                    m_radius = r;
                }
            }

            double Cylinder::getHeight() const {
                return m_height;
            }

            void Cylinder::setHeight(const double &h) {
                m_height = h;
            }

            const Vertex3& Cylinder::getColor() const {
                return m_color;
            }

            void Cylinder::setColor(const Vertex3 &c) {
                m_color = c;
            }

            int32_t Cylinder::getID() const {
                return 828;
            }

            const string Cylinder::getShortName() const {
                return "Cylinder";
            }

            const string Cylinder::getLongName() const {
                return "hesperia.data.scenario.Cylinder";
            }

            const string Cylinder::toString() const {
                stringstream s;
                s << Shape::toString() << ", Center: " << m_center.toString() << ", Radius: " << m_radius << ", Height: " << m_height << ", Color: " << m_color.toString();
                return s.str();
            }

            ostream& Cylinder::operator<<(ostream &out) const {
                // Serializer super class.
                Shape::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_center);

                s->write(2, m_radius);

                s->write(3, m_height);

                s->write(4, m_color);

                return out;
            }

            istream& Cylinder::operator>>(istream &in) {
                // Deserializer super class.
                Shape::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_center);

                d->read(2, m_radius);

                d->read(3, m_height);

                d->read(4, m_color);

                return in;
            }

        }
    }
} // core::data::scenario
