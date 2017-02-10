#include <limits>
#include <cmath>
#include <iostream>

#include "CANMessage.h"

namespace automotive {
    namespace odcantools {
    
        CANMessage::CANMessage():
            GenericCANMessage(),
            m_signals(),
            m_payload(),
            m_vectorByteOrder(false) { }
    
        CANMessage::CANMessage(const GenericCANMessage& gcm):
            GenericCANMessage(gcm),
            m_signals(),
            m_payload(),
            m_vectorByteOrder(false) {
            setFromUINT64(gcm.getData(), gcm.getLength());
        }
    
        CANMessage::CANMessage(const GenericCANMessage& gcm, const bool vectorByteOrder):
            GenericCANMessage(gcm),
            m_signals(),
            m_payload(),
            m_vectorByteOrder(vectorByteOrder) {
            setFromUINT64(gcm.getData(), gcm.getLength());
        }
        
        CANMessage::CANMessage(const GenericCANMessage& gcm, const string vectorByteOrder):
            GenericCANMessage(gcm),
            m_signals(),
            m_payload(),
            m_vectorByteOrder() {
            if(vectorByteOrder.compare("vector")==0 || vectorByteOrder.compare("inverted")==0)
                m_vectorByteOrder=true;
            
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
        
        uint64_t CANMessage::getToUINT64() {
            uint64_t data=0;
            
            for(int8_t i=m_payload.size()-1;i>=0;--i) {
                data=data<<8;
                data = data | m_payload.at(i);
            }
            
            return data;
        }
        
        bool CANMessage::addSignal(const uint16_t key, const CANSignal signal) {
            std::pair<std::map<const uint16_t, const CANSignal>::iterator,bool> result;
            result = m_signals.insert ( std::pair<const uint16_t, const CANSignal>(key, signal) );
            return result.second;
        }
        
        void CANMessage::advanceByteMask(uint8_t& byteMask) {
            // if the message is coded using the inverted vector byte order, move the mask to the left
            if(m_vectorByteOrder) {
                byteMask=byteMask<<1;
            }
            else { // otherwise move the mask to the right
                byteMask=byteMask>>1;
            }
        }

        void CANMessage::resetByteMask(uint8_t& byteMask) {
            // if the message is coded using the inverted vector byte order, move the mask to the extreme right
            if(m_vectorByteOrder) {
                byteMask=0x01;
            }
            else { // otherwise move the mask to the extreme left
                byteMask=0x80;
            }
        }

        void CANMessage::advanceByteNumberInCorrectEndianness(int8_t& byteNumber, const string endianness) {
            // if the signal is little endian, increase the byte number
            if(endianness.compare("little")==0) {
                ++byteNumber;
            }
            else { // otherwise decrease it
                --byteNumber;
            }
        }
        
        bool CANMessage::checkByteMaskInLastPosition(const uint8_t byteMask) {
            if(m_vectorByteOrder && byteMask==0x80) {
                return true;
            }
            else if(!m_vectorByteOrder && byteMask==0x01) {
                return true;
            }
            else return false;
        }

        uint8_t CANMessage::getStartBitInByteInCorrectByteOrder(const uint8_t startBit) {
            if(m_vectorByteOrder) {
                return startBit%8;
            }
            else {
                return 7-(startBit%8);
            }
        }

        void CANMessage::encodeSignal(const uint16_t key, double value) {
            std::map<const uint16_t, const CANSignal>::iterator it;
            it=m_signals.find(key);
            if(it != m_signals.end())
                encodeSignal(it->second, value);
        }
        
        void CANMessage::encodeSignal(const CANSignal signal, double value) {
            if(value<signal.m_rangeB)
                value=signal.m_rangeB;
            else if(value>signal.m_rangeE)
                value=signal.m_rangeE;
            
            value=round((value-signal.m_offset)/signal.m_factor);
            uint64_t signalValue=static_cast<uint64_t>(value);
            insertRawSignal(signal, signalValue);
        }
        
        void CANMessage::insertRawSignal(const CANSignal signal, const uint64_t value) {
            uint64_t signalMask=0x01;
            uint8_t byteMask=0x01;
            int8_t byteNumber=signal.m_startBit/8;
            
            // initialize the payload byte mask to the signal's starting position
            for(uint8_t i=0;i<getStartBitInByteInCorrectByteOrder(signal.m_startBit);++i) {
                advanceByteMask(byteMask);
            }
            
            for(uint8_t i=0;i<signal.m_length;++i) {
                // if the currently checked bit equals 1, set that bit to 1
                if( (value & signalMask) != 0x00) {
                    m_payload.at(byteNumber) = m_payload.at(byteNumber) | byteMask;
                }
                
                // if the mask points at the end of the current payload byte...
                if(checkByteMaskInLastPosition(byteMask)) {
                    //  ...go forward to the first bit...
                    resetByteMask(byteMask);
                    // ...of the next byte.
                    advanceByteNumberInCorrectEndianness(byteNumber, signal.m_endianness);
                    
                    // if the index is out-of-boundaries, stop
                    if(byteNumber<0 || byteNumber>8) {
                        return;
                    }
                }
                else { // same byte, next bit
                    advanceByteMask(byteMask);
                }
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
        }
        
        double CANMessage::decodeSignal(const uint16_t key) {
            std::map<const uint16_t, const CANSignal>::iterator it;
            it=m_signals.find(key);
            if(it != m_signals.end())
                return decodeSignal(it->second);
            else return numeric_limits<double>::lowest();
        }
        
        double CANMessage::decodeSignal(const CANSignal signal) {
            double signalValue=static_cast<double>(extractRawSignal(signal));
            std::cerr<<"[decode] "<<signalValue<<std::endl;
            signalValue=(signalValue*signal.m_factor)+signal.m_offset;
            
            if(signalValue<signal.m_rangeB)
                signalValue=signal.m_rangeB;
            else if(signalValue>signal.m_rangeE)
                signalValue=signal.m_rangeE;
            
            return signalValue;
        }

        uint64_t CANMessage::extractRawSignal(const CANSignal signal) {
            // useful resource: http://wuchenxu.com/2015/12/03/CAN-byte-order/Intel_Motorola_format_in_CANoe.png
            
            uint64_t signalValue=0x00, signalMask=0x01;
            uint8_t byteMask=0x01;
            int8_t byteNumber=signal.m_startBit/8;
            
            // initialize the payload byte mask to the signal's starting position
            for(uint8_t i=0;i<getStartBitInByteInCorrectByteOrder(signal.m_startBit);++i) {
                advanceByteMask(byteMask);
            }
            std::cerr<<"[extract] bm "<<byteMask<<std::endl;
            
            for(uint8_t i=0, currentByte=m_payload.at(byteNumber);i<signal.m_length;++i) {
                // if the currently checked bit equals 1, set that bit to 1
                if( (currentByte & byteMask) != 0x00) {
                    signalValue = signalValue | signalMask;
                    std::cerr<<"[extract] setting 1 "<<std::endl;
                }
                
                // if the mask points at the end of the current payload byte...
                if(checkByteMaskInLastPosition(byteMask)) {
                    //  ...go forward to the first bit...
                    resetByteMask(byteMask);
                    // ...of the next byte.
                    advanceByteNumberInCorrectEndianness(byteNumber, signal.m_endianness);
                    
                    // check for out-of-boundaries index
                    if(byteNumber>=0 && byteNumber<=8) {
                        currentByte=m_payload.at(byteNumber);
                    }
                    else { // if out-of-boundaries (it can happen on purpose), consider a zero-filled byte
                        currentByte=0x00;
                    }
                }
                else { // same byte, next bit
                    advanceByteMask(byteMask);
                    std::cerr<<"[extract] advancing bm"<<std::endl;
                }
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
            return signalValue;
        }
        
        CANSignal::CANSignal(const uint8_t startBit, const uint8_t length, const string signedness, const string endianness, const double factor, const double offset, const double rangeB, const double rangeE) : 
                m_startBit(startBit),
                m_length(length),
                m_signedness(signedness),
                m_endianness(endianness),
                m_factor(factor),
                m_offset(offset),
                m_rangeB(rangeB),
                m_rangeE(rangeE) { }
    } // odcantools
} // automotive

