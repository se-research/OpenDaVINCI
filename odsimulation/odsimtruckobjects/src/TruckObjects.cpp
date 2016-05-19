/**
 * odsimtruckobjects - Component to simulate distances acquired on the GCDC truck.
 * Copyright (C) 2016 Christian Berger
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
#include <sstream>
#include <string>

#include "TruckObjects.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/vehiclecontext/model/IRUS.h"
#include "automotivedata/generated/automotive/miniature/SensorBoardData.h"
#include "automotivedata/generated/from/opendlv/perception/Object.h"
#include "automotivedata/generated/from/opendlv/model/Direction.h"

namespace odcore { namespace base { class KeyValueDataStore; } }

namespace gcdc16 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace opendlv::data::environment;

    TruckObjects::TruckObjects(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimirus") {}

    TruckObjects::~TruckObjects() {}

    void TruckObjects::setUp() {}

    void TruckObjects::tearDown() {}

    odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode TruckObjects::body() {
        stringstream sstrConfiguration;
        getKeyValueConfiguration().writeTo(sstrConfiguration);

        // Use libodsimulation's odsimirus implementation.
        string config = sstrConfiguration.str();
        opendlv::vehiclecontext::model::IRUS irus(config);
        irus.setup();

        // Use the most recent EgoState available.
        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
            // Get current EgoState.
            Container c = kvs.get(opendlv::data::environment::EgoState::ID());
            EgoState es = c.getData<EgoState>();

            // Calculate result and propagate it.
            vector<Container> toBeSent = irus.calculate(es);
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();

                // Translate the first object into a from::opendlv::perception::Object.
                if (it->getDataType() == automotive::miniature::SensorBoardData::ID()) {
                    automotive::miniature::SensorBoardData sbd = it->getData<automotive::miniature::SensorBoardData>();
                    const double d = sbd.getValueForKey_MapOfDistances(0);
                    if (d > 0) {
                        from::opendlv::model::Direction dir(-4.0 * cartesian::Constants::DEG2RAD, 0);
                        from::opendlv::perception::Object obj;
                        obj.setDistance(d);
                        obj.setDirection(dir);
                        obj.setObjectId(2412);

                        Container c2(obj);
                        getConference().send(c2);
                    }
                }
            }
        }

        irus.tearDown();

        return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // irus
