/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2016 Christian Berger
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_TOOLS_PLAYER_PLAYERLISTENER_H_
#define OPENDAVINCI_TOOLS_PLAYER_PLAYERLISTENER_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"

namespace odtools {
    namespace player {

        using namespace std;

        /**
         * This interface allows other components to change the way how Containers
         * are read from the .rec file. player's default behavior is to restore
         * Containers as they come and to extract BLOB data from shared memory
         * segments from a file named .rec.mem.
         * This behavior can be changed by registering a PlayerDelegate instance
         * for a certain message ID.
         * Whenever a Container with that specified message ID is encountered,
         * the appropriate PlayerDelegate is called to process that container.
         */
        class PlayerListener {
            public:
                virtual ~PlayerListener();

                /**
                 * This method is invoked to report the amount that has
                 * been played back so far.
                 *
                 * @param v % of playback.
                 */
                virtual void percentagePlayedBack(const float &percentagePlayedBack) = 0;
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_PLAYERLISTENER_H_*/
