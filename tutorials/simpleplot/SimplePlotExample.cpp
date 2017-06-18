/**
 * OpenDaVINCI - Tutorial.
 * Copyright (C) 2017 Christian Berger
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

#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/generated/odcockpit/SimplePlot.h>
#include <opendavinci/generated/odcockpit/RuntimeConfiguration.h>

#include "SimplePlotExample.h"

using namespace std;

// We add some of OpenDaVINCI's namespaces for the sake of readability.
using namespace odcore::base::module;

SimplePlotExample::SimplePlotExample(const int32_t &argc, char **argv) :
    TimeTriggeredConferenceClientModule(argc, argv, "SimplePlotExample")
    {}

SimplePlotExample::~SimplePlotExample() {}

void SimplePlotExample::setUp() {
    cout << "This method is called before the component's body is executed." << endl;
}

void SimplePlotExample::tearDown() {
    cout << "This method is called after the program flow returns from the component's body." << endl;
}

odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode SimplePlotExample::body() {
    cout << "Hello from SimplePlot!" << endl;

    cout << "This is my name: " << getName() << endl;
    cout << "This is my execution frequency: " << getFrequency() << endl;
    cout << "This is my identifier: " << getIdentifier() << endl;

    odcore::base::Mutex inputMutex;
    double input = 1;

    double result = 0;
    double kP = 1;
    double kI = 1;
    double kD = 1;
    while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
        {
            // Do some calculation as example.
            odcore::base::Lock l(inputMutex);
            result += input * kP + input * kI + input * kD;
        }

        {
            // Do some calculation as example.
            odcore::base::Lock l(inputMutex);

            // Send "debug" values to odcockpit for display or plotting.
            odcockpit::SimplePlot sp;
            sp.putTo_MapOfValues("result", result);
            sp.putTo_MapOfValues("kP", kP);
            sp.putTo_MapOfValues("kI", kI);
            sp.putTo_MapOfValues("kD", kD);
            sp.putTo_MapOfValues("input", input);

            odcore::data::Container c(sp);
            getConference().send(c);
        }

        {
            // Try to read interactively updated values from RuntimeConfiguration object sent from odcockpit.
            odcore::data::Container c = getKeyValueDataStore().get(odcockpit::RuntimeConfiguration::ID());
            odcockpit::RuntimeConfiguration rc = c.getData<odcockpit::RuntimeConfiguration>();

            odcore::base::Lock l(inputMutex);
            if (rc.containsKey_MapOfParameters("input")) {
                input = rc.getValueForKey_MapOfParameters("input");
            }
            if (rc.containsKey_MapOfParameters("kP")) {
                kP = rc.getValueForKey_MapOfParameters("kP");
            }
            if (rc.containsKey_MapOfParameters("kI")) {
                kI = rc.getValueForKey_MapOfParameters("kI");
            }
            if (rc.containsKey_MapOfParameters("kD")) {
                kD = rc.getValueForKey_MapOfParameters("kD");
            }
        }
    }

    return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
}

int32_t main(int32_t argc, char **argv) {
    SimplePlotExample tte(argc, argv);

    return tte.runModule();
}

