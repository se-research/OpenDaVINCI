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

#include "MyService.hpp"

using namespace std;

// Your class needs to implement the method void beforeStop().
void MyService::beforeStop() {
    // This block is executed right before the thread will be stopped.
    cout << "This method is called right before isRunning will return false." << endl;        
}

// Your class needs to implement the method void run().
void MyService::run() {
    // Here, you can do some initialization of resources (e.g. data structures and the like).
    cout << "Here, I can do some initialization as the calling thread, which will start this service, will be blocked until serviceReady() has been called." << endl;

    serviceReady();

    // This is the body of the concurrently executed method.
    while (isRunning()) {
        cout << "This message is printed every second." << endl;        

        const uint32_t ONE_SECOND = 1000 * 1000;
        odcore::base::Thread::usleepFor(ONE_SECOND);
    }
}

int32_t main(int32_t argc, char **argv) {
    MyService s;

    s.start();
    const uint32_t ONE_SECOND = 1000 * 1000;
    odcore::base::Thread::usleepFor(10 * ONE_SECOND);

    s.stop();
}

