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

#include "core/macros.h"
#include "core/base/Hash.h"
#include "core/base/Deserializer.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/TrafficLight.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            TrafficLight::TrafficLight() {
                TrafficControl::setType(TrafficControl::TRAFFICLIGHT);
            }

            TrafficLight::TrafficLight(const TrafficLight &obj) :
                    TrafficControl(obj) {}

            TrafficLight::~TrafficLight() {}

            TrafficLight& TrafficLight::operator=(const TrafficLight &obj) {
                TrafficControl::operator=(obj);

                return (*this);
            }

            void TrafficLight::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                if (getShape() != NULL) {
                    getShape()->accept(visitor);
                }
            }

            int32_t TrafficLight::getID() const {
                return 822;
            }

            const string TrafficLight::getShortName() const {
                return "TrafficLight";
            }

            const string TrafficLight::getLongName() const {
                return "hesperia.data.scenario.TrafficLight";
            }

            const string TrafficLight::toString() const {
                return "Trafficlight";
            }

            ostream& TrafficLight::operator<<(ostream &out) const {
                // Serializer super class.
                TrafficControl::operator<<(out);

                return out;
            }

            istream& TrafficLight::operator>>(istream &in) {
                // Deserializer super class.
                TrafficControl::operator>>(in);

                return in;
            }

        }
    }
} // hesperia::data::scenario
