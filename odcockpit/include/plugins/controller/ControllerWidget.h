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

#ifndef CONTROLLERWIDGET_H_
#define CONTROLLERWIDGET_H_

#include <qobjectdefs.h>
#include <qwidget.h>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "automotivedata/generated/automotive/VehicleControl.h"
#include "automotivedata/generated/automotive/miniature/UserButtonData.h"

class QCheckBox;
class QKeyEvent;
class QLabel;
class QPushButton;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace data { class Container; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

      namespace controller {

          using namespace std;

            /**
             * This class is the container for the controller widget.
             */
            class ControllerWidget : public QWidget, public odcore::io::conference::ContainerListener {

                Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ControllerWidget(const ControllerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ControllerWidget& operator=(const ControllerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param kvc KeyValueConfiguration for this based widget.
                     * @param conf Client conference to send data to.
                     * @param prnt Pointer to the parental widget.
                     */
                    ControllerWidget(const PlugIn &plugIn, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt);

                    virtual ~ControllerWidget();

                    virtual void nextContainer(odcore::data::Container &c);

                protected:
                    void keyPressEvent(QKeyEvent *event);

                public slots:
                    void TimerEvent();
                    void setHz(int v);

                    void userButtonPressed();
                    void userButtonReleased();

                    void sendButtonReleased();

                private:
                    odcore::io::conference::ContainerConference &m_conference;
                    odcore::base::Mutex m_vehicleControlMutex;
                    automotive::VehicleControl m_vehicleControl;

                    odcore::base::Mutex m_HzMutex;
                    uint32_t m_Hz;
                    uint32_t m_counter;

                    QLabel *m_value;
                    QCheckBox *m_brakeLEDs;
                    QCheckBox *m_leftTurningLEDs;
                    QCheckBox *m_rightTurningLEDs;

                    odcore::base::Mutex m_userButtonMutex;
                    QPushButton *m_userButton;
                    odcore::data::TimeStamp m_userButtonPressedTS;
                    bool m_userButtonPressed;
                    automotive::miniature::UserButtonData m_userButtonData;

                    odcore::base::Mutex m_sendVehicleControlDataMutex;
                    bool m_sendVehicleControlData;
                    QPushButton *m_sendVehicleControlButton;
            };
        }
    }
}

#endif /*CONTROLLERWIDGET_H_*/

