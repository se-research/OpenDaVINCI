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

#ifndef HESPERIA_DATA_ENVIRONMENT_POINTSHAPEDOBJECT_H_
#define HESPERIA_DATA_ENVIRONMENT_POINTSHAPEDOBJECT_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/Position.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace opendlv::data::environment;

            /**
             * This class contains all data about a moving point shaped object.
             */
            class OPENDAVINCI_API PointShapedObject : public Position {
                public:
                    PointShapedObject();

                    /**
                     * Constructor.
                     *
                     * @param position Position.
                     * @param rotation Rotation.
                     * @param velocity Velocity.
                     * @param acceleration Acceleration.
                     */
                    PointShapedObject(const Point3 &position, const Point3 &rotation,
                                      const Point3 &velocity, const Point3 &acceleration);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointShapedObject(const PointShapedObject &obj);

                    virtual ~PointShapedObject();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointShapedObject& operator=(const PointShapedObject &obj);

                    /**
                     * This method returns the current velocity.
                     *
                     * @return velocity.
                     */
                    const Point3 getVelocity() const;

                    /**
                     * This method sets a velocity.
                     *
                     * @param velocity New velocity.
                     */
                    void setVelocity(const Point3 &velocity);

                    /**
                     * This method returns the current acceleration.
                     *
                     * @return acceleration.
                     */
                    const Point3 getAcceleration() const;

                    /**
                     * This method sets an acceleration.
                     *
                     * @param acceleration New acceleration.
                     */
                    void setAcceleration(const Point3 &acceleration);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    Point3 m_velocity;
                    Point3 m_acceleration;
            };

        }
    }
} // opendlv::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_POINTSHAPEDOBJECT_H_*/
