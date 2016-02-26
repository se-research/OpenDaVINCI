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

#ifndef HESPERIA_CORE_DATA_SCENARIO_HEIGHTIMAGE_H_
#define HESPERIA_CORE_DATA_SCENARIO_HEIGHTIMAGE_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"

#include "opendlv/data/scenario/Image.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a height image.
             */
            class OPENDAVINCI_API HeightImage : public Image {
                public:
                    HeightImage();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    HeightImage(const HeightImage &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    HeightImage& operator=(const HeightImage &obj);

                    virtual ~HeightImage();

                    virtual void accept(ScenarioVisitor &visitor);

                    /**
                     * This method returns the color representing the
                     * ground's height.
                     *
                     * @return Color representing the ground's height.
                     */
                    double getGroundHeight() const;

                    /**
                     * This method sets the color representing the
                     * ground's height.
                     *
                     * @return gh Color representing the ground's height.
                     */
                    void setGroundHeight(const double &gh);

                    /**
                     * This method returns the minimum height
                     * represented by color 0.
                     *
                     * @return Minimum height.
                     */
                    double getMinimumHeight() const;

                    /**
                     * This method sets the minimum height
                     * represented by color 0.
                     *
                     * @param minH Minimum height represented by color 0.
                     */
                    void setMinimumHeight(const double &minH);

                    /**
                     * This method returns the maximum height
                     * represented by color MAXCOLOR (depends
                     * on the image's data).
                     *
                     * @return Minimum height.
                     */
                    double getMaximumHeight() const;

                    /**
                     * This method sets the maximum height
                     * represented by color MAXCOLOR (depends
                     * on the image's data).
                     *
                     * @param maxH Maximum height represented by color MAXCOLOR.
                     */
                    void setMaximumHeight(const double &maxH);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual int32_t getID() const;
                    virtual const string getShortName() const;
                    virtual const string getLongName() const;
                    virtual const string toString() const;

                private:
                    double m_groundHeight;
                    double m_minimumHeight;
                    double m_maximumHeight;
            };

        }
    }
} // core::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_HEIGHTIMAGE_H_*/
