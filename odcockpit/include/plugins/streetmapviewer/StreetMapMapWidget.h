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

#ifndef PLUGINS_STREETMAP_STREETMAPMAPWIDGET_H_
#define PLUGINS_STREETMAP_STREETMAPMAPWIDGET_H_

#include <QWidget>

#include "core/io/conference/ContainerListener.h"

class SlippyMap;

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            class StreetMapMapWidget: public QWidget,
                                      public core::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    StreetMapMapWidget(const StreetMapMapWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    StreetMapMapWidget& operator=(const StreetMapMapWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param prnt Parent widget.
                     * @param latitude Location to be rendered.
                     * @param longitude Location to be rendered.
                     */
                    StreetMapMapWidget(QWidget *prnt, const double &latitude, const double &longitude);

                    void zoomIn();
                    void zoomOut();

                    virtual void nextContainer(core::data::Container &c);

                protected:
                    void resizeEvent(QResizeEvent *evnt);
                    void paintEvent(QPaintEvent *evnt);
                    void mousePressEvent(QMouseEvent *evnt);
                    void mouseMoveEvent(QMouseEvent *evnt);

                private slots:
                    void redrawMap(const QRect &r);

                private:
                    SlippyMap *m_mapTileProvider;
                    QPoint m_pressedPosition;
            };
        }
    }
} // plugins::streetmap

#endif /*PLUGINS_STREETMAP_STREETMAPMAPWIDGET_H_*/

