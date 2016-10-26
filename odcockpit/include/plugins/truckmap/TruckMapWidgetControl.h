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

#ifndef COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGETCONTROL_H_
#define COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGETCONTROL_H_

#include <QtCore>
#include <QtGui>

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace truckmap {

class TruckMapWidget;

            using namespace std;

            /**
             * This class is the container for the irus map widget control.
             */
            class TruckMapWidgetControl : public QWidget, public odcore::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    TruckMapWidgetControl(const TruckMapWidgetControl &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    TruckMapWidgetControl& operator=(const TruckMapWidgetControl &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param prnt Pointer to the parental widget.
                     */
                    TruckMapWidgetControl(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt);

                    virtual ~TruckMapWidgetControl();

                    virtual void nextContainer(odcore::data::Container &c);

                public slots:
                    void setScale(int val);

                private:
                    odcore::base::Mutex m_mapWidgetMutex;
                    TruckMapWidget *m_mapWidget;
            };

        }
    }
}

#endif /*COCKPIT_PLUGINS_TRUCKMAP_TRUCKMAPWIDGETCONTROL_H_*/

