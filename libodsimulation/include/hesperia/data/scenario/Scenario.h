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

#ifndef HESPERIA_CORE_DATA_SCENARIO_SCENARIO_H_
#define HESPERIA_CORE_DATA_SCENARIO_SCENARIO_H_

#include <string>
#include <vector>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/Ground.h"
#include "hesperia/data/scenario/Header.h"
#include "hesperia/data/scenario/Layer.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a scenario.
             */
            class OPENDAVINCI_API Scenario : public core::data::SerializableData, public ScenarioNode {
                public:
                    Scenario();

                    virtual ~Scenario();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Scenario(const Scenario &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Scenario& operator=(const Scenario &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the scenario's header.
                     *
                     * @return Scenario's header.
                     */
                    const Header& getHeader() const;

                    /**
                     * This method sets the scenario's header.
                     *
                     * @param h Scenario's header.
                     */
                    void setHeader(const Header &h);

                    /**
                     * This method returns the scenario's ground.
                     *
                     * @return Scenario's ground.
                     */
                    const Ground& getGround() const;

                    /**
                     * This method sets the scenario's ground.
                     *
                     * @param g Scenario's ground.
                     */
                    void setGround(const Ground &g);

                    /**
                     * This method returns the list of layers.
                     *
                     * @return List of layers.
                     */
                    const vector<Layer>& getListOfLayers() const;

                    /**
                     * This method adds a layer.
                     *
                     * @param l Layer to be added.
                     */
                    void addLayer(const Layer &l);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Header m_header;
                    Ground m_ground;
                    vector<Layer> m_listOfLayers;

                    /**
                     * This method creates a deep copy.
                     *
                     * @param obj Object of another instance of this class.
                     */
                    void deepCopy(const Scenario &obj);
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_SCENARIO_H_*/
