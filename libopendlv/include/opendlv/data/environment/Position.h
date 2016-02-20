/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef HESPERIA_DATA_ENVIRONMENT_POSITION_H_
#define HESPERIA_DATA_ENVIRONMENT_POSITION_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;

            /**
             * This class can be used to describe an object in a three dimensional
             * space using position and rotation.
             */
            class OPENDAVINCI_API Position : public odcore::data::SerializableData {
                public:
                    Position();

                    /**
                     * Constructor.
                     *
                     * @param position Position.
                     * @param rotation Rotation.
                     */
                    Position(const Point3 &position, const Point3 &rotation);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Position(const Position &obj);

                    virtual ~Position();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Position& operator=(const Position &obj);

                    /**
                     * This method returns the translation.
                     *
                     * @return Translation.
                     */
                    const Point3 getPosition() const;

                    /**
                     * This method sets the position.
                     *
                     * @param position Position.
                     */
                    void setPosition(const Point3 &position);

                    /**
                     * This method returns the rotation.
                     *
                     * @return Rotation.
                     */
                    const Point3 getRotation() const;

                    /**
                     * This method sets the rotation.
                     *
                     * @param rotation Rotation.
                     */
                    void setRotation(const Point3 &rotation);

                    bool operator==(const Position& other) const;
                    bool operator!=(const Position& other) const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    Point3 m_position;
                    Point3 m_rotation;
            };

        }
    }
} // opendlv::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_POSITION_H_*/
