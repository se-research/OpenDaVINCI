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
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/ComplexModel.h"
#include "opendlv/data/scenario/Cylinder.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Polygon.h"
#include "opendlv/data/scenario/Shape.h"
#include "opendlv/data/scenario/TrafficControl.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            TrafficControl::TrafficControl() :
                    m_name(""),
                    m_type(TrafficControl::TRAFFICSIGN),
                    m_position(),
                    m_shape(NULL) {}

            TrafficControl::TrafficControl(const TrafficControl &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_type(obj.m_type),
                    m_position(obj.getPosition()),
                    m_shape(NULL) {
                // Create a deep copy.
                deepCopy(obj);
            }

            TrafficControl::~TrafficControl() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_shape);
            }

            TrafficControl& TrafficControl::operator=(const TrafficControl &obj) {
                setName(obj.getName());
                setType(obj.getType());
                setPosition(obj.getPosition());

                // Create a deep copy.
                deepCopy(obj);

                return (*this);
            }

            void TrafficControl::deepCopy(const TrafficControl &obj) {
                OPENDAVINCI_CORE_DELETE_POINTER(m_shape);

                if (obj.getShape() != NULL) {
                    switch (obj.getShape()->getType()) {
                    case Shape::COMPLEXMODEL: {
                            ComplexModel *cm = new ComplexModel(*(dynamic_cast<ComplexModel*>(obj.getShape())));
                            setShape(cm);
                            break;
                        }
                    case Shape::CYLINDER: {
                            Cylinder *c = new Cylinder(*(dynamic_cast<Cylinder*>(obj.getShape())));
                            setShape(c);
                            break;
                        }
                    case Shape::POLYGON: {
                            Polygon *p = new Polygon(*(dynamic_cast<Polygon*>(obj.getShape())));
                            setShape(p);
                            break;
                        }
                    case Shape::UNDEFINED:
                        break;
                    }
                }
            }

            const string TrafficControl::getName() const {
                return m_name;
            }

            void TrafficControl::setName(const string &name) {
                m_name = name;
            }

            enum TrafficControl::TRAFFICCONTROLTYPE TrafficControl::getType() const {
                return m_type;
            }

            void TrafficControl::setType(const enum TrafficControl::TRAFFICCONTROLTYPE &type) {
                m_type = type;
            }

            const IDVertex3& TrafficControl::getPosition() const {
                return m_position;
            }

            void TrafficControl::setPosition(const IDVertex3 &p) {
                m_position = p;
            }

            Shape* TrafficControl::getShape() const {
                return m_shape;
            }

            void TrafficControl::setShape(Shape *s) {
                if (s != NULL) {
                    m_shape = s;
                }
            }

            int32_t TrafficControl::getID() const {
                return 820;
            }

            const string TrafficControl::getShortName() const {
                return "TrafficControl";
            }

            const string TrafficControl::getLongName() const {
                return "hesperia.data.scenario.TrafficControl";
            }

            const string TrafficControl::toString() const {
                stringstream s;
                s << "Name: '" << m_name << "', Type: " << static_cast<uint32_t>(m_type);
                return s.str();
            }

            ostream& TrafficControl::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getName());

                s->write(2, static_cast<uint32_t>(m_type));

                s->write(3, getPosition());

                if (getShape() == NULL) {
                    s->write(4, static_cast<uint32_t>(Shape::UNDEFINED));

                } else {
                    s->write(4, static_cast<uint32_t>(getShape()->getType()));

                    s->write(5, *(getShape()));
                }

                return out;
            }

            istream& TrafficControl::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_name);

                uint32_t type = 0;
                d->read(2, type);

                m_type = static_cast<enum TrafficControl::TRAFFICCONTROLTYPE>(type);

                d->read(3, m_position);

                // Read shape.
                OPENDAVINCI_CORE_DELETE_POINTER(m_shape);

                type = 0;

                d->read(4, type);

                enum Shape::SHAPETYPE shapeType = static_cast<enum Shape::SHAPETYPE>(type);

                switch (shapeType) {
                case Shape::COMPLEXMODEL: {
                        ComplexModel *cm = new ComplexModel();

                        d->read(5, *cm);

                        setShape(cm);
                        break;
                    }
                case Shape::CYLINDER: {
                        Cylinder *c = new Cylinder();

                        d->read(5, *c);

                        setShape(c);
                        break;
                    }
                case Shape::POLYGON: {
                        Polygon *p = new Polygon();

                        d->read(5, *p);

                        setShape(p);
                        break;
                    }
                case Shape::UNDEFINED:
                    break;
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
