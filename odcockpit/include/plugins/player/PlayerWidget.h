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

#ifndef COCKPIT_PLUGINS_PLAYERWIDGET_H_
#define COCKPIT_PLUGINS_PLAYERWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <string>

#include "opendavinci/odcore/opendavinci.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }
namespace odtools { namespace player { class Player; } }

namespace cockpit {

    namespace plugins {

        namespace player {

            using namespace std;

            /**
             * This class is the container for the cutter widget.
             */
            class PlayerWidget : public QWidget {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    PlayerWidget(const PlayerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    PlayerWidget& operator=(const PlayerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConference.
                     * @param conf Conference to send data to.
                     * @param prnt Pointer to the parental widget.
                     */
                    PlayerWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt);

                    virtual ~PlayerWidget();

                public slots:
                    void loadFile();

                    void play();
                    void pause();
                    void rewind();
                    void step();

                    void sendNextContainer();

                    void process();

                private:
                    const odcore::base::KeyValueConfiguration &m_kvc;
                    odcore::io::conference::ContainerConference &m_conference;

                    QPushButton *m_playBtn;
                    QPushButton *m_pauseBtn;
                    QPushButton *m_rewindBtn;
                    QPushButton *m_stepBtn;
                    QCheckBox *m_autoRewind;
                    QLabel *m_desc;
                    QLabel *m_containerCounterDesc;
                    int32_t m_containerCounter;
                    int32_t m_containerCounterTotal;

                    QPushButton *m_processBtn;
                    QLineEdit *m_start;
                    QLineEdit *m_end;

                    odtools::player::Player *m_player;

                    string m_fileName;
                    string m_currentWorkingDirectory;
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_PLAYERWIDGET_H_ */
