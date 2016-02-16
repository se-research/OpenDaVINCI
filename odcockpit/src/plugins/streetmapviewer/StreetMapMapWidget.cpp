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

#include "core/base/Lock.h"
#include "core/data/Container.h"
#include "hesperia/data/environment/EgoState.h"

#include "plugins/streetmapviewer/StreetMapMapWidget.h"
#include "plugins/streetmapviewer/slippymap.h"

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;
            using namespace core::base;
            using namespace core::data;
            using namespace hesperia::data::environment;

            StreetMapMapWidget::StreetMapMapWidget(QWidget *prnt) :
                QWidget(prnt),
                m_mapTileProvider(NULL),
                m_timer(NULL),
                m_pressedPosition(),
                m_positionMutex(),
                m_position() {

                // Map tile provider.
                m_mapTileProvider = new SlippyMap(this);
                connect(m_mapTileProvider, SIGNAL(updated(QRect)), SLOT(redrawMap(QRect)));

                // Timer repaint.
                m_timer = new QTimer(this);
                connect(m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
                m_timer->start(50);
            }

            void StreetMapMapWidget::setMapCenter(const double &latitude, const double &longitude) {
                m_mapTileProvider->latitude = latitude;
                m_mapTileProvider->longitude = longitude;
                m_mapTileProvider->invalidate();
            }

            void StreetMapMapWidget::setMapCenter(const WGS84Coordinate &position) {
                Lock l(m_positionMutex);
                m_position = position;
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
                Lock l(m_positionMutex);
                m_mapTileProvider->invalidate();
                if ( (fabs(m_position.getLatitude()) > 1e-1) &&
                     (fabs(m_position.getLongitude()) > 1e-1) ) {
                    m_mapTileProvider->latitude = m_position.getLatitude();
                    m_mapTileProvider->longitude = m_position.getLongitude();
                }

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
                if (c.getDataType() == hesperia::data::environment::EgoState::ID()) {
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
