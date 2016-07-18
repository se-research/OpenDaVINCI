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

#include <ostream>
#include <string>

#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/TrafficControl.h"
#include "opendlv/data/scenario/TrafficSign.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            TrafficSign::TrafficSign() :
                    m_value("") {
                TrafficControl::setType(TrafficControl::TRAFFICSIGN);
            }

            TrafficSign::TrafficSign(const TrafficSign &obj) :
                    TrafficControl(obj),
                    m_value(obj.getValue()) {}

            TrafficSign::~TrafficSign() {}

            TrafficSign& TrafficSign::operator=(const TrafficSign &obj) {
                TrafficControl::operator=(obj);
                setValue(obj.getValue());

                return (*this);
            }

            void TrafficSign::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                if (getShape() != NULL) {
                    getShape()->accept(visitor);
                }
            }

            const string& TrafficSign::getValue() const {
                return m_value;
            }

            void TrafficSign::setValue(const string &v) {
                m_value = v;
            }

            int32_t TrafficSign::getID() const {
                return 821;
            }

            const string TrafficSign::getShortName() const {
                return "TrafficSign";
            }

            const string TrafficSign::getLongName() const {
                return "hesperia.data.scenario.TrafficSign";
            }

            const string TrafficSign::toString() const {
                stringstream sstr;
                sstr << "Trafficsign: " << getValue();
                return sstr.str();
            }

            ostream& TrafficSign::operator<<(ostream &out) const {
                // Serializer super class.
                TrafficControl::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('v', 'a', 'l', 'u', 'e') >::RESULT,
                        getValue());

                return out;
            }

            istream& TrafficSign::operator>>(istream &in) {
                // Deserializer super class.
                TrafficControl::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('v', 'a', 'l', 'u', 'e') >::RESULT,
                       m_value);

                return in;
            }

        }
    }
} // opendlv::data::scenario
