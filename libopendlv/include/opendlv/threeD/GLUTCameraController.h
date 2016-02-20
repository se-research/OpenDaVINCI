/**
 * OpenDLV - Simulation environment
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

#ifndef HESPERIA_THREED_GLUTCAMERACONTROLLER_H_
#define HESPERIA_THREED_GLUTCAMERACONTROLLER_H_

#include "opendavinci/odcore/opendavinci.h"

namespace opendlv {
    namespace threeD {

        /**
         * Eases the use of a Camera in a GLUTWindow. Simply call the process... methods
         * and can control the camera like a First-Person-Shooter.
         */
class Camera;

        class GLUTCameraController
        {
            public:
                GLUTCameraController(opendlv::threeD::Camera& camera,
                                     double positionDelta = 0.5,
                                     double orientationDelta = 0.08 );

                virtual ~GLUTCameraController();

                void processKey(unsigned char key, int32_t x, int32_t y);
                void processMouseMotion(int32_t x, int32_t y);
                void processMouseEvent(int32_t button, int32_t state, int32_t x, int32_t y);

            protected:
                opendlv::threeD::Camera& m_camera;
                double m_positionDelta;
                double m_orientationDelta;
                int32_t m_mouseX;
                int32_t m_mouseY;
                int32_t m_mouseButton;
        };
    }
}
#endif // HESPERIA_THREED_GLUTCAMERACONTROLLER_H_
