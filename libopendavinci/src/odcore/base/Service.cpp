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

#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Service.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/wrapper/ConcurrencyFactory.h"
#include "opendavinci/odcore/wrapper/Thread.h"

namespace odcore {
    namespace base {

        using namespace exceptions;

        Service::Service() throw (ThreadException) :
            m_thread(),
            m_serviceStateMutex(),
            m_serviceState(INITIALIZED),
            m_serviceReadyCondition(),
            m_serviceReady(false) {
            m_thread = auto_ptr<odcore::wrapper::Thread>(wrapper::ConcurrencyFactory::createThread(*this));
            if (m_thread.get() == NULL) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(ThreadException, "[core::base::Service] Thread could not be created!");
            }
        }

        Service::~Service() {
            // Do not call this->stop() here because beforeStop() is a pure virtual method!
            m_thread->stop();
        }

        void Service::start() {
            Lock l(m_serviceStateMutex);
            if (m_serviceState == INITIALIZED) {
                m_serviceState = RUNNING;
                m_thread->start();

                // wait until new service signals readiness
                {
                    Lock ll(m_serviceReadyCondition);
                    while (!m_serviceReady) {
                        m_serviceReadyCondition.waitOnSignal();
                    }
                }
            }
        }

        void Service::stop() {
            bool doStop = false;
            {
                Lock l(m_serviceStateMutex);
                if (m_serviceState == RUNNING) {
                    m_serviceState = STOPPED;
                    doStop = true;
                }
            }
            if (doStop) {
                beforeStop();
                m_thread->stop();
            }
        }

        void Service::serviceReady() {
            Lock l(m_serviceReadyCondition);
            m_serviceReady = true;
            m_serviceReadyCondition.wakeAll();
        }

        bool Service::isRunning() {
            Lock l(m_serviceStateMutex);
            return (m_serviceState == RUNNING);
        }
    }
} // odcore::base
