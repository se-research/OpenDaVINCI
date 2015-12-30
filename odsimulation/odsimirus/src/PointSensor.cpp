/**
 * irus - Distance data generator (part of simulation environment)
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <cmath>
#include <sstream>
#include <vector>

#include "PointSensor.h"
#include "generated/cartesian/Constants.h"

namespace irus {

    using namespace std;
    using namespace core::data;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;

    PointSensor::PointSensor(const uint16_t &id, const string &name, const hesperia::data::environment::Point3 &translation, const double &rotZ, const double &angleFOV, const double &distanceFOV, const double &clampDistance, const bool &showFOV) :
        m_id(id),
        m_name(name),
        m_translation(translation),
        m_rotZ(rotZ),
        m_angleFOV(angleFOV),
        m_distanceFOV(distanceFOV),
        m_clampDistance(clampDistance),
        m_showFOV(showFOV),
        m_totalRotation(0),
        m_FOV(),
        m_sensorPosition()
    {}

    PointSensor::~PointSensor() {}

    Polygon PointSensor::updateFOV(const Point3 &translationGlobal, const Point3 &rotationGlobal) {
        // 1. Rotate the translation of the sensor w.r.t. the global rotation of the vehicle.
        m_sensorPosition = m_translation;
        m_sensorPosition.rotateZ(rotationGlobal.getAngleXY());
        m_sensorPosition += translationGlobal;

        m_totalRotation = rotationGlobal.getAngleXY() + m_rotZ*cartesian::Constants::DEG2RAD;

        // 2. Construct the FOV in the origin w.r.t. the global rotation of the vehicle.
        Point3 leftBoundaryFOV(m_distanceFOV, 0, 0);
        leftBoundaryFOV.rotateZ(m_totalRotation + (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD);

        Point3 rightBoundaryFOV(m_distanceFOV, 0, 0);
        rightBoundaryFOV.rotateZ(m_totalRotation - (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD);

        // 3. Translate the FOV to the sensor's position.
        leftBoundaryFOV += m_sensorPosition;
        rightBoundaryFOV += m_sensorPosition;

        // Iterate through all available polygons and intersect FOV-polygon with polygon.
        Polygon FOV;
        FOV.add(m_sensorPosition);
        FOV.add(leftBoundaryFOV);
        FOV.add(rightBoundaryFOV);
        FOV.add(m_sensorPosition);
        m_FOV = FOV;

        return m_FOV;
    }

    bool PointSensor::isInFOV(const Point3 &pt) const {
        bool retVal = false;

        // Calculate angle deviation.
        double angleDelta = (pt - m_sensorPosition).getAngleXY() - m_totalRotation;

        // If total rotation angle is negative, normalize angleDelta.
        if (m_totalRotation < 0) {
            // Normalize angle to interval -PI ... PI.
            while (angleDelta < -cartesian::Constants::PI) {
                angleDelta += 2.0*cartesian::Constants::PI;
            }
            while (angleDelta > cartesian::Constants::PI) {
                angleDelta -= 2.0*cartesian::Constants::PI;
            }
        }

//         cerr << m_name << " angleDelta: " << angleDelta << ", totalRotation: " << m_totalRotation << ", left: " << (m_totalRotation + (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD) << ", right: " << (m_totalRotation - (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD) << ", " << (m_totalRotation + angleDelta) << endl;

        // Check if the point is within the FOV.
        if ( ( ((m_totalRotation + angleDelta) > (m_totalRotation - (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD)) &&
               ((m_totalRotation + angleDelta) < (m_totalRotation + (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD)) ) || 
             ( (fabs((m_totalRotation - (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD) - (m_totalRotation + angleDelta)) < 1e-4) ||
               (fabs((m_totalRotation + (m_angleFOV/2.0)*cartesian::Constants::DEG2RAD) - (m_totalRotation + angleDelta)) < 1e-4) )
           ) {
            // Distance found.
//            cerr << "Object's distance: " << (pt - m_sensorPosition).lengthXY() << ", Pos: " << pt.toString() << ", angleDelta: " << angleDelta << endl;
            retVal = true;
        }

        return retVal;
    }

    double PointSensor::getDistance(map<uint32_t, hesperia::data::environment::Polygon> &mapOfPolygons) {
        Point3 nearest;
        double distanceToSensor = -1;

        map<uint32_t, hesperia::data::environment::Polygon>::const_iterator it = mapOfPolygons.begin();
        while (it != mapOfPolygons.end()) {
            Polygon p = it->second;

            // Get overlapping parts of polygon...
            Polygon contour = m_FOV.intersectIgnoreZ(p);

            if (contour.getSize() > 0) {
                // Get nearest point from contour.
                const vector<Point3> listOfPoints = contour.getVertices();
                vector<Point3>::const_iterator jt = listOfPoints.begin();

                while (jt != listOfPoints.end()) {
                    Point3 pt = (*jt++);
                    double d = (pt - m_sensorPosition).lengthXY();

                    if (isInFOV(pt)) {
                        if ((distanceToSensor < 0) || (d < distanceToSensor)) {
                            nearest = pt;
                            distanceToSensor = d;
                        }
                    }
                }
            }

            it++;
        }

        if (distanceToSensor > m_clampDistance) {
            distanceToSensor = -1;
        }

        return distanceToSensor;
    } 

    const string PointSensor::getName() const {
        return m_name;    
    }

    uint16_t PointSensor::getID() const {
        return m_id;    
    }

    bool PointSensor::hasShowFOV() const {
        return m_showFOV;
    }

    const string PointSensor::toString() const {
        stringstream sstr;
        sstr << m_name << "(" << m_id << ")" << ": " << m_translation.toString() << ", rot: " << m_rotZ << ", angle: " << m_angleFOV << ", range: " << m_distanceFOV << ", clampDistance: " << m_clampDistance <<  ", showFOV: " << m_showFOV;
        return sstr.str();
    }  

} // irus

