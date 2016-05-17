/**
 * cockpit - Visualization environment
 * Copyright (C) 2016 Christian Berger
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

#include <cstring>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "plugins/healthstatusviewer/HealthStatusViewerWidget.h"
#include "automotivedata/generated/from/opendlv/system/diagnostics/HealthStatus.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace healthstatusviewer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            HealthStatusViewerWidget::HealthStatusViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_healthStatusViewMutex(),
                m_healthStatusView() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QHBoxLayout* mainBox = new QHBoxLayout(this);

                m_healthStatusView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_healthStatusView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("system") << tr("status");
                m_healthStatusView->setColumnWidth(0, 180);
                m_healthStatusView->setColumnWidth(1, 80);
                m_healthStatusView->setHeaderLabels(headerLabel);
                m_healthStatusView->setSortingEnabled(true);
                m_healthStatusView->sortByColumn(0, Qt::AscendingOrder);

                // Add to Layout.
                mainBox->addWidget(m_healthStatusView.get());

                // Set layout manager.
                setLayout(mainBox);
            }

            HealthStatusViewerWidget::~HealthStatusViewerWidget() {}

            void HealthStatusViewerWidget::nextContainer(Container &container) {
                Lock l(m_healthStatusViewMutex);
                if (container.getDataType() == from::opendlv::system::diagnostics::HealthStatus::ID()) {
                    m_healthStatusView->setSortingEnabled(false);
                    m_healthStatusView->clear();

                    from::opendlv::system::diagnostics::HealthStatus hs = container.getData<from::opendlv::system::diagnostics::HealthStatus>();

                    // Update widget.
                    auto pairOfIterators = hs.iteratorPair_MapOfStatus();
                    auto it = pairOfIterators.first;
                    while (it != pairOfIterators.second) {
                        QTreeWidgetItem *newEntry = new QTreeWidgetItem(m_healthStatusView.get());
                        newEntry->setText(0, it->first.c_str());
                        newEntry->setText(1, it->second.c_str());

                        it++;
                    }

                    m_healthStatusView->setSortingEnabled(true);
                }
            }

        }
    }
}
