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

#ifndef COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTSWIDGET_H_
#define COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTSWIDGET_H_

#include <qobjectdefs.h>
#include <qwidget.h>

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "automotivedata/generated/automotive/miniature/SensorBoardData.h"

class QLabel;
class QwtPlot;
class QwtPlotCurve;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

      namespace iruscharts {

class IrUsChartData;

          using namespace std;

            /**
             * This class is the container for the IrUsCharts widget.
             */
            class IrUsChartsWidget : public QWidget, public odcore::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    IrUsChartsWidget(const IrUsChartsWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    IrUsChartsWidget& operator=(const IrUsChartsWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    IrUsChartsWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~IrUsChartsWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                public slots:
                    void TimerEvent();
                    void saveRecordingsFile();
                    void saveCSVFile();

                private:
                    vector<QwtPlot*> m_listOfPlots;
                    vector<QwtPlotCurve*> m_listOfPlotCurves;
                    vector<IrUsChartData*> m_listOfData;
                    map<uint32_t, string> m_mapOfSensors;
                    deque<automotive::miniature::SensorBoardData> m_data;
                    uint32_t m_bufferMax;
                    odcore::base::Mutex m_receivedSensorBoardDataContainersMutex;
                    deque<odcore::data::Container> m_receivedSensorBoardDataContainers;

                    QLabel *m_bufferFilling;
            };
        }
    }
}

#endif /*COCKPIT_PLUGINS_IRUSCHARTS_IRUSCHARTSWIDGET_H_*/
