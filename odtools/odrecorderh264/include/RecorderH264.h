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

#include <unistd.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/base/Condition.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odtools/recorder/Recorder.h"
#include "opendavinci/odtools/recorder/RecorderDelegate.h"

#include <opendavinci/odcore/io/ConnectionListener.h>
#include <opendavinci/odcore/io/StringListener.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptorListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptor.h>

#include "RecorderH264Encoder.h"

namespace odrecorderh264 {

    using namespace std;

    class RecorderH264ChildHandler : public odtools::recorder::RecorderDelegate,
                                     public odcore::io::tcp::TCPAcceptorListener,
                                     public odcore::io::ConnectionListener,
                                     public odcore::io::StringListener {
        public:
            RecorderH264ChildHandler();
            RecorderH264ChildHandler(const uint32_t &port);
            virtual ~RecorderH264ChildHandler();
            virtual void onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection);
            virtual void nextString(const std::string &s);
            virtual void handleConnectionError();

            virtual odcore::data::Container process(odcore::data::Container &c);

            void waitForClientToConnect();

        public:
            pid_t m_childPID;

        private:
            shared_ptr<odcore::io::tcp::TCPAcceptor> m_tcpacceptor;

        public:
            shared_ptr<odcore::io::tcp::TCPConnection> m_connection;

        private:
            odcore::base::Condition m_condition;
            odcore::data::Container m_response;
    };

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
             */
            RecorderH264(const string &url, const uint32_t &memorySegmentSize, const uint32_t &numberOfSegments, const bool &threading, const bool &dumpSharedData, const bool &lossless);

            virtual ~RecorderH264();

            virtual odcore::data::Container process(odcore::data::Container &c);

            virtual odcore::data::Container processOld(odcore::data::Container &c);

        private:
            string m_filenameBase;
            bool m_lossless;
            odcore::base::Mutex m_mapOfEncodersPerSharedImageSourceMutex;
            map<string, shared_ptr<RecorderH264Encoder> > m_mapOfEncodersPerSharedImageSource;

            map<string, shared_ptr<RecorderH264ChildHandler> > m_mapOfEncoders;
    };

} // odrecorderh264

#endif /*RECORDERH264*/
