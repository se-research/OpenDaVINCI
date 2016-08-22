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
#include "opendlv/data/situation/Header.h"
#include "opendlv/data/situation/Object.h"
#include "opendlv/data/situation/Situation.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            Situation::Situation() :
                    m_header(),
                    m_listOfObjects() {}

            Situation::Situation(const Situation &obj) :
                    SerializableData(),
                    m_header(obj.m_header),
                    m_listOfObjects() {
                // Create deep copy.
                deepCopy(obj);
            }

            Situation::~Situation() {}

            Situation& Situation::operator=(const Situation &obj) {
                setHeader(obj.getHeader());

                // Create deep copy.
                deepCopy(obj);

                return (*this);
            }

            void Situation::deepCopy(const Situation &obj) {
                m_listOfObjects.clear();
                const vector<Object>& list = obj.getListOfObjects();
                vector<Object>::const_iterator it = list.begin();
                while (it != list.end()) {
                    addObject((*it++));
                }
            }

            void Situation::accept(SituationVisitor &visitor) {
                visitor.visit(*this);

                m_header.accept(visitor);

                vector<Object>::iterator it = m_listOfObjects.begin();
                while (it != m_listOfObjects.end()) {
                    (*it++).accept(visitor);
                }
            }

            const Header& Situation::getHeader() const {
                return m_header;
            }

            void Situation::setHeader(const Header &h) {
                m_header = h;
            }

            const vector<Object>& Situation::getListOfObjects() const {
                return m_listOfObjects;
            }

            void Situation::addObject(const Object &o) {
                m_listOfObjects.push_back(o);
            }

            int32_t Situation::getID() const {
                return 851;
            }

            const string Situation::getShortName() const {
                return "Situation";
            }

            const string Situation::getLongName() const {
                return "hesperia.data.situation.Situation";
            }

            const string Situation::toString() const {
                return m_header.toString();
            }

            ostream& Situation::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_header);

                uint32_t numberOfObjects = static_cast<uint32_t>(m_listOfObjects.size());
                s->write(2, numberOfObjects);

                // Write roads to stringstream.
                stringstream sstr;
                for (uint32_t i = 0; i < numberOfObjects; i++) {
                    // Write data to stringstream.
                    sstr << m_listOfObjects.at(i);
                }

                // Write objects.
                if (numberOfObjects > 0) {
                    s->write(3, sstr.str());
                }

                return out;
            }

            istream& Situation::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_header);

                uint32_t numberOfObjects = 0;
                d->read(2, numberOfObjects);

                if (numberOfObjects > 0) {
                    string str;
                    // Read layers into stringstream.
                    d->read(3, str);

                    stringstream sstr(str);

                    // Read layer from stringstream.
                    for (uint32_t i = 0; i < numberOfObjects; i++) {
                        Object o;
                        sstr >> o;
                        addObject(o);
                    }
                }

                return in;
            }

        }
    }
} // opendlv::data::situation
