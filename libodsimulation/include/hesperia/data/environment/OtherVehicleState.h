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

#ifndef HESPERIA_DATA_ENVIRONMENT_OTHERVEHICLESTATE_H_
#define HESPERIA_DATA_ENVIRONMENT_OTHERVEHICLESTATE_H_

#include "core/opendavinci.h"

#include "hesperia/data/environment/PointShapedObject.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace hesperia::data::environment;

            /**
             * This class contains all relevant data for the own car.
             */
            class OPENDAVINCI_API OtherVehicleState : public PointShapedObject {
                public:
                    OtherVehicleState();

                    /**
                     * Constructor.
                     *
                     * @param id Identifier.
                     * @param position Position.
                     * @param rotation Rotation.
                     * @param velocity Velocity.
                     * @param acceleration Acceleration.
                     */
                    OtherVehicleState(const uint32_t &id,
                    		 const Point3 &position, const Point3 &rotation,
                             const Point3 &velocity, const Point3 &acceleration);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    OtherVehicleState(const OtherVehicleState &obj);

                    virtual ~OtherVehicleState();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    OtherVehicleState& operator=(const OtherVehicleState &obj);

                    /**
                     * This method returns this object's ID.
                     *
                     * @return ID.
                     */
                    uint32_t getID() const;

                    /**
                     * This method sets this object's ID.
                     *
                     * @param id.
                     */
                    void setID(const uint32_t &id);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    uint32_t m_id;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_OTHERVEHICLESTATE_H_*/
