/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2015 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <iostream>

#include "TimeTriggerExample.h"

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace core::base;

TimeTriggerExample::TimeTriggerExample(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "TimeTriggerExample")
	{}

TimeTriggerExample::~TimeTriggerExample() {}

void TimeTriggerExample::setUp() {
    cout << "This method is called before the component's body is executed." << endl;
}

void TimeTriggerExample::tearDown() {
    cout << "This method is called after the program flow returns from the component's body." << endl;
}

ModuleState::MODULE_EXITCODE TimeTriggerExample::body() {
    cout << "Hello OpenDaVINCI World!" << endl;

    cout << "This is my name: " << getName() << endl;
    cout << "This is my execution frequency: " << getFrequency() << endl;
    cout << "This is my identifier: " << getIdentifier() << endl;

    cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key1") << endl;
    cout << "  " << getKeyValueConfiguration().getValue<uint32_t>("timetriggerexample.key2") << endl;
    cout << "  " << getKeyValueConfiguration().getValue<float>("timetriggerexample.key3") << endl;
    cout << "  " << getKeyValueConfiguration().getValue<string>("timetriggerexample.key4") << endl;

	while (getModuleStateAndWaitForRemainingTimeInTimeslice() == ModuleState::RUNNING) {
        cout << "Inside the main processing loop." << endl;
    }

    return ModuleState::OKAY;
}

int32_t main(int32_t argc, char **argv) {
    TimeTriggerExample tte(argc, argv);

    return tte.runModule();
}

