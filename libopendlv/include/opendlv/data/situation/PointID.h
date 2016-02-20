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

#ifndef HESPERIA_CORE_DATA_SITUATION_POINTID_H_
#define HESPERIA_CORE_DATA_SITUATION_POINTID_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/SituationNode.h"
#include "opendlv/data/situation/SituationVisitor.h"

namespace opendlv {
    namespace data {
        namespace situation {

            using namespace std;

            /**
             * This class represents a connector between lanes or lanes and zones.
             */
            class OPENDAVINCI_API PointID : public odcore::data::SerializableData, public SituationNode {
                public:
                    PointID();

                    /**
                     * Constructor to set values from pointID of format
                     * Layer "." Road "." Lane "." Point
                     *
                     * @param pointID PointID to parse from.
                     */
                    PointID(const string &pointID);

                    virtual ~PointID();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointID(const PointID &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointID& operator=(const PointID &obj);

                    virtual void accept(situation::SituationVisitor &visitor);

                    /**
                     * This method returns the layerID.
                     *
                     * @return Layer identifier.
                     */
                    uint32_t getLayerID() const;

                    /**
                     * This method sets the layer identifier.
                     *
                     * @param layerID Layer identifier.
                     */
                    void setLayerID(const uint32_t &layerID);

                    /**
                     * This method returns the roadID.
                     *
                     * @return Road identifier.
                     */
                    uint32_t getRoadID() const;

                    /**
                     * This method sets the road identifier.
                     *
                     * @param roadID Road identifier.
                     */
                    void setRoadID(const uint32_t &roadID);

                    /**
                     * This method returns the laneID.
                     *
                     * @return Lane identifier.
                     */
                    uint32_t getLaneID() const;

                    /**
                     * This method sets the lane identifier.
                     *
                     * @param laneID Lane identifier.
                     */
                    void setLaneID(const uint32_t &laneID);

                    /**
                     * This method returns the pointID.
                     *
                     * @return Point identifier.
                     */
                    uint32_t getPointID() const;

                    /**
                     * This method sets the point identifier.
                     *
                     * @param pointID Point identifier.
                     */
                    void setPointID(const uint32_t &pointID);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_layerID;
                    uint32_t m_roadID;
                    uint32_t m_laneID;
                    uint32_t m_pointID;
            };

        }
    }
} // opendlv::data::situation

#endif /*HESPERIA_CORE_DATA_SITUATION_POINTID_H_*/
