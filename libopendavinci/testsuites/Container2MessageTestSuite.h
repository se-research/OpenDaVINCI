/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
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

#ifndef CORE_CONTAINER2MESSAGE_H_
#define CORE_CONTAINER2MESSAGE_H_

#include <iostream>

#include "cxxtest/TestSuite.h"          // for TS_ASSERT, TestSuite

#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/reflection/Message.h"
#include "opendavinci/odcore/reflection/MessagePrettyPrinterVisitor.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h"

using namespace std;
using namespace odcore::data;
using namespace odcore::reflection;

class Container2MessageTest : public CxxTest::TestSuite {
    public:
        void testMapping() {
            odcore::data::player::PlayerStatus ps;
            Container c(ps);

            bool successfullyMapped = false;
            odcore::reflection::Message msg = GeneratedHeaders_OpenDaVINCI_Helper::__map(c, successfullyMapped);

            TS_ASSERT(successfullyMapped);

            MessagePrettyPrinterVisitor mppv;
            msg.accept(mppv);
            mppv.getOutput(cout);

            TS_ASSERT(msg.getID() == odcore::data::player::PlayerStatus::ID());
            TS_ASSERT(msg.getLongName() == "odcore.data.player.PlayerStatus");
            TS_ASSERT(msg.getShortName() == "PlayerStatus");
        }
};

#endif /*CORE_CONTAINER2MESSAGE_H_*/
