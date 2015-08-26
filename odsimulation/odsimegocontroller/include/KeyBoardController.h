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

#ifndef EGOCONTROLLER_KEABOARDCONTROLLER_H_
#define EGOCONTROLLER_KEABOARDCONTROLLER_H_

#include "Controller.h"
#include "ControlBehaviour.h"

namespace egocontroller {

    using namespace std;

    class KeyboardController : public Controller
    {
        public:
            KeyboardController(
                    ControlBehaviour& behaviour,
                    const char& keyAcc,
                    const char& keyBrake,
                    const char& keyLeft,
                    const char& keyRight,
                    const char& keyStop);

            virtual ~KeyboardController();

            virtual void doWork();
            virtual hesperia::data::environment::EgoState getEgoState();

        private:
            ControlBehaviour& m_behaviour;
            char m_keyAcc;
            char m_keyBrake;
            char m_keyLeft;
            char m_keyRight;
            char m_keyStop;
    };
}

#endif // EGOCONTROLLER_KEABOARDCONTROLLER_H_
