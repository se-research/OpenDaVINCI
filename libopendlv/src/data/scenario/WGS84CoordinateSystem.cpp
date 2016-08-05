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
#include "opendlv/data/scenario/CoordinateSystem.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Vertex3.h"
#include "opendlv/data/scenario/WGS84CoordinateSystem.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            WGS84CoordinateSystem::WGS84CoordinateSystem() :
                    m_origin() {}

            WGS84CoordinateSystem::WGS84CoordinateSystem(const WGS84CoordinateSystem &obj) :
                    CoordinateSystem(obj),
                    m_origin(obj.m_origin) {}

            WGS84CoordinateSystem::~WGS84CoordinateSystem() {}

            WGS84CoordinateSystem& WGS84CoordinateSystem::operator=(const WGS84CoordinateSystem &obj) {
                CoordinateSystem::operator=(obj);
                setOrigin(obj.getOrigin());
                return (*this);
            }

            void WGS84CoordinateSystem::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_origin.accept(visitor);
            }

            const Vertex3 WGS84CoordinateSystem::getOrigin() const {
                return m_origin;
            }

            void WGS84CoordinateSystem::setOrigin(const Vertex3 &o) {
                m_origin = o;
            }

            int32_t WGS84CoordinateSystem::getID() const {
                return 849;
            }

            const string WGS84CoordinateSystem::getShortName() const {
                return "WGS84CoordinateSystem";
            }

            const string WGS84CoordinateSystem::getLongName() const {
                return "hesperia.data.scenario.WGS84CoordinateSystem";
            }

            const string WGS84CoordinateSystem::toString() const {
                stringstream s;
                s << CoordinateSystem::toString() << ", " << m_origin.toString();
                return s.str();
            }

            ostream& WGS84CoordinateSystem::operator<<(ostream &out) const {
                // Serializer super class.
                CoordinateSystem::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_origin);

                return out;
            }

            istream& WGS84CoordinateSystem::operator>>(istream &in) {
                // Deserializer super class.
                CoordinateSystem::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_origin);

                return in;
            }

        }
    }
} // opendlv::data::scenario
