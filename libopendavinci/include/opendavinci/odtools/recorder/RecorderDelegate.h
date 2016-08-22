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

#ifndef OPENDAVINCI_TOOLS_RECORDER_RECORDERDELEGATE_H_
#define OPENDAVINCI_TOOLS_RECORDER_RECORDERDELEGATE_H_

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/data/Container.h"

namespace odtools {
    namespace recorder {

        using namespace std;

        /**
         * This interface allows other components to change the way how Containers
         * are written to the .rec file. recorder's default behavior is to dump
         * Containers as they come and to extract BLOB data from shared memory
         * segments to disk in a file named .rec.mem.
         * This behavior can be changed by registering a RecorderDelegate instance
         * for a certain message ID.
         * Whenever a Container with that specified message ID is encountered,
         * the appropriate RecorderDelegate is called to process that container.
         */
        class RecorderDelegate {
            public:
                virtual ~RecorderDelegate();

                /**
                 * This method stores the given container using the
                 * RecorderDelegate logic (for instance, the Container could
                 * be encoded into a different format). To indicate
                 * in the original .rec data stream that the original Container
                 * has been replaced, a placeholder Container is expected
                 * that is written to the .rec file instead of c.
                 *
                 * @param c Container to be stored externally.
                 * @return Container that is written instead of c into the .rec file.
                 */
                virtual odcore::data::Container process(odcore::data::Container &c) = 0;
        };

    } // recorder
} // tools

#endif /*OPENDAVINCI_TOOLS_RECORDER_RECORDERDELEGATE_H_*/
