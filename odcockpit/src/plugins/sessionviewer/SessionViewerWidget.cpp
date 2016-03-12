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
#include <iostream>
#include <sstream>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "opendavinci/generated/odcore/data/dmcp/RuntimeStatistic.h"
#include "plugins/sessionviewer/SessionViewerWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace sessionviewer {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            SessionViewerWidget::SessionViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataView(),
                m_components() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(4);
                QStringList headerLabel;
                headerLabel << tr("Component") << tr("Version") << tr("Frequency") << tr("Slice Consumption");
                m_dataView->setColumnWidth(0, 150);
                m_dataView->setColumnWidth(1, 130);
                m_dataView->setColumnWidth(2, 80);
                m_dataView->setColumnWidth(3, 150);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            SessionViewerWidget::~SessionViewerWidget() {}

            void SessionViewerWidget::nextContainer(Container &container) {
                if (container.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
                    odcore::data::dmcp::ModuleStatistics mss = container.getData<odcore::data::dmcp::ModuleStatistics>();

                    // Update widget.
                    auto iterators = mss.iteratorPair_ListOfModuleStatistics();
                    auto it = iterators.first;
                    vector<string> updatedEntries;
                    while (it != iterators.second) {
                        odcore::data::dmcp::ModuleStatistic ms = (*it);

                        stringstream sstr;
                        sstr << ms.getModule().getName();
                        if (ms.getModule().getIdentifier().size() > 0) {
                            sstr << "-" << ms.getModule().getIdentifier();
                        }
                        addLogMessageToTree(sstr.str(), ms);
                        updatedEntries.push_back(sstr.str());

                        it++;
                    }

                    // Determine entries to remove due to non-updated values.
                    vector<string> entriesToRemove;
                    auto jt = m_components.begin();
                    while (jt != m_components.end()) {
                        auto hasEntry = std::find(std::begin(updatedEntries), std::end(updatedEntries), jt->first);
                        if (hasEntry == std::end(updatedEntries)) {
                            entriesToRemove.push_back(jt->first);
                        }
                        jt++;
                    }

                    // Remove entries.
                    auto kt = entriesToRemove.begin();
                    while (kt != entriesToRemove.end()) {
                        QTreeWidgetItem *entry = m_components[(*kt)];
                        auto mt = m_components.find(*kt);
                        m_components.erase(mt);
                        delete entry; entry = NULL;
                        kt++;
                    }
                }
            }

            void SessionViewerWidget::addLogMessageToTree(const string &module, const odcore::data::dmcp::ModuleStatistic &ms) {
                // Create new entry if needed
                if (m_components.find(module) == m_components.end()) {
                    QTreeWidgetItem *newEntry = new QTreeWidgetItem(m_dataView.get());
                    newEntry->setText(0, module.c_str());
                    m_components[module] = newEntry;
                }
                QTreeWidgetItem *componentEntry = m_components[module];

                // Update fields.
                componentEntry->setText(1, ms.getModule().getVersion().c_str());

                stringstream sstr1; sstr1 << ms.getModule().getFrequency() << " Hz";
                string str1(sstr1.str().c_str());
                componentEntry->setText(2, str1.c_str());

                stringstream sstr2; sstr2 << (ms.getRuntimeStatistic().getSliceConsumption() * 100.0) << "%";
                string str2(sstr2.str().c_str());
                componentEntry->setText(3, str2.c_str());
            }

        }
    }
}
