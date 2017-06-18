/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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

#include <string>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "plugins/runtimeconfiguration/RuntimeConfigurationWidget.h"
#include "odvdopendlv/generated/opendlv/proxy/ControlState.h"
#include "odvdopendlv/generated/opendlv/proxy/ControlOverrideState.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace runtimeconfiguration {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::io::conference;
            using namespace odcore::data;

            RuntimeConfigurationWidget::RuntimeConfigurationWidget(const PlugIn &/*plugIn*/, const odcore::base::KeyValueConfiguration &/*kvc*/, ContainerConference &conf, QWidget *prnt) :
                QWidget(prnt),
                m_conference(conf),
                m_keyValueTable(NULL),
                m_runtimeConfigurationMutex(),
                m_runtimeConfiguration() {

                // Set size.
                setMinimumSize(260, 350);

                m_keyValueTable = new QTableWidget(this);
                m_keyValueTable->setRowCount(10);
                m_keyValueTable->setColumnCount(2);

                QStringList keyValueTableHeader;
                keyValueTableHeader << "Key" << "Value";

                m_keyValueTable->setHorizontalHeaderLabels(keyValueTableHeader);
                connect(m_keyValueTable, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(tableItemChanged(QTableWidgetItem*)));

                // Combine KeyValue table.
                QVBoxLayout *v_layout = new QVBoxLayout();
                v_layout->addWidget(m_keyValueTable);

                setLayout(v_layout);

                // Timer for sending data regularly.
                QTimer* timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                timer->start(500);
            }

            RuntimeConfigurationWidget::~RuntimeConfigurationWidget() {}

            void RuntimeConfigurationWidget::tableItemChanged(QTableWidgetItem *item) {
                if (NULL != item) {
                    for(int row = 0; row < m_keyValueTable->rowCount(); row++) {
                        QTableWidgetItem *k = m_keyValueTable->item(row, 0);
                        QTableWidgetItem *v = m_keyValueTable->item(row, 1);
                        if ( (NULL != k) && (NULL != v) ) {
                            const string KEY = k->text().toStdString();
                            const string VALUE = v->text().toStdString();
                            if ( (KEY.size() > 0) && (VALUE.size() > 0) ) {
                                stringstream valueStr;
                                valueStr << VALUE;

                                double value = 0;
                                valueStr >> value;

                                Lock l(m_runtimeConfigurationMutex);
                                m_runtimeConfiguration.putTo_MapOfParameters(KEY, value);
                            }
                        }
                    }
                }
            }

            void RuntimeConfigurationWidget::TimerEvent() {
                Lock l(m_runtimeConfigurationMutex);
                Container c(m_runtimeConfiguration);
                m_conference.send(c);
            }

        }
    }
}

