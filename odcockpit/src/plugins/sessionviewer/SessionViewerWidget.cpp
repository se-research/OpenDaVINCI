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

            SessionViewerWidget::SessionViewerWidget(const PlugIn &/*plugIn*/, QWidget *prnt, const vector<string> &listOfExpectedModules) :
                QWidget(prnt),
                m_participatingModulesViewMutex(),
                m_expectedModulesToParticipateView(),
                m_participatingModulesView(),
                m_listOfExpectedModulesToParticipate(listOfExpectedModules),
                m_participatingModules(),
                m_expectedModulesToParticipateViewLabel(),
                m_participatingModulesViewLabel() {
                // Set size.
                setMinimumSize(640, 800);

                // Layout manager.
                QHBoxLayout* mainBox = new QHBoxLayout(this);

                // Modules expected to participate in this CID session.
                QVBoxLayout* expectedModulesBox = new QVBoxLayout();
                {
                    stringstream sstr;
                    sstr << m_listOfExpectedModulesToParticipate.size() << " modules expected to participate:";
                    const string s(sstr.str());

                    m_expectedModulesToParticipateViewLabel = unique_ptr<QLabel>(new QLabel(s.c_str()));
                    expectedModulesBox->addWidget(m_expectedModulesToParticipateViewLabel.get());

                    m_expectedModulesToParticipateView = unique_ptr<QListWidget>(new QListWidget(this));

                    expectedModulesBox->addWidget(m_expectedModulesToParticipateView.get());
                }

                // Modules participating in this CID session.
                QVBoxLayout* participatingModulesBox = new QVBoxLayout();
                {
                    stringstream sstr;
                    sstr << "0/" << m_listOfExpectedModulesToParticipate.size() << " modules currently participating:";
                    const string s(sstr.str());

                    m_participatingModulesViewLabel = unique_ptr<QLabel>(new QLabel(s.c_str()));
                    participatingModulesBox->addWidget(m_participatingModulesViewLabel.get());

                    m_participatingModulesView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                    m_participatingModulesView->setColumnCount(4);
                    QStringList headerLabel;
                    headerLabel << tr("Component") << tr("Version") << tr("Frequency") << tr("Slice Consumption");
                    m_participatingModulesView->setColumnWidth(0, 150);
                    m_participatingModulesView->setColumnWidth(1, 130);
                    m_participatingModulesView->setColumnWidth(2, 80);
                    m_participatingModulesView->setColumnWidth(3, 150);
                    m_participatingModulesView->setHeaderLabels(headerLabel);
                    m_participatingModulesView->setSortingEnabled(true);
                    m_participatingModulesView->sortByColumn(0, Qt::AscendingOrder);

                    participatingModulesBox->addWidget(m_participatingModulesView.get());
                }

                // Add to Layout.
                mainBox->addLayout(expectedModulesBox);
                mainBox->addLayout(participatingModulesBox);

                // Set layout manager.
                setLayout(mainBox);
            }

            SessionViewerWidget::~SessionViewerWidget() {}

            void SessionViewerWidget::nextContainer(Container &container) {
                Lock l(m_participatingModulesViewMutex);
                if (container.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
                    m_participatingModulesView->setSortingEnabled(false);

                    odcore::data::dmcp::ModuleStatistics mss = container.getData<odcore::data::dmcp::ModuleStatistics>();

                    // Update widget.
                    uint32_t totalNumberOfModules = 0;
                    auto iterators = mss.iteratorPair_ListOfModuleStatistics();
                    auto it = iterators.first;
                    vector<string> updatedEntries;
                    while (it != iterators.second) {
                        totalNumberOfModules++;
                        odcore::data::dmcp::ModuleStatistic ms = (*it);

                        stringstream sstr;
                        sstr << ms.getModule().getName();

                        if (ms.getModule().getIdentifier().size() > 0) {
                            sstr << ":" << ms.getModule().getIdentifier();
                        }
                        addLogMessageToTree(sstr.str(), ms);
                        updatedEntries.push_back(sstr.str());

                        it++;
                    }

                    // Determine entries to remove due to non-updated values.
                    vector<string> entriesToRemove;
                    auto jt = m_participatingModules.begin();
                    while (jt != m_participatingModules.end()) {
                        auto hasEntry = std::find(std::begin(updatedEntries), std::end(updatedEntries), jt->first);
                        if (hasEntry == std::end(updatedEntries)) {
                            entriesToRemove.push_back(jt->first);
                        }
                        jt++;
                    }

                    // Remove entries.
                    auto kt = entriesToRemove.begin();
                    while (kt != entriesToRemove.end()) {
                        QTreeWidgetItem *entry = m_participatingModules[(*kt)];
                        auto mt = m_participatingModules.find(*kt);
                        m_participatingModules.erase(mt);
                        delete entry; entry = NULL;
                        kt++;
                    }

                    // Update list of expected modules to participate by removing those who participate.
                    vector<string> expectedModulesToParticipate = m_listOfExpectedModulesToParticipate;
                    auto mt = m_participatingModules.begin();
                    while (mt != m_participatingModules.end()) {
                        auto hasEntry = std::find(std::begin(expectedModulesToParticipate), std::end(expectedModulesToParticipate), mt->first);
                        if (hasEntry != std::end(expectedModulesToParticipate)) {
                            expectedModulesToParticipate.erase(hasEntry);
                        }
                        mt++;
                    }
                    // Sort remaining modules.
                    std::sort(std::begin(expectedModulesToParticipate), std::end(expectedModulesToParticipate));

                    // Update list view of expected modules to participate.
                    m_expectedModulesToParticipateView->clear();
                    auto nt = expectedModulesToParticipate.begin();
                    while (nt != expectedModulesToParticipate.end()) {
                        m_expectedModulesToParticipateView->addItem(QString(nt->c_str()));
                        nt++;
                    }

                    // Update labels.
                    {
                        stringstream sstr;
                        sstr << expectedModulesToParticipate.size() << " modules expected to participate:";
                        const string l1(sstr.str());
                        m_expectedModulesToParticipateViewLabel->setText(l1.c_str());

                        sstr.str("");
                        int cnt = (m_listOfExpectedModulesToParticipate.size() - expectedModulesToParticipate.size());
                        cnt = (cnt < 0) ? 0 : cnt;
                        sstr << cnt << "/" << m_listOfExpectedModulesToParticipate.size() << " modules currently participating (total: " << totalNumberOfModules << "):";
                        const string l2(sstr.str());
                        m_participatingModulesViewLabel->setText(l2.c_str());
                    }

                    m_participatingModulesView->setSortingEnabled(true);
                }
            }

            void SessionViewerWidget::addLogMessageToTree(const string &module, const odcore::data::dmcp::ModuleStatistic &ms) {
                // Create new entry if needed
                if (m_participatingModules.find(module) == m_participatingModules.end()) {
                    QTreeWidgetItem *newEntry = new QTreeWidgetItem(m_participatingModulesView.get());
                    newEntry->setText(0, module.c_str());
                    m_participatingModules[module] = newEntry;
                }
                QTreeWidgetItem *componentEntry = m_participatingModules[module];

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
