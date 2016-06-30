#include "UDPReceiveBytes.h"
//#include <iostream>
#include <string>


namespace automotive {

    UDPReceiveBytes::UDPReceiveBytes(odcore::io::protocol::PCAPProtocol& pcap):
    m_pcap(pcap),
    buffer(""),
    wtb(){}
    
    UDPReceiveBytes::~UDPReceiveBytes(){}

    void UDPReceiveBytes::nextString(const std::string &s) {
        //std::cout<<"Receive 4000 bytes"<<std::endl;
        m_pcap.nextString(s);
        /*wtb.lock();
        buffer+=s;
        wtb.unlock();*/
    }
    
    std::string UDPReceiveBytes::getBuffer(){
        return buffer;
    }
    
    void UDPReceiveBytes::clearBuffer(){
        buffer.clear();
    }
}
