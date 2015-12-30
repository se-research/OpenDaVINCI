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

#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/TrafficControl.h"
#include "hesperia/data/scenario/TrafficSign.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
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

            const string TrafficSign::toString() const {
                stringstream sstr;
                sstr << "Trafficsign: " << getValue();
                return sstr.str();
            }

            ostream& TrafficSign::operator<<(ostream &out) const {
                // Serializer super class.
                TrafficControl::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('v', 'a', 'l', 'u', 'e') >::RESULT,
                        getValue());

                return out;
            }

            istream& TrafficSign::operator>>(istream &in) {
                // Deserializer super class.
                TrafficControl::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('v', 'a', 'l', 'u', 'e') >::RESULT,
                       m_value);

                return in;
            }

        }
    }
} // hesperia::data::scenario
