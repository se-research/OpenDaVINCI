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
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/Perimeter.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Spot.h"
#include "opendlv/data/scenario/Zone.h"

namespace opendlv {
    namespace data {
        namespace scenario {

class Layer;

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Zone::Zone() :
                    m_identifier(0),
                    m_name(""),
                    m_layer(NULL),
                    m_listOfConnectors(),
                    m_perimeter(),
                    m_listOfSpots() {}

            Zone::Zone(const Zone &obj) :
                    SerializableData(),
                    m_identifier(obj.getIdentifier()),
                    m_name(obj.getName()),
                    m_layer(obj.getLayer()),
                    m_listOfConnectors(),
                    m_perimeter(obj.getPerimeter()),
                    m_listOfSpots() {
                // Create deep copy.
                deepCopy(obj);
            }

            Zone::~Zone() {}

            Zone& Zone::operator=(const Zone &obj) {
                setIdentifier(obj.getIdentifier());
                setName(obj.getName());
                setLayer(obj.getLayer());
                setPerimeter(obj.getPerimeter());

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Zone::deepCopy(const Zone &obj) {
                m_listOfConnectors.clear();
                const vector<Connector>& listOfConnectors = obj.getListOfConnectors();
                vector<Connector>::const_iterator it = listOfConnectors.begin();
                while (it != listOfConnectors.end()) {
                    addConnector((*it++));
                }

                m_listOfSpots.clear();
                const vector<Spot>& listOfSpots = obj.getListOfSpots();
                vector<Spot>::const_iterator jt = listOfSpots.begin();
                while (jt != listOfSpots.end()) {
                    addSpot((*jt++));
                }
            }

            void Zone::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_perimeter.accept(visitor);

                vector<Connector>::iterator it = m_listOfConnectors.begin();
                while (it != m_listOfConnectors.end()) {
                    (*it++).accept(visitor);
                }
                vector<Spot>::iterator jt = m_listOfSpots.begin();
                while (jt != m_listOfSpots.end()) {
                    (*jt++).accept(visitor);
                }
            }

            uint32_t Zone::getIdentifier() const {
                return m_identifier;
            }

            void Zone::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            const string Zone::getName() const {
                return m_name;
            }

            void Zone::setName(const string &name) {
                m_name = name;
            }

            const vector<Connector>& Zone::getListOfConnectors() const {
                return m_listOfConnectors;
            }

            void Zone::addConnector(const Connector &c) {
                m_listOfConnectors.push_back(c);
            }

            const Perimeter& Zone::getPerimeter() const {
                return m_perimeter;
            }

            void Zone::setPerimeter(const Perimeter &p) {
                m_perimeter = p;
            }

            const vector<Spot>& Zone::getListOfSpots() const {
                return m_listOfSpots;
            }

            void Zone::addSpot(const Spot &s) {
                m_listOfSpots.push_back(s);
            }

            void Zone::setLayer(const Layer *l) {
                m_layer = l;
            }

            const Layer* Zone::getLayer() const {
                return m_layer;
            }

            int32_t Zone::getID() const {
                return 833;
            }

            const string Zone::getShortName() const {
                return "Zone";
            }

            const string Zone::getLongName() const {
                return "hesperia.data.scenario.Zone";
            }

            const string Zone::toString() const {
                stringstream s;
                s << "ID: " << getIdentifier() << ", Name: " << getName();
                return s.str();
            }

            ostream& Zone::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                s->write(2, getName());

                s->write(3, getPerimeter());

                uint32_t numberOfConnectors = static_cast<uint32_t>(m_listOfConnectors.size());
                s->write(4, numberOfConnectors);

                // Write connectors to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfConnectors; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfConnectors.at(i);
                }

                // Write connectors.
                if (numberOfConnectors > 0) {
                    s->write(5, sstr.str());
                }

                uint32_t numberOfSpots = static_cast<uint32_t>(m_listOfSpots.size());
                s->write(6, numberOfSpots);

                // Write spots to stringstream.
                sstr.str("");
                for (uint32_t i = 0; i < numberOfSpots; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfSpots.at(i);
                }

                // Write spots.
                if (numberOfSpots > 0) {
                    s->write(7, sstr.str());
                }

                return out;
            }

            istream& Zone::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                d->read(2, m_name);

                d->read(3, m_perimeter);

                uint32_t numberOfConnectors = 0;
                d->read(4, numberOfConnectors);

                if (numberOfConnectors > 0) {
                    string str;
                    // Read connectors into stringstream.
                    d->read(5, str);

                    stringstream sstr(str);

                    // Read connectors from stringstream.
                    for (uint32_t i = 0; i < numberOfConnectors; i++) {
                        Connector c;
                        sstr >> c;
                        addConnector(c);
                    }
                }

                uint32_t numberOfSpots = 0;
                d->read(6, numberOfSpots);

                if (numberOfSpots > 0) {
                    string str;
                    // Read spots into stringstream.
                    d->read(7, str);

                    stringstream sstr(str);

                    // Read spots from stringstream.
                    for (uint32_t i = 0; i < numberOfSpots; i++) {
                        Spot s;
                        sstr >> s;
                        addSpot(s);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
