/**
 * libvehiclecontext - Models for simulating automotive systems.
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

#include <iostream>
#include <string>
#include <vector>

#include "opendavinci/context/base/RuntimeControlInterface.h"
#include "opendavinci/context/base/StandaloneRuntimeControl.h"
#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendlv/vehiclecontext/VehicleRuntimeControl.h"
#include "opendlv/vehiclecontext/model/SimplifiedBicycleModel.h"

namespace opendlv { namespace vehiclecontext {

    using namespace std;
    using namespace core::base;
    using namespace opendlv::vehiclecontext::model;

    VehicleRuntimeControl::VehicleRuntimeControl(const odcontext::base::RuntimeControlInterface &sci) :
        odcontext::base::StandaloneRuntimeControl(sci),
        m_globalConfiguration() {
        m_globalConfiguration = sci.getConfiguration();
    }

    VehicleRuntimeControl::~VehicleRuntimeControl() {}

    const KeyValueConfiguration VehicleRuntimeControl::getConfigurationFor(const enum VEHICLECONTEXTMODULES &module) {
        KeyValueConfiguration config;

        switch (module) {
            case VehicleRuntimeControl::SIMPLIFIEDBICYCLEMODEL:
            {
                KeyValueConfiguration simplifiedBicycleModelSubset = m_globalConfiguration.getSubsetForSection("vehiclecontext.simplifiedbicyclemodel");
                if (simplifiedBicycleModelSubset.getListOfKeys().size() > 0) {
                    // Remove leading "vehiclecontext.".
                    config = simplifiedBicycleModelSubset.getSubsetForSectionRemoveLeadingSectionName("vehiclecontext.");
                }
            }
            break;
        }

        // Add global.*.
        KeyValueConfiguration globalConfig = m_globalConfiguration.getSubsetForSection("global");
        stringstream fusedConfig;
        globalConfig.writeTo(fusedConfig);
        fusedConfig << endl;

        config.writeTo(fusedConfig);

        // Re-read previously written configuration.
        config.readFrom(fusedConfig);

        return config;
    }

    void VehicleRuntimeControl::configureRuntimeEnvironment() {
        // Try to configure the environment.
        clog << "(vehiclecontext) Configuring module 'SimplifiedBicycleModel'..." << endl;
        const KeyValueConfiguration kvcSimplifiedBicycleModel = getConfigurationFor(VehicleRuntimeControl::SIMPLIFIEDBICYCLEMODEL);
        if (kvcSimplifiedBicycleModel.getListOfKeys().size() > 0) {
            stringstream config;
            kvcSimplifiedBicycleModel.writeTo(config);

            try {
                clog << config.str() << endl;

                SimplifiedBicycleModel *sbm = new SimplifiedBicycleModel(config.str());
                if (sbm != NULL) {
                    // Add SystemFeedbackComponent to StandaloneRuntimeControl for getting scheduled.
                    add(sbm);
                    clog << "(vehiclecontext) 'SimpleBicycleModel' configured." << endl;
                }
            }
            catch(...) {
                clog << "(vehiclecontext) Failed to configure 'SimpleBicycleModel'." << endl;
            }
        }
    }

} } // opendlv::vehiclecontext

