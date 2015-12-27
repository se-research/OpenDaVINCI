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

#include <errno.h>
#include <cmath>
#include <iostream>

#include "core/base/CommandLineArgument.h"
#include "core/base/CommandLineParser.h"
#include "core/base/Thread.h"
#include "core/base/module/AbstractCIDModule.h"
#include "core/data/TimeStamp.h"
#include "core/macros.h"

namespace core {
    namespace base {
        namespace module {

            using namespace std;
            using namespace exceptions;

            // Initialization of the static attribute.
            int32_t AbstractCIDModule::m_verbose = 0;

            AbstractCIDModule::AbstractCIDModule(const int32_t &argc, char **argv) throw (InvalidArgumentException) :
                    m_frequency(1),
                    m_identifier(),
                    m_multicastGroup(),
                    m_CID(0),
                    m_profiling(false),
                    m_realtime(false),
                    m_realtimePriority(0) {
                m_verbose = false;
                parseCommandLine(argc, argv);
            }

            AbstractCIDModule::~AbstractCIDModule() {}

            void AbstractCIDModule::parseCommandLine(const int32_t &argc, char **argv) throw (InvalidArgumentException) {
                if (argc <= 1) {
                    errno = 0;
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                  "Invalid number of arguments. At least a conference group id (--cid=) needed.");
                }

                CommandLineParser cmdParser;
                cmdParser.addCommandLineArgument("id");
                cmdParser.addCommandLineArgument("cid");
                cmdParser.addCommandLineArgument("freq");
                cmdParser.addCommandLineArgument("verbose");
                cmdParser.addCommandLineArgument("profiling");
                cmdParser.addCommandLineArgument("realtime");

                cmdParser.parse(argc, argv);

                CommandLineArgument cmdArgumentID = cmdParser.getCommandLineArgument("id");
                CommandLineArgument cmdArgumentCID = cmdParser.getCommandLineArgument("cid");
                CommandLineArgument cmdArgumentFREQ = cmdParser.getCommandLineArgument("freq");
                CommandLineArgument cmdArgumentVERBOSE = cmdParser.getCommandLineArgument("verbose");
                CommandLineArgument cmdArgumentPROFILING = cmdParser.getCommandLineArgument("profiling");
                CommandLineArgument cmdArgumentREALTIME = cmdParser.getCommandLineArgument("realtime");

                if (cmdArgumentVERBOSE.isSet()) {
                    AbstractCIDModule::m_verbose = cmdArgumentVERBOSE.getValue<int32_t>();;
                }

                if (cmdArgumentID.isSet()) {
                    m_identifier = cmdArgumentID.getValue<string>();
                }

                if (cmdArgumentFREQ.isSet()) {
                    m_frequency = cmdArgumentFREQ.getValue<float>();

                    if ( fabs(m_frequency) < 1e-5  ) {
                        errno = 0;
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                      "Runtime frequency must be greater than 0.");
                    }
                }
                else {
                    CLOG << "No runtime frequency set. Assuming a frequency of 1 Hz." << endl;
                }

                if (cmdArgumentCID.isSet()) {
                    m_CID = cmdArgumentCID.getValue<int>();

                    if ( (m_CID <= 1) || (m_CID >= 254) ) {
                        errno = 0;
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                      "The conference group id has to be in range [2, 254].");
                    }

                    m_multicastGroup = "225.0.0." + cmdArgumentCID.getValue<string>();
                } else {
                    errno = 0;
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                  "No conference group id specified");
                }

                if (cmdArgumentPROFILING.isSet()) {
                    m_profiling = true;
                }

                if (cmdArgumentREALTIME.isSet()) {
                    errno = 0;
#ifdef HAVE_LINUX_RT
                    int val = cmdArgumentREALTIME.getValue<int>();

                    if ( (val < 1) || (val > 49) ) {
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                      "The realtime scheduling priority has to be in range [1, 49].");
                    }

                    m_realtime = true;
                    m_realtimePriority = val;
#else
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException,
                                                  "Realtime is only available on Linux with rt-preempt.");
#endif
                }
            }

            bool AbstractCIDModule::isVerbose() {
                return (AbstractCIDModule::m_verbose > 0);
            }

            int32_t AbstractCIDModule::getVerbosity() {
                return AbstractCIDModule::m_verbose;
            }

            uint32_t AbstractCIDModule::getCID() const {
                return m_CID;
            }

            float AbstractCIDModule::getFrequency() const {
                return m_frequency;
            }

            const string AbstractCIDModule::getIdentifier() const {
                return m_identifier;
            }

            const string AbstractCIDModule::getMultiCastGroup() const {
                return m_multicastGroup;
            }

            uint32_t AbstractCIDModule::getRealtimePriority() const {
                return m_realtimePriority;
            }

            void AbstractCIDModule::waitForNextFullSecond(const uint32_t &secondsIncrement) {
                if (!isRealtime()) {
                    // Suspend this thread to the beginning of the secondsIncrement-th full second only
                    // if we are not executed with realtime flag because ManagedClientModule will do
                    // that for us.
                    Thread::usleepUntil(core::data::TimeStamp(core::data::TimeStamp().getSeconds() + secondsIncrement, 0));
                }
            }

        }
    }
} // core::base::module
