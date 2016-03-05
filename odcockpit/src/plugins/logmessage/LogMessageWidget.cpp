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

#include <cstring>
#include <sstream>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/generated/odcore/data/LogMessage.h"
#include "plugins/logmessage/LogMessageWidget.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace logmessage {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;

            LogMessageWidget::LogMessageWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataView(),
                m_components(),
                m_loglevelPerComponent() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("Component") << tr("Message");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);
            }

            LogMessageWidget::~LogMessageWidget() {}

            void LogMessageWidget::nextContainer(Container &container) {
                if (container.getDataType() == odcore::data::LogMessage::ID()) {
                    addLogMessageToTree(container);
                }
            }

            void LogMessageWidget::addLogMessageToTree(Container &container) {
                if (container.getDataType() == odcore::data::LogMessage::ID()) {
                    odcore::data::LogMessage lm = container.getData<odcore::data::LogMessage>();

                    // Create new entry if needed
                    if (m_components.find(lm.getComponentName()) == m_components.end()) {
                        QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                        newHeader->setText(0, lm.getComponentName().c_str());
                        m_components[lm.getComponentName()] = newHeader;
                    }
                    QTreeWidgetItem *componentEntry = m_components[lm.getComponentName()];

                    // Search for lm.getComponentName()-loglevel entry.
                    stringstream sstr;
                    sstr << lm.getComponentName() << "-"<< lm.getLogLevel();
                    const string subentry = sstr.str();

                    if (m_loglevelPerComponent.find(subentry) == m_loglevelPerComponent.end()) {
                        QTreeWidgetItem *newComponentLogLevelHeader = new QTreeWidgetItem();
                        switch (lm.getLogLevel()) {
                            case odcore::data::LogMessage::INFO:
                                newComponentLogLevelHeader->setText(0, "info");
                            break;
                            case odcore::data::LogMessage::WARN:
                                newComponentLogLevelHeader->setText(0, "warn");
                            break;
                            case odcore::data::LogMessage::DEBUG:
                                newComponentLogLevelHeader->setText(0, "debug");
                            break;
                            default:
                            break;
                        }
                        m_loglevelPerComponent[subentry] = newComponentLogLevelHeader;

                        componentEntry->insertChild(0, newComponentLogLevelHeader);
                    }

                    QTreeWidgetItem *componentSubEntry = m_loglevelPerComponent[subentry];
                    {
                        QTreeWidgetItem *logMessageEntry = new QTreeWidgetItem();
                        stringstream sstr2;
                        sstr2 << container.getSentTimeStamp().toString();
                        const string s2 = sstr2.str();

                        logMessageEntry->setText(0, s2.c_str());
                        logMessageEntry->setText(1, lm.getLogMessage().c_str());
                        componentSubEntry->insertChild(0, logMessageEntry);

                        const int32_t MAX_CHILDREN = 10;
                        componentSubEntry->takeChild(MAX_CHILDREN);
                   }
                }
            }

        }
    }
}
