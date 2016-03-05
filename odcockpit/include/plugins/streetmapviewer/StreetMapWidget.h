/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
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

#ifndef PLUGINS_STREETMAP_STREETMAPWIDGET_H_
#define PLUGINS_STREETMAP_STREETMAPWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <string>
#include <vector>

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/strings/StringComparator.h"
#include "opendlv/data/environment/WGS84Coordinate.h"

#include "plugins/streetmapviewer/StreetMapMapWidget.h"

class QNetworkSession;
class QSpinBox;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;

            /**
             * This class is the outer container for the map tile viewer.
             */
            class StreetMapWidget : public QWidget, public odcore::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    StreetMapWidget(const StreetMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    StreetMapWidget& operator=(const StreetMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     * @param rL WGS84 reference location.
                     */
                    StreetMapWidget(const PlugIn &plugIn, QWidget *prnt, const opendlv::data::environment::WGS84Coordinate &rL);

                    virtual ~StreetMapWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                private slots:
                    /**
                     * This method is called whenever zoom level has been changed.
                     *
                     * @param val New value.
                     */
                    void changeZoom(int val);

                    void sessionOpened();

                private:
                    StreetMapMapWidget *m_mapWidget;
                    QNetworkSession *m_networkSession;
                    QSpinBox *m_zoomLevel;
                    opendlv::data::environment::WGS84Coordinate m_referenceLocation;
            };
        }
    }
} // plugins::streetmap

#endif /*PLUGINS_STREETMAP_STREETMAPWIDGET_H_*/
