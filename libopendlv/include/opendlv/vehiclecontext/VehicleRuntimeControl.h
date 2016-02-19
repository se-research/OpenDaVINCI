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

#ifndef VEHICLECONTEXT_VEHICLERUNTIMECONTROL_H_
#define VEHICLECONTEXT_VEHICLERUNTIMECONTROL_H_

//#include "opendavinci/core/base/KeyValueConfiguration.h"

#include "opendavinci/context/base/StandaloneRuntimeControl.h"

namespace opendlv { namespace vehiclecontext {

    using namespace std;

    /**
     * This class is used to realize a standalone system simulations for vehicle-related simulations.
     */
    class OPENDAVINCI_API VehicleRuntimeControl : public context::base::StandaloneRuntimeControl {
		public:
			enum VEHICLECONTEXTMODULES {
				SIMPLIFIEDBICYCLEMODEL,
			};

        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            VehicleRuntimeControl(const VehicleRuntimeControl&);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            VehicleRuntimeControl& operator=(const VehicleRuntimeControl&);

        public:
            /**
             * Constructor.
             *
             * @param sci RuntimeControlInterface to be used.
             */
            VehicleRuntimeControl(const context::base::RuntimeControlInterface &sci);

            virtual ~VehicleRuntimeControl();

        private:
            core::base::KeyValueConfiguration m_globalConfiguration;

            /**
             * This method returns the appropriate configuration data.
             *
             * @param module Module to get configuration for.
             */
            const core::base::KeyValueConfiguration getConfigurationFor(const enum VEHICLECONTEXTMODULES &module);

            virtual void configureRuntimeEnvironment();
    };

} } // opendlv::vehiclecontext

#endif /*VEHICLECONTEXT_VEHICLERUNTIMECONTROL_H_*/
