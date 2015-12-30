/**
 * egocontroller - Manual control of the vehicle (part of simulation environment)
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

#include <cstdio>
#include <algorithm>
#include <iostream>

#include "Controller.h"
#include "EgoController.h"
#include "ForceControlBehaviour.h"
#include "ForceControlBehaviourBicycleModel.h"
#include "ForceControlBehaviourSimplifiedBicycleModel.h"
#include "JoystickController.h"
#include "KeyBoardController.h"
#include "LinearBicycleModelBehaviour.h"
#include "SimpleControlBehaviour.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/io/conference/ContainerConference.h"
#include "generated/coredata/dmcp/ModuleStateMessage.h"
#include "hesperia/data/environment/Point3.h"

namespace egocontroller {

class ControlBehaviour;

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace hesperia::data::environment;
    using namespace hesperia::data::environment;

    EgoController::EgoController(const int &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "EgoController"),
            m_device()
    {}

    EgoController::~EgoController() {}

    void EgoController::setUp() {}

    void EgoController::tearDown() {}

    ForceControlBehaviour* EgoController::createForceControlBehaviour() {
        KeyValueConfiguration kvc = getKeyValueConfiguration();

        return new ForceControlBehaviour(
                kvc.getValue<double>("egocontroller.minimumTurningRadius"),
                kvc.getValue<double>("egocontroller.vehicleMass"),
                kvc.getValue<double>("egocontroller.adherenceCoefficient"),
                kvc.getValue<double>("egocontroller.idleForce"),
                kvc.getValue<double>("egocontroller.Ksteering"),
                kvc.getValue<double>("egocontroller.maximumSteeringRate"),
                kvc.getValue<double>("egocontroller.Kthrottle"),
                kvc.getValue<double>("egocontroller.tauBrake"),
                kvc.getValue<double>("egocontroller.KstaticBrake"),
                kvc.getValue<double>("egocontroller.KdynamicBrake") );
    }

    ForceControlBehaviourBicycleModel* EgoController::createForceControlBehaviourBicycleModel() {
        KeyValueConfiguration kvc = getKeyValueConfiguration();

        return new ForceControlBehaviourBicycleModel(
                kvc.getValue<double>("egocontroller.minimumTurningRadius"),
                kvc.getValue<double>("egocontroller.vehicleMass"),
                kvc.getValue<double>("egocontroller.adherenceCoefficient"),
                kvc.getValue<double>("egocontroller.idleForce"),
                kvc.getValue<double>("egocontroller.Ksteering"),
                kvc.getValue<double>("egocontroller.maximumSteeringRate"),
                kvc.getValue<double>("egocontroller.Kthrottle"),
                kvc.getValue<double>("egocontroller.tauBrake"),
                kvc.getValue<double>("egocontroller.KstaticBrake"),
                kvc.getValue<double>("egocontroller.KdynamicBrake"),
                kvc.getValue<double>("egocontroller.distanceCenterOfMassToFrontAxle"),
                kvc.getValue<double>("egocontroller.distanceCenterOfMassToRearAxle"),
                kvc.getValue<double>("egocontroller.momentOfInertia"),
                kvc.getValue<double>("egocontroller.skewStiffnessFront"),
                kvc.getValue<double>("egocontroller.skewStiffnessRear"));
    }

    ForceControlBehaviourSimplifiedBicycleModel* EgoController::createForceControlBehaviourSimplifiedBicycleModel() {
        KeyValueConfiguration kvc = getKeyValueConfiguration();

        return new ForceControlBehaviourSimplifiedBicycleModel(
                kvc.getValue<double>("egocontroller.minimumTurningRadius"),
                kvc.getValue<double>("egocontroller.vehicleMass"),
                kvc.getValue<double>("egocontroller.adherenceCoefficient"),
                kvc.getValue<double>("egocontroller.idleForce"),
                kvc.getValue<double>("egocontroller.Ksteering"),
                kvc.getValue<double>("egocontroller.maximumSteeringRate"),
                kvc.getValue<double>("egocontroller.Kthrottle"),
                kvc.getValue<double>("egocontroller.tauBrake"),
                kvc.getValue<double>("egocontroller.KstaticBrake"),
                kvc.getValue<double>("egocontroller.KdynamicBrake"),
                kvc.getValue<double>("egocontroller.wheelbase") );
    }

    LinearBicycleModelBehaviour* EgoController::createLinearBicycleModelBehaviour() {
        cerr << "Using linearbicyclenew control." << endl;

        stringstream vehicleTranslation;
        vehicleTranslation << "egocontroller.start";
        Point3 translation(getKeyValueConfiguration().getValue<string>(vehicleTranslation.str()));

        stringstream vehicleRotZ;
        vehicleRotZ << "egocontroller.rotZ";
        const double rotZ = getKeyValueConfiguration().getValue<double>(vehicleRotZ.str());

        KeyValueConfiguration kvc = getKeyValueConfiguration();

        return new LinearBicycleModelBehaviour(translation, rotZ,
                kvc.getValue<double>("egocontroller.LinearBicycleModelNew.minimumTurningRadiusLeft"),
                kvc.getValue<double>("egocontroller.LinearBicycleModelNew.minimumTurningRadiusRight"),
                kvc.getValue<double>("egocontroller.LinearBicycleModelNew.wheelbase"),
                kvc.getValue<double>("egocontroller.LinearBicycleModelNew.maxSpeed") );
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode EgoController::body() {
        KeyValueConfiguration kvc = getKeyValueConfiguration();

        m_device = kvc.getValue<string>("egocontroller.device");
        transform(m_device.begin(), m_device.end(), m_device.begin(), ptr_fun(::tolower));

        string behaviorType = kvc.getValue<string>("egocontroller.behavior");
        transform(behaviorType.begin(), behaviorType.end(), behaviorType.begin(), ptr_fun(::tolower));

        ControlBehaviour* behaviour = NULL;
        if (behaviorType == "force") {
            cerr << "Using force control." << endl;
            behaviour = createForceControlBehaviour();
        } else if (behaviorType == "forcebicycle") {
            cerr << "Using bicycle control." << endl;
            behaviour = createForceControlBehaviourBicycleModel();
        } else if (behaviorType == "forcesimplifiedbicycle") {
            cerr << "Using simplified bicycle control." << endl;
            behaviour = createForceControlBehaviourSimplifiedBicycleModel();
        } else if (behaviorType == "simple") {
            cerr << "Using simple control." << endl;

            stringstream vehicleTranslation;
            vehicleTranslation << "egocontroller.start";
            Point3 translation(getKeyValueConfiguration().getValue<string>(vehicleTranslation.str()));

            stringstream vehicleRotZ;
            vehicleRotZ << "egocontroller.rotZ";
            const double rotZ = getKeyValueConfiguration().getValue<double>(vehicleRotZ.str());

            behaviour = new SimpleControlBehaviour(translation, rotZ);
        } else if (behaviorType == "linearbicyclenew") {
            behaviour = createLinearBicycleModelBehaviour();
        }

        if (behaviour == NULL) {
            cerr << "Cannot create control behavior " << behaviorType << endl;
            return coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;
        }

        Controller* controller = NULL;
        if (m_device == "keyboard") {
            controller = new KeyboardController(*behaviour, 'w', 's','a','d','b');
        }
        else {
            // Try joystick.
            controller = new JoystickController(*behaviour, m_device);
        }

        if (controller == NULL) {
            cerr << "Cannot create controller for " << m_device << endl;
            return coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;
        }


        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            controller->doWork();

            Container container(Container::EGOSTATE, controller->getEgoState());
/*
        // Update internal data.
        m_vehicleData.setPosition(position);
        m_vehicleData.setHeading(m_heading);
        m_vehicleData.setVelocity(velocity);
        m_vehicleData.setSpeed(m_speed);
        m_vehicleData.setV_log(0);
        m_vehicleData.setV_batt(0);
        // For fake :-)
        m_vehicleData.setTemp(19.5 + cos(m_heading + m_deltaHeading));
        m_vehicleData.setRelTraveledPath(relDrivenPath);
//        const double FAULT = (1+(rand()%10)/300.0);
        const double FAULT = 1.0;
        m_vehicleData.setAbsTraveledPath(m_vehicleData.getAbsTraveledPath() + (relDrivenPath * FAULT));
//cerr << "FAULT: " << FAULT << ", tD: " << m_vehicleData.getAbsTraveledPath() << endl;
*/

            getConference().send(container);
        }

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }
} // egocontroller
