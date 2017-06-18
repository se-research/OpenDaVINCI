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

#ifndef COCKPIT_PLUGINS_CHARTVIEWER_CHARTDATA_H_
#define COCKPIT_PLUGINS_CHARTVIEWER_CHARTDATA_H_

#include <deque>

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif
    #include <qwt_data.h>
#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#include "opendavinci/odcore/opendavinci.h"

namespace cockpit {
    namespace plugins {
      namespace chartviewer {

            using namespace std;

            /**
             * This class is the container of accessing previous signals.
             */
            class ChartData : public QwtData {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ChartData(const ChartData &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ChartData& operator=(const ChartData &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param data Reference to the deque of received SensorBoardData.
                     * @param dataSelection Select the type of data that is returned.
                     */
                    ChartData(deque<double> &data);

                    virtual ~ChartData();

                    virtual QwtData *copy() const;

                    virtual size_t size() const;

                    virtual double x(size_t i) const;

                    virtual double y(size_t i) const;

                private:
                    deque<double> &m_data;
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_CHARTVIEWER_CHARTDATA_H_*/
