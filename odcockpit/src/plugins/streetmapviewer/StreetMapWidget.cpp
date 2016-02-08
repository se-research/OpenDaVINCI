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

#include <cmath>
#include <iomanip>
#include <iostream>

#include <QtNetwork>
#include <Qt/qgridlayout.h>
#include <Qt/qlabel.h>
#include <Qt/qspinbox.h>
#include <qglobal.h>
#include <qnamespace.h>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/Container.h"
#include "hesperia/data/environment/EgoState.h"

#include "plugins/streetmapviewer/StreetMapWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {
    namespace plugins {
        namespace streetmap {

            using namespace std;
            using namespace core::data;
            using namespace hesperia::data::environment;

            StreetMapWidget::StreetMapWidget(const PlugIn &/*plugIn*/, QWidget *prnt, const hesperia::data::environment::WGS84Coordinate &rL) :
                QWidget(prnt),
                m_mapWidget(NULL),
                m_networkSession(NULL),
                m_zoomLevel(NULL),
                m_referenceLocation(rL) {

                QGridLayout *streetMapGrid = new QGridLayout(this);

                // Zoom control.
                QLabel *lblZoomLevel = new QLabel(tr("Zoom level:"));
                m_zoomLevel = new QSpinBox(this);
                m_zoomLevel->setRange(14, 17);
                m_zoomLevel->setSingleStep(1);
                m_zoomLevel->setValue(15);

                connect(m_zoomLevel, SIGNAL(valueChanged(int)), this, SLOT(changeZoom(int)));

                QWidget *sideBar = new QWidget(this);
                QGridLayout *sideBarLayout = new QGridLayout(this);
                sideBarLayout->addWidget(lblZoomLevel, 0, 0);
                sideBarLayout->addWidget(m_zoomLevel, 1, 0);
                sideBar->setLayout(sideBarLayout);

                // Setup tile viewer.
                m_mapWidget = new StreetMapMapWidget(this);
                m_mapWidget->setMapCenter(m_referenceLocation);

                // Setup layout.
                streetMapGrid->addWidget(m_mapWidget, 0, 0);
                streetMapGrid->addWidget(sideBar, 0, 1);
                streetMapGrid->setColumnStretch(0, 1);
                streetMapGrid->setColumnStretch(1, 0);

                setLayout(streetMapGrid);

                // Using Qt's network configuration manager to cache downloaded data.
                QNetworkConfigurationManager manager;
                if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
                    QSettings settings(QSettings::UserScope, QLatin1String("OpenDaVINCI"));
                    settings.beginGroup(QLatin1String("QtNetwork"));
                        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
                    settings.endGroup();

                    QNetworkConfiguration config = manager.configurationFromIdentifier(id);
                    if ((config.state() & QNetworkConfiguration::Discovered) != QNetworkConfiguration::Discovered) {
                        config = manager.defaultConfiguration();
                    }

                    m_networkSession = new QNetworkSession(config, this);
                    connect(m_networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

                    m_networkSession->open();
                }
            }

            StreetMapWidget::~StreetMapWidget() {}

            void StreetMapWidget::sessionOpened() {
                QNetworkConfiguration config = m_networkSession->configuration();
                QString id;
                if (config.type() == QNetworkConfiguration::UserChoice) {
                    id = m_networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
                }
                else {
                    id = config.identifier();
                }

                QSettings settings(QSettings::UserScope, QLatin1String("OpenDaVINCI"));
                settings.beginGroup(QLatin1String("QtNetwork"));
                    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
                settings.endGroup();
            }

            void StreetMapWidget::changeZoom(int val) {
                static int oldValue = 15;
                if ((oldValue - val) < 0) {
                    m_mapWidget->zoomIn();
                }
                if ((oldValue - val) > 0) {
                    m_mapWidget->zoomOut();
                }
                oldValue = val;
            }

            void StreetMapWidget::nextContainer(Container &c) {
                const double EPSILON = 1e-4;
                static WGS84Coordinate old = m_referenceLocation;
                if (c.getDataType() == Container::WGS84COORDINATE) {
                    WGS84Coordinate w = c.getData<WGS84Coordinate>();
                    const double deltaLat = fabs(old.getLatitude() - w.getLatitude());
                    const double deltaLon = fabs(old.getLongitude() - w.getLongitude());

                    if ( (deltaLat > EPSILON) || (deltaLon > EPSILON) ) {
                        m_mapWidget->setMapCenter(w);
                        old = w;
                    }
                }
                else {
                    m_mapWidget->nextContainer(c);
                }
            }
        }
    }
} // plugins::streetmap
