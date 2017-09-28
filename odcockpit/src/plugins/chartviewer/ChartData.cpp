/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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

#include "plugins/chartviewer/ChartData.h"

namespace cockpit {

    namespace plugins {

        namespace chartviewer {

            using namespace std;

            ChartData::ChartData(deque<pair<uint64_t, double> > &data) :
                QwtData(),
                m_data(data) {}

            ChartData::~ChartData() {}

            QwtData* ChartData::copy() const {
                return new ChartData(m_data);
            }

            size_t ChartData::size() const {
                return m_data.size();
            }

            double ChartData::x(size_t i) const {
                return static_cast<double>(i);
            }

            double ChartData::y(size_t i) const {
                return m_data.at(i).second;
            }

        }
    }
}

