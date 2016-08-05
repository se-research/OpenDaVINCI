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
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/base/Serializable.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/planning/Route.h"

namespace opendlv {
    namespace data {
        namespace planning {

            using namespace std;
            using namespace odcore::base;
            using namespace opendlv::data::environment;

            Route::Route() :
                m_listOfVertices() {}

            Route::Route(const vector<Point3> &vertices) :
                m_listOfVertices(vertices) {}

            Route::Route(const Route &obj) :
                m_listOfVertices(obj.m_listOfVertices) {}

            Route::~Route() {}

            Route& Route::operator=(const Route &obj) {
                m_listOfVertices = obj.m_listOfVertices;

                return (*this);
            }

            void Route::add(const Point3 &p) {
                m_listOfVertices.push_back(p);
            }

            uint32_t Route::getSize() const {
                return m_listOfVertices.size();
            }

            vector<Point3> Route::getListOfPoints() const {
                return m_listOfVertices;
            }

            double Route::getLength() const {
                double length = 0;

                if (m_listOfVertices.size() > 1) {
                    for (uint32_t i = 0; i < m_listOfVertices.size()-1; i++) {
                        length += m_listOfVertices.at(i).getDistanceTo(m_listOfVertices.at(i+1));
                    }
                }

                return length;
            }

            int32_t Route::ID() {
                return 38;
            }

            int32_t Route::getID() const {
                return 38;
            }

            const string Route::getShortName() const {
                return "Route";
            }

            const string Route::getLongName() const {
                return "hesperia.data.planning.Route";
            }

            const string Route::toString() const {
                stringstream sstr;
                sstr << "Route:";
                for (uint32_t i = 0; i < m_listOfVertices.size(); i++) {
                    sstr << " " << m_listOfVertices.at(i).toString();
                }
                return sstr.str();
            }

            ostream& Route::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                // Write number of vertices.
                uint32_t numberOfVertices = static_cast<uint32_t>(m_listOfVertices.size());
                s->write(1, numberOfVertices);

                // Write actual vertices to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfVertices; i++) {
                    sstr << m_listOfVertices.at(i);
                }

                // Write string of vertices.
                if (numberOfVertices > 0) {
                    s->write(2, sstr.str());
                }

                return out;
            }

            istream& Route::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                // Clean up.
                m_listOfVertices.clear();

                // Read number of vertices.
                uint32_t numberOfVertices = 0;
                d->read(1, numberOfVertices);

                if (numberOfVertices > 0) {
                    // Read string of vertices.
                    string vertices;
                    d->read(2, vertices);

                    stringstream sstr(vertices);

                    // Read actual vertices from stringstream.
                    for (uint32_t i = 0; i < numberOfVertices; i++) {
                        Point3 p;
                        sstr >> p;
                        add(p);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::planning
