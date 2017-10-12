#ifndef MESSAGEREDIRECTOR_H_
#define MESSAGEREDIRECTOR_H_

#include <iostream>
#include <string.h>
#include <stdlib.h>

#include <opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h>
#include <opendavinci/odcore/data/Container.h>

#include <opendavinci/odcore/wrapper/Mutex.h>
#include <opendavinci/odcore/io/tcp/TCPConnection.h>
#include <opendavinci/odcore/io/udp/UDPSender.h>

namespace messageredirector {
    using namespace std;
    using namespace odcore::io::udp;
    using namespace odcore::io::tcp;
    
    class MessageRedirector : public odcore::base::module::DataTriggeredConferenceClientModule{
        private:

            MessageRedirector(const MessageRedirector &/*obj*/);

            MessageRedirector& operator=(const MessageRedirector &/*obj*/);

        public:

            MessageRedirector(const int32_t &argc, char **argv);

            virtual ~MessageRedirector();
            virtual void nextContainer(odcore::data::Container &c);
            //odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

        private:
            virtual void setUp();

            virtual void tearDown();
            
            unique_ptr<odcore::wrapper::Mutex> m_containerHandlerMutex;
            
            string m_receiverIPAddr;
            uint32_t m_receiverTCPPort;
            uint32_t m_receiverUDPPort;
            std::shared_ptr<UDPSender> m_UDPSender;
            std::shared_ptr<TCPConnection> m_TCPConnection;
            bool m_TCPConnCreated;
            uint32_t m_count;
    };

} // messageredirector

#endif /*MESSAGEREDIRECTOR_H_*/
