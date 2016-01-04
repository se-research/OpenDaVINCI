/**
 * boxparker - Sample application for realizing a box parking car.
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

#include <iostream>

#include "core/data/Container.h"

#include "GeneratedHeaders_CoreData.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "BoxParker.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace core::base;
        using namespace core::base::module;
        using namespace core::data;
        using namespace automotive;

        BoxParker::BoxParker(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "BoxParker"),
            m_foundGaps() {}

        BoxParker::~BoxParker() {}

        void BoxParker::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void BoxParker::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        vector<double> BoxParker::getFoundGaps() const {
            return m_foundGaps;
        }

        // This method will do the main data processing job.
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode BoxParker::body() {
            double distanceOld = 0;
            double absPathStart = 0;
            double absPathEnd = 0;

            int stageMoving = 0;
            int stageMeasuring = 0;

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
                VehicleData vd = containerVehicleData.getData<VehicleData> ();

                // 2. Get most recent sensor board data describing virtual sensor data:
                Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();

                // Create vehicle control data.
                VehicleControl vc;

                // Moving state machine.
                if (stageMoving == 0) {
                    // Go forward.
                    vc.setSpeed(1);
                    vc.setSteeringWheelAngle(0);
                }
                if ((stageMoving > 0) && (stageMoving < 20)) {
                    // Move slightly forward.
                    vc.setSpeed(1);
                    vc.setSteeringWheelAngle(0);
                    stageMoving++;
                }
                if ((stageMoving >= 20) && (stageMoving < 25)) {
                    // Stop.
                    vc.setSpeed(0);
                    vc.setSteeringWheelAngle(0);
                    stageMoving++;
                }
                if ((stageMoving >= 25) && (stageMoving < 80)) {
                    // Backwards, steering wheel to the right.
                    vc.setSpeed(-2);
                    vc.setSteeringWheelAngle(25);
                    stageMoving++;
                }
                if (stageMoving >= 80) {
                    // Stop.
                    vc.setSpeed(0);
                    vc.setSteeringWheelAngle(0);

                    stageMoving++;
                }
                if (stageMoving >= 150) {
                    // End component.
                    break;
                }

                // Measuring state machine.
                switch (stageMeasuring) {
                    case 0:
                        {
                            // Initialize measurement.
                            distanceOld = sbd.getValueForKey_MapOfDistances(2);
                            stageMeasuring++;
                        }
                    break;
                    case 1:
                        {
                            // Checking for distance sequence +, -.
                            if ((distanceOld > 0) && (sbd.getValueForKey_MapOfDistances(2) < 0)) {
                                // Found distance sequence +, -.
                                stageMeasuring = 2;
                                absPathStart = vd.getAbsTraveledPath();
                            }
                            distanceOld = sbd.getValueForKey_MapOfDistances(2);
                        }
                    break;
                    case 2:
                        {
                            // Checking for distance sequence -, +.
                            if ((distanceOld < 0) && (sbd.getValueForKey_MapOfDistances(2) > 0)) {
                                // Found distance sequence -, +.
                                stageMeasuring = 1;
                                absPathEnd = vd.getAbsTraveledPath();

                                const double GAP_SIZE = (absPathEnd - absPathStart);
                                cerr << "Size = " << GAP_SIZE << endl;
                                m_foundGaps.push_back(GAP_SIZE);

                                if ((stageMoving < 1) && (GAP_SIZE > 3.5)) {
                                    stageMoving = 1;
                                }
                            }
                            distanceOld = sbd.getValueForKey_MapOfDistances(2);
                        }
                    break;
                }

                // Create container for finally sending the data.
                Container c(Container::VEHICLECONTROL, vc);
                // Send container.
                getConference().send(c);
            }

            return coredata::dmcp::ModuleExitCodeMessage::OKAY;
        }

    } // miniature
} // automotive

