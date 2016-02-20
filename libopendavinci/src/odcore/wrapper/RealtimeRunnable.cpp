/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifdef HAVE_LINUX_RT
    #include <sched.h>
    #include <sys/time.h>
#endif
#include <string>

#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/wrapper/RealtimeRunnable.h"

namespace odcore {
    namespace wrapper {

        using namespace std;

        RealtimeRunnable::RealtimeRunnable(const uint32_t &periodInMicroseconds) :
            m_periodInMicroseconds(periodInMicroseconds) {
        }

        RealtimeRunnable::~RealtimeRunnable() {}

        void RealtimeRunnable::run() {
#ifdef HAVE_LINUX_RT
            // Setup realtime task using FIFO scheduling.
            struct sched_param param;
            param.sched_priority = REALTIME_PRIORITY;

            if (::sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
                throw string("[core::wrapper::RealtimeRunnable] Failed to configure scheduler. Are you superuser?");
            }

            struct timespec waitForSlice;

            // Get actual time.
            ::clock_gettime(CLOCK_REALTIME , &waitForSlice);

            // Take next time slice and adjust to start after next completed second.
            waitForSlice.tv_sec++;
            waitForSlice.tv_nsec = 0;

            // Main realtime execution loop.
            while (isRunning()) {
                // Wait for next time slice.
                ::clock_nanosleep(CLOCK_REALTIME, TIMER_ABSTIME, &waitForSlice, NULL);

                // Get time before slice.
                odcore::data::TimeStamp before;

                // Execute slice.
                nextTimeSlice();

                // Get time after slice.
                odcore::data::TimeStamp after;

                // Compute delta using monotonic clock.
                const long delta = after.toMicroseconds() - before.toMicroseconds();

                if (isRunning() && !((m_periodInMicroseconds - delta) > 0)) {
                    throw string("[core::wrapper::RealtimeRunnable] Time slice ran out of time defined in microseconds!");
                }

                // Calculate waiting period; as clock_nanosleep is a sleepUntil call,
                // we simply define the next period and let clock_nanosleep do the job
                // for us. 
                waitForSlice.tv_nsec += (m_periodInMicroseconds * MICROSECOND); // in nanoseconds.
                while (waitForSlice.tv_nsec >= SECOND) {
                    waitForSlice.tv_nsec -= SECOND;
                    waitForSlice.tv_sec++;
                }
            }
#else
            throw string("[core::wrapper::RealtimeRunnable] Realtime is only available on Linux with rt-preempt.");
#endif
        }

    }
} // odcore::wrapper
