#ifndef UDPRECEIVEBYTES_H_
#define UDPRECEIVEBYTES_H_

#include <opendavinci/odcore/io/StringListener.h>
#include "PCAPProtocol.h"
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
