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

#ifndef HESPERIA_DATA_CAMERA_IMAGEGRABBERCALIBRATION_H_
#define HESPERIA_DATA_CAMERA_IMAGEGRABBERCALIBRATION_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/SerializableData.h"

#include "opendlv/data/camera/ExtrinsicParameters.h"
#include "opendlv/data/camera/IntrinsicParameters.h"

namespace opendlv {
    namespace data {
        namespace camera {

            using namespace std;

            /**
             * This class represents a calibration for an image grabber.
             */
            class OPENDAVINCI_API ImageGrabberCalibration : public odcore::data::SerializableData {
                public:
                    ImageGrabberCalibration();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    ImageGrabberCalibration(const ImageGrabberCalibration &obj);

                    virtual ~ImageGrabberCalibration();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    ImageGrabberCalibration& operator=(const ImageGrabberCalibration &obj);

                    /**
                     * This method returns the extrinsic calibration parameters.
                     *
                     * @return Extrinsic calibration parameters.
                     */
                    const ExtrinsicParameters getExtrinsicParameters() const;

                    /**
                     * This method sets the extrinsic calibration parameters.
                     *
                     * @param extrinsicParameters Extrinsic calibration parameters.
                     */
                    void setExtrinsicParameters(const ExtrinsicParameters &extrinsicParameters);

                    /**
                     * This method returns the intrinsic calibration parameters.
                     *
                     * @return Intrinsic calibration parameters.
                     */
                    const IntrinsicParameters getIntrinsicParameters() const;

                    /**
                     * This method sets the intrinsic calibration parameters.
                     *
                     * @param intrinsicParameters Intrinsic calibration parameters.
                     */
                    void setIntrinsicParameters(const IntrinsicParameters &intrinsicParameters);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    ExtrinsicParameters m_extrinsicParameters;
                    IntrinsicParameters m_intrinsicParameters;
            };
        }
    }
} // opendlv::data::camera

#endif /*HESPERIA_DATA_CAMERA_IMAGEGRABBERCALIBRATION_H_*/
