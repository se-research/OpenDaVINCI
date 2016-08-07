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

#ifndef RECORDERH264_H_
#define RECORDERH264_H_

// Include files from FFMPEG to have h264 encoding.
extern "C" {
    #include <libavcodec/avcodec.h>
    #include <libavutil/imgutils.h>
    #include <libswscale/swscale.h>
}

#include <cstdio>
#include <memory>
#include <string>

#include "opendavinci/odtools/recorder/Recorder.h"
#include "opendavinci/odtools/recorder/RecorderDelegate.h"
#include "opendavinci/odcore/wrapper/SharedMemory.h"

namespace odrecorderh264 {

    using namespace std;

    /**
     * This class can be used to record data distributed in a Container conference
     * and to encode SharedImage containers as h264 video streams.
     */
    class RecorderH264 : public odtools::recorder::Recorder,
                         public odtools::recorder::RecorderDelegate {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            RecorderH264(const RecorderH264 &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            RecorderH264& operator=(const RecorderH264 &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param url URL of the resource to be used for writing containers to.
             * @param memorySegmentSize Size of a memory segment for storing shared memory data (like shared images).
             * @param numberOfSegments Number of segments to be used.
             * @param threading If true recorder is using a background thread to dump shared memory data.
             *                  If set to true recorder can be used in real-time required scenarios where
             *                  it is embedded in user supplied apps; however, there is a risk that if the
             *                  queue size (numberOfSegments) is chosen too small or the low-level disk I/O
             *                  containers of type SharedImage or SharedMemory are dropped.
             * @param dumpSharedData If true, shared images and shared data will be stored as well.
             */
            RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData);

            virtual ~RecorderH264();

            virtual odcore::data::Container process(odcore::data::Container &c);

        private:
            /**
             * This method initializes the h.264 decoder.
             *
             * @return 0 if initialization succeeded, a value < 0 otherwise.
             */
            int initialize(const uint32_t &width, const uint32_t &height, const string &filename, const bool &lossless);

        private:
            // TODO: Add management for different SharedImage sources.

        private:
            bool m_hasAttachedToSharedImageMemory;
            std::shared_ptr<odcore::wrapper::SharedMemory> m_sharedImageMemory;

        private:
            uint32_t m_frameCounter;

            AVCodec *m_encodeCodec;
            AVCodecContext *m_encodeContext;
            SwsContext *m_pixelTransformationContext;
            FILE *m_outputFile;
            AVFrame *m_frame;
    };

} // odrecorderh264

#endif /*RECORDERH264*/
