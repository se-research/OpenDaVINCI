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

#ifndef OPENDAVINCI_CORE_BASE_MODULE_INTERRUPTIBLEMODULE_H_
#define OPENDAVINCI_CORE_BASE_MODULE_INTERRUPTIBLEMODULE_H_

// platform.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/base/Mutex.h"
#include "core/base/module/AbstractModule.h"
#include "generated/coredata/dmcp/ModuleExitCodeMessage.h"

namespace core {
    namespace base {
        namespace module {

class Breakpoint;

            using namespace std;

            /**
             * This class is the first derivate of AbstractModule allowing
             * interuption.
             */
            class OPENDAVINCI_API InterruptibleModule : public AbstractModule {
                protected:
                    /**
                     * Constructor for any module.
                     */
                    InterruptibleModule();

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    InterruptibleModule(const InterruptibleModule&);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    InterruptibleModule& operator=(const InterruptibleModule&);

                public:
                    virtual ~InterruptibleModule();

                    /**
                     * This method sets the breakpoint in getModuleStateAndWaitForRemainingTimeInTimeslice()
                     * to interrupt regular program execution.
                     *
                     * @param bp Breakpoint to set.
                     */
                    void setBreakpoint(Breakpoint *bp);

                    /**
                     * This method executes the application body.
                     */
                    virtual coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode runModule() = 0;

                private:
                    virtual void calledGetModuleState();

                private:
                    Mutex m_breakpointMutex;
                    Breakpoint *m_breakpoint;
            };

        }
    }
} // core::base::module

#endif /*OPENDAVINCI_CORE_BASE_MODULE_INTERRUPTIBLEMODULE_H_*/
