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

#include <opendavinci/odcore/base/Mutex.h>
#include <opendavinci/odcore/io/ConnectionListener.h>
#include <opendavinci/odcore/io/StringListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>
#include <opendavinci/odcore/wrapper/SharedMemory.h>
#include <opendavinci/odtools/recorder/RecorderDelegate.h>

namespace odrecorderh264 {

    using namespace std;

    /**
     * This class handles the actual video stream encoding. An instance is
     * embedded in an own process context and communicates with the
     * recorder instance via TCP to get information about the next SharedImage
     * to encode and to return the replacement H264Frame instance.
     */
    class RecorderH264Encoder : public odcore::io::ConnectionListener,
                                public odcore::io::StringListener,
                                public odtools::recorder::RecorderDelegate {
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
             * @param filenameBase Base file name of the file to write the video stream to where the actual video stream name is appended.
             * @param lossless If true, h264 is encoding the video frames in a lossless way.
             * @param port TCP port to connect to the recorder instance for communication.
             */
            RecorderH264Encoder(const string &filenameBase, const bool &lossless, const uint32_t &port);

            virtual ~RecorderH264Encoder();

            virtual odcore::data::Container process(odcore::data::Container &c);

            virtual void nextString(const std::string &s);

            virtual void handleConnectionError();

            /**
             * This method returns true as long as we have an established
             * connection to the recorder instance.
             *
             * @return true as long as this child process has a connection to the recorder.
             */
            bool hasConnection();

        private:
            /**
             * This method initializes the h.264 decoder.
             *
             * @return 0 if initialization succeeded, a value < 0 otherwise.
             */
            int initialize(const uint32_t &width, const uint32_t &height);

            /**
             * This method is cleaning up the encoding.
             */
            void stopAndCleanUpEncoding();

        private:
            shared_ptr<odcore::io::tcp::TCPConnection> m_connection;
            odcore::base::Mutex m_hasConnectionMutex;
            bool m_hasConnection;

        private:
            string m_filenameBase;
            string m_filename;
            bool m_lossless;

        private:
            odcore::base::Mutex m_isInitializedMutex;
            bool m_isInitialized;
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
