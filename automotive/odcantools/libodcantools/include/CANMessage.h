#ifndef CAN_MESSAGE_H_
#define CAN_MESSAGE_H_

#include <automotivedata/generated/automotive/GenericCANMessage.h>

#include <vector>

namespace automotive {
    namespace odcantools {
    
        class CANMessage : GenericCANMessage {
            
            public: 
                CANMessage();
                CANMessage(const GenericCANMessage&);
                CANMessage(const GenericCANMessage&, const bool);
                
                uint64_t getToUINT64();
                
                double getSignal(const uint8_t, const uint8_t, const string, const double, const double, const double, const double);
            
            private:
                void setFromUINT64(const uint64_t, const uint8_t);
                void advanceBitMask(uint8_t&);
                void resetBitMask(uint8_t&);
                bool checkBitMaskInLastPosition(const uint8_t);
                uint8_t getStartBitInCorrectByteOrder(const uint8_t);
                uint64_t extractRawSignal(const uint8_t, const uint8_t, const string);
            
            private: 
                vector<uint8_t> m_payload;
                bool m_vectorByteOrder;
        };
        
    }
}

#endif /* CAN_MESSAGE_H_ */

