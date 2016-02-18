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

#ifndef HESPERIA_DATA_CAMERA_INTRINSICPARAMETERS_H_
#define HESPERIA_DATA_CAMERA_INTRINSICPARAMETERS_H_

#include <string>

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/data/SerializableData.h"
#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace core;

            /* Parameter:

            float distortion[4];
            float alpha; (done)
            float focalLength[2]; (done)
            float principlePoint[2]; (done)
            float focalDistance; (done)
             */

            /**
             * This class represents intrinsic calibration parameters.
             */
            class OPENDAVINCI_API IntrinsicParameters : public core::data::SerializableData {
                public:
                    IntrinsicParameters();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    IntrinsicParameters(const IntrinsicParameters &obj);

                    virtual ~IntrinsicParameters();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    IntrinsicParameters& operator=(const IntrinsicParameters &obj);

                    /**
                     * This method returns the principle point, i.e. the
                     * two-dimensional point where the optic axis intersects
                     * the image.
                     *
                     * @return Principle point.
                     */
                    const opendlv::data::environment::Point3 getPrinciplePoint() const;

                    /**
                     * This method sets the principle point. The z-component
                     * is set to 0 automatically.
                     *
                     * @param principlePoint Two dimensional principle point.
                     */
                    void setPrinciplePoint(const opendlv::data::environment::Point3 &principlePoint);

                    /**
                     * This method returns the focal length in x- and y-
                     * direction.
                     *
                     * @return Focal length.
                     */
                    const opendlv::data::environment::Point3 getFocalLength() const;

                    /**
                     * This method sets the focal length. The z-component
                     * is set to 0 automatically.
                     *
                     * @param focalLength Two-dimensional focal length.
                     */
                    void setFocalLength(const opendlv::data::environment::Point3 &focalLength);

                    /**
                     * This method returns the focal distance.
                     *
                     * @return Focal distance.
                     */
                    double getFocalDistance() const;

                    /**
                     * This method sets the focal distance.
                     *
                     * @param focalDistance Focal distance.
                     */
                    void setFocalDistance(const double &focalDistance);

                    /**
                     * This method returns alpha (aspect ratio?) TODO: Read OpenCV doc.
                     *
                     * @return Alpha.
                     */
                    double getAlpha() const;

                    /**
                     * This method sets alpha.
                     *
                     * @param alpha
                     */
                    void setAlpha(const double &alpha);

                    virtual std::ostream& operator<<(std::ostream &out) const;
                    virtual std::istream& operator>>(std::istream &in);

                    virtual const std::string toString() const;

                private:
                    opendlv::data::environment::Point3 m_principlePoint;
                    opendlv::data::environment::Point3 m_focalLength;
                    double m_focalDistance;
                    double m_alpha;
            };
        }
    }
} // opendlv::data::camera

#endif /*HESPERIA_DATA_CAMERA_INTRINSICPARAMETERS_H_*/
