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

#ifndef HESPERIA_CORE_DATA_SCENARIO_IMAGE_H_
#define HESPERIA_CORE_DATA_SCENARIO_IMAGE_H_

#include <string>

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/data/SerializableData.h"
#include "hesperia/data/scenario/ScenarioNode.h"
#include "hesperia/data/scenario/ScenarioVisitor.h"

namespace hesperia {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents an image (aerial or height).
             */
            class OPENDAVINCI_API Image : public core::data::SerializableData, public ScenarioNode {
                public:
                    Image();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    Image(const Image &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    Image& operator=(const Image &obj);

                    virtual ~Image();

                    virtual void accept(ScenarioVisitor &visitor);

                    /**
                     * This method returns the filename or the image.
                     *
                     * @return File name of the image.
                     */
                    const string getFileName() const;

                    /**
                     * This method sets the filename.
                     *
                     * @param fileName Filename of the image
                     */
                    void setFileName(const string &fileName);

                    /**
                     * This method returns the the origin's X-coordinate.
                     *
                     * @return Origin's X-coordinate.
                     */
                    uint32_t getOriginX() const;

                    /**
                     * This method sets the origin's X-coordinate.
                     *
                     * @param x Origin's X-coordinate.
                     */
                    void setOriginX(const uint32_t &x);

                    /**
                     * This method returns the the origin's Y-coordinate.
                     *
                     * @return Origin's Y-coordinate.
                     */
                    uint32_t getOriginY() const;

                    /**
                     * This method sets the origin's Y-coordinate.
                     *
                     * @param y Origin's Y-coordinate.
                     */
                    void setOriginY(const uint32_t &y);

                    /**
                     * This method returns the image's resolution in
                     * meter per pixel in X-direction.
                     *
                     * @return Image's resolution in X-direction.
                     */
                    double getMeterPerPixelX() const;

                    /**
                     * This method sets the image's resolution in
                     * meter per pixel in X-direction.
                     *
                     * @param mppX Image's resolution in X-direction.
                     */
                    void setMeterPerPixelX(const double &mppX);

                    /**
                     * This method returns the image's resolution in
                     * meter per pixel in Y-direction.
                     *
                     * @return Image's resolution in Y-direction.
                     */
                    double getMeterPerPixelY() const;

                    /**
                     * This method sets the image's resolution in
                     * meter per pixel in Y-direction.
                     *
                     * @param mppY Image's resolution in Y-direction.
                     */
                    void setMeterPerPixelY(const double &mppY);

                    /**
                     * This method returns the image's rotation around
                     * the Z-axis. 3am is 0. Rotation is counterclockwise
                     * in RAD.
                     *
                     * @return Image's rotation around the Z-axis.
                     */
                    double getRotationZ() const;

                    /**
                     * This method sets the image's rotation around
                     * the Z-axis. 3am is 0. Rotation is counterclockwise
                     * in RAD.
                     *
                     * @param rotZ Image's rotation around the Z-axis.
                     */
                    void setRotationZ(const double &rotZ);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_fileName;
                    uint32_t m_originX;
                    uint32_t m_originY;
                    double m_meterPerPixelX;
                    double m_meterPerPixelY;
                    double m_rotationZ;
            };

        }
    }
} // hesperia::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_IMAGE_H_*/
