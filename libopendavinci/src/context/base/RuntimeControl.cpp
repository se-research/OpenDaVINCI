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

#include <cassert>
#include <iostream>
#include <string>

#include "opendavinci/context/base/Clock.h"
#include "opendavinci/context/base/ControlledContainerConferenceFactory.h"
#include "opendavinci/context/base/ControlledTime.h"
#include "opendavinci/context/base/ControlledTimeFactory.h"
#include "opendavinci/context/base/RuntimeControl.h"
#include "opendavinci/context/base/RuntimeControlInterface.h"
#include "opendavinci/context/base/RuntimeEnvironment.h"
#include "opendavinci/context/base/SuperComponent.h"
#include "opendavinci/context/base/SystemFeedbackComponent.h"
#include "opendavinci/context/base/SystemReportingComponent.h"
#include "opendavinci/context/base/TimeTriggeredConferenceClientModuleRunner.h"
#include "opendavinci/core/base/Lock.h"
#include "opendavinci/core/data/TimeStamp.h"
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendavinci/core/io/conference/ContainerConferenceFactory.h"
#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/wrapper/Time.h"
#include "opendavinci/generated/coredata/dmcp/ModuleStateMessage.h"

namespace core { namespace base { namespace module { class TimeTriggeredConferenceClientModule; } } }

namespace odcontext {
    namespace base {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::base::module;
        using namespace core::io;
        using namespace core::io::conference;

        RuntimeControl::RuntimeControl(const RuntimeControlInterface &sci) :
            m_controlMutex(),
            m_control(RuntimeControl::UNSPECIFIED),
            m_tearDownCalled(false),
            m_runtimeControlInterface(sci),
            m_superComponent(NULL),
            m_controlledContainerConferenceFactory(NULL),
            m_controlledTimeFactory(NULL) {
            // Initialize TimeFactory to avoid SEGFAULT.
            core::data::TimeStamp ts;
            if (ts.getSeconds() > 0) {};
        }

        RuntimeControl::~RuntimeControl() {
            if (!m_tearDownCalled) {
                tearDown();
            }

            OPENDAVINCI_CORE_DELETE_POINTER(m_superComponent);

            if (m_controlledContainerConferenceFactory != NULL) {
                // Disable and destroy.
                removeExistingContainerConferenceFactory();
            }

            if (m_controlledTimeFactory != NULL) {
                // Disable exchanged timefactory AND destroy.
                RuntimeControl::DisableTimeFactory dtf;
                dtf.disable();

                OPENDAVINCI_CORE_DELETE_POINTER(m_controlledTimeFactory);
            }
        }

        void RuntimeControl::setup(const enum RUNTIMECONTROL &takeControl) {
            Lock l(m_controlMutex);
            if (m_control == RuntimeControl::UNSPECIFIED) {
            	if (m_runtimeControlInterface.isSupercomponent()) {
					clog << "(context::base::RuntimeControl) setup..." << endl;
					m_superComponent = new SuperComponent(m_runtimeControlInterface.getMulticastGroup(), m_runtimeControlInterface.getCID(), m_runtimeControlInterface.getConfiguration());
					clog << "(context::base::RuntimeControl) setup done." << endl;
            	}
            	else {
					clog << "(context::base::RuntimeControl) Skipping creation of 'supercomponent' as requested by user." << endl;
            	}

                if (takeControl == RuntimeControl::TAKE_CONTROL) {
                    clog << "(context::base::RuntimeControl) Taking control..." << endl;
                    // Exchange TimeFactory.
                    removeExistingTimeFactory();
                    m_controlledTimeFactory = new ControlledTimeFactory();

                    // Remove any existing ContainerConferenceFactory.
                    removeExistingContainerConferenceFactory();
                    m_controlledContainerConferenceFactory = new ControlledContainerConferenceFactory();
                }

                m_control = takeControl;
            }
        }

        void RuntimeControl::removeExistingContainerConferenceFactory() {
            // Destroy any existing ContainerConferenceFactory.
            ContainerConferenceFactory &ccf = ContainerConferenceFactory::getInstance();
            ContainerConferenceFactory *ccf2 = &ccf;
            OPENDAVINCI_CORE_DELETE_POINTER(ccf2);
        }

        void RuntimeControl::removeExistingTimeFactory() {
            RuntimeControl::DisableTimeFactory dtf;
            dtf.disable();
        }

        void RuntimeControl::tearDown() {
            if (!m_tearDownCalled) {
                clog << "(context::base::RuntimeControl) tearDown..." << endl;
                // Remove any existing ContainerConferenceFactory.
                removeExistingContainerConferenceFactory();
                clog << "(context::base::RuntimeControl) done." << endl;
                m_tearDownCalled = true;
            }
        }

        enum RuntimeControl::ERRORCODES RuntimeControl::run() {
            return runStandalone();
        }

        enum RuntimeControl::ERRORCODES RuntimeControl::runStandalone() {
        	// This method MUST be overriden in subclasses (cf. StandaloneRuntimeControl).
        	return RuntimeControl::NO_ERROR_OCCURRED;
        }

        void RuntimeControl::registerSystemContextComponentsAddControlledContainerConferenceFactory(RuntimeEnvironment &rte) {
            if (rte.isValid() && rte.isExecuting() && (m_controlledContainerConferenceFactory != NULL)) {
                // Get list of SystemFeedbackComponents to register all SystemFeedbackComponents as receivers for Containers at ControlledContainerConferenceFactory.
                vector<SystemFeedbackComponent*> listOfSystemFeedbackComponents = rte.getListOfSystemFeedbackComponents();
                vector<SystemFeedbackComponent*>::iterator itSystemFeedbackComponent = listOfSystemFeedbackComponents.begin();
                while (itSystemFeedbackComponent != listOfSystemFeedbackComponents.end()) {
                    SystemFeedbackComponent *sfc = (*itSystemFeedbackComponent++);
                    if (sfc != NULL) {
                        // Register the SystemFeedbackComponent as receiver for new containers.
                        m_controlledContainerConferenceFactory->add(sfc);
                    }
                }

                // Get list of SystemReportingComponents to register all SystemReportingComponents as receivers for Containers at ControlledContainerConferenceFactory.
                vector<SystemReportingComponent*> listOfSystemReportingComponents = rte.getListOfSystemReportingComponents();
                vector<SystemReportingComponent*>::iterator itSystemReportingComponent = listOfSystemReportingComponents.begin();
                while (itSystemReportingComponent != listOfSystemReportingComponents.end()) {
                    SystemReportingComponent *src = (*itSystemReportingComponent++);
                    if (src != NULL) {
                        // Register the SystemReportingComponent as receiver for new containers.
                        m_controlledContainerConferenceFactory->add(src);
                    }
                }
            }
        }

        void RuntimeControl::setupSystemContext(RuntimeEnvironment &rte) {
            if (rte.isValid() && rte.isExecuting()) {
            	setupSystemContextComponents(rte);
            	setupSystemReportingComponents(rte);
            }
        }

        void RuntimeControl::setupSystemContextComponents(RuntimeEnvironment &rte) {
			// Get list of SystemFeedbackComponents to register all SystemFeedbackComponents as receivers for Containers at ControlledContainerConferenceFactory.
			vector<SystemFeedbackComponent*> listOfSystemFeedbackComponents = rte.getListOfSystemFeedbackComponents();
			vector<SystemFeedbackComponent*>::iterator itSystemFeedbackComponent = listOfSystemFeedbackComponents.begin();
			while (itSystemFeedbackComponent != listOfSystemFeedbackComponents.end()) {
				SystemFeedbackComponent *sfc = (*itSystemFeedbackComponent++);
				if (sfc != NULL) {
					sfc->setup();
				}
			}
        }

        void RuntimeControl::setupSystemReportingComponents(RuntimeEnvironment &rte) {
			// Get list of SystemReportingComponents to register all SystemReportingComponents as receivers for Containers at ControlledContainerConferenceFactory.
			vector<SystemReportingComponent*> listOfSystemReportingComponents = rte.getListOfSystemReportingComponents();
			vector<SystemReportingComponent*>::iterator itSystemReportingComponent = listOfSystemReportingComponents.begin();
			while (itSystemReportingComponent != listOfSystemReportingComponents.end()) {
				SystemReportingComponent *src = (*itSystemReportingComponent++);
				if (src != NULL) {
					src->setup();
				}
			}
        }

        void RuntimeControl::tearDownSystemContextComponents(RuntimeEnvironment &rte) {
            if (rte.isValid() && rte.isExecuting()) {
                // Get list of SystemFeedbackComponents to register all SystemFeedbackComponents as receivers for Containers at ControlledContainerConferenceFactory.
                vector<SystemFeedbackComponent*> listOfSystemFeedbackComponents = rte.getListOfSystemFeedbackComponents();
                vector<SystemFeedbackComponent*>::iterator itSystemFeedbackComponent = listOfSystemFeedbackComponents.begin();
                while (itSystemFeedbackComponent != listOfSystemFeedbackComponents.end()) {
                    SystemFeedbackComponent *sfc = (*itSystemFeedbackComponent++);
                    if (sfc != NULL) {
                        sfc->tearDown();
                    }
                }

                // Get list of SystemReportingComponents to register all SystemReportingComponents as receivers for Containers at ControlledContainerConferenceFactory.
                vector<SystemReportingComponent*> listOfSystemReportingComponents = rte.getListOfSystemReportingComponents();
                vector<SystemReportingComponent*>::iterator itSystemReportingComponent = listOfSystemReportingComponents.begin();
                while (itSystemReportingComponent != listOfSystemReportingComponents.end()) {
                    SystemReportingComponent *src = (*itSystemReportingComponent++);
                    if (src != NULL) {
                        src->tearDown();
                    }
                }
            }
        }

        vector<SharedPointer<TimeTriggeredConferenceClientModuleRunner> > RuntimeControl::createListOfTimeTriggeredConferenceClientModuleRunners(RuntimeEnvironment &rte) {
            vector<SharedPointer<TimeTriggeredConferenceClientModuleRunner> > listOfWrappedTimeTriggeredConferenceClientModules;

            if (rte.isValid() && rte.isExecuting()) {
                // Wrap all ConferenceClientModules. We use SharePointer to
                // get automatic destroying and thus releasing of any locked
                // resource when an exception is thrown.
                vector<TimeTriggeredConferenceClientModule*> listOfTimeTriggeredConferenceClientModules = rte.getListOfTimeTriggeredConferenceClientModules();
                vector<TimeTriggeredConferenceClientModule*>::iterator itTimeTriggeredConferenceClientModule = listOfTimeTriggeredConferenceClientModules.begin();
                while (itTimeTriggeredConferenceClientModule != listOfTimeTriggeredConferenceClientModules.end()) {
                    TimeTriggeredConferenceClientModule *ttccm = (*itTimeTriggeredConferenceClientModule++);
                    if (ttccm != NULL) {
                        // Create a blockable receiver per system under test.
                        // Register ContainerDispatcher to distribute Containers to all SystemParts.
                        SharedPointer<TimeTriggeredConferenceClientModuleRunner> wrappedTimeTriggeredConferenceClientModule(new TimeTriggeredConferenceClientModuleRunner(*ttccm));
                        listOfWrappedTimeTriggeredConferenceClientModules.push_back(wrappedTimeTriggeredConferenceClientModule);
                    }
                }
            }

            return listOfWrappedTimeTriggeredConferenceClientModules;
        }

        void RuntimeControl::doReporting(RuntimeEnvironment &rte, const core::wrapper::Time &time) {
            if (rte.isValid() && rte.isExecuting()) {
                // Get list of SystemReportingComponents to register all SystemReportingComponents as receivers for Containers at ControlledContainerConferenceFactory.
                vector<SystemReportingComponent*> listOfSystemReportingComponents = rte.getListOfSystemReportingComponents();
                vector<SystemReportingComponent*>::iterator mt = listOfSystemReportingComponents.begin();
                while (mt != listOfSystemReportingComponents.end()) {
                    SystemReportingComponent *src = (*mt++);
                    if (src != NULL) {
                        clog << "[SRC] at " << time.getSeconds() << "." << time.getPartialMicroseconds() << endl;

                        src->report(time);
                    }
                }
            }
        }

        enum RuntimeControl::ERRORCODES RuntimeControl::run(RuntimeEnvironment &rte, const uint32_t &maxRunningTimeInSeconds) {
            enum ERRORCODES retVal = RuntimeControl::NO_ERROR_OCCURRED;

            // Check if the user called setup(...) properly.
            enum RUNTIMECONTROL control = RuntimeControl::UNSPECIFIED;
            {
                Lock l(m_controlMutex);
                control = m_control;
            }

            if (control == RuntimeControl::TAKE_CONTROL) {
                if ( rte.isValid() && (maxRunningTimeInSeconds > 0) ) {
                    try {
                        // Stop adding further modules.
                        rte.beginExecution();

                        // Prepare RuntimeEnvironment (i.e. register ContainerListener at ControlledContainerConferenceFactory).
                        registerSystemContextComponentsAddControlledContainerConferenceFactory(rte);

                        // Setup SystemContext.
                        setupSystemContext(rte);

                        // Get list of SystemFeedbackComponents to register all SystemFeedbackComponents as receivers for Containers at ControlledContainerConferenceFactory.
                        vector<SystemFeedbackComponent*> listOfSystemFeedbackComponents = rte.getListOfSystemFeedbackComponents();

                        // Create list of wrapper ConferenceClientModules.
                        vector<SharedPointer<TimeTriggeredConferenceClientModuleRunner> > listOfWrappedTimeTriggeredConferenceClientModules = createListOfTimeTriggeredConferenceClientModuleRunners(rte);

                        // Compute greatest possible time step in the runtime environment.
                        const uint32_t SLEEPING_TIME = rte.getGreatestTimeStep();
                        clog << "(context::base::RuntimeControl) greatest common divisor: " << SLEEPING_TIME << "ms." << endl;

                        ////////////////////////////////////////////////////////
                        // Assert necessary things.
                        assert(SLEEPING_TIME > 0);
                        assert(listOfSystemFeedbackComponents.size() > 0);
                        assert(listOfWrappedTimeTriggeredConferenceClientModules.size() > 0);
                        ////////////////////////////////////////////////////////

                        // Ladies and Gentlemen: The time.
                        Clock time;

                        // Declare actual time.
                        m_controlledTimeFactory->setTime(time.now());

                        bool moreModulesSchedulable = true;

                        // Perform system's context simulation.
                        setModuleState(coredata::dmcp::ModuleStateMessage::RUNNING);
                        while ( (moreModulesSchedulable) && (static_cast<uint32_t>(time.now().getSeconds()) < maxRunningTimeInSeconds) && (getModuleStateAndWaitForRemainingTimeInTimeslice() == coredata::dmcp::ModuleStateMessage::RUNNING) ) {
                            clog << "------------------------------------------------------------------------------" << endl;
                            clog << "Time " << time.now().getSeconds() << "." << time.now().getPartialMicroseconds() << endl;

                            // Execute SystemFeedbackComponents.
                            vector<SystemFeedbackComponent*>::iterator jt = listOfSystemFeedbackComponents.begin();
                            while (jt != listOfSystemFeedbackComponents.end()) {
                                SystemFeedbackComponent *sfc = (*jt++);

                                bool hasExecutedSystemComponent = false;
                                if ( (sfc != NULL) && (sfc->needsExecution(time.now())) ) {
                                    clog << "[SFC] at " << time.now().getSeconds() << "." << time.now().getPartialMicroseconds() << endl;

                                    sfc->step(time.now(), *m_controlledContainerConferenceFactory);

                                    hasExecutedSystemComponent = true;
                                }

                                // When the SystemContextComponent was executed, call all reporters.
                                if (hasExecutedSystemComponent) {
                                    doReporting(rte, time.now());
                                }
                            }

                            // Execute wrapped ConferenceClientModules.
                            vector<SharedPointer<TimeTriggeredConferenceClientModuleRunner> >::iterator kt = listOfWrappedTimeTriggeredConferenceClientModules.begin();
                            while (kt != listOfWrappedTimeTriggeredConferenceClientModules.end()) {
                                SharedPointer<TimeTriggeredConferenceClientModuleRunner> runner = (*kt++);

                                // Check, if further cycles are necessary.
                                moreModulesSchedulable = false;
                                moreModulesSchedulable |= ( (runner.isValid()) && (!runner->hasFinished()) );

                                // Check if the application needs to be executed.
                                bool hasExecutedApplication = false;
                                if ( runner.isValid() && (runner->needsExecution(time.now())) ) {
                                    runner->step(time.now());
                                    hasExecutedApplication = true;
                                }

                                // When the application was executed, call all reporters.
                                if (hasExecutedApplication) {
                                    doReporting(rte, time.now());
                                }
                            }

                            // Increment the time using the computed greatest common divisor.
                            time.increment(SLEEPING_TIME);

                            // Feed forward current valid system time to TimeFactory.
                            m_controlledTimeFactory->setTime(time.now());
                        }

                        // Stop wrapped application.
                        vector<SharedPointer<TimeTriggeredConferenceClientModuleRunner> >::iterator kt = listOfWrappedTimeTriggeredConferenceClientModules.begin();
                        while (kt != listOfWrappedTimeTriggeredConferenceClientModules.end()) {
                            SharedPointer<TimeTriggeredConferenceClientModuleRunner> runner = (*kt++);
                            if (runner.isValid()) {
                                runner->stop();
                            }
                        }

                        // Check if the specified time has run out or if all simulatable modules have finished.
                        if (getModuleStateAndWaitForRemainingTimeInTimeslice() != coredata::dmcp::ModuleStateMessage::RUNNING) {
                            clog << "(context::base::RuntimeControl) Forced to quit." << endl;
                            retVal = RuntimeControl::RUNTIMECONTROL_FORCED_TO_QUIT;
                        }
                        else {
                            if (!moreModulesSchedulable) {
                                // All modules were scheduled.
                                clog << "(context::base::RuntimeControl) All applications in RuntimeEnvironment have finished." << endl;
                                retVal = RuntimeControl::APPLICATIONS_FINISHED;
                            }
                            else {
                                // There are still some applications to schedule, but the initially specified time out was to small.
                                clog << "(context::base::RuntimeControl) The specified overall timeout was to small! There are still schedulable applications available." << endl;
                                retVal = RuntimeControl::RUNTIME_TIMEOUT;
                            }
                        }
                    }
                    catch(core::exceptions::Exceptions &e) {
                        clog << "(context::base::RuntimeControl) Exception occurred: " << e.toString() << endl;
                        retVal = RuntimeControl::EXCEPTION_CAUGHT;
                    }
                    catch(string &s) {
                        clog << "(context::base::RuntimeControl) String exception occurred: " << s << endl;
                        retVal = RuntimeControl::STRING_EXCEPTION_CAUGHT;
                    }
                    catch(...) {
                        clog << "(context::base::RuntimeControl) Unknown exception occurred." << endl;
                        retVal = RuntimeControl::UNKNOWN_EXCEPTION_CAUGHT;
                    }

                    // Tear down SystemContextComponents in any case.
                    tearDownSystemContextComponents(rte);
                }
            }
            else {
                clog << "(context::base::RuntimeControl) setup(...) was not called! Aborting..." << endl;
                retVal = RuntimeControl::SETUP_NOT_CALLED;
            }

            return retVal;
        }

        void RuntimeControl::waitForNextFullSecond(const uint32_t &/*secondsIncrement*/) {}

        ////////////////////////////////////////////////////////////////////////

        void RuntimeControl::DisableTimeFactory::disable() {
            core::wrapper::TimeFactory::setSingleton(NULL);
        }

        core::SharedPointer<core::wrapper::Time> RuntimeControl::DisableTimeFactory::now() {
            core::SharedPointer<core::wrapper::Time> t;
            return t;
        }

    }
} // odcontext::base
