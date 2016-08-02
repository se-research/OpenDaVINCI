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

#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/scenario/IDVertex3.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/StraightLine.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
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

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getStart());

                s->write(2, getEnd());

                return out;
            }

            istream& StraightLine::operator>>(istream &in) {
                // Deserializer super class.
                LaneModel::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_start);

                d->read(2, m_end);

                return in;
            }

        }
    }
} // opendlv::data::scenario
