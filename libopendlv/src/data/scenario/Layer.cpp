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
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/Road.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/Zone.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Layer::Layer() :
                    m_name(""),
                    m_identifier(0),
                    m_height(0),
                    m_listOfRoads(),
                    m_listOfZones() {}

            Layer::Layer(const Layer &obj) :
                    SerializableData(),
                    m_name(obj.getName()),
                    m_identifier(obj.getIdentifier()),
                    m_height(obj.getHeight()),
                    m_listOfRoads(),
                    m_listOfZones() {
                // Create deep copy.
                deepCopy(obj);
            }

            Layer::~Layer() {}

            Layer& Layer::operator=(const Layer &obj) {
                setName(obj.getName());
                setIdentifier(obj.getIdentifier());
                setHeight(obj.getHeight());

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Layer::deepCopy(const Layer &obj) {
                m_listOfRoads.clear();
                const vector<Road>& listOfRoads = obj.getListOfRoads();
                vector<Road>::const_iterator it = listOfRoads.begin();
                while (it != listOfRoads.end()) {
                    addRoad((*it++));
                }

                m_listOfZones.clear();
                const vector<Zone>& listOfZones = obj.getListOfZones();
                vector<Zone>::const_iterator jt = listOfZones.begin();
                while (jt != listOfZones.end()) {
                    addZone((*jt++));
                }
            }

            void Layer::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                vector<Road>::iterator it = m_listOfRoads.begin();
                while (it != m_listOfRoads.end()) {
                    (*it++).accept(visitor);
                }

                vector<Zone>::iterator jt = m_listOfZones.begin();
                while (jt != m_listOfZones.end()) {
                    (*jt++).accept(visitor);
                }
            }

            const string Layer::getName() const {
                return m_name;
            }

            void Layer::setName(const string &name) {
                m_name = name;
            }

            uint32_t Layer::getIdentifier() const {
                return m_identifier;
            }

            void Layer::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            double Layer::getHeight() const {
                return m_height;
            }

            void Layer::setHeight(const double &h) {
                m_height = h;
            }

            const vector<Road>& Layer::getListOfRoads() const {
                return m_listOfRoads;
            }

            void Layer::addRoad(const Road &r) {
                // Ugly, but necessary :-(
                const_cast<Road&>(r).setLayer(this);
                m_listOfRoads.push_back(r);
            }

            const vector<Zone>& Layer::getListOfZones() const {
                return m_listOfZones;
            }

            void Layer::addZone(const Zone &z) {
                // Ugly, but necessary :-(
                const_cast<Zone&>(z).setLayer(this);
                m_listOfZones.push_back(z);
            }

            int32_t Layer::getID() const {
                return 839;
            }

            const string Layer::getShortName() const {
                return "Layer";
            }

            const string Layer::getLongName() const {
                return "hesperia.data.scenario.Layer";
            }

            const string Layer::toString() const {
                stringstream s;
                s << "Name: " << getName() << ", ID: " << getIdentifier() << ", Height: " << getHeight();
                return s.str();
            }

            ostream& Layer::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getName());

                s->write(2, getIdentifier());

                s->write(3, getHeight());

                uint32_t numberOfRoads = static_cast<uint32_t>(m_listOfRoads.size());
                s->write(4, numberOfRoads);

                // Write roads to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfRoads; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfRoads.at(i);
                }

                // Write roads.
                if (numberOfRoads > 0) {
                    s->write(5, sstr.str());
                }

                uint32_t numberOfZones = static_cast<uint32_t>(m_listOfZones.size());
                s->write(6, numberOfZones);

                // Write zones to stringstream.
                sstr.str("");
                for (uint32_t i = 0; i < numberOfZones; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfZones.at(i);
                }

                // Write zones.
                if (numberOfZones > 0) {
                    s->write(7, sstr.str());
                }

                return out;
            }

            istream& Layer::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Clean up.
                m_listOfRoads.clear();
                m_listOfZones.clear();

                d->read(1, m_name);

                d->read(2, m_identifier);

                d->read(3, m_height);

                uint32_t numberOfRoads = 0;
                d->read(4, numberOfRoads);

                if (numberOfRoads > 0) {
                    string str;
                    // Read roads into stringstream.
                    d->read(5, str);

                    stringstream sstr(str);

                    // Read roads from stringstream.
                    for (uint32_t i = 0; i < numberOfRoads; i++) {
                        Road r;
                        sstr >> r;
                        addRoad(r);
                    }
                }

                uint32_t numberOfZones = 0;
                d->read(6, numberOfZones);

                if (numberOfZones > 0) {
                    string str;
                    // Read zones into stringstream.
                    d->read(7, str);

                    stringstream sstr(str);

                    // Read zones from stringstream.
                    for (uint32_t i = 0; i < numberOfZones; i++) {
                        Zone z;
                        sstr >> z;
                        addZone(z);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
