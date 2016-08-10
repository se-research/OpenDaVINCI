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

#include <map>
#include <memory>
#include <string>

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odtools/recorder/Recorder.h"
#include "opendavinci/odtools/recorder/RecorderDelegate.h"

#include "RecorderH264Encoder.h"
#include "RecorderH264ChildHandler.h"

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
             * @param lossless If set to true, the video encoded is conducted in a lossless way.
             * @param basePort Base port to be used for letting the child processes communicate with the parent process.
             */
            RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData, const bool &lossless, const uint32_t &basePort);

            virtual ~RecorderH264();

            virtual odcore::data::Container process(odcore::data::Container &c);

        private:
            string m_filenameBase;
            bool m_lossless;
            uint32_t m_basePort;

            odcore::base::Mutex m_mapOfEncodersMutex;
            map<string, shared_ptr<RecorderH264ChildHandler> > m_mapOfEncoders;
    };

} // odrecorderh264

#endif /*RECORDERH264*/
