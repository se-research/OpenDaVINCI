/**
 * hesperia - Simulation environment
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

#ifndef HESPERIA_THREED_FRAMECOUNTER_H_
#define HESPERIA_THREED_FRAMECOUNTER_H_

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/data/TimeStamp.h"

namespace hesperia {
    namespace threeD {

        class FrameCounter
        {
            public:
                FrameCounter();
                ~FrameCounter();

                void reset();

                void update();

                double getFPS();

            protected:
                uint32_t m_frameCounter;
                core::data::TimeStamp m_lastFrame;
                double m_fps;
        };
    }
}
#endif // HESPERIA_THREED_CAMERA_H_
