/**
 * odplayerh264 - Tool for replaying video streams encoded with h264.
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

#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/generated/odcore/data/image/H264Frame.h"

#include "PlayerH264.h"

namespace odplayerh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::player;

    PlayerH264::PlayerH264(const odcore::io::URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const bool &threading) :
        Player(url, autoRewind, memorySegmentSize, numberOfMemorySegments, threading) {
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), this);
    }

    PlayerH264::~PlayerH264() {
        registerPlayerDelegate(odcore::data::image::H264Frame::ID(), NULL);
    }

    Container PlayerH264::process(Container &c) {
        Container replacementContainer = c;

        cout << "PlayerH264 called for " << c.getDataType() << endl;

        if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
            odcore::data::image::H264Frame h264frame = c.getData<odcore::data::image::H264Frame>();
            cout << "Replace " << h264frame.toString() << endl;
        }

        return c;
    }

} // odplayerh264
