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

#include "ConnectedModules.h"

#include "core/strings/StringToolbox.h"
#include "core/base/Lock.h"
#include "core/base/Thread.h"

namespace odsupercomponent {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace coredata::dmcp;

    ConnectedModules::ConnectedModules() :
        m_modulesMutex(),
        m_modules()
    {}

    ConnectedModules::~ConnectedModules() {
        deleteAllModules();
    }

    void ConnectedModules::addModule(const ModuleDescriptor& md, ConnectedModule* module) {
        Lock l(m_modulesMutex);
        m_modules[md.getName()] = module;
    }

    ConnectedModule* ConnectedModules::getModule(const ModuleDescriptor& md) {
        Lock l(m_modulesMutex);
        return m_modules[md.getName()];
    }

    void ConnectedModules::removeModule(const ModuleDescriptor& md) {
        Lock l(m_modulesMutex);
        m_modules.erase(md.getName());
    }

    bool ConnectedModules::hasModule(const ModuleDescriptor& md) {
        Lock l(m_modulesMutex);
        return (m_modules.count(md.getName()) != 0);
    }

    void ConnectedModules::pulse(const coredata::dmcp::PulseMessage &pm) {
        Lock l(m_modulesMutex);
        map<string, ConnectedModule*>::iterator iter;

        for (iter = m_modules.begin(); iter != m_modules.end(); ++iter) {
            iter->second->getConnection().pulse(pm);
        }
    }

    void ConnectedModules::pulseShift(const coredata::dmcp::PulseMessage &pm, const uint32_t &shift) {
        Lock l(m_modulesMutex);
        map<string, ConnectedModule*>::iterator iter;

        uint32_t connectedModulesCounter = 0;
        coredata::dmcp::PulseMessage pm_shifted = pm;
        const core::data::TimeStamp pm_org_ts = pm.getRealTimeFromSupercomponent();

        for (iter = m_modules.begin(); iter != m_modules.end(); ++iter) {
            core::data::TimeStamp ts(0, shift * connectedModulesCounter);
            core::data::TimeStamp shiftedTime = pm_org_ts + ts;

            pm_shifted.setRealTimeFromSupercomponent(shiftedTime);
            iter->second->getConnection().pulse(pm_shifted);

            connectedModulesCounter++;
        }
    }

    void ConnectedModules::pulse_ack(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout, const uint32_t &yield, const vector<string> &modulesToIgnore) {
        // Unfortunately, we cannot prevent code duplication here (cf. pulse_ack_containers)
        // as in this case, the dependent client module will NOT send its containers to using
        // this TCP link but via the regular UDP multicast conference.
        Lock l(m_modulesMutex);
        map<string, ConnectedModule*>::iterator iter;

        for (iter = m_modules.begin(); iter != m_modules.end(); ++iter) {
            // Get the module's name.
            string s = iter->first;
            transform(s.begin(), s.end(), s.begin(), ::tolower);

            // Check whether we have to skip this module when sending pulses.
            vector<string>::const_iterator it = find(modulesToIgnore.begin(), modulesToIgnore.end(), s);
            if (it == modulesToIgnore.end()) {
                // The following call blocks until the client has confirmed the processing of this pulse.
                iter->second->getConnection().pulse_ack(pm, timeout);

                // Allow delivery of packets on OS level.
                Thread::usleepFor(yield);
            }
        }
    }

    vector<Container> ConnectedModules::pulse_ack_containers(const coredata::dmcp::PulseMessage &pm, const uint32_t &timeout, const uint32_t &yield, const vector<string> &modulesToIgnore) {
        // Unfortunately, we cannot prevent code duplication here (cf. pulse_ack)
        // as in this case, the dependent client module will send all its containers
        // via this TCP link and NOT via the regular UDP multicast conference.
        vector<Container> allContainersToBeDeliveredInNextCycle;

        Lock l(m_modulesMutex);
        map<string, ConnectedModule*>::iterator iter;

        for (iter = m_modules.begin(); iter != m_modules.end(); ++iter) {
            // Get the module's name.
            string s = iter->first;
            transform(s.begin(), s.end(), s.begin(), ::tolower);

            // Check whether we have to skip this module when sending pulses.
            vector<string>::const_iterator it = find(modulesToIgnore.begin(), modulesToIgnore.end(), s);
            if (it == modulesToIgnore.end()) {
                // The following call blocks until the client has confirmed the processing of this pulse.
                vector<Container> containersToBeDeliveredInNextCycle = iter->second->getConnection().pulse_ack_containers(pm, timeout);

                // Add newly received containers to the overall list.
                allContainersToBeDeliveredInNextCycle.insert(allContainersToBeDeliveredInNextCycle.end(), containersToBeDeliveredInNextCycle.begin(), containersToBeDeliveredInNextCycle.end());

                // Allow delivery of packets on OS level.
                Thread::usleepFor(yield);
            }
        }

        return allContainersToBeDeliveredInNextCycle;
    }

    void ConnectedModules::deleteAllModules() {
        Lock l(m_modulesMutex);
        map<string, ConnectedModule*>::iterator iter;

        for (iter = m_modules.begin(); iter != m_modules.end(); ++iter) {
            iter->second->getConnection().setModuleStateListener(NULL);
            delete iter->second;
        }

        m_modules.clear();
    }

}
