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

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendavinci/core/data/SerializableData.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/Road.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/Zone.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
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

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        getName());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                        getIdentifier());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                        getHeight());

                uint32_t numberOfRoads = static_cast<uint32_t>(m_listOfRoads.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'r', 'o', 'a', 'd', 's') >::RESULT,
                        numberOfRoads);

                // Write roads to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfRoads; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfRoads.at(i);
                }

                // Write roads.
                if (numberOfRoads > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'o', 'a', 'd', 's') >::RESULT,
                            sstr.str());
                }

                uint32_t numberOfZones = static_cast<uint32_t>(m_listOfZones.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'z', 'o', 'n', 'e', 's') >::RESULT,
                        numberOfZones);

                // Write zones to stringstream.
                sstr.str("");
                for (uint32_t i = 0; i < numberOfZones; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfZones.at(i);
                }

                // Write zones.
                if (numberOfZones > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('z', 'o', 'n', 'e', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& Layer::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                m_listOfRoads.clear();
                m_listOfZones.clear();

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('i', 'd') >::RESULT,
                       m_identifier);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'i', 'g', 'h', 't') >::RESULT,
                       m_height);

                uint32_t numberOfRoads = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'r', 'o', 'a', 'd', 's') >::RESULT,
                       numberOfRoads);

                if (numberOfRoads > 0) {
                    string str;
                    // Read roads into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'o', 'a', 'd', 's') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read roads from stringstream.
                    for (uint32_t i = 0; i < numberOfRoads; i++) {
                        Road r;
                        sstr >> r;
                        addRoad(r);
                    }
                }

                uint32_t numberOfZones = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'z', 'o', 'n', 'e', 's') >::RESULT,
                       numberOfZones);

                if (numberOfZones > 0) {
                    string str;
                    // Read zones into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('z', 'o', 'n', 'e', 's') >::RESULT,
                           str);

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
} // hesperia::data::scenario
