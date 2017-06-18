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

#ifndef COCKPIT_PLUGINS_CHARTVIEWER_CHARTWIDGET_H_
#define COCKPIT_PLUGINS_CHARTVIEWER_CHARTWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/reflection/MessageResolver.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"

class QLabel;
class QwtPlot;
class QwtPlotCurve;

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

      namespace chartviewer {

class ChartData;

          using namespace std;

            /**
             * This class is the container for the Chart widget.
             */
            class ChartWidget : public QWidget, public odcore::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ChartWidget(const ChartWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ChartWidget& operator=(const ChartWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param dataType Container data type identifier to monitor.
                     * @param senderStamp Container sender stamp.
                     * @param fieldName Field from message to watch.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    ChartWidget(const PlugIn &plugIn, const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~ChartWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                public slots:
                    void TimerEvent();
                    void saveCSVFile();

                signals:
                    void updateLabel(QString s);

                private:
                    unique_ptr<odcore::reflection::MessageResolver> m_messageResolver;

                    int32_t m_dataType;
                    uint32_t m_senderStamp;
                    string m_fieldName;

                    QwtPlot* m_plot;
                    QwtPlotCurve* m_plotCurve;
                    ChartData* m_chartData;

                    odcore::base::Mutex m_dataMutex;
                    deque<pair<uint64_t, double> > m_data;
                    uint32_t m_bufferMax;

                    QLabel *m_bufferFilling;
            };
        }
    }
}

#endif /*COCKPIT_PLUGINS_CHARTVIEWER_CHARTWIDGET_H_*/
