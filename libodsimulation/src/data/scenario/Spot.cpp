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

#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/Spot.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

            Spot::Spot() :
                    m_identifier(0),
                    m_firstVertex(),
                    m_secondVertex() {
            }

            Spot::Spot(const Spot &obj) :
                    SerializableData(),
                    m_identifier(obj.getIdentifier()),
                    m_firstVertex(obj.getFirstVertex()),
                    m_secondVertex(obj.getSecondVertex()) {}

            Spot::~Spot() {}

            Spot& Spot::operator=(const Spot &obj) {
                setIdentifier(obj.getIdentifier());
                setFirstVertex(obj.getFirstVertex());
                setSecondVertex(obj.getSecondVertex());
                return (*this);
            }

            void Spot::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_firstVertex.accept(visitor);
                m_secondVertex.accept(visitor);
            }

            uint32_t Spot::getIdentifier() const {
                return m_identifier;
            }

            void Spot::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            const Vertex3& Spot::getFirstVertex() const {
                return m_firstVertex;
            }

            void Spot::setFirstVertex(const Vertex3 &v) {
                m_firstVertex = v;
            }

            const Vertex3& Spot::getSecondVertex() const {
                return m_secondVertex;
            }

            void Spot::setSecondVertex(const Vertex3 &v) {
                m_secondVertex = v;
            }

            int32_t Spot::getID() const {
                return 837;
            }

            const string Spot::getShortName() const {
                return "Spot";
            }

            const string Spot::getLongName() const {
                return "hesperia.data.scenario.Spot";
            }

            const string Spot::toString() const {
                stringstream s;
                s << "ID: " << getIdentifier() << " @ " << m_firstVertex.toString() << "/" << m_secondVertex.toString();
                return s.str();
            }

            ostream& Spot::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getIdentifier());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('f', 'i', 'r', 's', 't') >::RESULT,
                        getFirstVertex());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('s', 'e', 'c', 'o', 'n', 'd') >::RESULT,
                        getSecondVertex());

                return out;
            }

            istream& Spot::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_identifier);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('f', 'i', 'r', 's', 't') >::RESULT,
                       m_firstVertex);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('s', 'e', 'c', 'o', 'n', 'd') >::RESULT,
                       m_secondVertex);

                return in;
            }

        }
    }
} // hesperia::data::scenario
