/**
 * irus - Distance data generator (part of simulation environment)
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

#include <sstream>
#include <string>

#include "IRUS.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/vehiclecontext/model/IRUS.h"

namespace odcore { namespace base { class KeyValueDataStore; } }

namespace irus {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace opendlv::data::environment;

    IRUS::IRUS(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsimirus") {}

    IRUS::~IRUS() {}

    void IRUS::setUp() {}

    void IRUS::tearDown() {}

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode IRUS::body() {
        stringstream sstrConfiguration;
        getKeyValueConfiguration().writeTo(sstrConfiguration);

        // Use libodsimulation's odsimirus implementation.
        string config = sstrConfiguration.str();
        opendlv::vehiclecontext::model::IRUS irus(config);
        irus.setup();

        // Use the most recent EgoState available.
        KeyValueDataStore &kvs = getKeyValueDataStore();

        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
            // Get current EgoState.
            Container c = kvs.get(Container::EGOSTATE);
            EgoState es = c.getData<EgoState>();

            // Calculate result and propagate it.
            vector<Container> toBeSent = irus.calculate(es);
            if (toBeSent.size() > 0) {
                vector<Container>::iterator it = toBeSent.begin();
                while(it != toBeSent.end()) {
                    getConference().send(*it);
                    it++;
                    Thread::usleepFor(50);
                }
            }
        }

        irus.tearDown();

        return coredata::dmcp::ModuleExitCodeMessage::OKAY;
    }

} // irus
