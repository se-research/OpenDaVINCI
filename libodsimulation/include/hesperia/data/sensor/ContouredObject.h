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

#ifndef HESPERIA_CORE_DATA_SENSOR_CONTOUREDOBJECT_H_
#define HESPERIA_CORE_DATA_SENSOR_CONTOUREDOBJECT_H_

#include <vector>

#include "opendavinci/core/opendavinci.h"

#include "hesperia/data/environment/Point3.h"
#include "hesperia/data/environment/PointShapedObject.h"

namespace hesperia {
    namespace data {
        namespace sensor {

            using namespace std;

            /**
             * This class contains data about a measured object
             * either by the radar or laser system.
             */
            class OPENDAVINCI_API ContouredObject : public hesperia::data::environment::PointShapedObject {
                public:
                    ContouredObject();

                    /**
                     * Constructor.
                     *
                     * @param position Position.
                     * @param rotation Rotation.
                     * @param velocity Velocity.
                     * @param acceleration Acceleration.
                     */
                    ContouredObject(const hesperia::data::environment::Point3 &position, const hesperia::data::environment::Point3 &rotation,
                                    const hesperia::data::environment::Point3 &velocity, const hesperia::data::environment::Point3 &acceleration);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ContouredObject(const ContouredObject &obj);

                    virtual ~ContouredObject();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ContouredObject& operator=(const ContouredObject &obj);

                    /**
                     * This method returns the current contour.
                     *
                     * @return Contour.
                     */
                    const vector<hesperia::data::environment::Point3> getContour() const;

                    /**
                     * This method sets a contour.
                     *
                     * @param contour New contour.
                     */
                    void setContour(const vector<hesperia::data::environment::Point3> &contour);

                    /**
                     * This method resets the current contoured object.
                     */
                    void reset();

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    vector<hesperia::data::environment::Point3> m_contour;
            };

        }
    }
} // hesperia::data::sensor

#endif /*HESPERIA_CORE_DATA_SENSOR_CONTOUREDOBJECT_H_*/
