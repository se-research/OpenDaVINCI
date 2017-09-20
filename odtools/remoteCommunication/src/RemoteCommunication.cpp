/**
 * RemoteCommunication - Sample application to send data to a server through TCP and UDP sockets.
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



#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/wrapper/Mutex.h"
#include "opendavinci/odcore/wrapper/MutexFactory.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistics.h"

#include "RemoteCommunication.h"
namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::wrapper;
        using namespace odcore::data::dmcp;
        
        RemoteCommunication::RemoteCommunication(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv,"RemoteCommunication"),
        m_clientUDP(),
        m_clientTCP(),
        m_server_addr(),
        m_sentMessage(),
        m_containerHandlerMutex()
        {}

        RemoteCommunication::~RemoteCommunication() {
        }
        void RemoteCommunication::nextContainer(Container &c) {
            if (c.getDataType() == odcore::data::dmcp::ModuleStatistics::ID()) {
                m_containerHandlerMutex -> lock();
                stringstream ss;
                ss << c;
                m_sentMessage = ss.str();
                m_containerHandlerMutex ->unlock();
            }
        }
        void RemoteCommunication::handleIP(string const &ipAddress,int const &portNum) {
            char const* ip = ipAddress.c_str();
            m_server_addr.sin_family = AF_INET;
            
            m_server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");//fix this
            inet_pton(AF_INET, ip, &m_server_addr.sin_addr);
            
            m_server_addr.sin_port =htons(portNum);
        }
        void RemoteCommunication::connectSockets(){
            m_clientTCP=socket(AF_INET,SOCK_STREAM,0);
            connect(m_clientTCP,(struct sockaddr *)&m_server_addr,sizeof(m_server_addr));

            m_clientUDP = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
            connect(m_clientUDP,(struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
        }
        bool RemoteCommunication::checkTCP(int &client){
            if(client < 0){
                cout << "TCP socket couldnt create..."<< endl;
                return false;
            }
            return true;
            cout <<"TCP socket created!" << endl;
            
            // if (connect(m_clientTCP,(struct sockaddr *)&m_server_addr,sizeof(m_server_addr)) ==0){
            //     cout << "Connecting TCP.." <<endl;
            // }
        }
        bool RemoteCommunication::checkUDP(int &client){
            if (client<0){
                cout << "UDP socket coudlnt create..." << endl;
                exit(1);
                return false;
            }
            return true;
        }
        void RemoteCommunication::sendData(){
            if (!checkUDP(m_clientUDP)){
                cout << "UDP check failed"<<endl;
                exit(1);
            }
            if(!checkTCP(m_clientTCP)){
                cout << "TCP check failed"<<endl;
                exit(1);
            }
            m_containerHandlerMutex -> lock();
            sendto(m_clientUDP, m_sentMessage.c_str(), m_sentMessage.length(), 0, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
            sendto(m_clientTCP, m_sentMessage.c_str(), m_sentMessage.length(), 0, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
            m_containerHandlerMutex -> unlock();
            cout << "the message :" << m_sentMessage <<endl;
            cout <<"Sent UDP"<< endl;
            cout <<"Sent TCP"<< endl;
        }
        void RemoteCommunication::setUp() {
            cout << "Setup started" << endl;
            
            m_containerHandlerMutex = unique_ptr<odcore::wrapper::Mutex>(MutexFactory::createMutex());
            KeyValueConfiguration kv = getKeyValueConfiguration();
                                
            const string ipAddress = kv.getValue<string>("remoteCommunication.ip");
            const int portNum = kv.getValue<int>("remoteCommunication.port");
            handleIP(ipAddress,portNum);
            connectSockets();

            if (!checkUDP(m_clientUDP))
                exit(1);
            if(!checkTCP(m_clientTCP))
                exit(1);


            //CLIENT TCP /////////////////////////////////////////////////// Connect TCP - 
            //-----------------------------------------------------// Connect UDP 
            // Check connections
            //Tear it down
            //

        }
        
        void RemoteCommunication::tearDown() {
            m_containerHandlerMutex -> lock();
            m_sentMessage = "-1";

            sendto(m_clientTCP, m_sentMessage.c_str(), m_sentMessage.length(), 0, (struct sockaddr *)&m_server_addr, sizeof(m_server_addr));
            m_containerHandlerMutex -> unlock();
            close(m_clientUDP);
            close(m_clientTCP);
        }

        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode RemoteCommunication::body() {
            
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                Container ms = getKeyValueDataStore().get(odcore::data::dmcp::ModuleStatistics::ID());
                nextContainer(ms);
                sendData();
            }   
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
    }
} 