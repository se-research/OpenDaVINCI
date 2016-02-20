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

#include <iostream>
#include <string>

#include "opendavinci/odcore/data/SerializableData.h"
#include "opendlv/data/situation/SituationNode.h"
#include "opendlv/situation/SituationPrettyPrinter.h"

namespace opendlv {
    namespace situation {

        using namespace std;
        using namespace odcore::data;
        using namespace data::situation;

        SituationPrettyPrinter::SituationPrettyPrinter() {}

        SituationPrettyPrinter::~SituationPrettyPrinter() {}

        void SituationPrettyPrinter::visit(SituationNode &node) {
            try {
                SerializableData &s = dynamic_cast<SerializableData&>(node);
                clog << s.toString() << endl;
            } catch (...) {}
        }

    }
} // opendlv::situation
