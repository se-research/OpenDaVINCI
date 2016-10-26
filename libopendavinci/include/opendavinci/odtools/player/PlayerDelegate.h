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

#ifndef OPENDAVINCI_TOOLS_PLAYER_PLAYERDELEGATE_H_
#define OPENDAVINCI_TOOLS_PLAYER_PLAYERDELEGATE_H_

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
        class PlayerDelegate {
            public:
                virtual ~PlayerDelegate();

                /**
                 * This method stores the given container using the
                 * PlayerDelegate logic (for instance, the Container needs to
                 * be restored from a different format). Thus, in the original
                 * .rec data stream might be a replacement container that
                 * needs to be restored to the original Container.
                 *
                 * @param c Container to be restored.
                 * @return Restored container.
                 */
                virtual odcore::data::Container process(odcore::data::Container &c) = 0;
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_PLAYERDELEGATE_H_*/
