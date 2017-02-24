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

#ifndef COCKPIT_PLUGINS_PLAYER2WIDGET_H_
#define COCKPIT_PLUGINS_PLAYER2WIDGET_H_

#include <QtCore>
#include <QtGui>

#include <memory>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odtools/player/PlayerListener.h"

#include "FIFOMultiplexer.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }
namespace odtools { namespace player { class Player2; } }

namespace cockpit {

    namespace plugins {

        namespace player2 {

            using namespace std;

            /**
             * This class is the container for the cutter widget.
             */
            class Player2Widget : public QWidget,
                                  public odtools::player::PlayerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    Player2Widget(const Player2Widget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    Player2Widget& operator=(const Player2Widget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConference.
                     * @param conf Conference to send data to.
                     * @param prnt Pointer to the parental widget.
                     */
                    Player2Widget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt);

                    virtual ~Player2Widget();

                    virtual void percentagePlayedBack(const float &percentagePlayedBack);

                public slots:
                    void speedValue(int);
                    void loadFile();

                    void play();
                    void pause();
                    void rewind();
                    void step();

                    void sendNextContainer();

                    void process();

                signals:
                    void showProgress(int);

                private:
                    const odcore::base::KeyValueConfiguration &m_kvc;
                    odcore::io::conference::ContainerConference &m_conference;
                    FIFOMultiplexer &m_multiplexer;

                    QPushButton *m_playBtn;
                    QPushButton *m_pauseBtn;
                    QPushButton *m_rewindBtn;
                    QPushButton *m_stepBtn;
                    QCheckBox *m_autoRewind;

                    odcore::base::Mutex m_speedValueMutex;
                    int m_speedValue;

                    QLabel *m_desc;
                    QLabel *m_containerCounterDesc;
                    int32_t m_containerCounter;
                    int32_t m_containerCounterTotal;

                    QPushButton *m_processBtn;
                    QLineEdit *m_start;
                    QLineEdit *m_end;

                    QProgressBar *m_timeline;

                    shared_ptr<odtools::player::Player2> m_player2;

                    string m_fileName;
                    string m_currentWorkingDirectory;
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_PLAYER2WIDGET_H_ */
