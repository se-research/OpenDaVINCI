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
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/PointID.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
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

            int32_t Connector::getID() const {
                return 836;
            }

            const string Connector::getShortName() const {
                return "Connector";
            }

            const string Connector::getLongName() const {
                return "hesperia.data.scenario.Connector";
            }

            const string Connector::toString() const {
                stringstream s;
                s << "(" << getSource().toString() << ")" << " -> " << "(" << getTarget().toString() << ")";
                return s.str();
            }

            ostream& Connector::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getSource());

                s->write(2, getTarget());

                return out;
            }

            istream& Connector::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_source);

                d->read(2, m_target);

                return in;
            }

        }
    }
} // opendlv::data::scenario
