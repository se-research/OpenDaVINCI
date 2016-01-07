/**
 * odredirector - Tool for dumping data to stdout or reading back from stdin
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

#ifndef REDIRECTOR_H_
#define REDIRECTOR_H_

#include <map>
#include <string>

#include "core/opendavinci.h"
#include "core/SharedPointer.h"
#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace core { namespace wrapper { class SharedMemory; } }

namespace odredirector {

    using namespace std;

    /**
     * This class can be used to simply display data distributed
     * using a conference.
     */
    class Redirector : public core::base::module::TimeTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Redirector(const Redirector &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Redirector& operator=(const Redirector &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Redirector(const int32_t &argc, char **argv);

            virtual ~Redirector();

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            void parseAdditionalCommandLineParameters(const int &argc, char **argv);

            virtual void setUp();

            virtual void tearDown();

        private:
            bool m_fromstdin;
            bool m_tostdout;
            int32_t m_jpegQuality;
            map<string, core::SharedPointer<core::wrapper::SharedMemory> > m_mapOfSharedMemories;
    };

} // odredirector

#endif /*REDIRECTOR_H_*/
