/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
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

#ifndef COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGET_H_
#define COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <string>

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "automotivedata/generated/automotive/miniature/SensorBoardData.h"

class QPaintEvent;
class QTimer;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace truckmap {

class PointSensor;

            using namespace std;

            /**
             * This class is the container for the irus map widget.
             */
            class TruckMapWidget : public QWidget, public odcore::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    TruckMapWidget(const TruckMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    TruckMapWidget& operator=(const TruckMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    TruckMapWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~TruckMapWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                    void setScale(const int &val);

                    void stopTimer();

                private:
                    virtual void paintEvent(QPaintEvent *evnt);

                private:
                    QTimer *m_timer;

                    odcore::base::Mutex m_scaleFactorMutex;
                    double m_scaleFactor;
                    double m_rotation;

                    odcore::base::Mutex m_sensorBoardDataMutex;
                    automotive::miniature::SensorBoardData m_sensorBoardData;
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGET_H_*/

