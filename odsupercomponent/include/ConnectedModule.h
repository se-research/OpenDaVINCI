/**
 * odsupercomponent - Configuration and monitoring component for
 *                    distributed software systems
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe 
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

#ifndef SUPERCOMPONENT_CONNECTEDMODULE_H_
#define SUPERCOMPONENT_CONNECTEDMODULE_H_

#include "core/SharedPointer.h"
#include "core/dmcp/connection/ModuleConnection.h"

#include "GeneratedHeaders_CoreData.h"

namespace odsupercomponent {

    using namespace std;

    class ConnectedModule {
        public:
            ConnectedModule(core::SharedPointer<core::dmcp::connection::ModuleConnection> connection,
                            const coredata::dmcp::ModuleStateMessage::ModuleState& moduleState );

            virtual ~ConnectedModule();

            core::dmcp::connection::ModuleConnection& getConnection();

            coredata::dmcp::ModuleStateMessage::ModuleState getState() const;
            void setState(const coredata::dmcp::ModuleStateMessage::ModuleState& state);

            void setExitCode();
            bool hasExitCode() const;

        protected:
            coredata::dmcp::ModuleStateMessage::ModuleState m_state;
            core::SharedPointer<core::dmcp::connection::ModuleConnection> m_connection;
            bool m_hasExitCode;

        private:
            ConnectedModule(const ConnectedModule &);
            ConnectedModule& operator=(const ConnectedModule &);
    };
}

#endif /*SUPERCOMPONENT_CONNECTEDMODULE_H_*/
