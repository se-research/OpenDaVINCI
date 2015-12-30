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

#ifndef COCKPIT_PLUGINS_IRUSMAP_IRUSMAPWIDGET_H_
#define COCKPIT_PLUGINS_IRUSMAP_IRUSMAPWIDGET_H_

#if defined __GNUC__
#pragma GCC system_header
#elif defined __SUNPRO_CC
#pragma disable_warn
#elif defined _MSC_VER
#pragma warning(push, 1)
#endif

#include <qobjectdefs.h>
#include <qwidget.h>

#if defined __SUNPRO_CC
#pragma enable_warn
#elif defined _MSC_VER
#pragma warning(pop)
#endif

#include <map>
#include <string>

#include "core/base/Mutex.h"
#include "core/io/conference/ContainerListener.h"
#include "generated/automotive/miniature/SensorBoardData.h"

class QPaintEvent;
class QTimer;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace core { namespace base { class KeyValueConfiguration; } }
namespace core { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace irusmap {

class PointSensor;

            using namespace std;

            /**
             * This class is the container for the irus map widget.
             */
            class IrUsMapWidget : public QWidget, public core::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    IrUsMapWidget(const IrUsMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    IrUsMapWidget& operator=(const IrUsMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    IrUsMapWidget(const PlugIn &plugIn, const core::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~IrUsMapWidget();

                    virtual void nextContainer(core::data::Container &c);

                    void setScale(const int &val);

                    void stopTimer();

                private:
                    virtual void paintEvent(QPaintEvent *evnt);

                private:
                    QTimer *m_timer;

                    core::base::Mutex m_scaleFactorMutex;
                    double m_scaleFactor;
                    double m_rotation;

                    map<string, PointSensor*> m_mapOfPointSensors;

                    core::base::Mutex m_sensorBoardDataMutex;
                    automotive::miniature::SensorBoardData m_sensorBoardData;
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_IRUSMAP_IRUSMAPWIDGET_H_*/

