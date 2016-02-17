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

#include "hesperia/threeD/FrameCounter.h"

namespace hesperia {
    namespace threeD {

        using namespace core::data;

        FrameCounter::FrameCounter() :
            m_frameCounter(0),
            m_lastFrame(),
            m_fps(0)
        {}

        FrameCounter::~FrameCounter()
        {}

        void FrameCounter::reset() {
            m_frameCounter = 0;
            m_lastFrame = TimeStamp();
            m_fps = 0.0;
        }

        void FrameCounter::update() {
            TimeStamp current;
            TimeStamp duration = current - m_lastFrame;
            m_frameCounter++;

            if ( duration.toMicroseconds() > 1000*1000) {
                m_fps = m_frameCounter / duration.getSecond();
                m_frameCounter = 0;
                m_lastFrame = TimeStamp();
            }
        }


        double FrameCounter::getFPS() {
            return m_fps;
        }
    }
}
