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

#ifndef OPENDAVINCI_BASE_ABSTRACTCONFERENCECLIENTMODULE_H_
#define OPENDAVINCI_BASE_ABSTRACTCONFERENCECLIENTMODULE_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/module/ManagedClientModule.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/generated/odcore/data/LogMessage.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleExitCodeMessage.h"

namespace odcore { namespace data { class Container; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;

            /**
             * This class is the abstract base class for every client module.
             * It automatically joins a ContainerConference to send and receive
             * Containers.
             *
             * Concrete subclasses are:
             * - @See DataTriggeredConferenceClientModule
             * - @See TimeTriggeredConferenceClientModule
             */
            class OPENDAVINCI_API AbstractConferenceClientModule : public ManagedClientModule {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    AbstractConferenceClientModule(const AbstractConferenceClientModule& );

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    AbstractConferenceClientModule& operator=(const AbstractConferenceClientModule&);

                public:
                    /**
                     * Constructor.
                     *
                     * @param argc Number of command line arguments.
                     * @param argv Command line arguments.
                     * @param name Name of this module. This parameter is necessary for identifying the corresponding parts in the configuration.
                     * @throw InvalidArgumentException if the signal handler could not be registered.
                     */
                    AbstractConferenceClientModule(const int32_t &argc, char **argv, const string &name) throw (odcore::exceptions::InvalidArgumentException);

                    virtual ~AbstractConferenceClientModule();

                    /**
                     * This method returns the conference.
                     *
                     * @return Conference.
                     */
                    odcore::io::conference::ContainerConference& getConference();

                protected:
                    virtual void setUp() = 0;

                    virtual void tearDown() = 0;

                    virtual odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body() = 0;

                public:
                    /**
                     * This method propagates the message msg to the central logger.
                     *
                     * @param logLevel Level for the message.
                     * @param msg Message to be logged.
                     */
                    void toLogger(const odcore::data::LogMessage::LogLevel &logLevel, const string &msg);
            };

        }
    }
} // odcore::base::module

#endif /*OPENDAVINCI_BASE_ABSTRACTCONFERENCECLIENTMODULE_H_*/
