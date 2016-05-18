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

#ifndef STARTSTOPWIDGET_H_
#define STARTSTOPWIDGET_H_

#include <QtCore>
#include <QtGui>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "automotivedata/generated/automotive/VehicleControl.h"
#include "automotivedata/generated/automotive/miniature/UserButtonData.h"

class QPushButton;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

      namespace startstop {

          using namespace std;

            /**
             * This class is the container for the startstop widget.
             */
            class StartStopWidget : public QWidget, public odcore::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    StartStopWidget(const StartStopWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    StartStopWidget& operator=(const StartStopWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param conf Client conference to send data to.
                     * @param prnt Pointer to the parental widget.
                     */
                    StartStopWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt);

                    virtual ~StartStopWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                public slots:
                    void TimerEvent();
                    void startButtonPressed();

                private:
                    odcore::io::conference::ContainerConference &m_conference;

                    odcore::base::Mutex m_startedMutex;
                    bool m_started;
                    bool m_overrideActive;
                    QPushButton *m_startedButton;
                    QLabel *m_statusLabel;
            };
        }
    }
}

#endif /*STARTSTOPWIDGET_H_*/

