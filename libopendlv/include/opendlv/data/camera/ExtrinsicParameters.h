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

#ifndef HESPERIA_DATA_CAMERA_EXTRINSICPARAMETERS_H_
#define HESPERIA_DATA_CAMERA_EXTRINSICPARAMETERS_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/environment/Point3.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace std;
            using namespace odcore;

            /**
             * This class represents extrinsic calibration parameters.
             */
            class OPENDAVINCI_API ExtrinsicParameters : public odcore::data::SerializableData {
                public:
                    ExtrinsicParameters();

                    /**
                     * Constructor.
                     *
                     * @param translation Translation.
                     * @param rotation Rotation.
                     */
                    ExtrinsicParameters(const opendlv::data::environment::Point3 &translation, const cartesian::Matrix3x3 &rotation);

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ExtrinsicParameters(const ExtrinsicParameters &obj);

                    virtual ~ExtrinsicParameters();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ExtrinsicParameters& operator=(const ExtrinsicParameters &obj);

                    /**
                     * This method gets the translation.
                     *
                     * @return Translation.
                     */
                    const opendlv::data::environment::Point3 getTranslation() const;

                    /**
                     * This method sets the translation.
                     *
                     * @param translation Translation.
                     */
                    void setTranslation(const opendlv::data::environment::Point3 &translation);

                    /**
                     * This method gets the rotation.
                     *
                     * @return Rotation.
                     */
                    const cartesian::Matrix3x3 getRotation() const;

                    /**
                     * This method sets the rotation.
                     *
                     * @param rotation Rotation.
                     */
                    void setRotation(const cartesian::Matrix3x3 &rotation);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    opendlv::data::environment::Point3 m_translation;
                    cartesian::Matrix3x3 m_rotation;
            };
        }
    }
} // opendlv::data::camera

#endif /*HESPERIA_CORE_DATA_CAMERA_EXTRINSICPARAMETERS_H_*/
