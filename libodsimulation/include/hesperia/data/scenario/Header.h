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

#ifndef HESPERIA_CORE_DATA_SCENARIO_HEADER_H_
#define HESPERIA_CORE_DATA_SCENARIO_HEADER_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/scenario/WGS84CoordinateSystem.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents the header of a scenario.
             */
            class OPENDAVINCI_API Header : public core::data::SerializableData, public ScenarioNode {
                public:
                    Header();

                    virtual ~Header();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Header(const Header &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Header& operator=(const Header &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the scenario's name.
                     *
                     * @return Scenario's name.
                     */
                    const string getName() const;

                    /**
                     * This method sets the scenario's name.
                     *
                     * @param name Scenario's name.
                     */
                    void setName(const string &name);

                    /**
                     * This method returns the scenario's version.
                     *
                     * @return Scenario's version.
                     */
                    const string getVersion() const;

                    /**
                     * This method sets the scenario's version.
                     *
                     * @param v Scenario's version.
                     */
                    void setVersion(const string &v);

                    /**
                     * This method returns the scenario's date.
                     *
                     * @return Scenario's date.
                     */
                    const string getDate() const;

                    /**
                     * This method sets the scenario's date.
                     *
                     * @param d Scenario's date.
                     */
                    void setDate(const string &d);

                    /**
                     * This method returns the coordinate system.
                     *
                     * @return coordinate system.
                     */
                    const WGS84CoordinateSystem& getWGS84CoordinateSystem() const;

                    /**
                     * This method sets the coordinate system.
                     *
                     * @param c Coordinate system to by used.
                     */
                    void setWGS84CoordinateSystem(const WGS84CoordinateSystem &c);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_name;
                    string m_version;
                    string m_date;
                    WGS84CoordinateSystem m_coordinateSystem;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_HEADER_H_*/
