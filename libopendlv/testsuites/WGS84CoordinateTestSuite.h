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

#ifndef HESPERIA_WGS84COORDINATETESTSUITE_H_
#define HESPERIA_WGS84COORDINATETESTSUITE_H_

#include "cxxtest/TestSuite.h"

#include <sstream>
#include <vector>

#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/WGS84Coordinate.h"
#include "opendlv/data/sensor/nmea/GPRMC.h"

using namespace std;
using namespace odcore::data;
using namespace opendlv::data;
using namespace opendlv::data::environment;
using namespace opendlv::data::environment;
using namespace opendlv::data::sensor::nmea;

class WGS84CoordinateTest : public CxxTest::TestSuite {
    public:
        void testWGS84Coordinate() {
            WGS84Coordinate w1;

            TS_ASSERT(w1.toString() == "(0N; 0E)");

            w1.setLatitude(1);
            w1.setLATITUDE(WGS84Coordinate::SOUTH);
            w1.setLongitude(2);
            w1.setLONGITUDE(WGS84Coordinate::WEST);

            stringstream s;
            s << w1;

            WGS84Coordinate w2;
            s >> w2;

            TS_ASSERT(w2.toString() == "(1S; 2W)");
            TS_ASSERT_DELTA(w2.getLatitude(), 1, 1e-5);
            TS_ASSERT_DELTA(w2.getLongitude(), 2, 1e-5);
            TS_ASSERT(w2.getLATITUDE() == WGS84Coordinate::SOUTH);
            TS_ASSERT(w2.getLONGITUDE() == WGS84Coordinate::WEST);
        }

        void testWGS84CoordinateTransformationSelf() {
            double latitude = 52.247041;
            double longitude = 10.575830;
            WGS84Coordinate w(latitude, WGS84Coordinate::NORTH, longitude, WGS84Coordinate::EAST);
            Point3 coord = w.transform(w);

            TS_ASSERT_DELTA(coord.getX(), 0, 1e-5);
            TS_ASSERT_DELTA(coord.getY(), 0, 1e-5);
            TS_ASSERT_DELTA(coord.getZ(), 0, 1e-5);
        }

        void testWGS84CoordinateTransformation() {
            double latitude = 52.247041;
            double longitude = 10.575830;
            WGS84Coordinate reference(latitude, WGS84Coordinate::NORTH, longitude, WGS84Coordinate::EAST);

            vector<WGS84Coordinate> sources;
            vector<Point3> references;

            sources.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.57417, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.573923, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573693, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573485, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573255, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572916, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572737, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572507, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572254, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248098, WGS84Coordinate::NORTH, 10.572025, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248103, WGS84Coordinate::NORTH, 10.571816, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248117, WGS84Coordinate::NORTH, 10.571768, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248133, WGS84Coordinate::NORTH, 10.571738, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248213, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248327, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248403, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248534, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248668, WGS84Coordinate::NORTH, 10.571774, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248729, WGS84Coordinate::NORTH, 10.571911, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572084, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572314, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572525, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572752, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.572928, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.573094, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573321, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573536, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573807, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.574069, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248708, WGS84Coordinate::NORTH, 10.574284, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248647, WGS84Coordinate::NORTH, 10.574367, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248459, WGS84Coordinate::NORTH, 10.574373, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248349, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248218, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248232, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.248342, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.24845, WGS84Coordinate::NORTH, 10.574433, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.24864, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.249353, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.249477, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.249604, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.249728, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.249848, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250854, WGS84Coordinate::NORTH, 10.573687, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250793, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250664, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.573547, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.573351, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.25057, WGS84Coordinate::NORTH, 10.573139, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572931, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572728, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.572624, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.25065, WGS84Coordinate::NORTH, 10.572478, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250711, WGS84Coordinate::NORTH, 10.572463, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250774, WGS84Coordinate::NORTH, 10.572469, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250875, WGS84Coordinate::NORTH, 10.572582, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.572776, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250943, WGS84Coordinate::NORTH, 10.572966, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250971, WGS84Coordinate::NORTH, 10.573175, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.250999, WGS84Coordinate::NORTH, 10.573372, WGS84Coordinate::EAST));
            sources.push_back(WGS84Coordinate(52.251011, WGS84Coordinate::NORTH, 10.573568, WGS84Coordinate::EAST));

            references.push_back(Point3(-113.37, 116.84, 0));
            references.push_back(Point3(-130.24, 116.84, 0));
            references.push_back(Point3(-145.95, 116.62, 0));
            references.push_back(Point3(-160.16, 116.62, 0));
            references.push_back(Point3(-175.87, 117.40, 0));
            references.push_back(Point3(-190.28, 117.40, 0));
            references.push_back(Point3(-199.02, 117.40, 0));
            references.push_back(Point3(-211.24, 117.40, 0));
            references.push_back(Point3(-226.95, 117.40, 0));
            references.push_back(Point3(-244.23, 117.40, 0));
            references.push_back(Point3(-259.87, 117.62, 0));
            references.push_back(Point3(-274.15, 118.18, 0));
            references.push_back(Point3(-277.43, 119.74, 0));
            references.push_back(Point3(-279.47, 121.52, 0));
            references.push_back(Point3(-280.43, 130.42, 0));
            references.push_back(Point3(-280.43, 143.10, 0));
            references.push_back(Point3(-280.43, 151.56, 0));
            references.push_back(Point3(-280.43, 166.14, 0));
            references.push_back(Point3(-277.01, 181.05, 0));
            references.push_back(Point3(-267.65, 187.83, 0));
            references.push_back(Point3(-255.84, 188.61, 0));
            references.push_back(Point3(-240.13, 188.61, 0));
            references.push_back(Point3(-225.72, 188.61, 0));
            references.push_back(Point3(-210.22, 188.61, 0));
            references.push_back(Point3(-198.20, 188.39, 0));
            references.push_back(Point3(-186.86, 188.39, 0));
            references.push_back(Point3(-171.36, 188.05, 0));
            references.push_back(Point3(-156.67, 188.05, 0));
            references.push_back(Point3(-138.16, 188.05, 0));
            references.push_back(Point3(-120.27, 188.05, 0));
            references.push_back(Point3(-105.59, 185.49, 0));
            references.push_back(Point3(-99.92, 178.70, 0));
            references.push_back(Point3(-99.51, 157.78, 0));
            references.push_back(Point3(-99.71, 145.54, 0));
            references.push_back(Point3(-99.71, 130.97, 0));
            references.push_back(Point3(-95.62, 132.53, 0));
            references.push_back(Point3(-95.62, 144.77, 0));
            references.push_back(Point3(-95.41, 156.78, 0));
            references.push_back(Point3(-95.62, 177.92, 0));
            references.push_back(Point3(-190.68, 257.26, 0));
            references.push_back(Point3(-190.89, 271.06, 0));
            references.push_back(Point3(-190.89, 285.19, 0));
            references.push_back(Point3(-190.68, 298.99, 0));
            references.push_back(Point3(-190.27, 312.34, 0));
            references.push_back(Point3(-146.49, 431.07, 0));
            references.push_back(Point3(-146.35, 424.28, 0));
            references.push_back(Point3(-146.49, 417.50, 0));
            references.push_back(Point3(-146.49, 403.14, 0));
            references.push_back(Point3(-155.91, 393.24, 0));
            references.push_back(Point3(-169.30, 392.46, 0));
            references.push_back(Point3(-183.78, 392.68, 0));
            references.push_back(Point3(-197.98, 392.46, 0));
            references.push_back(Point3(-211.85, 392.46, 0));
            references.push_back(Point3(-218.95, 393.24, 0));
            references.push_back(Point3(-228.92, 401.59, 0));
            references.push_back(Point3(-229.94, 408.37, 0));
            references.push_back(Point3(-229.53, 415.38, 0));
            references.push_back(Point3(-221.82, 426.62, 0));
            references.push_back(Point3(-208.57, 431.07, 0));
            references.push_back(Point3(-195.59, 434.19, 0));
            references.push_back(Point3(-181.32, 437.30, 0));
            references.push_back(Point3(-167.86, 440.42, 0));
            references.push_back(Point3(-154.48, 441.75, 0));

            for (uint32_t i = 0; i < sources.size(); i++) {
                WGS84Coordinate w = sources.at(i);

                Point3 coord = reference.transform(w);
                TS_ASSERT_DELTA(coord.getX(), references.at(i).getX(), 1e-2);
                TS_ASSERT_DELTA(coord.getY(), references.at(i).getY(), 1e-2);
            }
        }

        void testInverseProjection() {
            double latitude = 52.247041;
            double longitude = 10.575830;
            WGS84Coordinate reference(latitude, WGS84Coordinate::NORTH, longitude, WGS84Coordinate::EAST);

            vector<WGS84Coordinate> references;
            vector<Point3> sources;

            references.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.57417, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.573923, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573693, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573485, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573255, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572916, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572737, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572507, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572254, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248098, WGS84Coordinate::NORTH, 10.572025, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248103, WGS84Coordinate::NORTH, 10.571816, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248117, WGS84Coordinate::NORTH, 10.571768, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248133, WGS84Coordinate::NORTH, 10.571738, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248213, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248327, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248403, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248534, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248668, WGS84Coordinate::NORTH, 10.571774, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248729, WGS84Coordinate::NORTH, 10.571911, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572084, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572314, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572525, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572752, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.572928, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.573094, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573321, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573536, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573807, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.574069, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248708, WGS84Coordinate::NORTH, 10.574284, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248647, WGS84Coordinate::NORTH, 10.574367, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248459, WGS84Coordinate::NORTH, 10.574373, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248349, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248218, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248232, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248342, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.24845, WGS84Coordinate::NORTH, 10.574433, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.24864, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249353, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249477, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249604, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249728, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249848, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250854, WGS84Coordinate::NORTH, 10.573687, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250793, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250664, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.573547, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.573351, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.25057, WGS84Coordinate::NORTH, 10.573139, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572931, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572728, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.572624, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.25065, WGS84Coordinate::NORTH, 10.572478, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250711, WGS84Coordinate::NORTH, 10.572463, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250774, WGS84Coordinate::NORTH, 10.572469, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250875, WGS84Coordinate::NORTH, 10.572582, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.572776, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250943, WGS84Coordinate::NORTH, 10.572966, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250971, WGS84Coordinate::NORTH, 10.573175, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250999, WGS84Coordinate::NORTH, 10.573372, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.251011, WGS84Coordinate::NORTH, 10.573568, WGS84Coordinate::EAST));

            sources.push_back(Point3(-113.37, 116.84, 0));
            sources.push_back(Point3(-130.24, 116.84, 0));
            sources.push_back(Point3(-145.95, 116.62, 0));
            sources.push_back(Point3(-160.16, 116.62, 0));
            sources.push_back(Point3(-175.87, 117.40, 0));
            sources.push_back(Point3(-190.28, 117.40, 0));
            sources.push_back(Point3(-199.02, 117.40, 0));
            sources.push_back(Point3(-211.24, 117.40, 0));
            sources.push_back(Point3(-226.95, 117.40, 0));
            sources.push_back(Point3(-244.23, 117.40, 0));
            sources.push_back(Point3(-259.87, 117.62, 0));
            sources.push_back(Point3(-274.15, 118.18, 0));
            sources.push_back(Point3(-277.43, 119.74, 0));
            sources.push_back(Point3(-279.47, 121.52, 0));
            sources.push_back(Point3(-280.43, 130.42, 0));
            sources.push_back(Point3(-280.43, 143.10, 0));
            sources.push_back(Point3(-280.43, 151.56, 0));
            sources.push_back(Point3(-280.43, 166.14, 0));
            sources.push_back(Point3(-277.01, 181.05, 0));
            sources.push_back(Point3(-267.65, 187.83, 0));
            sources.push_back(Point3(-255.84, 188.61, 0));
            sources.push_back(Point3(-240.13, 188.61, 0));
            sources.push_back(Point3(-225.72, 188.61, 0));
            sources.push_back(Point3(-210.22, 188.61, 0));
            sources.push_back(Point3(-198.20, 188.39, 0));
            sources.push_back(Point3(-186.86, 188.39, 0));
            sources.push_back(Point3(-171.36, 188.05, 0));
            sources.push_back(Point3(-156.67, 188.05, 0));
            sources.push_back(Point3(-138.16, 188.05, 0));
            sources.push_back(Point3(-120.27, 188.05, 0));
            sources.push_back(Point3(-105.59, 185.49, 0));
            sources.push_back(Point3(-99.92, 178.70, 0));
            sources.push_back(Point3(-99.51, 157.78, 0));
            sources.push_back(Point3(-99.71, 145.54, 0));
            sources.push_back(Point3(-99.71, 130.97, 0));
            sources.push_back(Point3(-95.62, 132.53, 0));
            sources.push_back(Point3(-95.62, 144.77, 0));
            sources.push_back(Point3(-95.41, 156.78, 0));
            sources.push_back(Point3(-95.62, 177.92, 0));
            sources.push_back(Point3(-190.68, 257.26, 0));
            sources.push_back(Point3(-190.89, 271.06, 0));
            sources.push_back(Point3(-190.89, 285.19, 0));
            sources.push_back(Point3(-190.68, 298.99, 0));
            sources.push_back(Point3(-190.27, 312.34, 0));
            sources.push_back(Point3(-146.49, 431.07, 0));
            sources.push_back(Point3(-146.35, 424.28, 0));
            sources.push_back(Point3(-146.49, 417.50, 0));
            sources.push_back(Point3(-146.49, 403.14, 0));
            sources.push_back(Point3(-155.91, 393.24, 0));
            sources.push_back(Point3(-169.30, 392.46, 0));
            sources.push_back(Point3(-183.78, 392.68, 0));
            sources.push_back(Point3(-197.98, 392.46, 0));
            sources.push_back(Point3(-211.85, 392.46, 0));
            sources.push_back(Point3(-218.95, 393.24, 0));
            sources.push_back(Point3(-228.92, 401.59, 0));
            sources.push_back(Point3(-229.94, 408.37, 0));
            sources.push_back(Point3(-229.53, 415.38, 0));
            sources.push_back(Point3(-221.82, 426.62, 0));
            sources.push_back(Point3(-208.57, 431.07, 0));
            sources.push_back(Point3(-195.59, 434.19, 0));
            sources.push_back(Point3(-181.32, 437.30, 0));
            sources.push_back(Point3(-167.86, 440.42, 0));
            sources.push_back(Point3(-154.48, 441.75, 0));

            for (uint32_t i = 0; i < sources.size(); i++) {
                Point3 p  = sources.at(i);

                WGS84Coordinate w = reference.transform(p);
                TS_ASSERT_DELTA(w.getLatitude(), references.at(i).getLatitude(), 1e-2);
                TS_ASSERT_DELTA(w.getLongitude(), references.at(i).getLongitude(), 1e-2);
            }
        }

        void testInverseProjectionWithAccuracy() {
            double latitude = 52.247041;
            double longitude = 10.575830;
            WGS84Coordinate reference(latitude, WGS84Coordinate::NORTH, longitude, WGS84Coordinate::EAST);

            vector<WGS84Coordinate> references;
            vector<Point3> sources;

            references.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.57417, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248091, WGS84Coordinate::NORTH, 10.573923, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573693, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248089, WGS84Coordinate::NORTH, 10.573485, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573255, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572916, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572737, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572507, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248096, WGS84Coordinate::NORTH, 10.572254, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248098, WGS84Coordinate::NORTH, 10.572025, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248103, WGS84Coordinate::NORTH, 10.571816, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248117, WGS84Coordinate::NORTH, 10.571768, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248133, WGS84Coordinate::NORTH, 10.571738, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248213, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248327, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248403, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248534, WGS84Coordinate::NORTH, 10.571724, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248668, WGS84Coordinate::NORTH, 10.571774, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248729, WGS84Coordinate::NORTH, 10.571911, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572084, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572314, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572525, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248736, WGS84Coordinate::NORTH, 10.572752, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.572928, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248734, WGS84Coordinate::NORTH, 10.573094, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573321, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573536, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.573807, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248731, WGS84Coordinate::NORTH, 10.574069, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248708, WGS84Coordinate::NORTH, 10.574284, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248647, WGS84Coordinate::NORTH, 10.574367, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248459, WGS84Coordinate::NORTH, 10.574373, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248349, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248218, WGS84Coordinate::NORTH, 10.57437, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248232, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.248342, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.24845, WGS84Coordinate::NORTH, 10.574433, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.24864, WGS84Coordinate::NORTH, 10.57443, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249353, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249477, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249604, WGS84Coordinate::NORTH, 10.573035, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249728, WGS84Coordinate::NORTH, 10.573038, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.249848, WGS84Coordinate::NORTH, 10.573044, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250854, WGS84Coordinate::NORTH, 10.573687, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250793, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250664, WGS84Coordinate::NORTH, 10.573685, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.573547, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.573351, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.25057, WGS84Coordinate::NORTH, 10.573139, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572931, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250568, WGS84Coordinate::NORTH, 10.572728, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250575, WGS84Coordinate::NORTH, 10.572624, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.25065, WGS84Coordinate::NORTH, 10.572478, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250711, WGS84Coordinate::NORTH, 10.572463, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250774, WGS84Coordinate::NORTH, 10.572469, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250875, WGS84Coordinate::NORTH, 10.572582, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250915, WGS84Coordinate::NORTH, 10.572776, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250943, WGS84Coordinate::NORTH, 10.572966, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250971, WGS84Coordinate::NORTH, 10.573175, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.250999, WGS84Coordinate::NORTH, 10.573372, WGS84Coordinate::EAST));
            references.push_back(WGS84Coordinate(52.251011, WGS84Coordinate::NORTH, 10.573568, WGS84Coordinate::EAST));

            sources.push_back(Point3(-113.37, 116.84, 0));
            sources.push_back(Point3(-130.24, 116.84, 0));
            sources.push_back(Point3(-145.95, 116.62, 0));
            sources.push_back(Point3(-160.16, 116.62, 0));
            sources.push_back(Point3(-175.87, 117.40, 0));
            sources.push_back(Point3(-190.28, 117.40, 0));
            sources.push_back(Point3(-199.02, 117.40, 0));
            sources.push_back(Point3(-211.24, 117.40, 0));
            sources.push_back(Point3(-226.95, 117.40, 0));
            sources.push_back(Point3(-244.23, 117.40, 0));
            sources.push_back(Point3(-259.87, 117.62, 0));
            sources.push_back(Point3(-274.15, 118.18, 0));
            sources.push_back(Point3(-277.43, 119.74, 0));
            sources.push_back(Point3(-279.47, 121.52, 0));
            sources.push_back(Point3(-280.43, 130.42, 0));
            sources.push_back(Point3(-280.43, 143.10, 0));
            sources.push_back(Point3(-280.43, 151.56, 0));
            sources.push_back(Point3(-280.43, 166.14, 0));
            sources.push_back(Point3(-277.01, 181.05, 0));
            sources.push_back(Point3(-267.65, 187.83, 0));
            sources.push_back(Point3(-255.84, 188.61, 0));
            sources.push_back(Point3(-240.13, 188.61, 0));
            sources.push_back(Point3(-225.72, 188.61, 0));
            sources.push_back(Point3(-210.22, 188.61, 0));
            sources.push_back(Point3(-198.20, 188.39, 0));
            sources.push_back(Point3(-186.86, 188.39, 0));
            sources.push_back(Point3(-171.36, 188.05, 0));
            sources.push_back(Point3(-156.67, 188.05, 0));
            sources.push_back(Point3(-138.16, 188.05, 0));
            sources.push_back(Point3(-120.27, 188.05, 0));
            sources.push_back(Point3(-105.59, 185.49, 0));
            sources.push_back(Point3(-99.92, 178.70, 0));
            sources.push_back(Point3(-99.51, 157.78, 0));
            sources.push_back(Point3(-99.71, 145.54, 0));
            sources.push_back(Point3(-99.71, 130.97, 0));
            sources.push_back(Point3(-95.62, 132.53, 0));
            sources.push_back(Point3(-95.62, 144.77, 0));
            sources.push_back(Point3(-95.41, 156.78, 0));
            sources.push_back(Point3(-95.62, 177.92, 0));
            sources.push_back(Point3(-190.68, 257.26, 0));
            sources.push_back(Point3(-190.89, 271.06, 0));
            sources.push_back(Point3(-190.89, 285.19, 0));
            sources.push_back(Point3(-190.68, 298.99, 0));
            sources.push_back(Point3(-190.27, 312.34, 0));
            sources.push_back(Point3(-146.49, 431.07, 0));
            sources.push_back(Point3(-146.35, 424.28, 0));
            sources.push_back(Point3(-146.49, 417.50, 0));
            sources.push_back(Point3(-146.49, 403.14, 0));
            sources.push_back(Point3(-155.91, 393.24, 0));
            sources.push_back(Point3(-169.30, 392.46, 0));
            sources.push_back(Point3(-183.78, 392.68, 0));
            sources.push_back(Point3(-197.98, 392.46, 0));
            sources.push_back(Point3(-211.85, 392.46, 0));
            sources.push_back(Point3(-218.95, 393.24, 0));
            sources.push_back(Point3(-228.92, 401.59, 0));
            sources.push_back(Point3(-229.94, 408.37, 0));
            sources.push_back(Point3(-229.53, 415.38, 0));
            sources.push_back(Point3(-221.82, 426.62, 0));
            sources.push_back(Point3(-208.57, 431.07, 0));
            sources.push_back(Point3(-195.59, 434.19, 0));
            sources.push_back(Point3(-181.32, 437.30, 0));
            sources.push_back(Point3(-167.86, 440.42, 0));
            sources.push_back(Point3(-154.48, 441.75, 0));

            for (uint32_t i = 0; i < sources.size(); i++) {
                Point3 p  = sources.at(i);

                WGS84Coordinate w = reference.transform(p, 10);
                TS_ASSERT_DELTA(w.getLatitude(), references.at(i).getLatitude(), 10);
                TS_ASSERT_DELTA(w.getLongitude(), references.at(i).getLongitude(), 10);
            }
        }

        void testGPRMC() {
            double latitude = 52.247041;
            double longitude = 10.575830;

            WGS84Coordinate reference(latitude, WGS84Coordinate::NORTH, longitude, WGS84Coordinate::EAST);

            TimeStamp ts(1240926174, 0);
            GPRMC gprmc;
            gprmc.setTimeStamp(ts);
            gprmc.setCoordinate(reference);

            stringstream ref;
            ref << "$GPRMC,134254,A,5214.8225,N,01034.5498,E,0.0,0.0,280409,0.0,E,S*c" << endl;

            TS_ASSERT(gprmc.toString() == ref.str());
            TS_ASSERT(gprmc.getTimeStamp().getSeconds() == ts.getSeconds());
            TS_ASSERT_DELTA(gprmc.getCoordinate().getLatitude(), latitude, 1e-6);
            TS_ASSERT(gprmc.getCoordinate().getLATITUDE() == WGS84Coordinate::NORTH);
            TS_ASSERT_DELTA(gprmc.getCoordinate().getLongitude(), longitude, 1e-6);
            TS_ASSERT(gprmc.getCoordinate().getLONGITUDE() == WGS84Coordinate::EAST);

            stringstream sstr;
            sstr << gprmc;

            GPRMC gprmc2;
            sstr >> gprmc2;
            TS_ASSERT(gprmc2.toString() == ref.str());
            TS_ASSERT(gprmc2.getTimeStamp().getSeconds() == ts.getSeconds());
            TS_ASSERT_DELTA(gprmc2.getCoordinate().getLatitude(), latitude, 1e-6);
            TS_ASSERT(gprmc2.getCoordinate().getLATITUDE() == WGS84Coordinate::NORTH);
            TS_ASSERT_DELTA(gprmc2.getCoordinate().getLongitude(), longitude, 1e-6);
            TS_ASSERT(gprmc2.getCoordinate().getLONGITUDE() == WGS84Coordinate::EAST);
        }
};

#endif /*HESPERIA_WGS84COORDINATETESTSUITE_H_*/
