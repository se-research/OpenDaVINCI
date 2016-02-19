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

#ifndef VEHICLECONTEXT_REPORT_DISTANCETOOBJECTS_H_
#define VEHICLECONTEXT_REPORT_DISTANCETOOBJECTS_H_

#include <list>
#include <string>

#include "opendavinci/core/base/KeyValueConfiguration.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/scenario/PointID.h"

#include "opendavinci/context/base/SystemReportingComponent.h"

namespace opendlv { namespace vehiclecontext {
    namespace report {

        using namespace std;

        /**
         * This class reports whether the distance to any object is less than a given threshold.
         */
        class OPENDAVINCI_API DistanceToObjectsReport : public context::base::SystemReportingComponent {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
				DistanceToObjectsReport(const DistanceToObjectsReport&);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
				DistanceToObjectsReport& operator=(const DistanceToObjectsReport&);

            public:
                /**
                 * Constructor.
                 *
                 * @param configuration Configuration data.
                 * @param threshold Threshold for the distance.
                 */
				DistanceToObjectsReport(const string &configuration, const float &threshold);

                virtual ~DistanceToObjectsReport();

                virtual void setup();

                virtual void tearDown();

                virtual void report(const core::wrapper::Time &t);

                /**
                 * This method returns true, if the distance to the objects was greater than the given threshold.
                 *
                 * @return True, when the distance to all encountered objects was always greater than the given threshold.
                 */
                bool hasCorrectDistance() const;

            private:
                core::base::KeyValueConfiguration m_configuration;
                const float m_threshold;
                bool m_correctDistance;
        };

    }
} } // opendlv::vehiclecontext::report

#endif /*VEHICLECONTEXT_REPORT_DISTANCETOOBJECTS_H_*/
