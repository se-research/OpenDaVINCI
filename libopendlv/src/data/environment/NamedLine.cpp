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

#include <sstream>
#include <string>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/environment/Line.h"
#include "opendlv/data/environment/NamedLine.h"
#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace opendlv::data::environment;

            NamedLine::NamedLine() :
                Line(),
                m_name("") {}

            NamedLine::NamedLine(const string &n, const Point3 &A, const Point3 &B) :
                Line(A, B),
                m_name(n) {}

            NamedLine::NamedLine(const NamedLine &obj) :
                Line(obj.getA(), obj.getB()),
                m_name(obj.getName()) {}

            NamedLine::~NamedLine() {}

            NamedLine& NamedLine::operator=(const NamedLine &obj) {
                setA(obj.getA());
                setB(obj.getB());
                setName(obj.getName());

                return (*this);
            }

            const string NamedLine::getName() const {
                return m_name;
            }

            void NamedLine::setName(const string &n) {
                m_name = n;
            }

            const string NamedLine::toString() const {
                stringstream sstr;
                sstr << m_name << ": " << Line::toString();
                return sstr.str();
            }

            ostream& NamedLine::operator<<(ostream &out) const {
                // Serializer super class.
                Line::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n','a','m','e') >::RESULT,
                        m_name);

                return out;
            }

            istream& NamedLine::operator>>(istream &in) {
                // Deserializer super class.
                Line::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('n','a','m','e') >::RESULT,
                       m_name);

                return in;
            }

        }
    }
} // opendlv::data::environment
