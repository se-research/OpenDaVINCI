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

#include "core/SharedPointer.h"
#include "core/base/Deserializer.h"
#include "core/base/Hash.h"
#include "core/base/SerializationFactory.h"
#include "core/base/Serializer.h"
#include "hesperia/data/scenario/IDVertex3.h"
#include "hesperia/data/scenario/LaneModel.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"
#include "hesperia/data/scenario/StraightLine.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace core::base;
            using namespace scenario;

            StraightLine::StraightLine() :
                    m_start(),
                    m_end() {
                LaneModel::setType(LaneModel::STRAIGHTLINE);
            }

            StraightLine::StraightLine(const StraightLine &obj) :
                    LaneModel(obj),
                    m_start(obj.getStart()),
                    m_end(obj.getEnd()) {}

            StraightLine::~StraightLine() {}

            StraightLine& StraightLine::operator=(const StraightLine &obj) {
                LaneModel::operator=(obj);
                setStart(obj.getStart());
                setEnd(obj.getEnd());

                return (*this);
            }

            void StraightLine::accept(ScenarioVisitor &visitor) {
                LaneModel::accept(visitor);
                visitor.visit(*this);

                m_start.accept(visitor);
                m_end.accept(visitor);
            }

            const IDVertex3& StraightLine::getStart() const {
                return m_start;
            }

            void StraightLine::setStart(const IDVertex3 &s) {
                m_start = s;
            }

            const IDVertex3& StraightLine::getEnd() const {
                return m_end;
            }

            void StraightLine::setEnd(const IDVertex3 &e) {
                m_end = e;
            }

            int32_t StraightLine::getID() const {
                return 823;
            }

            const string StraightLine::getShortName() const {
                return "StraightLine";
            }

            const string StraightLine::getLongName() const {
                return "hesperia.data.scenario.StraightLine";
            }

            const string StraightLine::toString() const {
                return "";
            }

            ostream& StraightLine::operator<<(ostream &out) const {
                // Serializer super class.
                LaneModel::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 't', 'a', 'r', 't') >::RESULT,
                        getStart());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('e', 'n', 'd') >::RESULT,
                        getEnd());

                return out;
            }

            istream& StraightLine::operator>>(istream &in) {
                // Deserializer super class.
                LaneModel::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('s', 't', 'a', 'r', 't') >::RESULT,
                       m_start);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('e', 'n', 'd') >::RESULT,
                       m_end);

                return in;
            }

        }
    }
} // hesperia::data::scenario
