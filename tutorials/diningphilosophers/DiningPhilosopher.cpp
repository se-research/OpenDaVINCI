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
#include <cstdlib>
#include <iostream>
#include <opendavinci/odcore/base/Lock.h>
#include <opendavinci/odcore/base/Thread.h>

#include "DiningPhilosopher.hpp"

using namespace std;
using namespace odcore::base;

// Constructor of a dining philosopher.
DiningPhilosopher::DiningPhilosopher(const uint32_t &numberOfPhilosophers,
                                     const uint32_t &id,
                                     std::vector<Mutex*> &silverware) :
    m_numberOfPhilosophers(numberOfPhilosophers),
    m_id(id),
    m_silverware(silverware)
{}

// Your class needs to implement the method void beforeStop().
void DiningPhilosopher::beforeStop() {}

// Your class needs to implement the method void run().
void DiningPhilosopher::run() {
    // Inform calling thread that this new thread is ready.
    serviceReady();

    const uint32_t ONE_SECOND = 1000 * 1000;

    // This is the body of the concurrently executed method.
    while (isRunning()) {
        cout << "Philosopher " << m_id << " is thinking...";
        odcore::base::Thread::usleepFor(ONE_SECOND * (1.0 + (rand()/(float)RAND_MAX)));
        cout << "done." << endl;

        cout << "Philosopher " << m_id << " is trying to grab left fork...";
        Lock left(*m_silverware[m_id]);
        cout << "success." << endl;

        cout << "Philosopher " << m_id << " is trying to grab right fork...";
        Lock right(*m_silverware[(m_id + 1)%m_numberOfPhilosophers]);
        cout << "success." << endl;

        cout << "Philosopher " << m_id << " is eating..." << endl;        
        odcore::base::Thread::usleepFor(ONE_SECOND * (1.0 + (rand()/(float)RAND_MAX)));
        cout << "done." << endl;
    }
}

int32_t main(int32_t argc, char **argv) {
    const uint32_t ONE_SECOND = 1000 * 1000;
    const uint32_t PHILOSOPHERS = 5;

    // Create silverware.
    vector<Mutex*> silverware;
    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        silverware.push_back(new Mutex());
    }

    // Create dining philosophers.
    vector<DiningPhilosopher*> philosophers;
    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        philosophers.push_back(new DiningPhilosopher(PHILOSOPHERS, i,   silverware));
    }

    // Start the dinner.
    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        philosophers[i]->start();
    }

    // Wait for ten seconds.
    odcore::base::Thread::usleepFor(10 * ONE_SECOND);

    // Stop dinner.
    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        philosophers[i]->stop();
    }

    // Clean up dinner.
    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        delete philosophers[i];
    }

    for (uint32_t i = 0; i < PHILOSOPHERS; i++) {
        delete silverware[i];
    }
}

