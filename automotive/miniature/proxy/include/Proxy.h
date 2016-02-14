/**
 * proxy - Sample application to encapsulate HW/SW interfacing with embedded systems.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef PROXY_H_
#define PROXY_H_

#include <map>
#include <memory>

#include "core/base/module/TimeTriggeredConferenceClientModule.h"
#include "core/data/Container.h"
#include "tools/recorder/Recorder.h"

#include "Camera.h"

namespace automotive {
    namespace miniature {

        using namespace std;

        /**
         * This class wraps the software/hardware interface board.
         */
        class Proxy : public core::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                Proxy(const Proxy &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                Proxy& operator=(const Proxy &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                Proxy(const int32_t &argc, char **argv);

                virtual ~Proxy();

                coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:
                virtual void setUp();

                virtual void tearDown();

                void distribute(core::data::Container c);

            private:
                auto_ptr<tools::recorder::Recorder> m_recorder;
                auto_ptr<Camera> m_camera;
        };

    }
} // automotive::miniature

#endif /*PROXY_H_*/
