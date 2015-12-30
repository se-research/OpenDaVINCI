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

#ifndef COCKPIT_PLUGINS_MODULESTATISTICSVIEWER_LOADPERMODULE_H_
#define COCKPIT_PLUGINS_MODULESTATISTICSVIEWER_LOADPERMODULE_H_

#include <qcolor.h>

#include <deque>
#include <string>
#include <vector>

#include "core/base/Mutex.h"
#include "generated/coredata/dmcp/ModuleDescriptor.h"
#include "generated/coredata/dmcp/RuntimeStatistic.h"

class QwtPlotCurve;

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            using namespace std;

            /**
             * This class collects all data per module.
             */
            class LoadPerModule {
                private:
                    enum {
                        MAX_ENTRIES_TO_QUEUE = 100,
                    };

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    LoadPerModule(const LoadPerModule &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    LoadPerModule& operator=(const LoadPerModule &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plot Parental plot.
                     * @param md Module's descriptor.
                     * @param color Curve's color.
                     */
                    LoadPerModule( const coredata::dmcp::ModuleDescriptor &md, const QColor &color);

                    virtual ~LoadPerModule();

                    /**
                     * This method adds new runtime statistics.
                     *
                     * @param rts RunTimeStatistics to be added.
                     */
                    void addRuntimeStatistics(const coredata::dmcp::RuntimeStatistic &rts);

                    QwtPlotCurve* getCurve();

                    const string getModuleName() const;

                private:
                    coredata::dmcp::ModuleDescriptor m_moduleDescriptor;
                    QwtPlotCurve *m_curve;
                    core::base::Mutex m_loadMutex;
                    deque<coredata::dmcp::RuntimeStatistic> m_load;
                    vector<double> m_data;
                    vector<double> m_reference;
                    double m_referenceOffset;
            };

        }
    }
} // cockpit::plugins::modulestatisticsviewer

#endif /*COCKPIT_PLUGINS_MODULESTATISTICSVIEWER_LOADPERMODULE_H_*/
