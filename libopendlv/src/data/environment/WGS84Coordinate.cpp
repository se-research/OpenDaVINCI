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

#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Deserializer.h"
#include "opendavinci/odcore/base/Hash.h"
#include "opendavinci/odcore/base/SerializationFactory.h"
#include "opendavinci/odcore/base/Serializer.h"
#include "automotivedata/generated/cartesian/Constants.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/WGS84Coordinate.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace opendlv::data::environment;

            const double WGS84Coordinate::EQUATOR_RADIUS = 6378137.0;
            const double WGS84Coordinate::FLATTENING = 1.0 / 298.257223563;
            const double WGS84Coordinate::SQUARED_ECCENTRICITY = 2.0 * FLATTENING - FLATTENING * FLATTENING;
            const double WGS84Coordinate::POLE_RADIUS = EQUATOR_RADIUS * sqrt(1.0 - SQUARED_ECCENTRICITY);

            const double WGS84Coordinate::C00 = 1.0;
            const double WGS84Coordinate::C02 = 0.25;
            const double WGS84Coordinate::C04 = 0.046875;
            const double WGS84Coordinate::C06 = 0.01953125;
            const double WGS84Coordinate::C08 = 0.01068115234375;
            const double WGS84Coordinate::C22 = 0.75;
            const double WGS84Coordinate::C44 = 0.46875;
            const double WGS84Coordinate::C46 = 0.01302083333333333333;
            const double WGS84Coordinate::C48 = 0.00712076822916666666;
            const double WGS84Coordinate::C66 = 0.36458333333333333333;
            const double WGS84Coordinate::C68 = 0.00569661458333333333;
            const double WGS84Coordinate::C88 = 0.3076171875;

            const double WGS84Coordinate::R0 = WGS84Coordinate::C00 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C02 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C04 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C06 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C08)));
            const double WGS84Coordinate::R1 = WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C22 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C04 + WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C06 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C08)));
            const double WGS84Coordinate::R2T = WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::SQUARED_ECCENTRICITY;
            const double WGS84Coordinate::R2 = WGS84Coordinate::R2T * (WGS84Coordinate::C44 - WGS84Coordinate::SQUARED_ECCENTRICITY * (WGS84Coordinate::C46 + WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C48));
            const double WGS84Coordinate::R3T = WGS84Coordinate::R2T* WGS84Coordinate::SQUARED_ECCENTRICITY;
            const double WGS84Coordinate::R3 = WGS84Coordinate::R3T * (WGS84Coordinate::C66 - WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C68);;
            const double WGS84Coordinate::R4 = WGS84Coordinate::R3T * WGS84Coordinate::SQUARED_ECCENTRICITY * WGS84Coordinate::C88;

            WGS84Coordinate::WGS84Coordinate() :
                    m_lat(0),
                    m_lon(0),
                    m_LATITUDE(WGS84Coordinate::NORTH),
                    m_LONGITUDE(WGS84Coordinate::EAST),
                    m_latitude(0),
                    m_longitude(0),
                    m_ml0(0) {
                initialize();
            }

            WGS84Coordinate::WGS84Coordinate(const double &lat, const enum LATITUDE &LAT, const double &lon, const enum LONGITUDE &LON) :
                    m_lat(lat),
                    m_lon(lon),
                    m_LATITUDE(LAT),
                    m_LONGITUDE(LON),
                    m_latitude(0),
                    m_longitude(0),
                    m_ml0(0) {
                initialize();
            }

            WGS84Coordinate::~WGS84Coordinate() {}

            WGS84Coordinate& WGS84Coordinate::operator=(const WGS84Coordinate &obj) {
                m_lat = obj.m_lat;
                m_lon = obj.m_lon;
                setLATITUDE(obj.getLATITUDE());
                setLONGITUDE(obj.getLONGITUDE());
                m_latitude = obj.m_latitude;
                m_longitude = obj.m_longitude;
                m_ml0 = obj.m_ml0;

                initialize();

                return (*this);
            }

            void WGS84Coordinate::initialize() {
                m_latitude = m_lat * cartesian::Constants::DEG2RAD;
                m_longitude = m_lon * cartesian::Constants::DEG2RAD;

                m_ml0 = mlfn(m_latitude);
            }

            double WGS84Coordinate::mlfn(const double &lat) const {
                double sin_phi = sin(lat);
                double cos_phi = cos(lat);
                cos_phi *= sin_phi;
                sin_phi *= sin_phi;

                return (R0 * lat - cos_phi * (R1 + sin_phi * (R2 + sin_phi * (R3 + sin_phi * R4))));
            }

            double WGS84Coordinate::msfn(const double &sinPhi, const double &cosPhi, const double &es) const {
                return (cosPhi / sqrt(1.0 - es * sinPhi * sinPhi));
            }

            pair<double, double> WGS84Coordinate::fwd(double lat, double lon) const {
                pair<double, double> result;

                double t = abs(lat) - cartesian::Constants::PI / 2.0;

                if ( (t > 1.0e-12) ||
                        (abs(lon) > 10.0) ) {
                    return result;
                }

                if (abs(t) < 1.0e-12) {
                    if (lat < 0.0) {
                        lat = -cartesian::Constants::PI / 2.0;
                    } else {
                        lat = cartesian::Constants::PI / 2.0;
                    }
                }

                lon -= m_longitude;

                pair<double, double> projectiveResult = project(lat, lon);
                result.first = EQUATOR_RADIUS * projectiveResult.first;
                result.second = EQUATOR_RADIUS * projectiveResult.second;

                return result;
            }

            pair<double, double> WGS84Coordinate::project(double lat, double lon) const {
                pair<double, double> result;

                if (abs(lat) < 1e-10 ) {
                    result.first = lon;
                    result.second = -m_ml0;
                } else {
                    double ms;
                    if (abs(sin(lat)) > 1e-10) {
                        ms = msfn(sin(lat), cos(lat), SQUARED_ECCENTRICITY) / sin(lat);
                    } else {
                        ms = 0.0;
                    }
                    result.first = ms * sin(lon *= sin(lat));
                    result.second = (mlfn(lat) - m_ml0) + ms * (1.0 - cos(lon));
                }

                return result;
            }

            const Point3 WGS84Coordinate::transform(const WGS84Coordinate &coordinate) const {
                pair<double, double> result = fwd(coordinate.getLatitude() * cartesian::Constants::DEG2RAD, coordinate.getLongitude() * cartesian::Constants::DEG2RAD);

                return Point3(result.first, result.second, 0);
            }

            const WGS84Coordinate WGS84Coordinate::transform(const Point3 &coordinate) const {
                return transform(coordinate, 1e-2);
            }

            const WGS84Coordinate WGS84Coordinate::transform(const Point3 &coordinate, const double &accuracy) const {
                WGS84Coordinate result(*this);
                Point3 point3Result;

                double addLon = 1e-5;
                int32_t signLon = (coordinate.getX() < 0) ? -1 : 1;
                double addLat = 1e-5;
                int32_t signLat = (coordinate.getY() < 0) ? -1 : 1;

                double epsilon = accuracy;
                if (epsilon < 0) {
                    epsilon = 1e-2;
                }

                point3Result = transform(result);
                double dOld = numeric_limits<double>::max();
                double d = abs(coordinate.getY() - point3Result.getY());
                uint32_t iterations = 0;
//                while ( (d < dOld) && (d > epsilon) && (iterations < 50000)) {
                while ( (d < dOld) && (d > epsilon) ) {
                    result = WGS84Coordinate(result.getLatitude() + signLat * addLat, result.getLATITUDE(), result.getLongitude(), result.getLONGITUDE());
                    point3Result = transform(result);
                    dOld = d;
                    d = abs(coordinate.getY() - point3Result.getY());
                    iterations++;
                }

                // Use the last transformed point3Result here.
                dOld = numeric_limits<double>::max();
                d = abs(coordinate.getX() - point3Result.getX());
                iterations = 0;
//                while ( (d < dOld) && (d > epsilon) && (iterations < 50000)) {
                while ( (d < dOld) && (d > epsilon) ) {
                    result = WGS84Coordinate(result.getLatitude(), result.getLATITUDE(), result.getLongitude() + signLon * addLon, result.getLONGITUDE());
                    point3Result = transform(result);
                    dOld = d;
                    d = abs(coordinate.getX() - point3Result.getX());
                    iterations++;
                }

                return result;
            }

            double WGS84Coordinate::getLatitude() const {
                return m_lat;
            }

            void WGS84Coordinate::setLatitude(const double &lat) {
                m_lat = lat;
            }

            double WGS84Coordinate::getLongitude() const {
                return m_lon;
            }

            void WGS84Coordinate::setLongitude(const double &lon) {
                m_lon = lon;
            }

            enum WGS84Coordinate::LATITUDE WGS84Coordinate::getLATITUDE() const {
                return m_LATITUDE;
            }

            void WGS84Coordinate::setLATITUDE(const enum WGS84Coordinate::LATITUDE &LAT) {
                m_LATITUDE = LAT;
            }

            enum WGS84Coordinate::LONGITUDE WGS84Coordinate::getLONGITUDE() const {
                return m_LONGITUDE;
            }

            void WGS84Coordinate::setLONGITUDE(const enum WGS84Coordinate::LONGITUDE &LON) {
                m_LONGITUDE = LON;
            }

            int32_t WGS84Coordinate::ID() {
                return 19;
            }

            int32_t WGS84Coordinate::getID() const {
                return 19;
            }

            const string WGS84Coordinate::getShortName() const {
                return "WGS84Coordinate";
            }

            const string WGS84Coordinate::getLongName() const {
                return "hesperia.data.environment.WGS84Coordinate";
            }

            const string WGS84Coordinate::toString() const {
                stringstream s;
                s << "(" << m_lat << ((getLATITUDE() == WGS84Coordinate::NORTH) ? "N" : "S") << "; " << m_lon << ((getLONGITUDE() == WGS84Coordinate::WEST) ? "W" : "E") << ")";
                return s.str();
            }

            ostream& WGS84Coordinate::operator<<(ostream &out) const {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Serializer> s = sf.getSerializer(out);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('l', 'a', 't') >::RESULT,
                        m_lat);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'a', 't', 'd', 'i', 'r') >::RESULT,
                        static_cast<uint32_t>(m_LATITUDE));

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('l', 'o', 'n') >::RESULT,
                        m_lon);

                s->write(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'o', 'n', 'd', 'i', 'r') >::RESULT,
                        static_cast<uint32_t>(m_LONGITUDE));

                return out;
            }

            istream& WGS84Coordinate::operator>>(istream &in) {
                SerializationFactory& sf=SerializationFactory::getInstance();

                std::shared_ptr<Deserializer> d = sf.getDeserializer(in);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('l', 'a', 't') >::RESULT,
                       m_lat);

                uint32_t l = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'a', 't', 'd', 'i', 'r') >::RESULT,
                       l);
                m_LATITUDE = static_cast<WGS84Coordinate::LATITUDE>(l);

                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL3('l', 'o', 'n') >::RESULT,
                       m_lon);

                l = 0;
                d->read(CRC32 < OPENDAVINCI_CORE_STRINGLITERAL6('l', 'o', 'n', 'd', 'i', 'r') >::RESULT,
                       l);
                m_LONGITUDE = static_cast<WGS84Coordinate::LONGITUDE>(l);

                return in;
            }

        }
    }
} // opendlv::data::environment
