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
#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/Serializable.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/PointModel.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            PointModel::PointModel() :
                    m_listOfIdentifiableVertices() {
                LaneModel::setType(LaneModel::POINTMODEL);
            }

            PointModel::PointModel(const PointModel &obj) :
                    LaneModel(obj),
                    m_listOfIdentifiableVertices() {
                // Create deep copy.
                deepCopy(obj);
            }

            PointModel::~PointModel() {}

            PointModel& PointModel::operator=(const PointModel &obj) {
                LaneModel::operator=(obj);

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void PointModel::deepCopy(const PointModel &obj) {
                m_listOfIdentifiableVertices.clear();
                const vector<IDVertex3>& list = obj.getListOfIdentifiableVertices();
                vector<IDVertex3>::const_iterator it = list.begin();
                while (it != list.end()) {
                    addIdentifiableVertex((*it++));
                }
            }

            void PointModel::accept(ScenarioVisitor &visitor) {
                LaneModel::accept(visitor);
                visitor.visit(*this);

                vector<IDVertex3>::iterator it = m_listOfIdentifiableVertices.begin();
                while (it != m_listOfIdentifiableVertices.end()) {
                    (*it++).accept(visitor);
                }
            }

            const vector<IDVertex3>& PointModel::getListOfIdentifiableVertices() const {
                return m_listOfIdentifiableVertices;
            }

            const IDVertex3 PointModel::getIDVertex3(const uint32_t &id) const throw (core::exceptions::InvalidArgumentException) {
                bool found = false;
                IDVertex3 retVal;
                vector<IDVertex3>::const_iterator it = m_listOfIdentifiableVertices.begin();
                while (it != m_listOfIdentifiableVertices.end()) {
                    retVal = (*it++);
                    if (retVal.getID() == id) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Invalid ID given.");
                }
                return retVal;
            }


            void PointModel::addIdentifiableVertex(const IDVertex3 &idV) {
                m_listOfIdentifiableVertices.push_back(idV);
            }

            const string PointModel::toString() const {
                return "";
            }

            ostream& PointModel::operator<<(ostream &out) const {
                // Serializer super class.
                LaneModel::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                uint32_t numberOfIdentifiableVertices = static_cast<uint32_t>(m_listOfIdentifiableVertices.size());
                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'u', 'm', 'i', 'd', 'v', 's') >::RESULT,
                        numberOfIdentifiableVertices);

                // Write identifiable vertices to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfIdentifiableVertices; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfIdentifiableVertices.at(i);
                }

                // Write identifiable vertices.
                if (numberOfIdentifiableVertices > 0) {
                    s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('i', 'd', 'v', 's') >::RESULT,
                            sstr.str());
                }

                return out;
            }

            istream& PointModel::operator>>(istream &in) {
                // Deserializer super class.
                LaneModel::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                // Clean up.
                m_listOfIdentifiableVertices.clear();

                uint32_t numberOfIdentifiableVertices = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('n', 'u', 'm', 'i', 'd', 'v', 's') >::RESULT,
                       numberOfIdentifiableVertices);

                if (numberOfIdentifiableVertices > 0) {
                    string str;
                    // Read identifiable vertices into stringstream.
                    d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('i', 'd', 'v', 's') >::RESULT,
                           str);

                    stringstream sstr(str);

                    // Read identifiable vertices from stringstream.
                    for (uint32_t i = 0; i < numberOfIdentifiableVertices; i++) {
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
