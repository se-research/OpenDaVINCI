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
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
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
                    m_id(0),
                    m_name(""),
                    m_layer(NULL),
                    m_listOfConnectors(),
                    m_perimeter(),
                    m_listOfSpots() {}

            Zone::Zone(const Zone &obj) :
                    SerializableData(),
                    m_id(obj.getID()),
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
                setID(obj.getID());
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

            uint32_t Zone::getID() const {
                return m_id;
            }

            void Zone::setID(const uint32_t &id) {
                m_id = id;
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

            const string Zone::toString() const {
                stringstream s;
                s << "ID: " << getID() << ", Name: " << getName();
                return s.str();
            }

            ostream& Zone::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        getName());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'e', 'r', 'i', 'm', 't', 'e', 'r') >::RESULT,
                        getPerimeter());

                uint32_t numberOfConnectors = static_cast<uint32_t>(m_listOfConnectors.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'c', 'o', 'n', 'n', 's') >::RESULT,
                        numberOfConnectors);

                // Write connectors to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfConnectors; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfConnectors.at(i);
                }

                // Write connectors.
                if (numberOfConnectors > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'n', 'n', 's') >::RESULT,
                            sstr.str());
                }

                uint32_t numberOfSpots = static_cast<uint32_t>(m_listOfSpots.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 's', 'p', 'o', 't', 's') >::RESULT,
                        numberOfSpots);

                // Write spots to stringstream.
                sstr.str("");
                for (uint32_t i = 0; i < numberOfSpots; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfSpots.at(i);
                }

                // Write spots.
                if (numberOfSpots > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'p', 'o', 't', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& Zone::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('p', 'e', 'r', 'i', 'm', 't', 'e', 'r') >::RESULT,
                       m_perimeter);

                uint32_t numberOfConnectors = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'c', 'o', 'n', 'n', 's') >::RESULT,
                       numberOfConnectors);

                if (numberOfConnectors > 0) {
                    string str;
                    // Read connectors into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'n', 'n', 's') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read connectors from stringstream.
                    for (uint32_t i = 0; i < numberOfConnectors; i++) {
                        Connector c;
                        sstr >> c;
                        addConnector(c);
                    }
                }

                uint32_t numberOfSpots = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 's', 'p', 'o', 't', 's') >::RESULT,
                       numberOfSpots);

                if (numberOfSpots > 0) {
                    string str;
                    // Read spots into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 'p', 'o', 't', 's') >::RESULT,
                           str);

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
