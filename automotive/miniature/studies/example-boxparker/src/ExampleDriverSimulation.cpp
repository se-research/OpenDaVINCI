/**
 * example-boxparker - This test suite demonstrates how to
 *                     compose a simulation including an SCNX
 *                     scenario.
 * Copyright (C) 2012 - 2016 Christian Berger
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
#include <sstream>
#include <string>

#include "opendavinci/odcontext/base/DirectInterface.h"
#include "opendavinci/odcontext/base/RecordingContainer.h"
#include "opendavinci/odcontext/base/RuntimeControl.h"
#include "opendavinci/odcontext/base/RuntimeEnvironment.h"
#include "opendlv/vehiclecontext/VehicleRuntimeControl.h"
#include "opendlv/vehiclecontext/model/IRUS.h"
#include "opendlv/vehiclecontext/model/SimplifiedBicycleModel.h"
#include "opendlv/vehiclecontext/report/DistanceToObjectsReport.h"

#include "ExampleDriverSimulation.h"

// Include file from system-under-test.
#include "BoxParker.h"

using namespace std;
using namespace odcontext::base;
using namespace opendlv::vehiclecontext;
using namespace opendlv::vehiclecontext::model;
using namespace opendlv::vehiclecontext::report;
using namespace automotive::miniature;

namespace simulation {

    bool ExampleDriverSimulation::run() {
        bool retVal = true;

        // 0. Setup system's configuration.
        stringstream sstrConfiguration;

        sstrConfiguration << "global.scenario = file://../../Parking_boxes.scnx" << endl
              << endl
              << "odsimvehicle.posX = 0                     # Initial position X in cartesian coordinates." << endl
              << "odsimvehicle.posY = 0                     # Initial position Y in cartesian coordinates." << endl
              << "odsimvehicle.headingDEG = 90" << endl
              << "odsimvehicle.model=LinearBicycleModelNew  # Which motion model to be used: LinearBicycleModelNew or LinearBicycleModel (for CaroloCup 2013!)." << endl
              << "odsimvehicle.LinearBicycleModelNew.withSpeedController=1          # iff 1: use the VehicleControl.m_speed field; otherwise, ignore m_speed and use VehicleControl.m_acceleration field" << endl
              << "odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusLeft=4.85  # Minimum turning radius to the left (for calculating maximum steering angle to the left); Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.minimumTurningRadiusRight=5.32 # Minimum turning radius to the right (for calculating maximum steering angle to the right); Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.wheelbase=2.65                 # Wheelbase; Attention! we used data from the miniature vehicle Meili and thus, all values are scaled by factor 10 to be compatible with the simulation!" << endl
              << "odsimvehicle.LinearBicycleModelNew.invertedSteering=0             # iff 0: interpret neg. steering wheel angles as steering to the left; iff 1: otherwise" << endl
              << "odsimvehicle.LinearBicycleModelNew.maxSpeed=2.0                   # maxium speed in m/ss" << endl
//                  << "odsimvehicle.LinearBicycleModelNew.faultModel.noise = 1.0         # Fault model noise data: interval [ -noise .. +noise ] random noise data will be added to the absolutely travelled distance." << endl
              << endl
              << "#" << endl
              << "# CONFIGURATION FOR ODSIMIRUS (Infrared and ultrasonic simulation)" << endl
              << "#" << endl
              << "odsimirus.numberOfSensors = 6                   # Number of configured sensors." << endl
              << "odsimirus.showPolygons = 1                      # Show explicitly all polygons." << endl
              << endl
              << "odsimirus.sensor0.id = 0                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor0.name = Infrared_FrontRight    # Name of the sensor" << endl
              << "odsimirus.sensor0.rotZ = -90                    # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor0.translation = (1.0;-1.0;0.0)  # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor0.angleFOV = 5                  # In degrees." << endl
              << "odsimirus.sensor0.distanceFOV = 3               # In meters." << endl
              << "odsimirus.sensor0.clampDistance = 2.9           # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor0.showFOV = 1                   # Show FOV in monitor." << endl
              << endl
              << "odsimirus.sensor1.id = 1                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor1.name = Infrared_Rear          # Name of the sensor" << endl
              << "odsimirus.sensor1.rotZ = -180                   # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor1.translation = (-1.0;0.0;0.0)  # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor1.angleFOV = 5                  # In degrees." << endl
              << "odsimirus.sensor1.distanceFOV = 3               # In meters." << endl
              << "odsimirus.sensor1.clampDistance = 2.9           # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor1.showFOV = 1                   # Show FOV in monitor." << endl
              << endl
              << "odsimirus.sensor2.id = 2                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor2.name = Infrared_RearRight     # Name of the sensor" << endl
              << "odsimirus.sensor2.rotZ = -90                     # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor2.translation = (-1.0;-1.0;0.0)   # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor2.angleFOV = 5                  # In degrees." << endl
              << "odsimirus.sensor2.distanceFOV = 3               # In meters." << endl
              << "odsimirus.sensor2.clampDistance = 2.9           # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor2.showFOV = 1                   # Show FOV in monitor." << endl
//                  << "odsimirus.sensor2.faultModel.skip = 0.1         # Fault model from the range [0 .. 1] where 0 = skip no distances for returning and 1 = skip all distances for returning; a value of 0.1 would mean that 10% of the distance to be returned will be skipped." << endl
//                  << "odsimirus.sensor2.faultModel.noise = 4.5        # Fault model noise data: interval [ -noise .. +noise ] random noise data will be added to the sensor data." << endl
              << endl
              << "odsimirus.sensor3.id = 3                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor3.name = UltraSonic_FrontCenter # Name of the sensor" << endl
              << "odsimirus.sensor3.rotZ = 0                      # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor3.translation = (1.0;0.0;0.0)   # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor3.angleFOV = 20                 # In degrees." << endl
              << "odsimirus.sensor3.distanceFOV = 40              # In meters." << endl
              << "odsimirus.sensor3.clampDistance = 39            # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor3.showFOV = 1                   # Show FOV in monitor." << endl
              << endl
              << "odsimirus.sensor4.id = 4                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor4.name = UltraSonic_FrontRight  # Name of the sensor" << endl
              << "odsimirus.sensor4.rotZ = -45                    # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor4.translation = (1.0;-1.0;0.0)  # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor4.angleFOV = 20                 # In degrees." << endl
              << "odsimirus.sensor4.distanceFOV = 40              # In meters." << endl
              << "odsimirus.sensor4.clampDistance = 39            # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor4.showFOV = 1                   # Show FOV in monitor." << endl
              << endl
              << "odsimirus.sensor5.id = 5                        # This ID is used in SensorBoardData structure." << endl
              << "odsimirus.sensor5.name = UltraSonic_RearRight   # Name of the sensor" << endl
              << "odsimirus.sensor5.rotZ = -135                     # Rotation of the sensor around the Z-axis in degrees, positive = counterclockwise, negative = clockwise, 0 = 12am, -90 = 3pm, ..." << endl
              << "odsimirus.sensor5.translation = (-1.0;-1.0;0.0)   # Translation (X;Y;Z) w.r.t. vehicle's center" << endl
              << "odsimirus.sensor5.angleFOV = 20                 # In degrees." << endl
              << "odsimirus.sensor5.distanceFOV = 40              # In meters." << endl
              << "odsimirus.sensor5.clampDistance = 39            # Any distances greater than this distance will be ignored and -1 will be returned." << endl
              << "odsimirus.sensor5.showFOV = 1                   # Show FOV in monitor." << endl;

        // 1. Setup runtime control.
        DirectInterface di("225.0.0.100", 100, sstrConfiguration.str());
        VehicleRuntimeControl vrc(di);
        vrc.setup(RuntimeControl::TAKE_CONTROL);

        // 2. Setup application.
        string argv0("boxparker");
        string argv1("--cid=100");
        string argv2("--freq=10");
        string argv3("--verbose=1");
        int32_t argc = 4;
        char **argv;
        argv = new char*[4];
        argv[0] = const_cast<char*>(argv0.c_str());
        argv[1] = const_cast<char*>(argv1.c_str());
        argv[2] = const_cast<char*>(argv2.c_str());
        argv[3] = const_cast<char*>(argv3.c_str());

        // 3. Instantiate actual System-Under-Test.
        BoxParker myDriver(argc, argv);

        // 4. System's context components.
        const float FREQ = 10;

        SimplifiedBicycleModel bicycleControl(FREQ, sstrConfiguration.str());
        IRUS irus(FREQ, sstrConfiguration.str());

        // 5. Distance to live obstacles reporter.
        const float THRESHOLD = 1.0;
        DistanceToObjectsReport distanceReporter(sstrConfiguration.str(), THRESHOLD);

        // 6. Define recorder.
        const uint32_t MEMORY_SEGMENT_SIZE = 1000 * 1000;
        const uint32_t NUMBER_OF_MEMORY_SEGMENTS = 10;
        RecordingContainer recorder(FREQ, "file://ExampleDriverSimulation.rec", MEMORY_SEGMENT_SIZE, NUMBER_OF_MEMORY_SEGMENTS);

        // 7. Compose simulation of system's context.
        RuntimeEnvironment rte;
        rte.add(myDriver);
        rte.add(bicycleControl);
        rte.add(irus);
        rte.add(distanceReporter);
        rte.add(recorder);

        // 8. Run application under supervision of RuntimeControl for maximum 100s.
        retVal &= vrc.run(rte, 100) == RuntimeControl::APPLICATIONS_FINISHED;

        // 9. Check the identified gaps with the specification.
        vector<double> foundGaps = myDriver.getFoundGaps();
        vector<double>::iterator it = foundGaps.begin();
        uint16_t i = 0;
        while (it != foundGaps.end()) {
            const double d = (*it++);
            cout << ++i << "-th gap: " << d << endl;
            switch (i) {
                case 1: retVal &= (fabs(d - 0.403339) < 1e-5); break;
                case 2: retVal &= (fabs(d - 0.806678) < 1e-5); break;
                case 3: retVal &= (fabs(d - 1.21002) < 1e-5); break;
                case 4: retVal &= (fabs(d - 1.00835) < 1e-5); break;
                case 5: retVal &= (fabs(d - 0.504174) < 1e-5); break;
                case 6: retVal &= (fabs(d - 0.705844) < 1e-5); break;
                case 7: retVal &= (fabs(d - 0.605009) < 1e-5); break;
                case 8: retVal &= (fabs(d - 3.52922) < 1e-5); break;

            }
        }

        // And finally clean up.
        vrc.tearDown();

        return retVal;
    }
}

