#include <limits>
#include <cmath>
#include <iostream>
#include <bitset>
#include <algorithm> // for std::rotate and std::transform

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
            
            // ROLL PAYLOAD FOR VECTOR NUMBERING. NEEDS TO BE TESTED FOR NON-VECTOR
            if(m_vectorByteOrder) {
                vector<uint8_t> temp;
                for(int8_t i=length-1;i>=0;--i) {
                    temp.push_back(m_payload.at(i));
                }
                m_payload=temp;
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
        
        uint8_t CANMessage::getPayloadByte(const int8_t index) {
            if(index<0 || index>8)
                return 0x00;
            else
                return m_payload.at(index);
        }
        
        int8_t CANMessage::getRealStartBit(const CANSignal signal) {
            // if the case is "Motorola Forward MSB" the real lsb position needs to be computed
            if(m_vectorByteOrder && signal.m_endianness.compare("big")==0) {
                int8_t position=signal.m_startBit%8;
                uint8_t byte=signal.m_startBit/8;
                for(uint8_t i=0;i<signal.m_length;++i) {
                    --position;
                    if(position<0) {
                        position=8;
                        ++byte;
                    }
                }
                return (byte*8+position);
            }
            else // if the case is "Intel Standard" the lsb position is already in the startBit value
                return signal.m_startBit;
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

        int64_t CANMessage::extractRawSignal(const CANSignal signal) {
            // useful resource: www.race-technology.com/wiki/index.php/CANInterface/ByteOrdering 
            // so far cases of interest are "Intel Standard" and "Motorola Forward MSB"
            
            int64_t signalValue=0x00;
            uint64_t signalMask=0x01;
            uint8_t byteMask=0x01;
            bool MSBEquals1=false;
            int8_t realStartBit=getRealStartBit(signal);
            int8_t byteNumber=realStartBit/8;
            std::cerr<<"[extract] real start bit "<<+realStartBit<<" init BN "<<+byteNumber<<" init bm "<<+byteMask<<std::endl;
            
            // initialize the payload byte mask to the signal's starting position
            for(uint8_t i=0;i<getStartBitInByteInCorrectByteOrder(realStartBit);++i) {
                advanceByteMask(byteMask);
            std::cerr<<"[extract] advance loop bm ("<<+byteMask<<")"<<std::endl;
            }
            std::cerr<<"[extract] starting bm "<<+byteMask<<std::endl;
            
            for(uint8_t i=0, currentByte=getPayloadByte(byteNumber);i<signal.m_length;++i) {
                std::cerr<<"[extract] current BN "<<+byteNumber<<" current byte "<<+currentByte<<endl;
                // if the currently checked bit equals 1, set that bit to 1
                if( (currentByte & byteMask) != 0x00) {
                    signalValue = signalValue | signalMask;
                    MSBEquals1 = true;
                    std::cerr<<"[extract] setting 1: "<<+signalValue<<std::endl;
                }
                else MSBEquals1=false;
                
                // if the mask points at the end of the current payload byte...
                if(checkByteMaskInLastPosition(byteMask)) {
                    //  ...go forward to the first bit...
                    resetByteMask(byteMask);
                    std::cerr<<"[extract] bm reset to "<<+byteMask<<std::endl;
                    // ...of the next byte.
                    std::cerr<<"[extract] BN advanced from "<<+byteNumber;
                    advanceByteNumberInCorrectEndianness(byteNumber, signal.m_endianness);
                    std::cerr<<" to "<<+byteNumber<<std::endl;
                    
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
                    std::cerr<<"[extract] advancing bm "<<+byteMask<<std::endl;
                }
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
            
            // if the signal's MSB equals 1, then the number is negative 
            if(MSBEquals1) {
            // set all the other "more" significant bits to 1 to preserve the two's complement representation
                for(;signalMask>0;signalMask=signalMask<<1) {
                    signalValue=signalValue|signalMask;
                }
            }
            
            return signalValue;
        }
        
        CANSignal::CANSignal(const uint8_t startBit, const uint8_t length, const string signedness, const string endianness, const double factor, const double offset, const double rangeB, const double rangeE) : 
            m_startBit(startBit),
            m_length(length),
            m_signedness(),
            m_endianness(),
            m_factor(factor),
            m_offset(offset),
            m_rangeB(rangeB),
            m_rangeE(rangeE) { 
            // health check on signedness value, assume unsigned if unrecognized
            m_signedness="unsigned";
            string s=signedness; // signedness is const
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            if(s.compare("signed")==0)
                m_signedness="signed";
            
            // health check on endianness value, assume little endian if unrecognized
            m_endianness="little"; // same as "intel"
            string e=endianness; // endianness is const
            std::transform(e.begin(), e.end(), e.begin(), ::tolower);
            if(e.compare("big")==0 || e.compare("motorola")==0)
                m_endianness="big";
        }
    } // odcantools
} // automotive

