/**
 * egocontroller - Manual control of the vehicle (part of simulation environment)
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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


#if !defined(WIN32) && !defined(__gnu_hurd__)
#include <cstdlib>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/joystick.h>
#endif

#include <iostream>

#include "ControlBehaviour.h"
#include "JoystickController.h"

#if !defined(WIN32) && !defined(__gnu_hurd__)
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <linux/joystick.h>
#endif

namespace egocontroller {

    using namespace std;
    using namespace opendlv::data::environment;

    JoystickController::JoystickController(ControlBehaviour& behaviour, const string& device) :
        m_behaviour(behaviour),
        MAX(32768.0),
        FACTOR_ACCELERATION(80),
        FACTOR_ROTATION(30),
        m_joy_fd(0),
        m_axes(NULL),
        m_lastAxis0(0.0),
        m_lastAxis1(0.0)
    {
        cerr << "Trying to open joystick " << device << endl;
#if !defined(WIN32) && !defined(__gnu_hurd__)
        int num_of_axes = 0;
        int num_of_buttons = 0;

        int name_of_joystick[80];

        if ((m_joy_fd = open(device.c_str() , O_RDONLY)) == -1) {
            cerr << "Could not open joystick " << device << endl;
            return;
        }

        ioctl(m_joy_fd, JSIOCGAXES, &num_of_axes);
        ioctl(m_joy_fd, JSIOCGBUTTONS, &num_of_buttons);
        ioctl(m_joy_fd, JSIOCGNAME(80), &name_of_joystick);

        m_axes = (int *)calloc(num_of_axes, sizeof(int));
        cerr << "Joystick found " << name_of_joystick << ", number of axes: " << num_of_axes << ", number of buttons: " << num_of_buttons <<endl;

        // Use non blocking reading.
        fcntl(m_joy_fd, F_SETFL, O_NONBLOCK);
#endif
    }

    JoystickController::~JoystickController()
    {
        close(m_joy_fd);
    }

    void JoystickController::doWork()
    {
#if !defined(WIN32) && !defined(__gnu_hurd__)
        struct js_event js;
        read(m_joy_fd, &js, sizeof(struct js_event));

        // Check event.
        switch (js.type & ~JS_EVENT_INIT) {
            case JS_EVENT_AXIS:
                m_axes[js.number] = js.value;
            break;
        }
#endif

        double acceleration = 0;
        double deceleration = 0;
        double rotation = 0;
        if (m_axes[1] > 0) {
            // Braking.
            deceleration = (m_axes[1]/MAX)*FACTOR_ACCELERATION;
            m_behaviour.brake(deceleration);
        }
        else {
            // Accelerating.
            acceleration = ((-m_axes[1])/MAX)*FACTOR_ACCELERATION;
            m_behaviour.accelerate(acceleration);
        }

        // Steering.
        rotation = (m_axes[0]/MAX)*FACTOR_ROTATION;
        m_behaviour.turnRight(rotation);

        cerr << "Values: A: " << acceleration << ", B: " << deceleration << ", R: " << rotation << endl;
    }

    EgoState JoystickController::getEgoState()
    {
        return m_behaviour.computeEgoState();
    }
}
