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

#ifndef HESPERIA_THREED_CAMERA_H_
#define HESPERIA_THREED_CAMERA_H_

#include "opendlv/data/environment/Point3.h"

namespace opendlv {
    namespace threeD {

    class Camera
    {
            /**
             * Simple Camera that can be positioned in 3D space with orientation
             * given by head, pitch and roll angles.
             */
            public:
                /**
                 * Creates a new camera located in the origin (0,0,0) with
                 * orientation head,pitch, roll = 0.
                 */
                Camera();

                /**
                 * Creates a new camera with given position and orientation
                 */
                Camera(const opendlv::data::environment::Point3& position,
                       const float& head,
                       const float& pitch,
                       const float& roll);

                ~Camera();

                /**
                 * Moves the camera backwards along the view direction.
                 * position += length*orientation
                 */
                void moveBackward(const float& length);

                /**
                 * Moves the camera forward along the view direction.
                 * position -= length*orientation
                 */
                void moveFoward(const float& length);

                /**
                 * Move the camera up
                 * position.z -= length*orientation.z
                 */
                void moveUp(const float& length);

                /**
                 * Move the camera down
                 * position.z += length*orientation.z
                 */
                void moveDown(const float& length);

                /**
                 * Moves the camera right (based on 2D normal vector of
                 * the orientation).
                 * normal = (orientation.y, -orientation.x, 0)
                 * position += length*normal;
                 */
                void strafeRight(const float& length);

                /**
                 * Moves the camera left (based on 2D normal vector of
                 * the orientation).
                 * normal = (orientation.y, -orientation.x, 0)
                 * position -= length*normal;
                 */
                void strafeLeft(const float& length);

                /**
                 * Changes the head angle by delta degrees.
                 */
                void changeHead(const float& delta);

                /**
                 * Changes the pitch angle by delta degrees.
                 */
                void changePitch(const float& delta);

                /**
                 * Changes the roll angle by delta degrees.
                 */
                void changeRoll(const float& delta);


                /**
                 * Sets a new camera position.
                 */
                void setPosition(const opendlv::data::environment::Point3& position);

                /**
                 * Sets new head angle.
                 * @param head New head angle.
                 */
                void setHead(const float& head);

                /**
                 * Sets new pitch angle.
                 * @param pitch New pitch angle.
                 */
                void setPitch(const float& pitch);

                /**
                 * Sets new roll angle.
                 * @param roll New roll angle.
                 */
                void setRoll(const float& roll);

                /**
                 * Applies this camera in OpenGL
                 */
                void apply();

            private:
                opendlv::data::environment::Point3 m_position;
                opendlv::data::environment::Point3 m_orientation;
                opendlv::data::environment::Point3 m_up;

                float m_head;
                float m_pitch;
                float m_roll;
        };
    }
}
#endif // HESPERIA_THREED_CAMERA_H_
