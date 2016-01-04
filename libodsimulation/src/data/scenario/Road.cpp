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
#include <vector>

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/Serializable.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/Lane.h"
#include "hesperia/data/scenario/Road.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

class Layer;

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            Road::Road() :
                    m_id(0),
                    m_name(""),
                    m_layer(NULL),
                    m_listOfLanes() {}

            Road::Road(const Road &obj) :
                    SerializableData(),
                    m_id(obj.getID()),
                    m_name(obj.getName()),
                    m_layer(obj.getLayer()),
                    m_listOfLanes() {
                // Create deep copy.
                deepCopy(obj);
            }

            Road::~Road() {}

            Road& Road::operator=(const Road &obj) {
                setID(obj.getID());
                setName(obj.getName());
                setLayer(obj.getLayer());

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Road::deepCopy(const Road &obj) {
                m_listOfLanes.clear();
                const vector<Lane>& list = obj.getListOfLanes();
                vector<Lane>::const_iterator it = list.begin();
                while (it != list.end()) {
                    addLane((*it++));
                }
            }

            void Road::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                vector<Lane>::iterator it = m_listOfLanes.begin();
                while (it != m_listOfLanes.end()) {
                    (*it++).accept(visitor);
                }
            }

            uint32_t Road::getID() const {
                return m_id;
            }

            void Road::setID(const uint32_t &id) {
                m_id = id;
            }

            const string Road::getName() const {
                return m_name;
            }

            void Road::setName(const string &name) {
                m_name = name;
            }

            const vector<Lane>& Road::getListOfLanes() const {
                return m_listOfLanes;
            }

            void Road::addLane(const Lane &l) {
                // Ugly, but necessary :-(
                const_cast<Lane&>(l).setRoad(this);
                m_listOfLanes.push_back(l);
            }

            const string Road::toString() const {
                stringstream s;
                s << "ID: " << getID() << ", Name: " << getName();
                return s.str();
            }

            void Road::setLayer(const Layer *l) {
                m_layer = l;
            }

            const Layer* Road::getLayer() const {
                return m_layer;
            }

            ostream& Road::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getID());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        getName());

                uint32_t numberOfLanes = static_cast<uint32_t>(m_listOfLanes.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'l', 'a', 'n', 'e', 's') >::RESULT,
                        numberOfLanes);

                // Write lanes to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfLanes; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfLanes.at(i);
                }

                // Write lanes.
                if (numberOfLanes > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 'n', 'e', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& Road::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                m_listOfLanes.clear();

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_id);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                uint32_t numberOfLanes = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'l', 'a', 'n', 'e', 's') >::RESULT,
                       numberOfLanes);

                if (numberOfLanes > 0) {
                    string str;
                    // Read lanes into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 'n', 'e', 's') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read lanes from stringstream.
                    for (uint32_t i = 0; i < numberOfLanes; i++) {
                        Lane l;
                        sstr >> l;
                        addLane(l);
                    }
                }

                return in;
            }

        }
    }
} // hesperia::data::scenario
