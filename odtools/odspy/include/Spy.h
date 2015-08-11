/**
 * odspy - Tool for printint content from containers to stdout in a user-readable representation.
 * Copyright (C) 2015 Christian Berger
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

#ifndef SPY_H_
#define SPY_H_

#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/base/FIFOQueue.h"

namespace odspy {

    using namespace std;

    /**
     * This class can be used to simply display data distributed
     * using a conference.
     */
    class Spy : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Spy(const Spy &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Spy& operator=(const Spy &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Spy(const int32_t &argc, char **argv);

            virtual ~Spy();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            core::base::FIFOQueue m_fifo;

            virtual void setUp();

            virtual void tearDown();
    };

} // odspy

#endif /*SPY_H_*/
