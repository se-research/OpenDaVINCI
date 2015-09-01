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

#include "core/base/Lock.h"
#include "core/data/Container.h"
#include "GeneratedHeaders_AutomotiveData.h"

#include "QtIncludes.h"

#include "plugins/controller/ControllerWidget.h"

namespace cockpit {

    namespace plugins {

        namespace controller {

            using namespace std;
            using namespace core::base;
            using namespace core::io::conference;
            using namespace core::data;
            using namespace automotive;

            ControllerWidget::ControllerWidget(const PlugIn &/*plugIn*/, const core::base::KeyValueConfiguration &/*kvc*/, ContainerConference &conf, QWidget *prnt) :
                QWidget(prnt),
                m_conference(conf),
                m_vehicleControlMutex(),
                m_vehicleControl(),
                m_HzMutex(),
                m_Hz(10),
                m_counter(0),
                m_value(NULL),
                m_brakeLEDs(NULL),
                m_leftTurningLEDs(NULL),
                m_rightTurningLEDs(NULL),
                m_userButtonMutex(),
                m_userButton(NULL),
                m_userButtonPressedTS(),
                m_userButtonPressed(false),
                m_userButtonData(),
                m_sendVehicleControlDataMutex(),
                m_sendVehicleControlData(false),
                m_sendVehicleControlButton(NULL) {

                // Set size.
                setMinimumSize(640, 480);

                // Set frequency.
                QGroupBox *frequencyGroup = new QGroupBox(tr("Runtime frequency"));
                frequencyGroup->setFlat(false);
                QLabel *runtimeFrequencyLabel = new QLabel(tr("Runtime frequency [Hz]: "), this);
                QSpinBox *frequencySelector = new QSpinBox(this);
                frequencySelector->setMinimum(1);
                frequencySelector->setMaximum(20);
                frequencySelector->setValue(10);
                connect(frequencySelector, SIGNAL(valueChanged(int)), this, SLOT(setHz(int)));// Changing the value of spinbox will change the position of dial

                QHBoxLayout *frequencyLayout = new QHBoxLayout(this);
                frequencyLayout->addWidget(runtimeFrequencyLabel);
                frequencyLayout->addWidget(frequencySelector);
                frequencyGroup->setLayout(frequencyLayout);

                // Binary LED lights selectors.
                QGroupBox *LEDGroup = new QGroupBox(tr("Vehicle's LEDs"));
                LEDGroup->setFlat(false);
                m_brakeLEDs = new QCheckBox(tr("Brake LEDs"));
                m_leftTurningLEDs = new QCheckBox(tr("Left flashing LEDs"));
                m_rightTurningLEDs = new QCheckBox(tr("Right flashing LEDs"));
                
                m_userButton = new QPushButton(tr("UserButton"));
                connect(m_userButton, SIGNAL(pressed()),this, SLOT(userButtonPressed()));
                connect(m_userButton, SIGNAL(released()),this, SLOT(userButtonReleased()));
                m_userButtonData.setButtonStatus(automotive::miniature::UserButtonData::RELEASED);
                m_userButtonData.setDuration(0);

                m_sendVehicleControlButton = new QPushButton(tr("NOT sending control"));
                connect(m_sendVehicleControlButton, SIGNAL(released()),this, SLOT(sendButtonReleased()));

                QVBoxLayout *LEDselectorLayout = new QVBoxLayout();
                LEDselectorLayout->addWidget(m_userButton);
                LEDselectorLayout->addWidget(m_sendVehicleControlButton);
                LEDselectorLayout->addWidget(m_brakeLEDs);
                LEDselectorLayout->addWidget(m_leftTurningLEDs);
                LEDselectorLayout->addWidget(m_rightTurningLEDs);
                LEDGroup->setLayout(LEDselectorLayout);

                // Combine frequency and LED status.
                QHBoxLayout *frequency_LED = new QHBoxLayout();
                frequency_LED->addWidget(frequencyGroup);
                frequency_LED->addWidget(LEDGroup);

                // ForceControl text.
                QGroupBox *ControlGroup = new QGroupBox(tr("Vehicle control (you must click in this area to control by keyboard!)"));
                QVBoxLayout *vehicleControlLayout = new QVBoxLayout();

                QLabel *description = new QLabel(tr("w=accel., s=decel., up=inc speed, down=dec speed, left, right"));
                vehicleControlLayout->addWidget(description);
                m_value = new QLabel(m_vehicleControl.toString().c_str());
                vehicleControlLayout->addWidget(m_value);

                ControlGroup->setLayout(vehicleControlLayout);

                // Combine frequency_LED and ForceControl text.
                QVBoxLayout *frequency_LED_fc = new QVBoxLayout();
                frequency_LED_fc->addLayout(frequency_LED);
                frequency_LED_fc->addWidget(ControlGroup);

                setLayout(frequency_LED_fc);

                // Enforce the user to click into the window to control the vehicle.
                setFocusPolicy(Qt::StrongFocus);

                // Timer for sending data regularly.
                QTimer* timer = new QTimer(this);
                connect(timer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
                timer->start(50);
            }

            ControllerWidget::~ControllerWidget() {}

            void ControllerWidget::nextContainer(Container &container) {
                if (container.getDataType() == Container::VEHICLECONTROL) {
                    VehicleControl vc = container.getData<VehicleControl>();
                    m_value->setText(vc.toString().c_str());
                }
            }

            void ControllerWidget::userButtonPressed() {
                Lock l(m_userButtonMutex);
                if (!m_userButtonPressed) {
                    m_userButtonPressed = true;
                    m_userButtonPressedTS = TimeStamp();

                    m_userButtonData.setButtonStatus(automotive::miniature::UserButtonData::PRESSED);
                    m_userButtonData.setDuration(0);

                    Container c(Container::USER_BUTTON, m_userButtonData);
                    m_conference.send(c);
                }
            }

            void ControllerWidget::userButtonReleased() {
                Lock l(m_userButtonMutex);
                m_userButtonPressed = false;
                TimeStamp now;
                double duration = (now - m_userButtonPressedTS).toMicroseconds() / 1000000.0;

                m_userButtonData.setButtonStatus(automotive::miniature::UserButtonData::RELEASED);
                m_userButtonData.setDuration(duration);
                Container c(Container::USER_BUTTON, m_userButtonData);
                m_conference.send(c);
            }

            void ControllerWidget::sendButtonReleased() {
                Lock l(m_sendVehicleControlDataMutex);
                m_sendVehicleControlData = !m_sendVehicleControlData;

                if (m_sendVehicleControlData) {
                    m_sendVehicleControlButton->setText(tr("sending control"));
                }
                else {
                    m_sendVehicleControlButton->setText(tr("NOT sending control"));
                }
            }

            void ControllerWidget::TimerEvent() {
                Lock l(m_HzMutex);
                
                if (m_counter == (20/m_Hz) ) {
                    Lock l2(m_vehicleControlMutex);

                    m_vehicleControl.setBrakeLights(m_brakeLEDs->isChecked());
                    m_vehicleControl.setFlashingLightsLeft(m_leftTurningLEDs->isChecked());
                    m_vehicleControl.setFlashingLightsRight(m_rightTurningLEDs->isChecked());

                    {
                        Lock l3(m_sendVehicleControlDataMutex);

                        if (m_sendVehicleControlData) {
                            Container c(Container::VEHICLECONTROL, m_vehicleControl);
                            m_conference.send(c);
                            m_counter = 0;
                        }
                    }
                }

                if (m_counter > (20/m_Hz)) {
                    m_counter = 0;
                }

                m_counter++;
            }

            void ControllerWidget::setHz(int hz) {
                Lock l(m_HzMutex);
                if ( (hz > 0) && (hz < 21) ) {
                    m_Hz = hz;
                }
            }

            void ControllerWidget::keyPressEvent(QKeyEvent *evt) {
                switch(evt->key()){
                    case Qt::Key_W:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setAcceleration(m_vehicleControl.getAcceleration() + 0.25);
                            break;
                        }
                    case Qt::Key_S:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setAcceleration(m_vehicleControl.getAcceleration() - 0.25);
                            break;
                        }
                    case Qt::Key_Up:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setSpeed(m_vehicleControl.getSpeed() + 0.5);
                            break;
                        }
                    case Qt::Key_Down:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setSpeed(m_vehicleControl.getSpeed() - 0.5);
                            break;
                        }
                    case Qt::Key_Left:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setSteeringWheelAngle(m_vehicleControl.getSteeringWheelAngle() - 1*cartesian::Constants::DEG2RAD);
                            break;
                        }
                    case Qt::Key_Right:
                        {
                            Lock l2(m_vehicleControlMutex);
                            m_vehicleControl.setSteeringWheelAngle(m_vehicleControl.getSteeringWheelAngle() + 1*cartesian::Constants::DEG2RAD);
                            break;
                        }
                }
            }
        }
    }
}

