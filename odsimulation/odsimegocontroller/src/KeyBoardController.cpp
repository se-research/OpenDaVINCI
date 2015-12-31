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

#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

#include <cstdio>
#include <iostream>

#include "ControlBehaviour.h"
#include "KeyBoardController.h"

namespace egocontroller {

    using namespace std;
    using namespace hesperia::data::environment;

    KeyboardController::KeyboardController(
            ControlBehaviour& behaviour,
            const char& keyAcc,
            const char& keyBrake,
            const char& keyLeft,
            const char& keyRight,
            const char& keyStop) :
        m_behaviour(behaviour),
        m_keyAcc(keyAcc),
        m_keyBrake(keyBrake),
        m_keyLeft(keyLeft),
        m_keyRight(keyRight),
        m_keyStop(keyStop)
    {
        struct termios ttystate;

        //get the terminal state
        tcgetattr(STDIN_FILENO, &ttystate);

        //turn off canonical mode
        ttystate.c_lflag &= ~ICANON;
        //minimum of number input read.
        ttystate.c_cc[VMIN] = 1;
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

        cout << "KeyboardController: " << endl;
        cout << "'" << m_keyAcc <<  "': Accelerate" << endl;
        cout << "'" << m_keyBrake <<  "': Brake" << endl;
        cout << "'" << m_keyLeft <<  "': Turn left" << endl;
        cout << "'" << m_keyRight <<  "': Turn right" << endl;
        cout << "'" << m_keyStop <<  "': Stop" << endl;
    }

    KeyboardController::~KeyboardController()
    {
        struct termios ttystate;
        //get the terminal state
        tcgetattr(STDIN_FILENO, &ttystate);

        //turn on canonical mode
        ttystate.c_lflag |= ICANON;
        //set the terminal attributes.
        tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
    }

    void KeyboardController::doWork()
    {
        struct timeval tv;
        fd_set fds;
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds); //STDOUT_FILENO is 0
        select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);

        if (FD_ISSET(STDIN_FILENO, &fds) != 0) {
            char c = fgetc(stdin);

            // Check pressed key.
            if (c == m_keyStop) {
                m_behaviour.stop();
            }
            else if (c == m_keyAcc) {
                m_behaviour.accelerate(0.4);
            }
            else if (c == m_keyBrake) {
                m_behaviour.brake(0.4);
            }
            else if (c == m_keyLeft) {
                m_behaviour.turnLeft(0.1);
            }
            else if (c == m_keyRight) {
                m_behaviour.turnRight(0.1);
            }
        }
    }

    EgoState KeyboardController::getEgoState()
    {
        return m_behaviour.computeEgoState();
    }
}
