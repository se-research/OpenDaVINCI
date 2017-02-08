#include "CANMessage.h"

namespace automotive {
    namespace odcantools {
    
        CANMessage::CANMessage():
            GenericCANMessage(),
            m_payload(),
            m_vectorByteOrder(true) { }
    
        CANMessage::CANMessage(const GenericCANMessage& gcm):
            GenericCANMessage(gcm),
            m_payload(),
            m_vectorByteOrder(true) {
            setFromUINT64(gcm.getData(), gcm.getLength());
        }
    
        CANMessage::CANMessage(const GenericCANMessage& gcm, const bool vectorByteOrder):
            GenericCANMessage(gcm),
            m_payload(),
            m_vectorByteOrder(vectorByteOrder) {
            setFromUINT64(gcm.getData(), gcm.getLength());
        }
    
        void CANMessage::setFromUINT64(const uint64_t payload, const uint8_t length) {
            uint64_t data=payload;
            uint8_t mask=0xFF;
            
            for(uint8_t i=0;i<length;++i) {
                m_payload.push_back(data & mask);
                data=data>>8;
            }
        }
        
        uint64_t CANMessage::getPayload() {
            uint64_t data=0;
            
            for(int8_t i=m_payload.size()-1;i>=0;--i) {
                data=data<<8;
                data = data | m_payload.at(i);
            }
            
            return data;
        }
        
        double CANMessage::getSignal(const uint8_t startBit, const uint8_t length, const string endianness, const double factor, const double offset, const double rangeB, const double rangeE) {
            double signal=static_cast<double>(extractRawSignal(startBit, length, endianness));
            signal=(signal*factor)+offset;
            
            if(signal<rangeB)
                signal=rangeB;
            else if(signal>rangeE)
                signal=rangeE;
            
            return signal;
        }

        void CANMessage::advanceBitMask(uint8_t& bitMask) {
            if(m_vectorByteOrder) {
                bitMask=bitMask<<1;
            }
            else {
                bitMask=bitMask>>1;
            }
        }

        void CANMessage::resetBitMask(uint8_t& bitMask) {
            if(m_vectorByteOrder) {
                bitMask=0x01;
            }
            else {
                bitMask=0x80;
            }
        }

        bool CANMessage::checkBitMaskInLastPosition(const uint8_t bitMask) {
            if(m_vectorByteOrder && bitMask==0x80) {
                return true;
            }
            else if(!m_vectorByteOrder && bitMask==0x01) {
                return true;
            }
            else return false;
        }

        uint64_t CANMessage::extractRawSignal(const uint8_t startBit, const uint8_t length, const string endianness) {
            // useful resource: http://wuchenxu.com/2015/12/03/CAN-byte-order/Intel_Motorola_format_in_CANoe.png
            
            uint64_t signal=0x00;
            bool littleEndian= (endianness.compare("little")==0);
            
            uint8_t bitMask=0x01, signalMask=0x01;
            int8_t byteNumber=startBit/8;
            for(uint8_t i=0;i<startBit%8;++i)
                advanceBitMask(bitMask);
            
            for(uint8_t i=0, currentByte=m_payload.at(byteNumber);i<length;++i) {
                // if the current bit==1
                if( (currentByte & bitMask) != 0x00)
                    signal = signal | signalMask;
                
                // if the mask points at the end of the current payload byte, go to the first bit of next byte
                if(checkBitMaskInLastPosition(bitMask)) {
                    resetBitMask(bitMask);
                    
                    if(littleEndian)
                        ++byteNumber;
                    else
                        --byteNumber;
                    
                    // check for out-of-boundaries signal (it can happen on purpose)
                    if(byteNumber<0 || byteNumber>8)
                        currentByte=0x00;
                }
                else // same byte, next bit
                    advanceBitMask(bitMask);
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
            
            return signal;
        }
    }
}

