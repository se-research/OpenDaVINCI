 /**
 * hesperia - Simulation environment
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

#include "core/platform.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SerializableData.h"
#include "core/macros.h"
#include "hesperia/data/scenario/ComplexModel.h"
#include "hesperia/data/scenario/Cylinder.h"
#include "hesperia/data/scenario/IDVertex3.h"
#include "hesperia/data/scenario/Polygon.h"
#include "hesperia/data/scenario/Shape.h"
#include "hesperia/data/scenario/TrafficControl.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

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

            const string TrafficControl::toString() const {
                stringstream s;
                s << "Name: '" << m_name << "', Type: " << static_cast<uint32_t>(m_type);
                return s.str();
            }

            ostream& TrafficControl::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        getName());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                        static_cast<uint32_t>(m_type));

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'o', 's', 'i', 't', 'i', 'o', 'n') >::RESULT,
                        getPosition());

                if (getShape() == NULL) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('s', 'h', 'a', 'p', 't', 'y', 'p', 'e') >::RESULT,
                            static_cast<uint32_t>(Shape::UNDEFINED));

                } else {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('s', 'h', 'a', 'p', 't', 'y', 'p', 'e') >::RESULT,
                            static_cast<uint32_t>(getShape()->getType()));

                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                            *(getShape()));
                }

                return out;
            }

            istream& TrafficControl::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                uint32_t type = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('t', 'y', 'p', 'e') >::RESULT,
                       type);

                m_type = static_cast<enum TrafficControl::TRAFFICCONTROLTYPE>(type);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'o', 's', 'i', 't', 'i', 'o', 'n') >::RESULT,
                       m_position);

                // Read shape.
                OPENDAVINCI_CORE_DELETE_POINTER(m_shape);

                type = 0;

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('s', 'h', 'a', 'p', 't', 'y', 'p', 'e') >::RESULT,
                       type);

                enum Shape::SHAPETYPE shapeType = static_cast<enum Shape::SHAPETYPE>(type);

                switch (shapeType) {
                case Shape::COMPLEXMODEL: {
                        ComplexModel *cm = new ComplexModel();

                        d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                               *cm);

                        setShape(cm);
                        break;
                    }
                case Shape::CYLINDER: {
                        Cylinder *c = new Cylinder();

                        d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                               *c);

                        setShape(c);
                        break;
                    }
                case Shape::POLYGON: {
                        Polygon *p = new Polygon();

                        d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                               *p);

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
} // hesperia::data::scenario
