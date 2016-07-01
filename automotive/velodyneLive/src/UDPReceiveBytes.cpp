#include "UDPReceiveBytes.h"
#include <string>


namespace automotive {

    UDPReceiveBytes::UDPReceiveBytes(odcore::io::protocol::PCAPProtocol& pcap):
    m_pcap(pcap),
    buffer(""),
    wtb(){}
    
    UDPReceiveBytes::~UDPReceiveBytes(){}

    void UDPReceiveBytes::nextString(const std::string &s) {
        wtb.lock();
        buffer+=s;
        wtb.unlock();
    }
    
    std::string UDPReceiveBytes::getBuffer(){
        return buffer;
    }
    
    void UDPReceiveBytes::consume(int i){
        wtb.lock();
        buffer.erase(0,i);
        wtb.unlock();
    }
}
