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

#ifndef COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTDATA_H_
#define COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTDATA_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#ifndef PANDABOARD

#include <deque>

#include "QtIncludes.h"

#include "GeneratedHeaders_AutomotiveData.h"

namespace cockpit {

    namespace plugins {

      namespace iruscharts {

            using namespace std;

            /**
             * This class is the container of accessing previous SensorBoardData.
             */
            class IrUsChartData : public QwtData {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    IrUsChartData(const IrUsChartData &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    IrUsChartData& operator=(const IrUsChartData &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param data Reference to the deque of received SensorBoardData.
                     * @param dataSelection Select the type of data that is returned.
                     */
                    IrUsChartData(deque<automotive::miniature::SensorBoardData> &data, const uint32_t &dataSelection);

                    virtual ~IrUsChartData();

                    virtual QwtData *copy() const;

                    virtual size_t size() const;

                    virtual double x(size_t i) const;

                    virtual double y(size_t i) const;

                private:
                    deque<automotive::miniature::SensorBoardData> &m_data;
                    const uint32_t m_dataSelection;
            };
        }
    }
}

#endif

#endif /*COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTDATA_H_*/

