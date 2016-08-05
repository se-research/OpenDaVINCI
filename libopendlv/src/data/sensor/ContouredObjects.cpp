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
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/sensor/ContouredObject.h"
#include "opendlv/data/sensor/ContouredObjects.h"

namespace opendlv {
    namespace data {
        namespace sensor {

            using namespace std;
            using namespace odcore::base;

            ContouredObjects::ContouredObjects() :
                    m_contouredObjects(), m_color(RED) {}

            ContouredObjects::ContouredObjects(const ContouredObjects &obj) :
                    SerializableData(),
                    m_contouredObjects(obj.m_contouredObjects),
                    m_color(obj.m_color) {}

            ContouredObjects::~ContouredObjects() {
                reset();
            }

            ContouredObjects& ContouredObjects::operator=(const ContouredObjects &obj) {
                m_contouredObjects = obj.m_contouredObjects;
                setColor(obj.getColor());

                return (*this);
            }
            const vector<ContouredObject> ContouredObjects::getContouredObjects() const {
                return m_contouredObjects;
            }

            void ContouredObjects::add(const ContouredObject &contouredObject) {
                m_contouredObjects.push_back(contouredObject);
            }

            void ContouredObjects::reset() {
                m_contouredObjects.clear();
            }

            enum ContouredObjects::COLOR ContouredObjects::getColor() const {
                return m_color;
            }

            void ContouredObjects::setColor(const enum ContouredObjects::COLOR &color) {
                m_color = color;
            }

            int32_t ContouredObjects::ID() {
                return 31;
            }

            int32_t ContouredObjects::getID() const {
                return 31;
            }

            const string ContouredObjects::getShortName() const {
                return "ContouredObjects";
            }

            const string ContouredObjects::getLongName() const {
                return "hesperia.data.sensor.ContouredObjects";
            }

            const string ContouredObjects::toString() const {
                stringstream s;
                s << "Containing " << static_cast<uint32_t>(m_contouredObjects.size()) << " contoured objects.";
                return s.str();
            }

            ostream& ContouredObjects::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                // Write contoured objects.
                s->write(1, static_cast<uint32_t>(m_contouredObjects.size()));

                // Contour.
                stringstream sstr;
                vector<ContouredObject>::const_iterator it = m_contouredObjects.begin();
                while (it != m_contouredObjects.end()) {
                    sstr << (*it++);
                }
                s->write(2, sstr.str());

                // Color.
                s->write(3, static_cast<uint32_t>(m_color));

                return out;
            }

            istream& ContouredObjects::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Read contoured objects.
                uint32_t numberOfContouredObjects = 0;
                d->read(1, numberOfContouredObjects);
                reset();

                string contour;
                d->read(2, contour);
                stringstream sstr;
                sstr.str(contour);
                while (numberOfContouredObjects > 0) {
                    ContouredObject co;
                    sstr >> co;
                    m_contouredObjects.push_back(co);
                    numberOfContouredObjects--;
                }

                uint32_t color = 0;
                d->read(3, color);
                m_color = static_cast<enum COLOR>(color);

                return in;
            }

        }
    }
} // opendlv::data::sensor
