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

#include <iosfwd>
#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/Serializable.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Ground.h"
#include "opendlv/data/scenario/Header.h"
#include "opendlv/data/scenario/Layer.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            Scenario::Scenario() :
                    m_header(),
                    m_ground(),
                    m_listOfLayers() {}

            Scenario::Scenario(const Scenario &obj) :
                    SerializableData(),
                    m_header(obj.m_header),
                    m_ground(obj.m_ground),
                    m_listOfLayers() {
                // Create deep copy.
                deepCopy(obj);
            }

            Scenario::~Scenario() {}

            Scenario& Scenario::operator=(const Scenario &obj) {
                setHeader(obj.getHeader());
                setGround(obj.getGround());

                // Create deep copy.

                deepCopy(obj);
                return (*this);
            }

            void Scenario::deepCopy(const Scenario &obj) {
                m_listOfLayers.clear();
                const vector<Layer>& list = obj.getListOfLayers();
                vector<Layer>::const_iterator it = list.begin();
                while (it != list.end()) {
                    addLayer((*it++));
                }
            }

            void Scenario::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_header.accept(visitor);
                m_ground.accept(visitor);

                vector<Layer>::iterator it = m_listOfLayers.begin();
                while (it != m_listOfLayers.end()) {
                    (*it++).accept(visitor);
                }
            }

            const Header& Scenario::getHeader() const {
                return m_header;
            }

            void Scenario::setHeader(const Header &h) {
                m_header = h;
            }

            const Ground& Scenario::getGround() const {
                return m_ground;
            }

            void Scenario::setGround(const Ground &g) {
                m_ground = g;
            }

            const vector<Layer>& Scenario::getListOfLayers() const {
                return m_listOfLayers;
            }

            void Scenario::addLayer(const Layer &l) {
                m_listOfLayers.push_back(l);
            }

            int32_t Scenario::getID() const {
                return 830;
            }

            const string Scenario::getShortName() const {
                return "Scenario";
            }

            const string Scenario::getLongName() const {
                return "hesperia.data.scenario.Scenario";
            }

            const string Scenario::toString() const {
                return "";
            }

            ostream& Scenario::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_header);

                s->write(2, m_ground);

                uint32_t numberOfLayers = static_cast<uint32_t>(m_listOfLayers.size());
                s->write(3, numberOfLayers);

                // Write roads to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfLayers; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfLayers.at(i);
                }

                // Write layers.
                if (numberOfLayers > 0) {
                    s->write(4, sstr.str());
                }

                return out;
            }

            istream& Scenario::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Clean up.
                m_listOfLayers.clear();

                d->read(1, m_header);

                d->read(2, m_ground);

                uint32_t numberOfLayers = 0;
                d->read(3, numberOfLayers);

                if (numberOfLayers > 0) {
                    string str;
                    // Read layers into stringstream.
                    d->read(4, str);

                    stringstream sstr(str);

                    // Read layer from stringstream.
                    for (uint32_t i = 0; i < numberOfLayers; i++) {
                        Layer l;
                        sstr >> l;
                        addLayer(l);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
