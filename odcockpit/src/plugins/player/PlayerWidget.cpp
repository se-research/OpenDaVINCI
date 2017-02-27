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

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/generated/odcore/data/player/PlayerStatus.h"

#include "plugins/player/PlayerWidget.h"

#ifdef HAVE_ODPLAYERH264
    #include "PlayerH264.h"
#endif

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace player {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odtools::player;

            PlayerWidget::PlayerWidget(const PlugIn &/*plugIn*/, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt) :
                QWidget(prnt),
                m_kvc(kvc),
                m_conference(conf),
                m_multiplexer(multiplexer),
                m_playBtn(NULL),
                m_pauseBtn(NULL),
                m_rewindBtn(NULL),
                m_stepBtn(NULL),
                m_autoRewind(NULL),
                m_relayToConference(NULL),
                m_speedValueMutex(),
                m_speedValue(100),
                m_desc(NULL),
                m_containerCounterDesc(NULL),
                m_containerCounter(0),
                m_containerCounterTotal(0),
                m_processBtn(NULL),
                m_start(NULL),
                m_end(NULL),
                m_timeline(NULL),
                m_player(NULL),
                m_fileName(""),
                m_currentWorkingDirectory("") {
                m_currentWorkingDirectory = QDir::currentPath().toStdString();

                // Set size.
                setMinimumSize(400, 150);

                // Button control.
                QPushButton *loadFileBtn = new QPushButton("Load .rec file", this);
                QObject::connect(loadFileBtn, SIGNAL(clicked()), this, SLOT(loadFile()));

                QHBoxLayout *fileOperations = new QHBoxLayout();
                fileOperations->addWidget(loadFileBtn);

                m_desc = new QLabel("No .rec file loaded.");
                m_containerCounterDesc = new QLabel("0/0 container(s) replayed.");

                // Play/pause control.
                m_playBtn = new QPushButton("Play", this);
                m_playBtn->setEnabled(false);
                QObject::connect(m_playBtn, SIGNAL(clicked()), this, SLOT(play()));

                m_pauseBtn = new QPushButton("Pause", this);
                m_pauseBtn->setEnabled(false);
                QObject::connect(m_pauseBtn, SIGNAL(clicked()), this, SLOT(pause()));

//                m_rewindBtn = new QPushButton("Rewind", this);
//                m_rewindBtn->setEnabled(false);
//                QObject::connect(m_rewindBtn, SIGNAL(clicked()), this, SLOT(rewind()));

                m_stepBtn = new QPushButton("Step", this);
                m_stepBtn->setEnabled(false);
                QObject::connect(m_stepBtn, SIGNAL(clicked()), this, SLOT(step()));

//                m_autoRewind = new QCheckBox("Auto rewind", this);

                QHBoxLayout *operations = new QHBoxLayout();
                operations->addWidget(m_playBtn);
                operations->addWidget(m_pauseBtn);
//TODO: Implement rewind for h264 files.
//                operations->addWidget(m_rewindBtn);
                operations->addWidget(m_stepBtn);
//TODO: Implement autorewind for h264 files.
//                operations->addWidget(m_autoRewind);

//                // Splitting file.
//                m_processBtn = new QPushButton("Split", this);
//                m_processBtn->setEnabled(false);
//                QObject::connect(m_processBtn, SIGNAL(clicked()), this, SLOT(process()));

//                QLabel *lblStart = new QLabel(tr("Start container:"));
//                QLabel *lblEnd = new QLabel(tr("End container:"));
//                m_start = new QLineEdit();
//                m_end = new QLineEdit();

//                QHBoxLayout *splitting = new QHBoxLayout();
////TODO: Validate splitting for h264 files
//                splitting->addWidget(m_processBtn);
//                splitting->addWidget(lblStart);
//                splitting->addWidget(m_start);
//                splitting->addWidget(lblEnd);
//                splitting->addWidget(m_end);

                m_timeline = new QProgressBar(this);
                m_timeline->setValue(0);
                connect(this, SIGNAL(showProgress(int)), m_timeline, SLOT(setValue(int)));

                QHBoxLayout *speedSliderLayout = new QHBoxLayout();
                {
                    QLabel *lblSpeedSlider = new QLabel(tr("Replay speed up:"));

                    QSlider *speedSlider = new QSlider(Qt::Horizontal, this);
                    speedSlider->setValue(99);
                    connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(speedValue(int)));

                    speedSliderLayout->addWidget(lblSpeedSlider);
                    speedSliderLayout->addWidget(speedSlider);
                }

                m_relayToConference = new QCheckBox("Relay Containers to Conference.", this);

                // Final layout.
                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(fileOperations);
                mainLayout->addWidget(m_desc);
                mainLayout->addWidget(m_containerCounterDesc);
                mainLayout->addWidget(m_timeline);
                mainLayout->addLayout(operations);
                mainLayout->addLayout(speedSliderLayout);
                mainLayout->addWidget(m_relayToConference);
//TODO: Validate splitting for h264 files.
//                mainLayout->addLayout(splitting);

                setLayout(mainLayout);
            }

            PlayerWidget::~PlayerWidget() {
                m_player.reset();
            }

            void PlayerWidget::percentagePlayedBack(const float &percentagePlayedBack) {
                emit showProgress(static_cast<uint32_t>(fabs(percentagePlayedBack) * 100));
            }

            void PlayerWidget::speedValue(int value) {
                Lock l(m_speedValueMutex);
                m_speedValue = value + 1;
            }

            void PlayerWidget::play() {
                m_playBtn->setEnabled(false);
                m_pauseBtn->setEnabled(true);
                m_stepBtn->setEnabled(false);
//                m_rewindBtn->setEnabled(false);
//                m_processBtn->setEnabled(false);

                sendNextContainer();
            }

            void PlayerWidget::pause() {
                m_playBtn->setEnabled(true);
                m_pauseBtn->setEnabled(false);
                m_stepBtn->setEnabled(true);
//                m_rewindBtn->setEnabled(true);
//                m_processBtn->setEnabled(true);
            }

            void PlayerWidget::rewind() {
                if (m_player != NULL) {
                    m_player->rewind();
                    m_containerCounter = 0;
                }
                m_playBtn->setEnabled(true);
                m_pauseBtn->setEnabled(false);
                m_stepBtn->setEnabled(true);
//                m_rewindBtn->setEnabled(false);
//                m_processBtn->setEnabled(true);

                stringstream sstr;
                sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                m_containerCounterDesc->setText(sstr.str().c_str());
            }

            void PlayerWidget::step() {
                sendNextContainer();
            }

            void PlayerWidget::sendNextContainer() {
                if (m_player.get() != NULL) {
                    if (!m_player->hasMoreData() && (m_autoRewind != NULL) && m_autoRewind->isChecked()) {
                        m_player->rewind();
                        m_containerCounter = 0;
                    }

                    if (m_player->hasMoreData()) {
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
                        sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed; " << nextContainerToBeSent.getSampleTimeStamp().getYYYYMMDD_HHMMSSms();
                        m_containerCounterDesc->setText(sstr.str().c_str());

                        // Get delay to wait _after_ sending the container.
                        uint32_t delay = m_player->getCorrectedDelay() / 1000;

                        {
                            // Fasten playback if desired.
                            Lock l(m_speedValueMutex);
                            float f = m_speedValue/100.0;
                            f = (f > 0.1) ? f : 0.1;
                            delay *= f;
                        }

                        // Send container.
                        if (nextContainerToBeSent.getDataType() != Container::UNDEFINEDDATA) {
                            if ((m_relayToConference != NULL) && m_relayToConference->isChecked()) {
                                m_conference.send(nextContainerToBeSent);
                            }
                            m_multiplexer.distributeContainer(nextContainerToBeSent);
                        }

                        // Continously playing if "pause" button is enabled.
                        if (m_pauseBtn->isEnabled()) {
                            QTimer::singleShot(delay, this, SLOT(sendNextContainer()));
                        }

                        // If end of file has been reached, stop playback.
                        if (!m_player->hasMoreData() && (m_autoRewind != NULL) && !m_autoRewind->isChecked()) {
                            pause();
                        }
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
//                        const uint32_t MEMORY_SEGMENT_SIZE = m_kvc.getValue<uint32_t>("global.buffer.memorySegmentSize");

//                        Splitter s;
//                        s.process(m_fileName, MEMORY_SEGMENT_SIZE, start, end);
                        
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
                QDir::setCurrent(m_currentWorkingDirectory.c_str());
                m_fileName = QFileDialog::getOpenFileName(this, tr("Open previous recording file"), "", tr("Recording files (*.rec)")).toStdString();

                if (!m_fileName.empty()) {
                    m_player.reset();
                    emit showProgress(0);

                    // Set current working directory.
                    {
                        m_currentWorkingDirectory = "";
                        vector<string> tokens = odcore::strings::StringToolbox::split(m_fileName, '/');
                        auto it = tokens.begin();
                        while ((it+1) != tokens.end()) {
                            m_currentWorkingDirectory += "/" + (*it);
                            it++;
                        }
                        QDir::setCurrent(m_currentWorkingDirectory.c_str());
                    }

                    stringstream s;
                    s << "file://" << m_fileName;
                    odcore::io::URL url(s.str());

                    m_desc->setText(url.toString().c_str());

                    // Size of the memory buffer.
                    const uint32_t MEMORY_SEGMENT_SIZE = m_kvc.getValue<uint32_t>("global.buffer.memorySegmentSize");

                    // Number of memory segments.
                    const uint32_t NUMBER_OF_SEGMENTS = m_kvc.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

                    // We use the asychronous player to allow data caching in background.
                    const bool THREADING = true;
                    const bool AUTO_REWIND = false;
#ifdef HAVE_ODPLAYERH264
//                    // Base port for letting spawned children connect to parent process.
//                    const uint32_t BASE_PORT = m_kvc.getValue<uint32_t>("odplayerh264.portbaseforchildprocesses");
//                    m_player = shared_ptr<Player>(new odplayerh264::PlayerH264(url, AUTO_REWIND, BASE_PORT));

                    m_player = shared_ptr<Player>(new odplayerh264::PlayerH264(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
#else
                    m_player = shared_ptr<Player>(new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
#endif
                    m_player->setPlayerListener(this);
                    // Inform Qt widgets that a new file has been loaded.
                    {
                        odcore::data::player::PlayerStatus ps;
                        ps.setStatus(odcore::data::player::PlayerStatus::NEW_FILE_LOADED);
                        Container c(ps);
                        m_multiplexer.distributeContainer(c);
                    }

                    m_playBtn->setEnabled(true);
                    m_pauseBtn->setEnabled(false);
                    m_stepBtn->setEnabled(true);
//                    m_rewindBtn->setEnabled(false);

                    m_containerCounter = 0;
                    m_containerCounterTotal = m_player->getTotalNumberOfContainersInRecFile()-1;

                    stringstream sstr;
                    sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                    m_containerCounterDesc->setText(sstr.str().c_str());
                }
            }

        }
    }
}
