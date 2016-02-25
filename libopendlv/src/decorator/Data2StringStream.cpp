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

#include <ostream>
#include <string>

#include "opendavinci/odcore/data/Container.h"
#include "opendlv/data/environment/EgoState.h"
#include "opendlv/data/planning/Route.h"
#include "opendlv/decorator/Data2StringStream.h"

namespace opendlv {
    namespace decorator {

        using namespace std;
        using namespace odcore::data;
        using namespace odcore::base;
        using namespace opendlv::data::environment;
        using namespace opendlv::data::planning;

        Data2StringStream::Data2StringStream(stringstream &sstr) :
            m_sstr(sstr) {}

        Data2StringStream::~Data2StringStream() {}

        void Data2StringStream::toStringStream(Container &c) {
            if (c.getDataType() == opendlv::data::environment::EgoState::ID()) {
                toStringStream(c.getData<EgoState>());
            }

            if (c.getDataType() == opendlv::data::planning::Route::ID()) {
                toStringStream(c.getData<Route>());
            }
        }

        void Data2StringStream::toStringStream(const EgoState &es) {
            m_sstr << es.toString();
        }

        void Data2StringStream::toStringStream(const Route &r) {
            m_sstr << r.toString();
        }

    }
} // opendlv::decorator
