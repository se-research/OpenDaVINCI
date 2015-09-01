/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#ifndef PANDABOARD

#include "plugins/forcecontrolviewer/ForceControlData.h"

namespace cockpit {

    namespace plugins {

        namespace forcecontrolviewer {

            using namespace std;
            using namespace automotive;

            ForceControlData::ForceControlData(deque<ForceControl> &data, const FORCECONTROLDATA_INTERFACE &dataSelection) :
                QwtData(),
                m_data(data),
                m_selectedData(dataSelection) {}

            ForceControlData::~ForceControlData() {}

            QwtData* ForceControlData::copy() const {
                return new ForceControlData(m_data, m_selectedData);
            }

            size_t ForceControlData::size() const {
                return m_data.size();
            }

            double ForceControlData::x(size_t i) const {
                return (double)i;
            }

            double ForceControlData::y(size_t i) const {
                double value = 0;
                switch (m_selectedData) {
                    case ACCELERATION_FORCE:
                        value = m_data.at(i).getAccelerationForce();
                    break;
                    case BRAKE_FORCE:
                        value = m_data.at(i).getBrakeForce();
                    break;
                    case STEERING_FORCE:
                        value = m_data.at(i).getSteeringForce();
                    break;
                }
                return value;
            }

        }
    }
}

#endif
