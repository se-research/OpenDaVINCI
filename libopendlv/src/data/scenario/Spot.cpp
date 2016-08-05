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
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Spot.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

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

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                s->write(2, getFirstVertex());

                s->write(3, getSecondVertex());

                return out;
            }

            istream& Spot::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                d->read(2, m_firstVertex);

                d->read(3, m_secondVertex);

                return in;
            }

        }
    }
} // opendlv::data::scenario
