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

#include <stdint.h>
#include <iostream>
#include <opendavinci/odcore/base/Thread.h>

#include "MyRealtimeService.hpp"

using namespace std;

MyRealtimeService::MyRealtimeService(const enum PERIOD &period) :
    odcore::base::RealtimeService(period) {}

void MyRealtimeService::nextTimeSlice() {
    cout << "This message is printed every 100 ms." << endl;        
}

int32_t main(int32_t argc, char **argv) {
    MyRealtimeService rts(odcore::base::RealtimeService::ONEHUNDREDMILLISECONDS);

    rts.start();

    const uint32_t ONE_SECOND = 1000 * 1000;
    odcore::base::Thread::usleepFor(5 * ONE_SECOND);

    rts.stop();
}

