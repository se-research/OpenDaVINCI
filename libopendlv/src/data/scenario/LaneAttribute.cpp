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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/scenario/LaneAttribute.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;
            using namespace odcore::base;

            LaneAttribute::LaneAttribute() :
                    m_width(0),
                    m_leftLaneMarking(LaneAttribute::UNDEFINED),
                    m_rightLaneMarking(LaneAttribute::UNDEFINED) {}

            LaneAttribute::LaneAttribute(const LaneAttribute &obj) :
                    SerializableData(),
                    m_width(obj.getWidth()),
                    m_leftLaneMarking(obj.getLeftLaneMarking()),
                    m_rightLaneMarking(obj.getRightLaneMarking()) {}

            LaneAttribute::~LaneAttribute() {}

            LaneAttribute& LaneAttribute::operator=(const LaneAttribute &obj) {
                setWidth(obj.getWidth());
                setLeftLaneMarking(obj.getLeftLaneMarking());
                setRightLaneMarking(obj.getRightLaneMarking());

                return (*this);
            }

            void LaneAttribute::accept(ScenarioVisitor &visitor) {
                visitor.visit(*this);
            }

            double LaneAttribute::getWidth() const {
                return m_width;
            }

            void LaneAttribute::setWidth(const double &w) {
                m_width = w;
            }

            enum LaneAttribute::BOUNDARYSTYLE LaneAttribute::getLeftLaneMarking() const {
                return m_leftLaneMarking;
            }

            void LaneAttribute::setLeftLaneMarking(const enum BOUNDARYSTYLE &bs) {
                m_leftLaneMarking = bs;
            }

            enum LaneAttribute::BOUNDARYSTYLE LaneAttribute::getRightLaneMarking() const {
                return m_rightLaneMarking;
            }

            void LaneAttribute::setRightLaneMarking(const enum BOUNDARYSTYLE &bs) {
                m_rightLaneMarking = bs;
            }

            int32_t LaneAttribute::getID() const {
                return 832;
            }

            const string LaneAttribute::getShortName() const {
                return "LaneAttribute";
            }

            const string LaneAttribute::getLongName() const {
                return "hesperia.data.scenario.LaneAttribute";
            }

            const string LaneAttribute::toString() const {
                stringstream s;
                s << "Width: " << getWidth() << ", Left lane's marking: " << getLeftLaneMarking() << ", Right lane's marking: " << getRightLaneMarking();
                return s.str();
            }

            ostream& LaneAttribute::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('w', 'i', 'd', 't', 'h') >::RESULT,
                        getWidth());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                        static_cast<uint32_t>(getLeftLaneMarking()));

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                        static_cast<uint32_t>(getRightLaneMarking()));

                return out;
            }

            istream& LaneAttribute::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                odcore::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('w', 'i', 'd', 't', 'h') >::RESULT,
                       m_width);

                uint32_t left;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'e', 'f', 't') >::RESULT,
                       left);
                m_leftLaneMarking = static_cast<enum BOUNDARYSTYLE>(left);

                uint32_t right;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('r', 'i', 'g', 'h', 't') >::RESULT,
                       right);
                m_rightLaneMarking = static_cast<enum BOUNDARYSTYLE>(right);

                return in;
            }

        }
    }
} // opendlv::data::scenario
