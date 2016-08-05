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
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Lane.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

class Layer;

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Road::Road() :
                    m_identifier(0),
                    m_name(""),
                    m_layer(NULL),
                    m_listOfLanes() {}

            Road::Road(const Road &obj) :
                    SerializableData(),
                    m_identifier(obj.getIdentifier()),
                    m_name(obj.getName()),
                    m_layer(obj.getLayer()),
                    m_listOfLanes() {
                // Create deep copy.
                deepCopy(obj);
            }

            Road::~Road() {}

            Road& Road::operator=(const Road &obj) {
                setIdentifier(obj.getIdentifier());
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

            uint32_t Road::getIdentifier() const {
                return m_identifier;
            }

            void Road::setIdentifier(const uint32_t &id) {
                m_identifier = id;
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

            int32_t Road::getID() const {
                return 847;
            }

            const string Road::getShortName() const {
                return "Road";
            }

            const string Road::getLongName() const {
                return "hesperia.data.scenario.Road";
            }

            const string Road::toString() const {
                stringstream s;
                s << "ID: " << getIdentifier() << ", Name: " << getName();
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

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                s->write(2, getName());

                uint32_t numberOfLanes = static_cast<uint32_t>(m_listOfLanes.size());
                s->write(3, numberOfLanes);

                // Write lanes to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfLanes; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfLanes.at(i);
                }

                // Write lanes.
                if (numberOfLanes > 0) {
                    s->write(4, sstr.str());
                }

                return out;
            }

            istream& Road::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Clean up.
                m_listOfLanes.clear();

                d->read(1, m_identifier);

                d->read(2, m_name);

                uint32_t numberOfLanes = 0;
                d->read(3, numberOfLanes);

                if (numberOfLanes > 0) {
                    string str;
                    // Read lanes into stringstream.
                    d->read(4, str);

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
} // opendlv::data::scenario
