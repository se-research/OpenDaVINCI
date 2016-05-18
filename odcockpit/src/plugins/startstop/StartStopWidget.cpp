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

#include <QtCore>
#include <QtGui>

#include <string>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "plugins/startstop/StartStopWidget.h"
#include "automotivedata/generated/from/opendlv/proxy/ControlState.h"
#include "automotivedata/generated/from/opendlv/proxy/ControlOverrideState.h"

namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace startstop {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::io::conference;
            using namespace odcore::data;
            using namespace automotive;

            StartStopWidget::StartStopWidget(const PlugIn &/*plugIn*/, const odcore::base::KeyValueConfiguration &/*kvc*/, ContainerConference &conf, QWidget *prnt) :
                QWidget(prnt),
                m_conference(conf),
                m_startedMutex(),
                m_started(false),
                m_overrideActive(false),
                m_startedButton(NULL),
                m_statusLabel(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                {
                    m_startedButton = new QPushButton(tr("NOT ACTIVATED"));
                    m_startedButton->setStyleSheet("background-color: lightgray");
                    connect(m_startedButton, SIGNAL(released()),this, SLOT(startButtonPressed()));
                }

                {
                    m_statusLabel = new QLabel("");
                    m_statusLabel->setAlignment(Qt::AlignCenter);
                    QPalette _palette;
                    _palette.setColor(QPalette::WindowText,Qt::red);
                    m_statusLabel->setPalette(_palette);
                }

                // Combine button and status.
                QVBoxLayout *v_layout = new QVBoxLayout();
                v_layout->addWidget(m_startedButton);
                v_layout->addWidget(m_statusLabel);

                QHBoxLayout *h_layout = new QHBoxLayout();
                h_layout->addLayout(v_layout);

                setLayout(h_layout);

                // Timer for sending data regularly.
                QTimer* timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                timer->start(1000);
            }

            StartStopWidget::~StartStopWidget() {}

            void StartStopWidget::nextContainer(Container &container) {
                if (container.getDataType() == from::opendlv::proxy::ControlOverrideState::ID()) {
                    Lock l(m_startedMutex);
                    from::opendlv::proxy::ControlOverrideState cos = container.getData<from::opendlv::proxy::ControlOverrideState>();
                    m_overrideActive = cos.getIsOverridden();

                    m_statusLabel->setText(m_overrideActive ? "manual override" : "");
                }
            }

            void StartStopWidget::startButtonPressed() {
                Lock l(m_startedMutex);
                m_started = !m_started;

                if (m_started) {
                    m_startedButton->setText(tr("ACTIVATED"));

                    m_startedButton->setStyleSheet("background-color: lightgreen");
                }
                else {
                    m_startedButton->setText(tr("NOT ACTIVATED"));

                    m_startedButton->setStyleSheet("background-color: lightgray");
                }
            }

            void StartStopWidget::TimerEvent() {
                Lock l(m_startedMutex);
                
                if (m_started) {
                    from::opendlv::proxy::ControlState cs(m_started);
                    Container c(cs);
                    m_conference.send(c);
                }
            }

        }
    }
}

