/**
 * odrecorderh264 - Tool for recording data and encoding video streams with h264.
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

#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include "RecorderH264.h"

namespace odrecorderh264 {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odtools::recorder;

    RecorderH264::RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData) :
        Recorder(url, memorySegmentSize, numberOfSegments, threading, dumpSharedData) {
        registerRecorderDelegate(odcore::data::image::SharedImage::ID(), this);
    }

    RecorderH264::~RecorderH264() {}

    Container RecorderH264::process(Container &c) {
        cout << "RecorderH264: Got called for " << c.getDataType() << endl;
        return c;
    }

} // odrecorderh264
