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

#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "hesperia/data/scenario/Arc.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/StraightLine.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            Arc::Arc() :
                    StraightLine(),
                    m_radius(0),
                    m_beginInterval(0),
                    m_endInterval(0),
                    m_rotationZ(0) {
                LaneModel::setType(LaneModel::ARC);
            }

            Arc::Arc(const Arc &obj) :
                    StraightLine(obj),
                    m_radius(obj.getRadius()),
                    m_beginInterval(obj.getBeginInterval()),
                    m_endInterval(obj.getEndInterval()),
                    m_rotationZ(obj.getRotationZ()) {}

            Arc::~Arc() {}

            Arc& Arc::operator=(const Arc &obj) {
                StraightLine::operator=(obj);
                setRadius(obj.getRadius());
                setBeginInterval(obj.getBeginInterval());
                setEndInterval(obj.getEndInterval());
                setRotationZ(obj.getRotationZ());

                return (*this);
            }

            void Arc::accept(ScenarioVisitor &visitor) {
                StraightLine::accept(visitor);
                visitor.visit(*this);
            }

            double Arc::getRadius() const {
                return m_radius;
            }

            void Arc::setRadius(const double &r) {
                m_radius = r;
            }

            double Arc::getBeginInterval() const {
                return m_beginInterval;
            }

            void Arc::setBeginInterval(const double &bi) {
                m_beginInterval = bi;
            }

            double Arc::getEndInterval() const {
                return m_endInterval;
            }

            void Arc::setEndInterval(const double &ei) {
                m_endInterval = ei;
            }

            double Arc::getRotationZ() const {
                return m_rotationZ;
            }

            void Arc::setRotationZ(const double &rotationZ) {
                m_rotationZ = rotationZ;
            }

            const string Arc::toString() const {
                stringstream sstr;
                sstr << "R: " << getRadius() << ", [" << getBeginInterval() << "; " << getEndInterval() << "], Rotation: " << getRotationZ();
                return sstr.str();
            }

            ostream& Arc::operator<<(ostream &out) const {
                // Serializer super class.
                StraightLine::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('r', 'a', 'd', 'i', 'u', 's') >::RESULT,
                        getRadius());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'e', 'g', 'i', 'n') >::RESULT,
                        getBeginInterval());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('e', 'n', 'd') >::RESULT,
                        getEndInterval());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                        getRotationZ());

                return out;
            }

            istream& Arc::operator>>(istream &in) {
                // Deserializer super class.
                StraightLine::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('r', 'a', 'd', 'i', 'u', 's') >::RESULT,
                       m_radius);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('b', 'e', 'g', 'i', 'n') >::RESULT,
                       m_beginInterval);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('e', 'n', 'd') >::RESULT,
                       m_endInterval);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                       m_rotationZ);

                return in;
            }

        }
    }
} // hesperia::data::scenario
