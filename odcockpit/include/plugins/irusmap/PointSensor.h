/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifndef COCKPIT_PLUGINS_IRUSMAP_POINTSENSOR_H_
#define COCKPIT_PLUGINS_IRUSMAP_POINTSENSOR_H_

#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendlv/data/environment/Point3.h"

class QPainter;
namespace automotive { namespace miniature { class SensorBoardData; } }

namespace cockpit {

    namespace plugins {

        namespace irusmap {

            using namespace std;

            /**
             * This class encapsulates a point providing sensor to be drawn by IrUsMap.
             */
            class PointSensor {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    PointSensor(const PointSensor &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    PointSensor& operator=(const PointSensor &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param id ID.
                     * @param name Name.
                     * @param translation Translation of the sensor.
                     * @param rotZ Rotation in DEG around the Z-axis. +: counterclockwise, -:clockwise, 0 = 12am, -90 = 3pm, ...
                     * @param angleFOV Field of view angle in DEG.
                     * @param distanceFOV Range of the FOV.
                     * @param clampDistance Maximum distance for the sensor; any distance greater than this will be set to -1.
                     */
                    PointSensor(const uint16_t &id, const string &name, const hesperia::data::environment::Point3 &translation, const double &rotZ, const double &angleFOV, const double &distanceFOV, const double &clampDistance);

                    virtual ~PointSensor();

                    void drawFOV(QPainter &painter) const;

                    void drawMatchingDistances(QPainter &painter, automotive::miniature::SensorBoardData &sbd) const;

                    const string getName() const;

                    uint16_t getID() const;

                    const string toString() const;

                    hesperia::data::environment::Point3 getTranslation() const;

                    hesperia::data::environment::Point3 getDescPoint() const;

                private:
                    uint16_t m_id;
                    string m_name;
                    hesperia::data::environment::Point3 m_translation;
                    double m_rotZ;
                    double m_angleFOV;
                    double m_distanceFOV;
                    double m_clampDistance;
            };
 
       }
    }
}

#endif /*COCKPIT_PLUGINS_IRUSMAP_POINTSENSOR_H_*/
