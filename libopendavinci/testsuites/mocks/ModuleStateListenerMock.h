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

#ifndef MOCKS__MODULESTATELISTENERMOCK_H_
#define MOCKS__MODULESTATELISTENERMOCK_H_

#include "opendavinci/odcore/opendavinci.h"

#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

#include "opendavinci/odcore/dmcp/ModuleStateListener.h"
#include "opendavinci/odcore/data/dmcp/ModuleDescriptor.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"

namespace mocks {

    class ModuleStateListenerMock : public odcore::dmcp::ModuleStateListener {
        private:
            odcore::data::dmcp::ModuleStateMessage::ModuleState m_ms;
            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode m_me;
            bool m_stateCalled;
            bool m_exitCalled;
            odcore::base::Condition m_stateCondition;
            odcore::base::Condition m_exitCondition;

        public:
            ModuleStateListenerMock()
                    : m_ms(odcore::data::dmcp::ModuleStateMessage::UNDEFINED_STATE),
                    m_me(odcore::data::dmcp::ModuleExitCodeMessage::UNDEFINED_EXITCODE),
                    m_stateCalled(false),
                    m_exitCalled(false),
                    m_stateCondition(),
                    m_exitCondition() {};

            virtual ~ModuleStateListenerMock() {};

            void waitForStateCall() {
                odcore::base::Lock l(m_stateCondition);

                if (!wasStateCalled() ) {
                    m_stateCondition.waitOnSignalWithTimeout(1000);
                }
            }

            bool wasStateCalled() {
                return m_stateCalled;
            }

            void waitForExitCodeCall() {
                odcore::base::Lock l(m_exitCondition);

                if (!wasExitCodeCalled() ) {
                    m_exitCondition.waitOnSignalWithTimeout(1000);
                }
            }

            bool wasExitCodeCalled() {
                return m_exitCalled;
            }

            virtual void handleChangeState(const odcore::data::dmcp::ModuleDescriptor& /*md*/,
                                           const odcore::data::dmcp::ModuleStateMessage::ModuleState &ms) {
                odcore::base::Lock l(m_stateCondition);
                m_ms = ms;
                m_stateCalled = true;
                m_stateCondition.wakeAll();
            }

            virtual void handleExitCode(const odcore::data::dmcp::ModuleDescriptor& /*md*/,
                                        const odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode &me) {
                odcore::base::Lock l(m_exitCondition);
                m_me = me;
                m_exitCalled = true;
                m_exitCondition.wakeAll();
            }

            void reset() {
                m_ms = odcore::data::dmcp::ModuleStateMessage::UNDEFINED_STATE;
                m_me = odcore::data::dmcp::ModuleExitCodeMessage::UNDEFINED_EXITCODE;
                m_stateCalled = false;
                m_exitCalled = false;
            }

            odcore::data::dmcp::ModuleStateMessage::ModuleState getModuleStateAndWaitForRemainingTimeInTimeslice() {
                odcore::base::Lock l(m_stateCondition);
                return m_ms;
            }

            odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode getExitCode() {
                odcore::base::Lock l(m_exitCondition);
                return m_me;
            }
    };
}
#endif
