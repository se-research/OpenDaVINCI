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
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/situation/OnEnteringPolygon.h"
#include "opendlv/data/situation/SituationVisitor.h"
#include "opendlv/data/situation/StartType.h"
#include "opendlv/data/situation/Vertex3.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            OnEnteringPolygon::OnEnteringPolygon() :
                    StartType(),
                    m_identifier(0),
                    m_listOfVertices() {
                setType(StartType::ONENTERINGPOLYGON);
            }

            OnEnteringPolygon::OnEnteringPolygon(const OnEnteringPolygon &obj) :
                    StartType(obj),
                    m_identifier(obj.getIdentifier()),
                    m_listOfVertices() {
                deepCopy(obj);
            }

            OnEnteringPolygon::~OnEnteringPolygon() {}

            OnEnteringPolygon& OnEnteringPolygon::operator=(const OnEnteringPolygon &obj) {
                StartType::operator=(obj);
                setIdentifier(obj.getIdentifier());
                deepCopy(obj);
                return (*this);
            }

            void OnEnteringPolygon::deepCopy(const OnEnteringPolygon &obj) {
                m_listOfVertices.clear();
                const vector<Vertex3> &listOfVertices = obj.getListOfVertices();
                vector<Vertex3>::const_iterator it = listOfVertices.begin();
                while (it != listOfVertices.end()) {
                    add((*it++));
                }
            }

            void OnEnteringPolygon::accept(SituationVisitor &visitor) {
                visitor.visit(*this);

                vector<Vertex3>::iterator it = m_listOfVertices.begin();
                while (it != m_listOfVertices.end()) {
                    (*it).accept(visitor);
                    it++;
                }
            }

            uint32_t OnEnteringPolygon::getIdentifier() const {
                return m_identifier;
            }

            void OnEnteringPolygon::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            const vector<Vertex3>& OnEnteringPolygon::getListOfVertices() const {
                return m_listOfVertices;
            }

            void OnEnteringPolygon::add(const Vertex3 &v) {
                m_listOfVertices.push_back(v);
            }

            int32_t OnEnteringPolygon::getID() const {
                return 867;
            }

            const string OnEnteringPolygon::getShortName() const {
                return "OnEnteringPolygon";
            }

            const string OnEnteringPolygon::getLongName() const {
                return "hesperia.data.situation.OnEnteringPolygon";
            }

            const string OnEnteringPolygon::toString() const {
                stringstream s;
                s << "Type: " << getType() << " on entering ID: " << getIdentifier();
                return s.str();
            }

            ostream& OnEnteringPolygon::operator<<(ostream &out) const {
                // Serializer super class.
                StartType::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getIdentifier());

                // Write number of vertices.
                uint32_t numberOfVertices = static_cast<uint32_t>(m_listOfVertices.size());
                s->write(2, numberOfVertices);

                // Write actual vertices to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfVertices; i++) {
                    sstr << m_listOfVertices.at(i);
                }

                // Write string of vertices.
                if (numberOfVertices > 0) {
                    s->write(3, sstr.str());
                }

                return out;
            }

            istream& OnEnteringPolygon::operator>>(istream &in) {
                // Deserializer super class.
                StartType::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                // Read number of vertices.
                uint32_t numberOfVertices = 0;
                d->read(2, numberOfVertices);

                if (numberOfVertices > 0) {
                    // Read string of vertices.
                    string vertices;
                    d->read(3, vertices);

                    stringstream sstr(vertices);

                    // Read actual vertices from stringstream.
                    for (uint32_t i = 0; i < numberOfVertices; i++) {
                        Vertex3 v;
                        sstr >> v;
                        add(v);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::situation
