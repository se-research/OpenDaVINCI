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
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            IDVertex3::IDVertex3() :
                    Vertex3(),
                    m_identifier(0) {}

            IDVertex3::IDVertex3(const IDVertex3 &obj) :
                    Vertex3(obj),
                    m_identifier(obj.getIdentifier()) {}

            IDVertex3::~IDVertex3() {}

            IDVertex3& IDVertex3::operator=(const IDVertex3 &obj) {
                Vertex3::operator=(obj);
                setIdentifier(obj.getIdentifier());

                return (*this);
            }

            void IDVertex3::accept(ScenarioVisitor &visitor) {
                Vertex3::accept(visitor);
                visitor.visit(*this);
            }

            uint32_t IDVertex3::getIdentifier() const {
                return m_identifier;
            }

            void IDVertex3::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            int32_t IDVertex3::getID() const {
                return 818;
            }

            const string IDVertex3::getShortName() const {
                return "IDVertex3";
            }

            const string IDVertex3::getLongName() const {
                return "hesperia.data.scenario.IDVertex3";
            }

            const string IDVertex3::toString() const {
                stringstream s;
                s << "ID: " << getIdentifier() << ": " << Vertex3::toString();
                return s.str();
            }

            ostream& IDVertex3::operator<<(ostream &out) const {
                // Serializer super class.
                Vertex3::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                return out;
            }

            istream& IDVertex3::operator>>(istream &in) {
                // Deserializer super class.
                Vertex3::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                return in;
            }

        }
    }
} // opendlv::data::scenario
