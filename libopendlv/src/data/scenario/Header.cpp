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

#include <ostream>
#include <string>

#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/Header.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/WGS84CoordinateSystem.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Header::Header() :
                    m_name(""),
                    m_version(""),
                    m_date(""),
                    m_coordinateSystem() {}

            Header::Header(const Header &obj) :
                    SerializableData(),
                    m_name(obj.m_name),
                    m_version(obj.m_version),
                    m_date(obj.m_date),
                    m_coordinateSystem(obj.m_coordinateSystem) {}

            Header::~Header() {}

            Header& Header::operator=(const Header &obj) {
                setName(obj.getName());
                setVersion(obj.getVersion());
                setDate(obj.getDate());
                setWGS84CoordinateSystem(obj.getWGS84CoordinateSystem());
                return (*this);
            }

            void Header::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);

                m_coordinateSystem.accept(visitor);
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

            const WGS84CoordinateSystem& Header::getWGS84CoordinateSystem() const {
                return m_coordinateSystem;
            }

            void Header::setWGS84CoordinateSystem(const WGS84CoordinateSystem &c) {
                m_coordinateSystem = c;
            }

            int32_t Header::getID() const {
                return 834;
            }

            const string Header::getShortName() const {
                return "Header";
            }

            const string Header::getLongName() const {
                return "hesperia.data.scenario.Header";
            }

            const string Header::toString() const {
                stringstream s;
                s << "Scenario: '" << m_name << "', Version: " << m_version << ", Date: " << m_date;
                return s.str();
            }

            ostream& Header::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                        m_name);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('v', 'e', 'r', 's', 'i', 'o', 'n') >::RESULT,
                        m_version);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'e') >::RESULT,
                        m_date);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'o', 'r', 'd') >::RESULT,
                        m_coordinateSystem);

                return out;
            }

            istream& Header::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n', 'a', 'm', 'e') >::RESULT,
                       m_name);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL7('v', 'e', 'r', 's', 'i', 'o', 'n') >::RESULT,
                       m_version);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('d', 'a', 't', 'e') >::RESULT,
                       m_date);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('c', 'o', 'o', 'r', 'd') >::RESULT,
                       m_coordinateSystem);

                return in;
            }

        }
    }
} // core::data::scenario
