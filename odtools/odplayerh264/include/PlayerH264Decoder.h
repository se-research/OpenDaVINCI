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

#ifndef PLAYERH264DECODER_H_
#define PLAYERH264DECODER_H_

#include <cstdio>

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <memory>
#include <vector>

#include "opendavinci/odcore/wrapper/SharedMemory.h"
#include "opendavinci/generated/odcore/data/image/SharedImage.h"

#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/odtools/player/PlayerDelegate.h"

namespace odplayerh264 {

    using namespace std;

    /**
     * This class can be used to replay previously recorded data using a
     * conference for distribution. In addition, this class is also
     * restoring h264 video streams.
     */
    class PlayerH264Decoder : public odtools::player::PlayerDelegate {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            PlayerH264Decoder(const PlayerH264Decoder &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            PlayerH264Decoder& operator=(const PlayerH264Decoder &/*obj*/);

        public:
            /**
             * Constructor.
             */
            PlayerH264Decoder();

            virtual ~PlayerH264Decoder();

            virtual odcore::data::Container process(odcore::data::Container &c);

        private:
            /**
             * This method initializes the h.264 decoder.
             *
             * @param filename Name of the file to read data from.
             * @return true if initialization succeeded.
             */
            bool initialize(const string &filename);

            /**
             * This method returns the next frame from the given h264 file.
             *
             * @return true if succeeded; the shared memory segment contains the decoded frame in BGR24 format.
             */
            bool getNextFrame();

            /**
             * This method fills up the internal buffe with bytes.
             *
             * @return The amount of bytes read into the internal buffer.
             */
            int fillBuffer();

            /**
             * This method is called whenever more bytes in the internal buffer
             * are needed.
             *
             * @param readMoreBytes indicate whether we need to read more bytes.
             * @return true if succeeded.
             */
            bool update(bool &readMoreBytes);

            /**
             * This method does the actual decoding.
             *
             * @param data Raw h264-encoded data.
             * @param size Size of encoded data.
             */
            void decodeFrame(uint8_t *data, uint32_t size);

        private:
            // This shared memory will contain the resulting decoded image frame.
            std::shared_ptr<odcore::wrapper::SharedMemory> m_mySharedMemory;

            // This SharedImage described the resuling frame.
            odcore::data::image::SharedImage m_mySharedImage;

        private:
            // Counter for successfully decoded frames.
            uint32_t m_frameCounter;

            // Buffer to read from video file.
            uint8_t *m_readFromFileBuffer;

            // Internal buffer to handle processed and unprocessed data.
            vector<uint8_t> m_internalBuffer;

            // Handle to input file.
            FILE *m_inputFile;

            // Decoder context.
            AVCodecContext *m_decodeContext;

            // Parser for decoding.
            AVCodecParserContext *m_parser;

            // Picture will hold the decoded picture.
            AVFrame* m_picture;

            // Image pixel transformation context.
            SwsContext *m_pixelTransformationContext;

            // We return the image in BGR pixel format; thus, we need to transform the data from the decoder.
            AVFrame *m_frameBGR;
    };

} // odplayerh264

#endif /*PLAYERH264DECODER_H_*/
