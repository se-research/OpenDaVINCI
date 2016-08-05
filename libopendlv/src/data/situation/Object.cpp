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
#include <sstream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/Behavior.h"
#include "opendlv/data/situation/ComplexModel.h"
#include "opendlv/data/situation/ExternalDriver.h"
#include "opendlv/data/situation/Object.h"
#include "opendlv/data/situation/PointIDDriver.h"
#include "opendlv/data/situation/Polygon.h"
#include "opendlv/data/situation/Rectangle.h"
#include "opendlv/data/situation/Shape.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            Object::Object() :
                    m_name(""),
                    m_identifier(0),
                    m_shape(NULL),
                    m_rotationZ(0),
                    m_behavior(NULL) {}

            Object::Object(const Object &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_identifier(obj.m_identifier),
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
                setIdentifier(obj.getIdentifier());
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

            uint32_t Object::getIdentifier() const {
                return m_identifier;
            }

            void Object::setIdentifier(const uint32_t &id) {
                m_identifier = id;
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

            int32_t Object::getID() const {
                return 854;
            }

            const string Object::getShortName() const {
                return "Object";
            }

            const string Object::getLongName() const {
                return "hesperia.data.situation.Object";
            }

            const string Object::toString() const {
                stringstream s;
                s << "Object: '" << m_name << "', ID: " << m_identifier << ", RotationZ: " << m_rotationZ;
                return s.str();
            }

            ostream& Object::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_name);

                s->write(2, m_identifier);

                s->write(3, (m_shape != NULL));

                if (m_shape != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_shape->getType())
                    << *m_shape;

                    s->write(4, sstr.str());
                }

                s->write(5, m_rotationZ);

                s->write(6, (m_behavior != NULL));

                if (m_behavior != NULL) {
                    // Write data to stringstream.
                    stringstream sstr;
                    sstr << static_cast<uint32_t>(m_behavior->getType())
                    << *m_behavior;

                    s->write(7, sstr.str());
                }
                return out;
            }

            istream& Object::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_name);

                d->read(2, m_identifier);

                bool hasShape = false;
                d->read(3, hasShape);

                if (hasShape) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(4, str);

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

                d->read(5, m_rotationZ);

                bool hasBehavior = false;
                d->read(6, hasBehavior);

                if (hasBehavior) {
                    string str;
                    // Read shapes into stringstream.
                    d->read(7, str);

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
} // opendlv::data::situation
