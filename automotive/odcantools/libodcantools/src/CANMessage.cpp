#include <limits>
#include <cmath>
#include <iostream>
#include <algorithm> // for std::rotate and std::transform

#include "CANMessage.h"

// the implemented logic is based on the resource: www.race-technology.com/wiki/index.php/CANInterface/ByteOrdering 
// implemented cases of interest are "Intel Standard" and "Motorola Forward MSB"

namespace automotive {
    namespace odcantools {
        CANMessage::CANMessage(const GenericCANMessage& gcm) :
            GenericCANMessage(gcm),
            m_payload(),
            m_signals() {
            m_payload.reserve(8);
            setFromUINT64(gcm.getData(), gcm.getLength());
        }

        CANMessage::CANMessage(const uint64_t& identifier, const uint8_t& length, const uint64_t& payload) :
            m_payload(),
            m_signals() {
            setIdentifier(identifier);
            setLength(length);
            setData(payload);
            setFromUINT64(payload, length);
        }

        CANMessage::CANMessage(const CANMessage& canmessage) :
            GenericCANMessage(canmessage),
            m_payload(canmessage.m_payload),
            m_signals(canmessage.m_signals)
            {
        }
        
        void CANMessage::setFromUINT64(const uint64_t payload, const uint8_t length) {
            // superclass methods
            setData(payload);
            setLength(length);
            
            uint64_t data=payload;
            uint8_t mask=0xFF;
            
            for(uint8_t i=0;i<length;++i) {
                m_payload.push_back(data & mask);
                data=data>>8;
            }
            
            // invert payload due to the way it is represented in log files or traces
            m_payload=invertPayloadVector(m_payload);
        }
        
        vector<uint8_t> CANMessage::invertPayloadVector(vector<uint8_t> payload) {
            vector<uint8_t> temp;
            for(int8_t i=getLength()-1;i>=0;--i) {
                temp.push_back(payload.at(i));
            }
            return temp;
        }
        
        uint64_t CANMessage::getPayloadToUINT64() {
            // invert payload due to the way it is represented in log files or traces
            vector<uint8_t> temp=m_payload;
            temp=invertPayloadVector(temp);
            
            uint64_t data=0;
            
            for(int8_t i=temp.size()-1;i>=0;--i) {
                data=data<<8;
                data = data | temp.at(i);
            }
            
            return data;
        }
        
        automotive::GenericCANMessage CANMessage::getGenericCANMessage() {
            automotive::GenericCANMessage gcm;
            
            // use superclass getters
            gcm.setIdentifier(getIdentifier());
            gcm.setLength(getLength());
            gcm.setData(getData());
            
            return gcm;
        }
        
        bool CANMessage::addSignal(const uint16_t& key, const CANSignal& signal) {
            std::pair<std::map<const uint16_t, const CANSignal>::iterator,bool> result;
            result = m_signals.insert ( std::pair<const uint16_t, const CANSignal>(key, signal) );
            return result.second;
        }
        
        void CANMessage::advanceByteMask(uint8_t& byteMask) {
            // both Intel Standard and Motorola Forward MSB number bits in a byte from the msb to the lsb (7 6 5 4 3 2 1 0)
            byteMask=byteMask<<1;
        }

        void CANMessage::resetByteMask(uint8_t& byteMask) {
            // move the mask back to the extreme right (bit 0 in a byte)
            byteMask=0x01;
        }

        void CANMessage::advanceByteNumberInCorrectEndianness(int8_t& byteNumber, const Endianness endianness) {
            // if the signal is little endian, increase the byte number
            if(endianness==Endianness::LITTLE) {
                ++byteNumber;
            }
            else { // otherwise decrease it
                --byteNumber;
            }
        }
        
        bool CANMessage::checkByteMaskInLastPosition(const uint8_t byteMask) {
            // valid for non-sequential numbering, i.e. both Intel Standard and Motorola Forward MSB
            if(byteMask==0x80) {
                return true;
            }
            return false;
        }

        uint8_t CANMessage::getStartBitInByteInCorrectByteOrder(const uint8_t startBit) {
            // valid for non-sequential numbering, i.e. both Intel Standard and Motorola Forward MSB
            return startBit%8;
        }

        void CANMessage::encodeSignal(const uint16_t& key, double& value) {
            std::map<const uint16_t, const CANSignal>::iterator it;
            it=m_signals.find(key);
            if(it != m_signals.end())
                encodeSignal(it->second, value);
        }
        
        void CANMessage::encodeSignal(const CANSignal& signal, double& value) {
            // if the range is [0,0], skip the range check
            double tolerance=1e-5;
            if(!(signal.m_rangeB-signal.m_rangeE<tolerance && signal.m_rangeB<tolerance)) {
                if(value<signal.m_rangeB)
                    value=signal.m_rangeB;
                else if(value>signal.m_rangeE)
                    value=signal.m_rangeE;
            }
            
            value=round((value-signal.m_offset)/signal.m_factor);
            int64_t signalValue=static_cast<int64_t>(value);
            insertRawSignal(signal, signalValue);
        }
        
        void CANMessage::insertRawSignal(const CANSignal signal, const int64_t value) {
            uint64_t signalMask=0x01;
            uint8_t byteMask=0x01;
            int8_t lsbPosition=getLSBPosition(signal);
            int8_t byteNumber=lsbPosition/8;
            
            // initialize the payload byte mask to the signal's starting position
            for(uint8_t i=0;i<getStartBitInByteInCorrectByteOrder(lsbPosition);++i) {
                advanceByteMask(byteMask);
            }
            uint8_t currentByte=getPayloadByte(byteNumber);
            
            for(uint8_t i=0;i<signal.m_length;++i) {
                // if the currently checked bit equals 1, set that bit to 1
                if( (value & signalMask) != 0x00) {
                    currentByte = currentByte | byteMask;
                }
                
                // if the mask points at the end of the current payload byte...
                if(checkByteMaskInLastPosition(byteMask)) {
                    // ...save the current byte, then...
                    if(byteNumber>=0 && byteNumber<getLength()) { // in case we start out of the message boundaries -it can happen on purpose-
                        m_payload.at(byteNumber)=currentByte;
                    }
                    //  ...go forward to the first bit...
                    resetByteMask(byteMask);
                    // ...of the next byte.
                    advanceByteNumberInCorrectEndianness(byteNumber, signal.m_endianness);
                    
                    // if the index is out-of-boundaries, stop and exit
                    if(byteNumber<0 || byteNumber>getLength()-1) {
                        updateGCMData();
                        return;
                    }
                    else 
                        currentByte=getPayloadByte(byteNumber);
                }
                else { // same byte, next bit
                    advanceByteMask(byteMask);
                }
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
            
            // if all went correctly, save the current byte, then exit
            if(byteNumber>=0 && byteNumber<8) { // in case we start out of the message boundaries -it should not happen here-
                m_payload.at(byteNumber)=currentByte;
            }
            updateGCMData();
        }
        
        void CANMessage::updateGCMData() {
            const uint64_t payload=getPayloadToUINT64();
            uint8_t length;
            
            // set the new payload
            setData(payload);
            // find the new payload length
            if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-1))) ) // 1 byte
                length=1;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-2))) ) // 2 bytes
                length=2;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-3))) ) // 3 bytes
                length=3;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-4))) ) // 4 bytes
                length=4;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-5))) ) // 5 bytes
                length=5;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-6))) ) // 6 bytes
                length=6;
            else if(payload <= (std::numerical_limits<uint64_t>::max()>>(8 * (8-7))) ) // 7 bytes
                length=7;
            else // (implicit) if(payload <= 0xFFFFFFFFFFFFFFFF)
                length=8;
            // if the new payload is longer than the nominal length, update it - normally it should not happen
            if(length>getLength())
                setLength(length);
        }
        
        uint8_t CANMessage::getPayloadByte(const int8_t index) {
            if(index>=0 && index<getLength())
                return m_payload.at(index);
            else
                return 0x00;
        }
        
        int8_t CANMessage::getLSBPosition(const CANSignal signal) {
            // if the case is "Motorola Forward MSB" the real lsb position needs to be computed
            if(signal.m_endianness==Endianness::BIG) {
                int8_t position=signal.m_startBit%8;
                uint8_t byte=signal.m_startBit/8;
                for(uint8_t i=1;i<signal.m_length;++i) {
                    --position;
                    if(position<0) {
                        position=7;
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
            signalValue=(signalValue*signal.m_factor)+signal.m_offset;
            
            // if the range is [0,0], skip the range check
            double tolerance=1e-5;
            if(!(signal.m_rangeB-signal.m_rangeE<tolerance && signal.m_rangeB<tolerance)) {
                if(signalValue<signal.m_rangeB)
                    signalValue=signal.m_rangeB;
                else if(signalValue>signal.m_rangeE)
                    signalValue=signal.m_rangeE;
            }
            
            return signalValue;
        }

        int64_t CANMessage::extractRawSignal(const CANSignal signal) {
            int64_t signalValue=0x00;
            uint64_t signalMask=0x01;
            uint8_t byteMask=0x01;
            bool MSBEquals1=false;
            int8_t lsbPosition=getLSBPosition(signal);
            int8_t byteNumber=lsbPosition/8;
            
            // initialize the payload byte mask to the signal's starting position
            for(uint8_t i=0;i<getStartBitInByteInCorrectByteOrder(lsbPosition);++i) {
                advanceByteMask(byteMask);
            }
            
            for(uint8_t i=0, currentByte=getPayloadByte(byteNumber);i<signal.m_length;++i) {
                // if the currently checked bit equals 1, set that bit to 1
                if( (currentByte & byteMask) != 0x00) {
                    signalValue = signalValue | signalMask;
                    MSBEquals1 = true;
                }
                else MSBEquals1=false;
                
                // if the mask points at the end of the current payload byte...
                if(checkByteMaskInLastPosition(byteMask)) {
                    //  ...go forward to the first bit...
                    resetByteMask(byteMask);
                    // ...of the next byte.
                    advanceByteNumberInCorrectEndianness(byteNumber, signal.m_endianness);
                    
                    // update the current byte
                    currentByte=getPayloadByte(byteNumber);
                }
                else { // same byte, next bit
                    advanceByteMask(byteMask);
                }
                
                // always move forward the signal mask
                signalMask=signalMask<<1;
            }
            
            // if the signal is signed and its MSB equals 1, then the number is negative 
            if(signal.m_signedness==Signedness::SIGNED && MSBEquals1) {
            // set all the other "more" significant bits to 1 to preserve the two's complement representation
                for(;signalMask>0;signalMask=signalMask<<1) {
                    signalValue=signalValue|signalMask;
                }
            }
            
            return signalValue;
        }
        
        CANSignal::CANSignal(const uint8_t& startBit, const uint8_t& length, const Signedness& signedness, const Endianness& endianness, const double& factor, const double& offset, const double& rangeB, const double& rangeE) : 
            m_startBit(startBit),
            m_length(length),
            m_signedness(signedness),
            m_endianness(endianness),
            m_factor(factor),
            m_offset(offset),
            m_rangeB(rangeB),
            m_rangeE(rangeE) { 
        }
        
        string CANSignal::toString() const {//at bit 16 for 16 bit is unsigned little endian multiply by 1 add 0 with range [0, 0]
            stringstream signal;
            signal  << "signal at bit "<<+m_startBit
                    <<" for "<<+m_length
                    <<" bit is "<<((m_signedness==Signedness::UNSIGNED)?"unsigned":"signed")
                    <<" "<<((m_endianness==Endianness::LITTLE)?"little":"big")
                    <<" endian multiply by "<<m_factor
                    <<" add "<<m_offset
                    <<" with range ["<<m_rangeB
                    <<","<<m_rangeE<<"]";
            return signal.str();
        }
    } // odcantools
} // automotive

