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

#include "automotivedata/generated/automotive/miniature/SensorBoardData.h"
#include "plugins/iruscharts/IrUsChartData.h"

namespace cockpit {

    namespace plugins {

        namespace iruscharts {

            using namespace std;

#ifdef HAVE_QWT5QWT4
            IrUsChartData::IrUsChartData(deque<automotive::miniature::SensorBoardData> &data, const uint32_t &dataSelection) :
                QwtData(),
                m_data(data),
                m_dataSelection(dataSelection) {}

            IrUsChartData::~IrUsChartData() {}

            QwtData* IrUsChartData::copy() const {
                return new IrUsChartData(m_data, m_dataSelection);
            }

            size_t IrUsChartData::size() const {
                return m_data.size();
            }

            double IrUsChartData::x(size_t i) const {
                return (double)i;
            }

            double IrUsChartData::y(size_t i) const {
                double value = m_data.at(i).getValueForKey_MapOfDistances(m_dataSelection);
                return value;
            }
#endif

        }
    }
}

