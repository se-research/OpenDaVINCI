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

#include <iostream>

#include <QtCore>
#include <QtGui>
#include <QtNetwork>

#include "core/data/Container.h"
#include "hesperia/data/environment/EgoState.h"

#include "plugins/streetmapviewer/StreetMapMapWidget.h"
#include "plugins/streetmapviewer/slippymap.h"

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;

            StreetMapMapWidget::StreetMapMapWidget(QWidget *prnt, const double &latitude, const double &longitude) :
                QWidget(prnt),
                m_mapTileProvider(NULL),
                m_pressedPosition() {

                // Map tile provider.
                m_mapTileProvider = new SlippyMap(this);
                m_mapTileProvider->latitude = latitude;
                m_mapTileProvider->longitude = longitude;
                connect(m_mapTileProvider, SIGNAL(updated(QRect)), SLOT(redrawMap(QRect)));
            }

            void StreetMapMapWidget::redrawMap(const QRect &r) {
                update(r);
            }

            void StreetMapMapWidget::resizeEvent(QResizeEvent *) {
                m_mapTileProvider->width = width();
                m_mapTileProvider->height = height();
                m_mapTileProvider->invalidate();
            }

            void StreetMapMapWidget::paintEvent(QPaintEvent *evnt) {
                QPainter painter;
                painter.begin(this);
                    painter.setRenderHint(QPainter::Antialiasing);
                    m_mapTileProvider->render(&painter, evnt->rect());
                    painter.setPen(Qt::black);
                    painter.drawText(rect(),  Qt::AlignBottom | Qt::TextWordWrap, "Map data (c) OpenStreetMap contributors (CC-BY-SA).");
                painter.end();

                {
                    // TODO: Draw something on top of the map like the EgoState of the vehicle.
                    QPainter egoStatePainter;
                    egoStatePainter.begin(this);
                    egoStatePainter.setBrush(QBrush(Qt::red));
                    egoStatePainter.drawEllipse(width()/2, height()/2, 10, 10);
                    egoStatePainter.end();
                }
            }

            void StreetMapMapWidget::mousePressEvent(QMouseEvent *evnt) {
                if (evnt->buttons() == Qt::LeftButton) {
                    m_pressedPosition = evnt->pos();
                }
            }

            void StreetMapMapWidget::mouseMoveEvent(QMouseEvent *evnt) {
                if (evnt->buttons() == Qt::LeftButton) {
                    QPoint delta = evnt->pos() - m_pressedPosition;
                    m_pressedPosition = evnt->pos();
                    m_mapTileProvider->pan(delta);
                }
            }

            void StreetMapMapWidget::zoomIn() {
                m_mapTileProvider->zoom++;
                m_mapTileProvider->invalidate();
                repaint();
            }

            void StreetMapMapWidget::zoomOut() {
                m_mapTileProvider->zoom--;
                m_mapTileProvider->invalidate();
                repaint();
            }

            void StreetMapMapWidget::nextContainer(Container &c) {
                if (c.getDataType() == Container::EGOSTATE) {
                    EgoState es = c.getData<EgoState>();
                    cout << "[StreetMapMapWidget]: " << es.toString() << endl;
                }
                else {
                    cout << "[StreetMapMapWidget]: Received container " << c.getDataType() << endl;
                }
            }

        }
    }
} // plugins::streetmap
