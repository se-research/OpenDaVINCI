/**
 * odrecorderh264 - Tool for recording data and encoding video streams with h264.
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

#ifndef RECORDERH264ENCODER_H_
#define RECORDERH264ENCODER_H_

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <cstdio>
#include <memory>
#include <string>

#include "opendavinci/odtools/recorder/RecorderDelegate.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace odrecorderh264 {

    using namespace std;

    /**
     * This class can be used to record data distributed in a Container conference
     * and to encode SharedImage containers as h264 video streams.
     */
    class RecorderH264Encoder : public odtools::recorder::RecorderDelegate {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecorderH264Encoder(const RecorderH264Encoder &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecorderH264Encoder& operator=(const RecorderH264Encoder &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param filename Name of the file to write the video stream to.
             */
            RecorderH264Encoder(const string &filename, const bool &lossless);

            virtual ~RecorderH264Encoder();

            virtual odcore::data::Container process(odcore::data::Container &c);

        private:
            /**
             * This method initializes the h.264 decoder.
             *
             * @return 0 if initialization succeeded, a value < 0 otherwise.
             */
            int initialize(const uint32_t &width, const uint32_t &height);

        private:
            string m_filename;
            bool m_lossless;

        private:
            bool m_hasAttachedToSharedImageMemory;
            std::shared_ptr<odcore::wrapper::SharedMemory> m_sharedImageMemory;

            uint32_t m_frameCounter;

            AVCodec *m_encodeCodec;
            AVCodecContext *m_encodeContext;
            SwsContext *m_pixelTransformationContext;
            FILE *m_outputFile;
            AVFrame *m_frame;
    };

} // odrecorderh264

#endif /*RECORDERH264ENCODER_H_*/
