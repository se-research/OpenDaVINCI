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

#include <Qt/qcheckbox.h>
#include <Qt/qfiledialog.h>
#include <Qt/qlabel.h>
#include <Qt/qlineedit.h>
#include <Qt/qmessagebox.h>
#include <Qt/qpushbutton.h>
#include <Qt/qtimer.h>
#include <qboxlayout.h>
#include <qobject.h>
#include <qstring.h>

#include <iostream>
#include <sstream>
#include <string>

#include "core/opendavinci.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "core/io/conference/ContainerConference.h"
#include "core/opendavinci.h"
#include "plugins/player/PlayerWidget.h"
#include "tools/player/Player.h"
#include "tools/splitter/Splitter.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace player {

            using namespace std;
            using namespace core::data;
            using namespace tools::player;
            using namespace tools::splitter;

            PlayerWidget::PlayerWidget(const PlugIn &/*plugIn*/, const core::base::KeyValueConfiguration &kvc, core::io::conference::ContainerConference &conf, QWidget *prnt) :
                QWidget(prnt),
                m_kvc(kvc),
                m_conference(conf),
                m_playBtn(NULL),
                m_pauseBtn(NULL),
                m_rewindBtn(NULL),
                m_stepBtn(NULL),
                m_autoRewind(NULL),
                m_desc(NULL),
                m_containerCounterDesc(NULL),
                m_containerCounter(0),
                m_containerCounterTotal(0),
                m_processBtn(NULL),
                m_start(NULL),
                m_end(NULL),
                m_player(NULL),
                m_fileName("") {
                // Set size.
                setMinimumSize(400, 150);

                // Button control.
                QPushButton *loadFileBtn = new QPushButton("Load recording", this);
                QObject::connect(loadFileBtn, SIGNAL(clicked()), this, SLOT(loadFile()));

                QHBoxLayout *fileOperations = new QHBoxLayout();
                fileOperations->addWidget(loadFileBtn);

                m_desc = new QLabel("No file loaded.");
                m_containerCounterDesc = new QLabel("0/0 container(s) replayed.");

                // Play/pause control.
                m_playBtn = new QPushButton("Play", this);
                m_playBtn->setEnabled(false);
                QObject::connect(m_playBtn, SIGNAL(clicked()), this, SLOT(play()));

                m_pauseBtn = new QPushButton("Pause", this);
                m_pauseBtn->setEnabled(false);
                QObject::connect(m_pauseBtn, SIGNAL(clicked()), this, SLOT(pause()));

                m_rewindBtn = new QPushButton("Rewind", this);
                m_rewindBtn->setEnabled(false);
                QObject::connect(m_rewindBtn, SIGNAL(clicked()), this, SLOT(rewind()));

                m_stepBtn = new QPushButton("Step", this);
                m_stepBtn->setEnabled(false);
                QObject::connect(m_stepBtn, SIGNAL(clicked()), this, SLOT(step()));

                m_autoRewind = new QCheckBox("Auto rewind", this);

                QHBoxLayout *operations = new QHBoxLayout();
                operations->addWidget(m_playBtn);
                operations->addWidget(m_pauseBtn);
                operations->addWidget(m_rewindBtn);
                operations->addWidget(m_stepBtn);
                operations->addWidget(m_autoRewind);

                // Splitting file.
                m_processBtn = new QPushButton("Split", this);
                m_processBtn->setEnabled(false);
                QObject::connect(m_processBtn, SIGNAL(clicked()), this, SLOT(process()));

                QLabel *lblStart = new QLabel(tr("Start container:"));
                QLabel *lblEnd = new QLabel(tr("End container:"));
                m_start = new QLineEdit();
                m_end = new QLineEdit();

                QHBoxLayout *splitting = new QHBoxLayout();
                splitting->addWidget(m_processBtn);
                splitting->addWidget(lblStart);
                splitting->addWidget(m_start);
                splitting->addWidget(lblEnd);
                splitting->addWidget(m_end);

                // Final layout.
                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(fileOperations);
                mainLayout->addWidget(m_desc);
                mainLayout->addWidget(m_containerCounterDesc);
                mainLayout->addLayout(operations);
                mainLayout->addLayout(splitting);

                setLayout(mainLayout);
            }

            PlayerWidget::~PlayerWidget() {
                OPENDAVINCI_CORE_DELETE_POINTER(m_player);
            }

            void PlayerWidget::play() {
                m_playBtn->setEnabled(false);
                m_pauseBtn->setEnabled(true);
                m_rewindBtn->setEnabled(false);
                m_stepBtn->setEnabled(false);
                m_processBtn->setEnabled(false);

                sendNextContainer();
            }

            void PlayerWidget::pause() {
                m_playBtn->setEnabled(true);
                m_pauseBtn->setEnabled(false);
                m_stepBtn->setEnabled(true);
                m_rewindBtn->setEnabled(true);
                m_processBtn->setEnabled(true);
            }

            void PlayerWidget::rewind() {
                if (m_player != NULL) {
                    m_player->rewind();
                    m_containerCounter = 0;
                }
                m_playBtn->setEnabled(true);
                m_pauseBtn->setEnabled(false);
                m_stepBtn->setEnabled(true);
                m_rewindBtn->setEnabled(false);
                m_processBtn->setEnabled(true);

                stringstream sstr;
                sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                m_containerCounterDesc->setText(sstr.str().c_str());
            }

            void PlayerWidget::step() {
                sendNextContainer();
            }

            void PlayerWidget::sendNextContainer() {
                if (m_player != NULL) {
                    if (!m_player->hasMoreData() && m_autoRewind->isChecked()) {
                        m_player->rewind();
                        m_containerCounter = 0;
                    }

                    // Get container to be sent.
                    Container nextContainerToBeSent = m_player->getNextContainerToBeSent();

                    // Increment the counters.
                    if (m_player->hasMoreData()) {
                        m_containerCounter++;
                        if (!(m_containerCounter < m_containerCounterTotal)) {
                            m_containerCounterTotal = m_containerCounter;
                        }
                    }

                    stringstream sstr;
                    sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                    m_containerCounterDesc->setText(sstr.str().c_str());

                    // Get delay to wait _after_ sending the container.
                    uint32_t delay = m_player->getDelay() / 1000;

                    // Send container.
                    if ( (nextContainerToBeSent.getDataType() != Container::UNDEFINEDDATA) &&
                         (nextContainerToBeSent.getDataType() != Container::PLAYER_COMMAND) ) {
                        m_conference.send(nextContainerToBeSent);
                    }

                    // Continously playing if "pause" button is enabled.
                    if (m_pauseBtn->isEnabled()) {
                        QTimer::singleShot(delay, this, SLOT(sendNextContainer()));
                    }

                    // If end of file has been reached, stop playback.
                    if (!m_player->hasMoreData() && !m_autoRewind->isChecked()) {
                        pause();
                    }
                }
            }

            void PlayerWidget::process() {
                if (!m_fileName.empty()) {
                    uint32_t start = 0, end = 0;
                    stringstream s_start;
                    s_start << m_start->text().toStdString();
                    s_start >> start;

                    stringstream s_end;
                    s_end << m_end->text().toStdString();
                    s_end >> end;

                    if (start < end) {
                        // Size of the memory buffer.
                        const uint32_t MEMORY_SEGMENT_SIZE = m_kvc.getValue<uint32_t>("global.buffer.memorySegmentSize");

                        Splitter s;
                        s.process(m_fileName, MEMORY_SEGMENT_SIZE, start, end);
                        
                        QMessageBox msgBox;
                        msgBox.setText("Current file split completed.");
                        msgBox.exec();
                    }
                    else {
                        QMessageBox msgBox;
                        msgBox.setText("Invalid range specified.");
                        msgBox.exec();
                    }
                }
                else {
                    QMessageBox msgBox;
                    msgBox.setText("No recording specified.");
                    msgBox.exec();
                }
            }

            void PlayerWidget::loadFile() {
                m_fileName = QFileDialog::getOpenFileName(this, tr("Open previous recording file"), "", tr("Recording files (*.rec)")).toStdString();

                if (!m_fileName.empty()) {
                    OPENDAVINCI_CORE_DELETE_POINTER(m_player);

                    stringstream s;
                    s << "file://" << m_fileName;
                    core::io::URL url(s.str());

                    m_desc->setText(url.toString().c_str());

                    // Size of the memory buffer.
                    const uint32_t MEMORY_SEGMENT_SIZE = m_kvc.getValue<uint32_t>("global.buffer.memorySegmentSize");

                    // Number of memory segments.
                    const uint32_t NUMBER_OF_SEGMENTS = m_kvc.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

                    // We use the asychronous player to allow data caching in background.
                    const bool THREADING = false;
                    const bool AUTO_REWIND = false;
                    m_player = new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING);

                    m_playBtn->setEnabled(true);
                    m_pauseBtn->setEnabled(false);
                    m_stepBtn->setEnabled(true);
                    m_rewindBtn->setEnabled(false);

                    m_containerCounter = 0;
                    m_containerCounterTotal = 0;

                    stringstream sstr;
                    sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                    m_containerCounterDesc->setText(sstr.str().c_str());
                }
            }

        }
    }
}
