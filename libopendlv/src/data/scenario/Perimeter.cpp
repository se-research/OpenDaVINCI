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
#include <iosfwd>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/Perimeter.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Perimeter::Perimeter() :
                    m_listOfIdentifiableVertices() {}

            Perimeter::Perimeter(const Perimeter &obj) :
                    SerializableData(),
                    m_listOfIdentifiableVertices() {
                // Create deep copy.
                deepCopy(obj);
            }

            Perimeter::~Perimeter() {}

            Perimeter& Perimeter::operator=(const Perimeter &obj) {
                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Perimeter::deepCopy(const Perimeter &obj) {
                m_listOfIdentifiableVertices.clear();
                const vector<IDVertex3>& list = obj.getListOfIdentifiableVertices();
                vector<IDVertex3>::const_iterator it = list.begin();
                while (it != list.end()) {
                    addIdentifiableVertex((*it++));
                }
            }

            void Perimeter::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                vector<IDVertex3>::iterator it = m_listOfIdentifiableVertices.begin();
                while (it != m_listOfIdentifiableVertices.end()) {
                    (*it++).accept(visitor);
                }
            }

            const vector<IDVertex3>& Perimeter::getListOfIdentifiableVertices() const {
                return m_listOfIdentifiableVertices;
            }

            void Perimeter::addIdentifiableVertex(const IDVertex3 &idV) {
                m_listOfIdentifiableVertices.push_back(idV);
            }

            int32_t Perimeter::getID() const {
                return 845;
            }

            const string Perimeter::getShortName() const {
                return "Perimeter";
            }

            const string Perimeter::getLongName() const {
                return "hesperia.data.scenario.Perimeter";
            }

            const string Perimeter::toString() const {
                return "";
            }

            ostream& Perimeter::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                uint32_t numberOfIDVertices = static_cast<uint32_t>(m_listOfIdentifiableVertices.size());
                s->write(1, numberOfIDVertices);

                // Write lanes to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfIDVertices; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfIdentifiableVertices.at(i);
                }

                // Write lanes.
                if (numberOfIDVertices > 0) {
                    s->write(2, sstr.str());
                }

                return out;
            }

            istream& Perimeter::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Clean up.
                m_listOfIdentifiableVertices.clear();

                uint32_t numberOfIDVertices = 0;
                d->read(1, numberOfIDVertices);

                if (numberOfIDVertices > 0) {
                    string str;
                    // Read lanes into stringstream.
                    d->read(2, str);

                    stringstream sstr(str);

                    // Read lanes from stringstream.
                    for (uint32_t i = 0; i < numberOfIDVertices; i++) {
                        IDVertex3 idV;
                        sstr >> idV;
                        addIdentifiableVertex(idV);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::scenario
