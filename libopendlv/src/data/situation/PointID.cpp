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

#include <istream>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/SharedPointer.h"
#include "opendavinci/core/base/Deserializer.h"
#include "opendavinci/core/base/Hash.h"
#include "opendavinci/core/base/SerializationFactory.h"
#include "opendavinci/core/base/Serializer.h"
#include "opendavinci/core/data/SerializableData.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace hesperia {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace core::base;
            using namespace situation;

            PointID::PointID() :
                    m_layerID(),
                    m_roadID(),
                    m_laneID(),
                    m_pointID() {}

            PointID::PointID(const string &pointID) :
                    m_layerID(),
                    m_roadID(),
                    m_laneID(),
                    m_pointID() {
                if ((pointID != "") && (pointID.length() >= 7) ) {
                    stringstream sstr(pointID);

                    char ignore = 0;

                    sstr >> m_layerID;

                    sstr >> ignore; // '.'

                    sstr >> m_roadID;

                    sstr >> ignore; // '.'

                    sstr >> m_laneID;

                    sstr >> ignore; // '.'

                    sstr >> m_pointID;
                }
            }

            PointID::PointID(const PointID &obj) :
                    SerializableData(),
                    m_layerID(obj.getLayerID()),
                    m_roadID(obj.getRoadID()),
                    m_laneID(obj.getLaneID()),
                    m_pointID(obj.getPointID()) {}

            PointID::~PointID() {}

            PointID& PointID::operator=(const PointID &obj) {
                setLayerID(obj.getLayerID());
                setRoadID(obj.getRoadID());
                setLaneID(obj.getLaneID());
                setPointID(obj.getPointID());

                return (*this);
            }

            void PointID::accept(SituationVisitor &visitor) {
                visitor.visit(*this);
            }

            uint32_t PointID::getLayerID() const {
                return m_layerID;
            }

            void PointID::setLayerID(const uint32_t &layerID) {
                m_layerID = layerID;
            }

            uint32_t PointID::getRoadID() const {
                return m_roadID;
            }

            void PointID::setRoadID(const uint32_t &roadID) {
                m_roadID = roadID;
            }

            uint32_t PointID::getLaneID() const {
                return m_laneID;
            }

            void PointID::setLaneID(const uint32_t &laneID) {
                m_laneID = laneID;
            }

            uint32_t PointID::getPointID() const {
                return m_pointID;
            }

            void PointID::setPointID(const uint32_t &pointID) {
                m_pointID = pointID;
            }

            const string PointID::toString() const {
                stringstream s;
                s << getLayerID() << "." << getRoadID() << "." << getLaneID() << "." << getPointID();
                return s.str();
            }

            ostream& PointID::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 'y', 'e', 'r') >::RESULT,
                        getLayerID());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 'a', 'd') >::RESULT,
                        getRoadID());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'a', 'n', 'e') >::RESULT,
                        getLaneID());

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('p', 'o', 'i', 'n', 't') >::RESULT,
                        getPointID());

                return out;
            }

            istream& PointID::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                core::SharedPointer<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('l', 'a', 'y', 'e', 'r') >::RESULT,
                       m_layerID);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('r', 'o', 'a', 'd') >::RESULT,
                       m_roadID);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL4('l', 'a', 'n', 'e') >::RESULT,
                       m_laneID);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL5('p', 'o', 'i', 'n', 't') >::RESULT,
                       m_pointID);

                return in;
            }

        }
    }
} // hesperia::data::situation
