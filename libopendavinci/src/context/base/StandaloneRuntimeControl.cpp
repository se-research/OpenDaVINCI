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

#include "core/macros.h"
#include "core/base/Lock.h"
#include "core/base/Thread.h"
#include "core/data/TimeStamp.h"
#include "core/io/conference/ContainerConferenceFactory.h"

#include "context/base/Clock.h"
#include "context/base/StandaloneRuntimeControl.h"

namespace context {
	namespace base {

		using namespace std;
		using namespace core::base;
		using namespace core::data;
		using namespace core::io;
        using namespace core::io::conference;

		StandaloneRuntimeControl::StandaloneRuntimeControl(const RuntimeControlInterface &sci) :
			context::base::RuntimeControl(sci),
			m_conference(NULL),
			m_rte(),
			m_listOfSystemFeedbackComponentsMutex(),
			m_listOfSystemFeedbackComponents() {
			// Add the standalone system simulation to the current ClientConference.
			m_conference = ContainerConferenceFactory::getInstance().getContainerConference(sci.getMulticastGroup());

			// Register ourselves as ContainerListener.
			m_conference->setContainerListener(this);
		}

		StandaloneRuntimeControl::~StandaloneRuntimeControl() {
			// Remove ourselves from the ContainerConference.
			m_conference->setContainerListener(NULL);

			// Clean up. This method may be overriden in subclasses and disable the destruction of SystemFeedbackComponents.
			destroySystemFeedbackComponents();

			m_listOfSystemFeedbackComponents.clear();
		}

		void StandaloneRuntimeControl::destroySystemFeedbackComponents() {
			Lock l(m_listOfSystemFeedbackComponentsMutex);

			vector<SystemFeedbackComponent*>::iterator it = m_listOfSystemFeedbackComponents.begin();
			while (it != m_listOfSystemFeedbackComponents.end()) {
				SystemFeedbackComponent *sfc = (*it++);
				OPENDAVINCI_CORE_DELETE_POINTER(sfc);
			}
		}

		void StandaloneRuntimeControl::nextContainer(Container &c) {
			Lock l(m_listOfSystemFeedbackComponentsMutex);

//			clog << "(StandaloneRuntimeControl) Received container of type '" << c.toString() << "'." << endl;

			// Distribute data to simulation components.
			vector<SystemFeedbackComponent*>::iterator it = m_listOfSystemFeedbackComponents.begin();
			while (it != m_listOfSystemFeedbackComponents.end()) {
				SystemFeedbackComponent *sfc = (*it++);
				sfc->nextContainer(c);
			}
		}

		void StandaloneRuntimeControl::add(SystemFeedbackComponent *sfc) {
			if (sfc != NULL) {
				Lock l(m_listOfSystemFeedbackComponentsMutex);
				m_listOfSystemFeedbackComponents.push_back(sfc);

				// Add SystemFeedbackComponent to the current RuntimeEnvironment.
				m_rte.add(*sfc);
			}
		}

		void StandaloneRuntimeControl::sendToSystemsUnderTest(Container &c) {
			// Distribute containers directly.
			m_conference->send(c);
		}

		enum RuntimeControl::ERRORCODES StandaloneRuntimeControl::runStandalone() {
			clog << "(StandaloneRuntimeControl) Creating RuntimeEnvironment." << endl;

			// Let the subclass configure its runtime environment.
			configureRuntimeEnvironment();

			if (m_listOfSystemFeedbackComponents.size() > 0) {
				m_rte.beginExecution();

				setupSystemContextComponents(m_rte);

				const uint32_t SLEEPING_TIME = m_rte.getGreatestTimeStep();
				clog << "(StandaloneRuntimeControl) Greatest time step: " << SLEEPING_TIME << "ms." << endl;

				Clock time;
				TimeStamp startTime;
				setModuleState(coredata::dmcp::ModuleStateMessage::RUNNING);
				while (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) {
					// Get time at the beginning of the time slice.
					TimeStamp startTimeSlice;

					if ( ( (time.now().getSeconds() % 5) == 0 ) && (time.now().getPartialMicroseconds() == 0) ) {
						clog << "(StandaloneRuntimeControl) ------------------------------------------------------------------------------" << endl;
						clog << "Time " << time.now().getSeconds() << "." << time.now().getPartialMicroseconds() << endl;
					}

					// Execute SystemFeedbackComponents.
					vector<SystemFeedbackComponent*>::iterator it = m_listOfSystemFeedbackComponents.begin();
					while (it != m_listOfSystemFeedbackComponents.end()) {
						SystemFeedbackComponent *sfc = (*it++);

						if ( (sfc != NULL) && (sfc->needsExecution(time.now())) ) {
							// Step simulation component and let ourselves distribute any containers.
							sfc->step(time.now(), *this);
						}
					}

					// Get time at the end of the time slice.
					TimeStamp endTimeSlice;

					// Calculate the real sleeping time to map simulation time onto the real time.
					TimeStamp consumedTimeFromTimeSlice = endTimeSlice - startTimeSlice;

					const double nominalTimeInMicroSeconds = SLEEPING_TIME * 1000.0; // Multiply by 1000.0 to convert milliseconds to microseconds.
					const double consumedTimeInMicroSeconds = consumedTimeFromTimeSlice.toMicroseconds();
					const double CURRENT_SLEEPING_TIME = nominalTimeInMicroSeconds - consumedTimeInMicroSeconds;
					if (CURRENT_SLEEPING_TIME > 0) {
						// Delay the simulation to map the simulation time onto the real time.
						Thread::usleepFor(CURRENT_SLEEPING_TIME);
					}

					// Increment the time using the computed greatest common divisor.
					time.increment(SLEEPING_TIME);
				}
				TimeStamp endTime;

				clog << "(StandaloneRuntimeControl) ran for " << ((endTime - startTime).toMicroseconds() / (1000.0 * 1000.0)) << "s." << endl;
				tearDownSystemContextComponents(m_rte);
			}

			return RuntimeControl::NO_ERROR_OCCURRED;
		}
	}
} // context::base
