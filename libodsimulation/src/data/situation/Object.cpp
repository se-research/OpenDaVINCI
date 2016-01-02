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

#include <sstream>
#include <string>

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SerializableData.h"
#include "hesperia/data/situation/Behavior.h"
#include "hesperia/data/situation/ComplexModel.h"
#include "hesperia/data/situation/ExternalDriver.h"
#include "hesperia/data/situation/Object.h"
#include "hesperia/data/situation/PointIDDriver.h"
#include "hesperia/data/situation/Polygon.h"
#include "hesperia/data/situation/Rectangle.h"
#include "hesperia/data/situation/Shape.h"
#include "hesperia/data/situation/SituationVisitor.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace core::base;

            Object::Object() :
                    m_name(""),
                    m_id(0),
                    m_shape(NULL),
                    m_rotationZ(0),
                    m_behavior(NULL) {}

            Object::Object(const Object &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_id(obj.m_id),
                    m_shape(NULL),
                    m_rotationZ(obj.m_rotationZ),
                    m_behavior(NULL) {
                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);
            }

            Object::~Object() {
                // Clean up.
                cleanUp();
            }

            Object& Object::operator=(const Object &obj) {
                setName(obj.getName());
                setID(obj.getID());
                setRotationZ(obj.getRotationZ());

                // Clean up.
                cleanUp();

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Object::deepCopy(const Object &obj) {
                Shape *s = obj.getShape();
                if (s != NULL) {
                    switch (s->getType()) {
                    case Shape::COMPLEXMODEL: {
                            ComplexModel *cm = new ComplexModel(dynamic_cast<ComplexModel&>(*s));
                            setShape(cm);
                            break;
                        }
                    case Shape::RECTANGLE: {
                            Rectangle *r = new Rectangle(dynamic_cast<Rectangle&>(*s));
                            setShape(r);
                            break;
                        }
                    case Shape::POLYGON: {
                            Polygon *p = new Polygon(dynamic_cast<Polygon&>(*s));
                            setShape(p);
                            break;
                        }
                    case Shape::UNDEFINED:
                        break;
                    }
                }

                Behavior *b = obj.getBehavior();
                if (b != NULL) {
                    switch (b->getType()) {
                    case Behavior::EXTERNALDRIVER: {
                            ExternalDriver *ed = new ExternalDriver(dynamic_cast<ExternalDriver&>(*b));
                            setBehavior(ed);
                            break;
                        }
                    case Behavior::POINTIDDRIVER: {
                            PointIDDriver *pidd = new PointIDDriver(dynamic_cast<PointIDDriver&>(*b));
                            setBehavior(pidd);
                            break;
                        }
                    case Behavior::UNDEFINED:
                        break;
                    }
                }
            }

            void Object::cleanUp() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_shape);
                OPENDAVINCI_CORE_DELETE_POINTER(m_behavior);
            }

            void Object::accept(SituationVisitor &visitor) {
                visitor.visit(*this);

                if (m_shape != NULL) {
                    m_shape->accept(visitor);
                }

                if (m_behavior != NULL) {
                    m_behavior->accept(visitor);
                }
            }

            const string Object::getName() const {
                return m_name;
            }

            void Object::setName(const string &name) {
                m_name = name;
            }

            uint32_t Object::getID() const {
                return m_id;
            }

            void Object::setID(const uint32_t &id) {
                m_id = id;
            }

            Shape* Object::getShape() const {
                return m_shape;
            }

            void Object::setShape(Shape *s) {
                if (s != NULL) {
                    m_shape = s;
                }
            }

            double Object::getRotationZ() const {
                return m_rotationZ;
            }

            void Object::setRotationZ(const double &rotationZ) {
                m_rotationZ = rotationZ;
            }

            Behavior* Object::getBehavior() const {
                return m_behavior;
            }

            void Object::setBehavior(Behavior *b) {
                if (b != NULL) {
                    m_behavior = b;
                }
            }

            const string Object::toString() const {
                stringstream s;
                s << "Object: '" << m_name << "', ID: " << m_id << ", RotationZ: " << m_rotationZ;
                return s.str();
            }

            ostream& Object::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        m_name);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        m_id);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('h', 'a', 's', 's', 'h', 'a', 'p', 'e') >::RESULT,
                        (m_shape != NULL));

                if (m_shape != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_shape->getType())
                    << *m_shape;

                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                            sstr.str());
                }

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                        m_rotationZ);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('h', 'a', 's', 'b', 'e', 'h', 'a', 'v') >::RESULT,
                        (m_behavior != NULL));

                if (m_behavior != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_behavior->getType())
                    << *m_behavior;

                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'e', 'h', 'a', 'v') >::RESULT,
                            sstr.str());
                }
                return out;
            }

            istream& Object::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                bool hasShape = false;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('h', 'a', 's', 's', 'h', 'a', 'p', 'e') >::RESULT,
                       hasShape);

                if (hasShape) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'h', 'a', 'p', 'e') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read shape from stringstream.
                    uint32_t type = 0;
                    sstr >> type;
                    enum Shape::SHAPETYPE shapeType = static_cast<enum Shape::SHAPETYPE>(type);

                    switch (shapeType) {
                    case Shape::COMPLEXMODEL: {
                            ComplexModel *cm = new ComplexModel();
                            sstr >> *cm;
                            setShape(cm);
                            break;
                        }
                    case Shape::RECTANGLE: {
                            Rectangle *r = new Rectangle();
                            sstr >> *r;
                            setShape(r);
                            break;
                        }
                    case Shape::POLYGON: {
                            Polygon *p = new Polygon();
                            sstr >> *p;
                            setShape(p);
                            break;
                        }
                    case Shape::UNDEFINED:
                        break;
                    }
                }

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                       m_rotationZ);

                bool hasBehavior = false;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('h', 'a', 's', 'b', 'e', 'h', 'a', 'v') >::RESULT,
                       hasBehavior);

                if (hasBehavior) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'e', 'h', 'a', 'v') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read shape from stringstream.
                    uint32_t type = 0;
                    sstr >> type;
                    enum Behavior::BEHAVIORTYPE behaviorType = static_cast<enum Behavior::BEHAVIORTYPE>(type);

                    switch (behaviorType) {
                    case Behavior::EXTERNALDRIVER: {
                            ExternalDriver *ed = new ExternalDriver();
                            sstr >> *ed;
                            setBehavior(ed);
                            break;
                        }
                    case Behavior::POINTIDDRIVER: {
                            PointIDDriver *pidd = new PointIDDriver();
                            sstr >> *pidd;
                            setBehavior(pidd);
                            break;
                        }
                    case Behavior::UNDEFINED:
                        break;
                    }
                }

                return in;
            }

        }
    }
} // hesperia::data::situation
