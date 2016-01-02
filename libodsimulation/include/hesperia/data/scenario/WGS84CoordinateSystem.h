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

#ifndef HESPERIA_CORE_DATA_SCENARIO_WGS84COORDINATESYSTEM_H_
#define HESPERIA_CORE_DATA_SCENARIO_WGS84COORDINATESYSTEM_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "hesperia/data/scenario/CoordinateSystem.h"
#include "hesperia/data/scenario/Vertex3.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a two-dimensional WGS84-coordinate
             * system to be used of a scenario.
             */
            class OPENDAVINCI_API WGS84CoordinateSystem : public CoordinateSystem {
                public:
                    WGS84CoordinateSystem();

                    virtual ~WGS84CoordinateSystem();

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    WGS84CoordinateSystem(const WGS84CoordinateSystem &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    WGS84CoordinateSystem& operator=(const WGS84CoordinateSystem &obj);

                    /**
                     * This method returns the origin of the WGS84 coordinate system.
                     *
                     * @return Origin of the coordinate system.
                     */
                    const Vertex3 getOrigin() const;

                    /**
                     * This method sets the coordinate system's origin.
                     *
                     * @param o Origin of the coordinate system.
                     */
                    void setOrigin(const Vertex3 &o);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Vertex3 m_origin;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_WGS84COORDINATESYSTEM_H_*/
