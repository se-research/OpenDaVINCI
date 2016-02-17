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

#ifndef HESPERIA_CORE_DATA_SCENARIO_CONNECTOR_H_
#define HESPERIA_CORE_DATA_SCENARIO_CONNECTOR_H_

#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/SerializableData.h"

#include "hesperia/data/scenario/PointID.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a connector between lanes or lanes and zones.
             */
            class OPENDAVINCI_API Connector : public core::data::SerializableData, public ScenarioNode {
                public:
                    Connector();

                    virtual ~Connector();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Connector(const Connector &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Connector& operator=(const Connector &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the source point identifier.
                     *
                     * @return Source point identifier.
                     */
                    const PointID& getSource() const;

                    /**
                     * This method sets the source point identifier.
                     *
                     * @param sourceID Source point identifier.
                     */
                    void setSource(const PointID &sourceID);

                    /**
                     * This method returns the target point identifier.
                     *
                     * @return Target point identifier.
                     */
                    const PointID& getTarget() const;

                    /**
                     * This method sets the target point identifier.
                     *
                     * @param targetID Target point identifier.
                     */
                    void setTarget(const PointID &targetID);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    PointID m_source;
                    PointID m_target;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_CONNECTOR_H_*/
