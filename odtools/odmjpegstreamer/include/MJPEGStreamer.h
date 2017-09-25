/**
 * odmjpegstreamer - Tool to stream a given SharedImage as HTTP encapsulated MJPEG stream
 * Copyright (C) 2017 Christian Berger
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

#ifndef MJPEGSTREAMER_H_
#define MJPEGSTREAMER_H_

#include <memory>
#include <vector>

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptor.h>
#include <opendavinci/odcore/io/tcp/TCPAcceptorListener.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>

#include "MJPEGClientHandler.h"

namespace odcore { namespace wrapper { class SharedMemory; } }

namespace odmjpegstreamer {

    using namespace std;

    /**
     * This class provides an MJPEG stream from a given SharedImage source.
     */
    class MJPEGStreamer : public odcore::base::module::DataTriggeredConferenceClientModule,
                          public odcore::io::tcp::TCPAcceptorListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            MJPEGStreamer(const MJPEGStreamer &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            MJPEGStreamer& operator=(const MJPEGStreamer &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            MJPEGStreamer(const int32_t &argc, char **argv);

            virtual ~MJPEGStreamer();

            virtual void nextContainer(odcore::data::Container &c);

            virtual void onNewConnection(std::shared_ptr<odcore::io::tcp::TCPConnection> connection);

       private:
            void parseAdditionalCommandLineParameters(const int &argc, char **argv);

            virtual void setUp();

            virtual void tearDown();

        private:
            shared_ptr<odcore::io::tcp::TCPAcceptor> m_tcpAcceptor;
            vector<shared_ptr<odcore::io::tcp::TCPConnection> > m_listOfConnections;
            vector<shared_ptr<MJPEGClientHandler> > m_listOfClientHandlers;

            uint32_t m_port;
            int32_t m_jpegQuality;
            bool m_bgr2rgb;
            string m_sharedimagename;
            void *m_buffer;
    };

} // odmjpegstreamer

#endif /*MJPEGSTREAMER_H_*/
