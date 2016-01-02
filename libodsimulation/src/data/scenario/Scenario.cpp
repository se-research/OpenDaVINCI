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

#include <iosfwd>
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
#include "hesperia/data/scenario/Ground.h"
#include "hesperia/data/scenario/Header.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;

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

            const string Scenario::toString() const {
                return "";
            }

            ostream& Scenario::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'a', 'd', 'e', 'r') >::RESULT,
                        m_header);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('g', 'r', 'o', 'u', 'n', 'd') >::RESULT,
                        m_ground);

                uint32_t numberOfLayers = static_cast<uint32_t>(m_listOfLayers.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'l', 'a', 'y', 'e', 'r') >::RESULT,
                        numberOfLayers);

                // Write roads to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfLayers; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfLayers.at(i);
                }

                // Write layers.
                if (numberOfLayers > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'a', 'y', 'e', 'r', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& Scenario::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                m_listOfLayers.clear();

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('h', 'e', 'a', 'd', 'e', 'r') >::RESULT,
                       m_header);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('g', 'r', 'o', 'u', 'n', 'd') >::RESULT,
                       m_ground);

                uint32_t numberOfLayers = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL8('n', 'u', 'm', 'l', 'a', 'y', 'e', 'r') >::RESULT,
                       numberOfLayers);

                if (numberOfLayers > 0) {
                    string str;
                    // Read layers into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'a', 'y', 'e', 'r', 's') >::RESULT,
                           str);

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
} // hesperia::data::scenario
