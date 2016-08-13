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

#include "UDPReceiveBytes.h"
#include <string>
#include "opendavinci/odcore/base/Lock.h"


namespace automotive {

    UDPReceiveBytes::UDPReceiveBytes(odcore::io::protocol::PCAPProtocol& pcap):
    m_pcap(pcap),
    buffer(""),
    wtb(){}
    
    UDPReceiveBytes::~UDPReceiveBytes(){}

    void UDPReceiveBytes::nextString(const std::string &s) {
        odcore::base::Lock l(wtb);
        buffer+=s;
    }
    
    std::string UDPReceiveBytes::getBuffer(){
        return buffer;
    }
    
    void UDPReceiveBytes::consume(int i){
        odcore::base::Lock l(wtb);
        buffer.erase(0,i);
    }
}
