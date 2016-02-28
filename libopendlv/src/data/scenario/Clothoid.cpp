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

#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendlv/data/scenario/Clothoid.h"
#include "opendlv/data/scenario/LaneModel.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/StraightLine.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;
            using namespace scenario;

            Clothoid::Clothoid() :
                    StraightLine(),
                    m_dk(0),
                    m_k(0),
                    m_rotationZ(0) {
                LaneModel::setType(LaneModel::CLOTHOID);
            }

            Clothoid::Clothoid(const Clothoid &obj) :
                    StraightLine(obj),
                    m_dk(obj.getDK()),
                    m_k(obj.getK()),
                    m_rotationZ(obj.getRotationZ()) {}

            Clothoid::~Clothoid() {}

            Clothoid& Clothoid::operator=(const Clothoid &obj) {
                LaneModel::operator=(obj);
                setDK(obj.getDK());
                setK(obj.getK());
                setRotationZ(obj.getRotationZ());

                return (*this);
            }

            void Clothoid::accept(ScenarioVisitor &visitor) {
                StraightLine::accept(visitor);
                visitor.visit(*this);
            }

            double Clothoid::getDK() const {
                return m_dk;
            }

            void Clothoid::setDK(const double &dk) {
                m_dk = dk;
            }

            double Clothoid::getK() const {
                return m_k;
            }

            void Clothoid::setK(const double &k) {
                m_k = k;
            }

            double Clothoid::getRotationZ() const {
                return m_rotationZ;
            }

            void Clothoid::setRotationZ(const double &rotationZ) {
                m_rotationZ = rotationZ;
            }

            int32_t Clothoid::getID() const {
                return 825;
            }

            const string Clothoid::getShortName() const {
                return "Clothoid";
            }

            const string Clothoid::getLongName() const {
                return "hesperia.data.scenario.Clothoid";
            }

            const string Clothoid::toString() const {
                return "";
            }

            ostream& Clothoid::operator<<(ostream &out) const {
                // Serializer super class.
                StraightLine::operator<<(out);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('d', 'k') >::RESULT,
                        getDK());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('k') >::RESULT,
                        getK());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                        getRotationZ());

                return out;
            }

            istream& Clothoid::operator>>(istream &in) {
                // Deserializer super class.
                StraightLine::operator>>(in);

                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL2('d', 'k') >::RESULT,
                       m_dk);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL1('k') >::RESULT,
                       m_k);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 't', 'z') >::RESULT,
                       m_rotationZ);

                return in;
            }

        }
    }
} // opendlv::data::scenario
