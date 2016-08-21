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

#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/Header.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;

            Header::Header() :
                    m_name(""),
                    m_version(""),
                    m_date(""),
                    m_scenario("") {}

            Header::Header(const Header &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_version(obj.m_version),
                    m_date(obj.m_date),
                    m_scenario(obj.m_scenario) {}

            Header::~Header() {}

            Header& Header::operator=(const Header &obj) {
                setName(obj.getName());
                setVersion(obj.getVersion());
                setDate(obj.getDate());
                setScenario(obj.getScenario());
                return (*this);
            }

            void Header::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            const string Header::getName() const {
                return m_name;
            }

            void Header::setName(const string &name) {
                m_name = name;
            }

            const string Header::getVersion() const {
                return m_version;
            }

            void Header::setVersion(const string &v) {
                m_version = v;
            }

            const string Header::getDate() const {
                return m_date;
            }

            void Header::setDate(const string &d) {
                m_date = d;
            }

            const string Header::getScenario() const {
                return m_scenario;
            }

            void Header::setScenario(const string &scenario) {
                m_scenario = scenario;
            }

            int32_t Header::getID() const {
                return 855;
            }

            const string Header::getShortName() const {
                return "Header";
            }

            const string Header::getLongName() const {
                return "hesperia.data.situation.Header";
            }

            const string Header::toString() const {
                stringstream s;
                s << "Situation: '" << m_name << "', Version: " << m_version << ", Date: " << m_date << ", Scenario: " << m_scenario;
                return s.str();
            }

            ostream& Header::operator<<(ostream &out) const {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_name);

                s->write(2, m_version);

                s->write(3, m_date);

                s->write(4, m_scenario);

                return out;
            }

            istream& Header::operator>>(istream &in) {
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_name);

                d->read(2, m_version);

                d->read(3, m_date);

                d->read(4, m_scenario);

                return in;
            }

        }
    }
} // opendlv::data::situation
