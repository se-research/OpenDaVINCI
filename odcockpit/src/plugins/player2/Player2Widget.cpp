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
#include "opendavinci/odtools/player/Player2.h"
#include "opendavinci/generated/odcore/data/player/PlayerCommand.h"

#include "plugins/player2/Player2Widget.h"

#ifdef HAVE_ODPLAYERH264
    #include "PlayerH264.h"
#endif

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace player2 {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odtools::player;

            Player2Widget::Player2Widget(const PlugIn &/*plugIn*/, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt) :
                QWidget(prnt),
                m_kvc(kvc),
                m_conference(conf),
                m_multiplexer(multiplexer),
                m_playBtn(NULL),
                m_pauseBtn(NULL),
                m_rewindBtn(NULL),
                m_stepBtn(NULL),
                m_autoRewind(NULL),
                m_speedValueMutex(),
                m_speedValue(100),
                m_desc(NULL),
                m_containerCounterDesc(NULL),
                m_containerCounter(0),
                m_containerCounterTotal(0),
                m_processBtn(NULL),
                m_start(NULL),
                m_end(NULL),
                m_player2(NULL),
                m_fileName(""),
                m_currentWorkingDirectory("") {
                m_currentWorkingDirectory = QDir::currentPath().toStdString();

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

                QSlider *speedSlider = new QSlider(Qt::Horizontal, this);
                speedSlider->setValue(99);
                connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(speedValue(int)));

                // Final layout.
                QVBoxLayout *mainLayout = new QVBoxLayout(this);
                mainLayout->addLayout(fileOperations);
                mainLayout->addWidget(m_desc);
                mainLayout->addWidget(m_containerCounterDesc);
                mainLayout->addWidget(speedSlider);
                mainLayout->addLayout(operations);
//TODO: Validate splitting for h264 files.
//                mainLayout->addLayout(splitting);

                setLayout(mainLayout);
            }

            Player2Widget::~Player2Widget() {
                m_player2.reset();
            }

            void Player2Widget::speedValue(int value) {
                Lock l(m_speedValueMutex);
                m_speedValue = value + 1;
            }

            void Player2Widget::play() {
                m_playBtn->setEnabled(false);
                m_pauseBtn->setEnabled(true);
                m_stepBtn->setEnabled(false);
//                m_rewindBtn->setEnabled(false);
//                m_processBtn->setEnabled(false);

                sendNextContainer();
            }

            void Player2Widget::pause() {
                m_playBtn->setEnabled(true);
                m_pauseBtn->setEnabled(false);
                m_stepBtn->setEnabled(true);
//                m_rewindBtn->setEnabled(true);
//                m_processBtn->setEnabled(true);
            }

            void Player2Widget::rewind() {
                if (m_player2 != NULL) {
                    m_player2->rewind();
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

            void Player2Widget::step() {
                sendNextContainer();
            }

            void Player2Widget::sendNextContainer() {
                if (m_player2.get() != NULL) {
                    if (!m_player2->hasMoreData() && (m_autoRewind != NULL) && m_autoRewind->isChecked()) {
                        m_player2->rewind();
                        m_containerCounter = 0;
                    }

                    if (m_player2->hasMoreData()) {
                        // Get container to be sent.
                        const Container &nextContainerToBeSent2 = m_player2->getNextContainerToBeSent();
                        Container &nextContainerToBeSent = const_cast<Container&>(nextContainerToBeSent2);

                        // Increment the counters.
                        if (m_player2->hasMoreData()) {
                            m_containerCounter++;
                            if (!(m_containerCounter < m_containerCounterTotal)) {
                                m_containerCounterTotal = m_containerCounter;
                            }
                        }

                        stringstream sstr;
                        sstr << m_containerCounter << "/" << m_containerCounterTotal << " container(s) replayed.";
                        m_containerCounterDesc->setText(sstr.str().c_str());

                        // Get delay to wait _after_ sending the container.
                        uint32_t delay = m_player2->getDelay() / 1000;

                        {
                            // Fasten playback if desired.
                            Lock l(m_speedValueMutex);
                            delay *= (m_speedValue/100.0);
                        }

                        // Send container.
                        if ( (nextContainerToBeSent.getDataType() != Container::UNDEFINEDDATA) &&
                             (nextContainerToBeSent.getDataType() != odcore::data::player::PlayerCommand::ID()) ) {
//                            m_conference.send(nextContainerToBeSent);
                            m_multiplexer.distributeContainer(nextContainerToBeSent);
                        }

                        // Continously playing if "pause" button is enabled.
                        if (m_pauseBtn->isEnabled()) {
                            QTimer::singleShot(delay, this, SLOT(sendNextContainer()));
                        }

                        // If end of file has been reached, stop playback.
                        if (!m_player2->hasMoreData() && (m_autoRewind != NULL) && !m_autoRewind->isChecked()) {
                            pause();
                        }
                    }
                }
            }

            void Player2Widget::process() {
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

            void Player2Widget::loadFile() {
                QDir::setCurrent(m_currentWorkingDirectory.c_str());
                m_fileName = QFileDialog::getOpenFileName(this, tr("Open previous recording file"), "", tr("Recording files (*.rec)")).toStdString();

                if (!m_fileName.empty()) {
                    m_player2.reset();

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
//                    const uint32_t MEMORY_SEGMENT_SIZE = m_kvc.getValue<uint32_t>("global.buffer.memorySegmentSize");

                    // Number of memory segments.
//                    const uint32_t NUMBER_OF_SEGMENTS = m_kvc.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

                    // We use the asychronous player to allow data caching in background.
//                    const bool THREADING = false;
                    const bool AUTO_REWIND = false;
//#ifdef HAVE_ODPLAYERH264
//                    // Base port for letting spawned children connect to parent process.
//                    const uint32_t BASE_PORT = m_kvc.getValue<uint32_t>("odplayerh264.portbaseforchildprocesses");
//                    m_player2 = shared_ptr<Player>(new odplayerh264::PlayerH264(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, BASE_PORT));
//#else
                    m_player2 = shared_ptr<Player2>(new Player2(url, AUTO_REWIND));
//#endif

                    m_playBtn->setEnabled(true);
                    m_pauseBtn->setEnabled(false);
                    m_stepBtn->setEnabled(true);
//                    m_rewindBtn->setEnabled(false);

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
