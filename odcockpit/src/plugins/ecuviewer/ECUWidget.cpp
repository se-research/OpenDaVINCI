/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <sstream>
#include <cstring>

#include "GeneratedHeaders_AutomotiveData.h"

#include "plugins/ecuviewer/ECUWidget.h"

namespace cockpit {

    namespace plugins {

        namespace ecuviewer {

            using namespace std;
            using namespace core::data;
            using namespace core::io::conference; 

            ECUWidget::ECUWidget(const PlugIn &/*plugIn*/, ContainerConference &conf, QWidget *prnt) :
                QWidget(prnt),
                m_conference(conf),
                m_rawDataFromECU(NULL),
                m_accelX(NULL),
                m_accelY(NULL),
                m_accelZ(NULL),
                m_firstCycle(true) {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QVBoxLayout* mainBox = new QVBoxLayout(this);

                //ListView and header construction
                m_rawDataFromECU = new QTextEdit(this);
                m_rawDataFromECU->setReadOnly(true);

                QFont courierFont("Courier", 12, QFont::Normal, false);
                m_rawDataFromECU->setFont(courierFont);

                QSpinBox *dataSelector = new QSpinBox(this);
                dataSelector->setMinimum(0);
                dataSelector->setMaximum(15);
                dataSelector->setValue(0);
                connect(dataSelector, SIGNAL(valueChanged(int)), this, SLOT(setDesiredData(int)));// Changing the value of spinbox will change the position of dial

                m_accelX = new QLabel(tr("0"), this);
                m_accelY = new QLabel(tr("0"), this);
                m_accelZ = new QLabel(tr("0"), this);

                QHBoxLayout *accelLayout = new QHBoxLayout(this);
                accelLayout->addWidget(m_accelX);
                accelLayout->addWidget(m_accelY);
                accelLayout->addWidget(m_accelZ);

                //add to Layout
                mainBox->addLayout(accelLayout);
                mainBox->addWidget(m_rawDataFromECU);

                // Set layout manager.
                setLayout(mainBox);
            }

            ECUWidget::~ECUWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_rawDataFromECU);
                OPENDAVINCI_CORE_DELETE_POINTER(m_accelX);
                OPENDAVINCI_CORE_DELETE_POINTER(m_accelY);
                OPENDAVINCI_CORE_DELETE_POINTER(m_accelZ);
            }

            void ECUWidget::nextContainer(Container &container) {
                if (container.getDataType() == Container::USER_DATA_0) {
                    automotive::miniature::STM32F4Data d = container.getData<automotive::miniature::STM32F4Data>();
                    m_rawDataFromECU->append(QString(d.toString().c_str()));
                    m_rawDataFromECU->verticalScrollBar()->setValue(m_rawDataFromECU->verticalScrollBar()->maximum());
                }
            }

            void ECUWidget::setDesiredData(int v) {
                if (!m_firstCycle) {
                    automotive::miniature::STM32F4Control feed;
                    feed.setDataFeed(v);

                    Container c(Container::USER_DATA_1, feed);

                    m_conference.send(c);
                }
                m_firstCycle = false;
            }

        } 
    }
}
