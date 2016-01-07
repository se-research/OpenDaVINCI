/**
 * vehicle - Vehicle dynamics (part of simulation environment)
 * Copyright (C) 2016 Christian Berger
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

#include <sstream>
#include <string>
#include <vector>

#include "core/base/Thread.h"
#include "core/data/Container.h"
#include "vehiclecontext/model/SimplifiedBicycleModel.h"
#include "generated/automotive/VehicleControl.h"

#include "Vehicle.h"

namespace core { namespace base { class KeyValueDataStore; } }

namespace vehicle {

    using namespace std;
    using namespace core::base;
    using namespace core::data;

    Vehicle::Vehicle(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimvehicle") {}

    Vehicle::~Vehicle() {}

    void Vehicle::setUp() {}

    void Vehicle::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode Vehicle::body() {
        stringstream sstrConfiguration;
        getKeyValueConfiguration().writeTo(sstrConfiguration);

        // Use libodsimulation's odsimirus implementation.
        string config = sstrConfiguration.str();
        vehiclecontext::model::SimplifiedBicycleModel simplifiedBicycleModel(config);
        simplifiedBicycleModel.setup();

        // Use the most recent EgoState available.
        KeyValueDataStore &kvs = getKeyValueDataStore();

        TimeStamp previousTime;

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Get current VehicleControl.
            Container c = kvs.get(Container::VEHICLECONTROL);
            automotive::VehicleControl vc = c.getData<automotive::VehicleControl>();

            TimeStamp currentTime;
            const double timeStep = (currentTime.toMicroseconds() - previousTime.toMicroseconds()) / (1000.0 * 1000.0);

            // Calculate result and propagate it.
            vector<Container> toBeSent = simplifiedBicycleModel.calculate(vc, timeStep);
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();
                while(it != toBeSent.end()) {
                    getConference().send(*it);
                    it++;
                    Thread::usleepFor(50);
                }
            }

<<<<<<< HEAD
            if (vc.getFlashingLightsRight()) {
                cout << "Turn ON right flashing lights." << endl;
            }
           
            EgoState es = lbmn.computeEgoState();
            
            // Get vehicle data.
            VehicleData vd = lbmn.getVehicleData();
            cerr << "VehicleData: '" << vd.toString() << "'" << endl;

            Container container(es);
            getConference().send(container);

            // Send vehicledata.
            Container c2(vd);
            getConference().send(c2);
=======
            previousTime = currentTime;
>>>>>>> master
        }

        simplifiedBicycleModel.tearDown();

<<<<<<< HEAD
            if (fc.getFlashingLightsRight()) {
                cout << "Turn ON right flashing lights." << endl;
            }
            else {
            }
           
            EgoState es = lbm.computeEgoState();
            
            // Get vehicle data.
            VehicleData vd = lbm.getVehicleData();
            cerr << "VehicleData: '" << vd.toString() << "'" << endl;

            Container container(es);
            getConference().send(container);

            // Send vehicledata.
            Container c2(vd);
            getConference().send(c2);
        }
=======
>>>>>>> master
        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // vehicle
