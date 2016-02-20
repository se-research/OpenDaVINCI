/**
 * overtaker - Sample application for overtaking obstacles.
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

#include <cstdio>
#include <cmath>

#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/data/Container.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "Overtaker.h"

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace automotive;
        using namespace automotive::miniature;

        Overtaker::Overtaker(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "overtaker") {
        }

        Overtaker::~Overtaker() {}

        void Overtaker::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void Overtaker::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Overtaker::body() {
            const int32_t ULTRASONIC_FRONT_CENTER = 3;
            const int32_t ULTRASONIC_FRONT_RIGHT = 4;
            const int32_t INFRARED_FRONT_RIGHT = 0;
            const int32_t INFRARED_REAR_RIGHT = 2;

            const double OVERTAKING_DISTANCE = 5.5;
            const double HEADING_PARALLEL = 0.04;

            // Overall state machines for moving and measuring.
            enum StateMachineMoving { FORWARD, TO_LEFT_LANE_LEFT_TURN, TO_LEFT_LANE_RIGHT_TURN, CONTINUE_ON_LEFT_LANE, TO_RIGHT_LANE_RIGHT_TURN, TO_RIGHT_LANE_LEFT_TURN };
            enum StateMachineMeasuring { DISABLE, FIND_OBJECT_INIT, FIND_OBJECT, FIND_OBJECT_PLAUSIBLE, HAVE_BOTH_IR, HAVE_BOTH_IR_SAME_DISTANCE, END_OF_OBJECT };

            StateMachineMoving stageMoving = FORWARD;
            StateMachineMeasuring stageMeasuring = FIND_OBJECT_INIT;

            // State counter for dynamically moving back to right lane.
            int32_t stageToRightLaneRightTurn = 0;
            int32_t stageToRightLaneLeftTurn = 0;

            // Distance variables to ensure we are overtaking only stationary or slowly driving obstacles.
            double distanceToObstacle = 0;
            double distanceToObstacleOld = 0;

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
	            // 1. Get most recent vehicle data:
	            Container containerVehicleData = getKeyValueDataStore().get(Container::VEHICLEDATA);
	            VehicleData vd = containerVehicleData.getData<VehicleData> ();

	            // 2. Get most recent sensor board data:
	            Container containerSensorBoardData = getKeyValueDataStore().get(Container::USER_DATA_0);
	            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();

	            // Create vehicle control data.
	            VehicleControl vc;

                // Moving state machine.
                if (stageMoving == FORWARD) {
                    // Go forward.
                    vc.setSpeed(2);
                    vc.setSteeringWheelAngle(0);

                    stageToRightLaneLeftTurn = 0;
                    stageToRightLaneRightTurn = 0;
                }
                else if (stageMoving == TO_LEFT_LANE_LEFT_TURN) {
                    // Move to the left lane: Turn left part until both IRs see something.
                    vc.setSpeed(1);
                    vc.setSteeringWheelAngle(-25);

                    // State machine measuring: Both IRs need to see something before leaving this moving state.
                    stageMeasuring = HAVE_BOTH_IR;

                    stageToRightLaneRightTurn++;
                }
                else if (stageMoving == TO_LEFT_LANE_RIGHT_TURN) {
                    // Move to the left lane: Turn right part until both IRs have the same distance to obstacle.
                    vc.setSpeed(1);
                    vc.setSteeringWheelAngle(25);

                    // State machine measuring: Both IRs need to have the same distance before leaving this moving state.
                    stageMeasuring = HAVE_BOTH_IR_SAME_DISTANCE;

                    stageToRightLaneLeftTurn++;
                }
                else if (stageMoving == CONTINUE_ON_LEFT_LANE) {
                    // Move to the left lane: Passing stage.
                    vc.setSpeed(2);
                    vc.setSteeringWheelAngle(0);

                    // Find end of object.
                    stageMeasuring = END_OF_OBJECT;
                }
                else if (stageMoving == TO_RIGHT_LANE_RIGHT_TURN) {
                    // Move to the right lane: Turn right part.
                    vc.setSpeed(1.5);
                    vc.setSteeringWheelAngle(25);

                    stageToRightLaneRightTurn--;
                    if (stageToRightLaneRightTurn == 0) {
                        stageMoving = TO_RIGHT_LANE_LEFT_TURN;
                    }
                }
                else if (stageMoving == TO_RIGHT_LANE_LEFT_TURN) {
                    // Move to the left lane: Turn left part.
                    vc.setSpeed(.9);
                    vc.setSteeringWheelAngle(-25);

                    stageToRightLaneLeftTurn--;
                    if (stageToRightLaneLeftTurn == 0) {
                        // Start over.
                        stageMoving = FORWARD;
                        stageMeasuring = FIND_OBJECT_INIT;

                        distanceToObstacle = 0;
                        distanceToObstacleOld = 0;
                    }
                }

                // Measuring state machine.
                if (stageMeasuring == FIND_OBJECT_INIT) {
                    distanceToObstacleOld = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);
                    stageMeasuring = FIND_OBJECT;
                }
                else if (stageMeasuring == FIND_OBJECT) {
                    distanceToObstacle = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);

                    // Approaching an obstacle (stationary or driving slower than us).
                    if ( (distanceToObstacle > 0) && (((distanceToObstacleOld - distanceToObstacle) > 0) || (fabs(distanceToObstacleOld - distanceToObstacle) < 1e-2)) ) {
                        // Check if overtaking shall be started.                        
                        stageMeasuring = FIND_OBJECT_PLAUSIBLE;
                    }

                    distanceToObstacleOld = distanceToObstacle;
                }
                else if (stageMeasuring == FIND_OBJECT_PLAUSIBLE) {
                    if (sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) < OVERTAKING_DISTANCE) {
                        stageMoving = TO_LEFT_LANE_LEFT_TURN;

                        // Disable measuring until requested from moving state machine again.
                        stageMeasuring = DISABLE;
                    }
                    else {
                        stageMeasuring = FIND_OBJECT;
                    }
                }
                else if (stageMeasuring == HAVE_BOTH_IR) {
                    // Remain in this stage until both IRs see something.
                    if ( (sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT) > 0) && (sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT) > 0) ) {
                        // Turn to right.
                        stageMoving = TO_LEFT_LANE_RIGHT_TURN;
                    }
                }
                else if (stageMeasuring == HAVE_BOTH_IR_SAME_DISTANCE) {
                    // Remain in this stage until both IRs have the similar distance to obstacle (i.e. turn car)
                    // and the driven parts of the turn are plausible.
                    const double IR_FR = sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT);
                    const double IR_RR = sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT);

                    if ((fabs(IR_FR - IR_RR) < HEADING_PARALLEL) && ((stageToRightLaneLeftTurn - stageToRightLaneRightTurn) > 0)) {
                        // Straight forward again.
                        stageMoving = CONTINUE_ON_LEFT_LANE;
                    }
                }
                else if (stageMeasuring == END_OF_OBJECT) {
                    // Find end of object.
                    distanceToObstacle = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT);

                    if (distanceToObstacle < 0) {
                        // Move to right lane again.
                        stageMoving = TO_RIGHT_LANE_RIGHT_TURN;

                        // Disable measuring until requested from moving state machine again.
                        stageMeasuring = DISABLE;
                    }
                }

	            // Create container for finally sending the data.
	            Container c(Container::VEHICLECONTROL, vc);
	            // Send container.
	            getConference().send(c);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

