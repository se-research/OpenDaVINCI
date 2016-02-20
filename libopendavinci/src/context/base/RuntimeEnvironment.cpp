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

#include "opendavinci/context/base/RuntimeEnvironment.h"
#include "opendavinci/context/base/SystemFeedbackComponent.h"
#include "opendavinci/context/base/TimeConstants.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/base/module/TimeTriggeredConferenceClientModule.h"

namespace odcontext {
    namespace base {

class SystemReportingComponent;

        using namespace std;
        using namespace core::base;
        using namespace core::base::module;

        RuntimeEnvironment::RuntimeEnvironment() :
            m_listsMutex(),
            m_listOfTimeTriggeredConferenceClientModules(),
            m_listOfSystemFeedbackComponents(),
            m_listOfSystemReportingComponents(),
            m_executingMutex(),
            m_executing(false) {}

        RuntimeEnvironment::~RuntimeEnvironment() {
            Lock l(m_listsMutex);
            m_listOfTimeTriggeredConferenceClientModules.clear();
            m_listOfSystemFeedbackComponents.clear();
            m_listOfSystemReportingComponents.clear();
        }

        void RuntimeEnvironment::add(TimeTriggeredConferenceClientModule &ttccm) {
            if (!isExecuting()) {
                Lock l1(m_executingMutex);
                {
                    Lock l2(m_listsMutex);
                    m_listOfTimeTriggeredConferenceClientModules.push_back(&ttccm);
                }
            }
        }

        void RuntimeEnvironment::add(SystemFeedbackComponent &sfc) {
            if (!isExecuting()) {
                Lock l1(m_executingMutex);
                {
                    Lock l2(m_listsMutex);
                    m_listOfSystemFeedbackComponents.push_back(&sfc);
                }
            }
        }

        void RuntimeEnvironment::add(SystemReportingComponent &src) {
            if (!isExecuting()) {
                Lock l1(m_executingMutex);
                {
                    Lock l2(m_listsMutex);
                    m_listOfSystemReportingComponents.push_back(&src);
                }
            }
        }

        bool RuntimeEnvironment::isValid() const {
            bool retVal = false;
            {
                Lock l(m_listsMutex);

                retVal = ( (m_listOfTimeTriggeredConferenceClientModules.size() > 0) && (m_listOfSystemFeedbackComponents.size() > 0) );

                // Reporting components are not required but still useful...
            }
            return retVal;
        }

        vector<core::base::module::TimeTriggeredConferenceClientModule*> RuntimeEnvironment::getListOfTimeTriggeredConferenceClientModules() {
            Lock l(m_listsMutex);
            return m_listOfTimeTriggeredConferenceClientModules;
        }

        vector<SystemFeedbackComponent*> RuntimeEnvironment::getListOfSystemFeedbackComponents() {
            Lock l(m_listsMutex);
            return m_listOfSystemFeedbackComponents;
        }

        vector<SystemReportingComponent*> RuntimeEnvironment::getListOfSystemReportingComponents() {
            Lock l(m_listsMutex);
            return m_listOfSystemReportingComponents;
        }

        uint32_t RuntimeEnvironment::getGreatestTimeStep() const {
            Lock l(m_listsMutex);

            // First, build a joined vector of all frequencies.
            vector<uint32_t> listOfRunAtTimes;

            vector<TimeTriggeredConferenceClientModule*>::const_iterator it = m_listOfTimeTriggeredConferenceClientModules.begin();
            while (it != m_listOfTimeTriggeredConferenceClientModules.end()) {
                const uint32_t APP_RUNATTIME = static_cast<uint32_t>(TimeConstants::ONE_SECOND_IN_MILLISECONDS / (*it++)->getFrequency());
                listOfRunAtTimes.push_back(APP_RUNATTIME);
            }

            vector<SystemFeedbackComponent*>::const_iterator jt = m_listOfSystemFeedbackComponents.begin();
            while (jt != m_listOfSystemFeedbackComponents.end()) {
                const uint32_t SFC_RUNATTIME = static_cast<uint32_t>(TimeConstants::ONE_SECOND_IN_MILLISECONDS / (*jt++)->getFrequency());
                listOfRunAtTimes.push_back(SFC_RUNATTIME);
            }

            // Now, find the greatest common divisor among this list.
            uint32_t gcd = RuntimeEnvironment::DEFAULT_TIMESTEP;
            if (listOfRunAtTimes.size() > 0) {
                uint32_t a = 0;
                uint32_t b = 0;
                vector<uint32_t>::const_iterator kt = listOfRunAtTimes.begin();
                while (kt != listOfRunAtTimes.end()) {
                    b = (*kt++);
                    a = getGreatestCommonDivisor(a, b);
                }

                // Avoid locking due to misuse of getFrequency().
                gcd = (a == 0) ? static_cast<uint32_t>(RuntimeEnvironment::DEFAULT_TIMESTEP) : a;
            }

            return gcd;
        }

        uint32_t RuntimeEnvironment::getGreatestCommonDivisor(const uint32_t &a, const uint32_t &b) const {
            uint32_t _a = a;
            uint32_t _b = b;

            while (_b > 0) {
                uint32_t r = _a % _b;
                _a = _b;
                _b = r;
            }

            return _a;
        }

        void RuntimeEnvironment::beginExecution() {
            Lock l(m_executingMutex);
            m_executing = true;
        }

        bool RuntimeEnvironment::isExecuting() const {
            bool retVal = false;
            {
                Lock l(m_executingMutex);
                retVal = m_executing;
            }
            return retVal;
        }

    }
} // odcontext::base
