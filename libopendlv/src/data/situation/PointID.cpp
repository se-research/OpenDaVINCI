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

#include <istream>
#include <memory>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/PointID.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;
            using namespace odcore::base;
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

            int32_t PointID::getID() const {
                return 857;
            }

            const string PointID::getShortName() const {
                return "PointID";
            }

            const string PointID::getLongName() const {
                return "hesperia.data.situation.PointID";
            }

            const string PointID::toString() const {
                stringstream s;
                s << getLayerID() << "." << getRoadID() << "." << getLaneID() << "." << getPointID();
                return s.str();
            }

            ostream& PointID::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, getLayerID());

                s->write(2, getRoadID());

                s->write(3, getLaneID());

                s->write(4, getPointID());

                return out;
            }

            istream& PointID::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_layerID);

                d->read(2, m_roadID);

                d->read(3, m_laneID);

                d->read(4, m_pointID);

                return in;
            }

        }
    }
} // opendlv::data::situation
