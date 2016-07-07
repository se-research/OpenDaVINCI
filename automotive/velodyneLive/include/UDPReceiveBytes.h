/**
 * velodyneListener is used to 
 *              decode Velodyne data realized
 *              with OpenDaVINCI
 * Copyright (C) 2016 Christian Berger and Hang Yin
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

#ifndef UDPRECEIVEBYTES_H_
#define UDPRECEIVEBYTES_H_

#include <opendavinci/odcore/io/StringListener.h>
#include "opendavinci/odcore/io/protocol/PCAPProtocol.h"
#include <mutex>

namespace automotive {
    // This class will handle the bytes received via a UDP socket.
    class UDPReceiveBytes : public odcore::io::StringListener {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            UDPReceiveBytes(const UDPReceiveBytes&);
            
            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            UDPReceiveBytes& operator=(const UDPReceiveBytes&);

        public:
            UDPReceiveBytes(odcore::io::protocol::PCAPProtocol&);
            virtual ~UDPReceiveBytes();
            virtual void nextString(const std::string &s);
            std::string getBuffer();
            void consume(int);
        private:
            odcore::io::protocol::PCAPProtocol& m_pcap;
            std::string buffer;
            std::mutex wtb;
    };
}
#endif /*UDPRECEIVEBYTES_H_*/
