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

#ifndef HESPERIA_CORE_DATA_SCENARIO_COORDINATESYSTEM_H_
#define HESPERIA_CORE_DATA_SCENARIO_COORDINATESYSTEM_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/scenario/ScenarioNode.h"
#include "opendlv/data/scenario/ScenarioVisitor.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents the coordinate system to be used of a scenario.
             */
            class OPENDAVINCI_API CoordinateSystem : public odcore::data::SerializableData, public ScenarioNode {
                protected:
                    CoordinateSystem();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    CoordinateSystem(const CoordinateSystem &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    CoordinateSystem& operator=(const CoordinateSystem &obj);

                public:
                    virtual ~CoordinateSystem();

                    virtual void accept(ScenarioVisitor &visitor) = 0;

                    /**
                     * This method returns the type of the coordinate system.
                     *
                     * @return Type of coordinate system.
                     */
                    const string getType() const;

                    /**
                     * This method sets the coordinate system's type.
                     *
                     * @param type Type of the coordinate system.
                     */
                    void setType(const string &type);

                    /**
                     * This method returns the coordinate system's rotation.
                     *
                     * @return Rotation of the coordinate system.
                     */
                    double getRotation() const;

                    /**
                     * This method sets the coordinate system's rotation.
                     *
                     * @param r Rotation of the coordinate system.
                     */
                    void setRotation(const double &r);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    string m_type;
                    double m_rotation;
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_COORDINATESYSTEM_H_*/
