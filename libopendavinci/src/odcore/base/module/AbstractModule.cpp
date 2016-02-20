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

#include <cstring>
#include <csignal>
#include <cstdlib>

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Thread.h"
#include "opendavinci/odcore/base/module/AbstractModule.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/wrapper/DisposalService.h"

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;
            using namespace exceptions;

            // Signal handler structs.
#ifndef WIN32
            struct sigaction ourSignalHandler;
            struct sigaction ignoreSignal;
#endif

            // Initialization of the static attribute.
            vector<AbstractModule*> AbstractModule::m_listOfModules;

            // Function declaration.
            void signalHandler(int32_t signal);
            // Function declaration.
            void finalize();

            void signalHandler(int32_t signal) {
                if ( (signal == SIGINT) ||
                     (signal == SIGTERM) ) {
                    vector<AbstractModule*>::iterator it = AbstractModule::getListOfModules().begin();
                    while (it != AbstractModule::getListOfModules().end()) {
                        AbstractModule *m = *it++;
                        if (m != NULL) {
                            m->setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
                        }
                    }
                }
            }

            void finalize() {
                if (AbstractModule::getListOfModules().size() == 0) {
                    wrapper::DisposalService &ds = wrapper::DisposalService::getInstance();
                    ds.cleanUpFinally();
                }
            }

            AbstractModule::AbstractModule() :
                m_moduleStateMutex(),
                m_moduleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING) {
                m_listOfModules.push_back(this);

                atexit(finalize);

#ifdef WIN32 /* The following code is for Windows. */
                // Catch signal SIGINT (ctrl-c) from console.
                if (::signal(SIGINT, &signalHandler) == SIG_ERR) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Failed to register signal SIGINT.");
                }
#endif

#ifndef WIN32 /* The following code is only supported on POSIX. */
                memset(&ourSignalHandler, 0, sizeof(ourSignalHandler));
                ourSignalHandler.sa_handler = &signalHandler;

                // Catch signal SIGINT (ctrl-c) from console.
                if (::sigaction(SIGINT, &ourSignalHandler, NULL) < 0) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Failed to register signal SIGINT.");
                }

                // Catch signal SIGTERM.
                if (::sigaction(SIGTERM, &ourSignalHandler, NULL) < 0) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Failed to register signal SIGTERM.");
                }

                memset(&ignoreSignal, 0, sizeof(ignoreSignal));
                ignoreSignal.sa_handler = SIG_IGN;

                // Ignore signal SIGPIPE that is triggered in the case that a socket connection is closed.
                // If this call would be missing the program would simply be closed (which is the unintended behavior).
                if (::sigaction(SIGPIPE, &ignoreSignal, NULL) < 0) {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Failed to ignore signal SIGPIPE.");
                }
#endif
            }

            AbstractModule::~AbstractModule() {
                vector<AbstractModule*>::iterator it = AbstractModule::getListOfModules().begin();
                while (it != AbstractModule::getListOfModules().end()) {
                    AbstractModule *m = *it;
                    if (m == this) {
                        break;
                    }
                    ++it;
                }

                if (it != AbstractModule::getListOfModules().end()) {
                    AbstractModule::getListOfModules().erase(it);
                }
            }

            vector<AbstractModule*>& AbstractModule::getListOfModules() {
                return m_listOfModules;
            }

            void AbstractModule::setModuleState(const coredata::dmcp::ModuleStateMessage::ModuleState &s) {
                Lock l(m_moduleStateMutex);
                m_moduleState = s;
            }

            void AbstractModule::wait() {
                Thread::usleepFor(25);
            }

            void AbstractModule::calledGetModuleState() {
                wait();
            }

            coredata::dmcp::ModuleStateMessage::ModuleState AbstractModule::getModuleState() {
                Lock l(m_moduleStateMutex);
                return m_moduleState;
            }

            coredata::dmcp::ModuleStateMessage::ModuleState AbstractModule::getModuleStateAndWaitForRemainingTimeInTimeslice() {
                calledGetModuleState();

                return getModuleState();
            }

        }
    }
} // odcore::base
