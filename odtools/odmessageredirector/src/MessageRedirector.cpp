/**
 * MessageRedirector - Sample application to send data to a server through TCP and UDP sockets.
 * Copyright (C) 2012 - 2015 Christian Berger
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

#include <opendavinci/odcore/wrapper/MutexFactory.h>
#include <opendavinci/odcore/io/udp/UDPFactory.h>
#include <opendavinci/odcore/io/tcp/TCPFactory.h>

#include <iomanip>

#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"
#include "MessageRedirector.h"

namespace messageredirector {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::wrapper;
    
    MessageRedirector::MessageRedirector(const int32_t &argc, char **argv) :
        DataTriggeredConferenceClientModule(argc, argv,"MessageRedirector"),
        m_containerHandlerMutex(),
        m_receiverIPAddr(),
        m_receiverTCPPort(),
        m_receiverUDPPort(),
        m_UDPSender(),
        m_TCPConnection(),
        m_TCPConnCreated(false),
        m_count(0)
    {}

    MessageRedirector::~MessageRedirector() {}
    
    void MessageRedirector::setUp() {
        m_receiverIPAddr = getKeyValueConfiguration().getValue<string>("messageredirector.ipaddress");
        m_receiverTCPPort = getKeyValueConfiguration().getValue<uint32_t>("messageredirector.tcpport");
        m_receiverUDPPort = getKeyValueConfiguration().getValue<uint32_t>("messageredirector.udpport");
        
        m_containerHandlerMutex = unique_ptr<odcore::wrapper::Mutex>(MutexFactory::createMutex());
        
        try {
            m_UDPSender = std::shared_ptr<UDPSender>(UDPFactory::createUDPSender(m_receiverIPAddr, m_receiverUDPPort));
            cout << "UDP Client successfully created  ["<<m_receiverIPAddr<<":"<<m_receiverUDPPort<<"]" << endl ;
        } catch(string &exception) {
            cerr << "Error creating UDPSender ["<<m_receiverIPAddr<<":"<<m_receiverUDPPort<<"] = " << exception << endl;
        }
        
        try {
            m_TCPConnection = std::shared_ptr<TCPConnection>(TCPFactory::createTCPConnectionTo(m_receiverIPAddr, m_receiverTCPPort));
            cout << "TCP Client successfully created  ["<<m_receiverIPAddr<<":"<<m_receiverTCPPort<<"]" << endl ;
            m_TCPConnCreated = true;
        } catch(string &exception) {
            cerr << "Error creating TCPConnection ["<<m_receiverIPAddr<<":"<<m_receiverTCPPort<<"] = " << exception << endl;
            m_TCPConnCreated = false;
        }
    }
    
    void MessageRedirector::tearDown() {}
    
    void MessageRedirector::nextContainer(Container &c) {
        if (c.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
            stringstream msgUDP, msgTCP;
            m_containerHandlerMutex -> lock();
            
//            msgUDP<<"UDP test #"<<m_count<<"\r\n";
            msgUDP<<c;
            cout<<"Payload: ";
            for (uint64_t i = 0; i<msgUDP.str().size(); ++i)
                cout << hex << setfill('0') << setw(2) << +msgUDP.str().c_str()[i] << dec << " ";
            cout<<endl;
            try {
//                m_UDPSender->send(msgUDP.str());
//                cout << msgUDP.str() << endl;
                m_UDPSender->send(msgUDP.str());
                cout << msgUDP.str() << endl;
            } catch(string &exception) {
                cerr << "Data could not be sent: " << exception << endl;
            }
            
            if(m_TCPConnCreated)
            {
                msgTCP<<"TCP test #"<<m_count<<"\r\n";
                try {
                    m_TCPConnection->send(msgTCP.str());
                    cout << msgTCP.str() << endl;
                } catch(string &exception) {
                    cerr << "Data could not be sent: " << exception << endl;
                }
            }
            ++m_count;
            m_containerHandlerMutex->unlock();
        }
    }
} // messageredirector
