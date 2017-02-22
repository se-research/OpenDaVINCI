/**
 * odplayerh264 - Tool for replaying video streams encoded with h264.
 * Copyright (C) 2016 Christian Berger
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

#ifndef PLAYERH264_H_
#define PLAYERH264_H_

#include <map>
#include <memory>
#include <string>

#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odtools/player/Player2.h>
#include <opendavinci/odtools/player/PlayerDelegate.h>

#include "PlayerH264ChildHandler.h"
#include "PlayerH264Decoder.h"

namespace odplayerh264 {

    using namespace std;

    /**
     * This class can be used to replay previously recorded data using a
     * conference for distribution. In addition, this class is also
     * restoring h264 video streams.
     */
    class PlayerH264 : public odtools::player::Player2,
                       public odtools::player::PlayerDelegate {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            PlayerH264(const PlayerH264 &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            PlayerH264& operator=(const PlayerH264 &/*obj*/);

        public:
            /**
             * Constructor for single h264 decoder (one video stream only mode).
             *
             * @param url Resource to play.
             * @param autoRewind True if the file should be rewind at EOF.
             * @param memorySegmentSize Size of the memory segment to be used for buffering.
             * @param numberOfMemorySegments Number of memory segments to be used for buffering.
             */
            PlayerH264(const odcore::io::URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments);

            /**
             * Constructor.
             *
             * @param url Resource to play.
             * @param autoRewind True if the file should be rewind at EOF.
             * @param memorySegmentSize Size of the memory segment to be used for buffering.
             * @param numberOfMemorySegments Number of memory segments to be used for buffering.
             * @param basePort Base port for letting spawned children connect to the parent process.
             */
            PlayerH264(const odcore::io::URL &url, const bool &autoRewind, const uint32_t &memorySegmentSize, const uint32_t &numberOfMemorySegments, const uint32_t &basePort);

            virtual ~PlayerH264();

            virtual odcore::data::Container process(odcore::data::Container &c);

        private:
            shared_ptr<PlayerH264Decoder> m_singleDecoder;

            uint32_t m_basePort;

            odcore::base::Mutex m_mapOfDecodersMutex;
            map<string, shared_ptr<PlayerH264ChildHandler> > m_mapOfDecoders;
    };

} // odplayerh264

#endif /*PLAYERH264_H_*/
