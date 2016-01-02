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

#ifndef HESPERIA_DATA_ENVIRONMENT_WGS84COORDINATE_H_
#define HESPERIA_DATA_ENVIRONMENT_WGS84COORDINATE_H_

#include <map>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

#include "core/data/SerializableData.h"
#include "hesperia/data/environment/Point3.h"

namespace hesperia {
    namespace data {
        namespace environment {

            using namespace std;

            using namespace hesperia::data::environment;

            /**
             * This class is the main class for a WGS84 coordinate.
             */
            class OPENDAVINCI_API WGS84Coordinate : public core::data::SerializableData {
                private:
                    // The following constants are necessary the project WGS84 coordinates.
                    const static double EQUATOR_RADIUS;
                    const static double FLATTENING;
                    const static double SQUARED_ECCENTRICITY;
                    const static double ECCENTRICITY;
                    const static double POLE_RADIUS;

                    const static double C00;
                    const static double C02;
                    const static double C04;
                    const static double C06;
                    const static double C08;
                    const static double C22;
                    const static double C44;
                    const static double C46;
                    const static double C48;
                    const static double C66;
                    const static double C68;
                    const static double C88;

                    const static double R0;
                    const static double R1;
                    const static double R2T;
                    const static double R2;
                    const static double R3T;
                    const static double R3;
                    const static double R4;

                public:
                    enum LATITUDE {
                        NORTH,
                        SOUTH
                    };

                    enum LONGITUDE {
                        WEST,
                        EAST
                    };

                public:
                    WGS84Coordinate();

                    /**
                     * Constructor.
                     *
                     * @param lat Latitude.
                     * @param LAT WGS84Coordinate::NORTH or WGS84Coordinate::SOUTH
                     * @param lon Longitude.
                     * @param LON WGS84Coordinate::WEST or WGS84Coordinate::EAST
                     */
                    WGS84Coordinate(const double &lat, const enum LATITUDE &LAT, const double &lon, const enum LONGITUDE &LON);

                    virtual ~WGS84Coordinate();

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    WGS84Coordinate& operator=(const WGS84Coordinate &obj);

                    /**
                     * This method returns the latitude.
                     *
                     * @return Latitude.
                     */
                    double getLatitude() const;

                    /**
                     * This method sets the latitude.
                     *
                     * @param lat.
                     */
                    void setLatitude(const double &lat);

                    /**
                     * This method returns the longitude.
                     *
                     * @return Longitude.
                     */
                    double getLongitude() const;

                    /**
                     * This method sets the longitude.
                     *
                     * @param lon.
                     */
                    void setLongitude(const double &lon);

                    /**
                     * This method returns the LATITUDE.
                     *
                     * @return LATITUDE.
                     */
                    enum LATITUDE getLATITUDE() const;

                    /**
                     * This method sets the LATITUDE.
                     *
                     * @param LAT.
                     */
                    void setLATITUDE(const enum LATITUDE &LAT);

                    /**
                     * This method returns the LONGITUDE.
                     *
                     * @return LONGITUDE.
                     */
                    enum LONGITUDE getLONGITUDE() const;

                    /**
                     * This method sets the LONGITUDE.
                     *
                     * @param LON.
                     */
                    void setLONGITUDE(const enum LONGITUDE &LON);

                    /**
                     * This method transforms the given WGS84 coordinate
                     * using this as reference coordinate.
                     *
                     * @param coordinate WGS84 coordinate to transform.
                     * @return Cartesian coordinate.
                     */
                    const Point3 transform(const WGS84Coordinate &coordinate) const;

                    /**
                     * This method transforms the given Point3 coordinate
                     * using this as reference coordinate up to an accuracy
                     * of 1e-2.
                     *
                     * @param coordinate Point3 coordinate to transform.
                     * @return WGS84 coordinate.
                     */
                    const WGS84Coordinate transform(const Point3 &coordinate) const;

                    /**
                     * This method transforms the given Point3 coordinate
                     * using this as reference coordinate.
                     *
                     * @param coordinate Point3 coordinate to transform.
                     * @param accuracy Required accuracy.
                     * @return WGS84 coordinate.
                     */
                    const WGS84Coordinate transform(const Point3 &coordinate, const double &accuracy) const;

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    double m_lat;
                    double m_lon;
                    enum LATITUDE m_LATITUDE;
                    enum LONGITUDE m_LONGITUDE;

                    // These members are used in projective computations.
                    double m_latitude;
                    double m_longitude;
                    double m_ml0;

                    /**
                     * This method initializes the transformation.
                     */
                    void initialize();

                    /**
                     * This method computes mlfn.
                     *
                     * @return mlfn.
                     */
                    double mlfn(const double &lat) const;

                    /**
                     * This method computes msfn.
                     *
                     * @return msfn.
                     */
                    double msfn(const double &sinPhi, const double &cosPhi, const double &es) const;

                    /**
                     * This method computes fwd.
                     *
                     * @param lat
                     * @param lon
                     * @return fwd
                     */
                    pair<double, double> fwd(double lat, double lon) const;

                    /**
                     * This method projects.
                     *
                     * @param lat
                     * @param lon
                     * @return fwd
                     */
                    pair<double, double> project(double lat, double lon) const;
            };

        }
    }
} // hesperia::data::environment

#endif /*HESPERIA_DATA_ENVIRONMENT_WGS84COORDINATE_H_*/
