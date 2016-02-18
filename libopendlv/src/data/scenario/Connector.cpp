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
#include "opendavinci/core/data/SerializableData.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/PointID.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            Connector::Connector() :
                    m_source(),
                    m_target() {}

            Connector::Connector(const Connector &obj) :
                    SerializableData(),
                    m_source(obj.getSource()),
                    m_target(obj.getTarget()) {}

            Connector::~Connector() {}

            Connector& Connector::operator=(const Connector &obj) {
                setSource(obj.getSource());
                setTarget(obj.getTarget());
                return (*this);
            }

            void Connector::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_source.accept(visitor);
                m_target.accept(visitor);
            }

            const PointID& Connector::getSource() const {
                return m_source;
            }

            void Connector::setSource(const PointID &sourceID) {
                m_source = sourceID;
            }

            const PointID& Connector::getTarget() const {
                return m_target;
            }

            void Connector::setTarget(const PointID &targetID) {
                m_target = targetID;
            }

            const string Connector::toString() const {
                stringstream s;
                s << "(" << getSource().toString() << ")" << " -> " << "(" << getTarget().toString() << ")";
                return s.str();
            }

            ostream& Connector::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('s', 'o', 'u', 'r', 'c', 'e') >::RESULT,
                        getSource());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('t', 'a', 'r', 'g', 'e', 't') >::RESULT,
                        getTarget());

                return out;
            }

            istream& Connector::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('s', 'o', 'u', 'r', 'c', 'e') >::RESULT,
                       m_source);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('t', 'a', 'r', 'g', 'e', 't') >::RESULT,
                       m_target);

                return in;
            }

        }
    }
} // hesperia::data::scenario
