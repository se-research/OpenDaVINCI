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

#ifndef HESPERIA_CORE_DATA_SCENARIO_LANEMODEL_H_
#define HESPERIA_CORE_DATA_SCENARIO_LANEMODEL_H_

#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/scenario/Connector.h"
#include "opendlv/data/scenario/LaneAttribute.h"
#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"
#include "opendlv/data/scenario/TrafficControl.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /** Prevent circular dependencies. */
            class Lane;

            /**
             * This class represents a lane model as the super class for any shaped lanes.
             */
            class OPENDAVINCI_API LaneModel : public odcore::data::SerializableData, public ScenarioNode {
                public:
                    enum LANEMODELTYPE {
                        ARC,
                        CLOTHOID,
                        POINTMODEL,
                        STRAIGHTLINE
                    };

                protected:
                    LaneModel();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    LaneModel(const LaneModel &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    LaneModel& operator=(const LaneModel &obj);

                public:
                    virtual ~LaneModel();

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the lane's attributes.
                     *
                     * @return Lane's attributes.
                     */
                    const LaneAttribute& getLaneAttribute() const;

                    /**
                     * This method sets the lane's attributes.
                     *
                     * @param la Lane's attributes.
                     */
                    void setLaneAttribute(const LaneAttribute &la);

                    /**
                     * This method returns the type of the lane model.
                     *
                     * @return Type of lane model.
                     */
                    enum LANEMODELTYPE getType() const;

                    /**
                     * This method sets the lane model's type.
                     *
                     * @param type Type of the lane model.
                     */
                    void setType(const enum LANEMODELTYPE &type);

                    /**
                     * This method returns the list of traffic controls.
                     *
                     * @return List of traffic controls.
                     */
                    const vector<TrafficControl*>& getListOfTrafficControls() const;

                    /**
                     * This method adds a traffic control.
                     *
                     * @param tc Traffic control to be added.
                     */
                    void addTrafficControl(TrafficControl *c);

                    /**
                     * This method returns the list of connectors.
                     *
                     * @return List of connectors.
                     */
                    const vector<Connector>& getListOfConnectors() const;

                    /**
                     * This method adds a connector.
                     *
                     * @param c Connector to be added.
                     */
                    void addConnector(const Connector &c);

                    /**
                     * This method sets the lane to which this lanemodel belongs to.
                     *
                     * @param l Lane.
                     */
                    void setLane(const Lane *l);

                    /**
                     * This method returns the lane to which this lanemodel belongs to.
                     *
                     * @return Lane.
                     */
                    const Lane* getLane() const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    const Lane *m_lane;
                    LaneAttribute m_laneAttribute;
                    enum LANEMODELTYPE m_type;
                    vector<TrafficControl*> m_listOfTrafficControls;
                    vector<Connector> m_listOfConnectors;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const LaneModel &obj);

                    /**
                     * This method clean's up the data.
                     */
                    void cleanUp();
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_LANEMODEL_H_*/
