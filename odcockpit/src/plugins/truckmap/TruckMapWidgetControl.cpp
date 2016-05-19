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

#include <QtCore>
#include <QtGui>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "plugins/truckmap/TruckMapWidget.h"
#include "plugins/truckmap/TruckMapWidgetControl.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace truckmap {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            TruckMapWidgetControl::TruckMapWidgetControl(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                QWidget(prnt),
                m_mapWidgetMutex(),
                m_mapWidget(NULL) {

                {
                    Lock l(m_mapWidgetMutex);
                    m_mapWidget = new TruckMapWidget(plugIn, kvc, prnt);
                }

                QLabel *scaleLabel = new QLabel(tr("Scale: "), this);
                QSpinBox *scaleSelector = new QSpinBox(this);
                scaleSelector->setMinimum(1);
                scaleSelector->setMaximum(10);
                scaleSelector->setValue(5);
                connect(scaleSelector, SIGNAL(valueChanged(int)), this, SLOT(setScale(int)));

                QHBoxLayout *scaleLayout = new QHBoxLayout();
                scaleLayout->addWidget(scaleLabel);
                scaleLayout->addWidget(scaleSelector);

                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(scaleLayout);
                mainLayout->addWidget(m_mapWidget);

                setLayout(mainLayout);

                // Set size.
                setMinimumSize(640, 480);
            }

            TruckMapWidgetControl::~TruckMapWidgetControl() {
                Lock l(m_mapWidgetMutex);
                m_mapWidget->stopTimer();
                OPENDAVINCI_CORE_DELETE_POINTER(m_mapWidget);
            }

            void TruckMapWidgetControl::setScale(int val) {
                Lock l(m_mapWidgetMutex);
                if (m_mapWidget != NULL) {
                    m_mapWidget->setScale(val);
                }
            }

            void TruckMapWidgetControl::nextContainer(Container &c) {
                Lock l(m_mapWidgetMutex);
                if (m_mapWidget != NULL) {
                    m_mapWidget->nextContainer(c);
                }
            }

        }
    }
}

