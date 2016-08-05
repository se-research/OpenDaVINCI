/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_SERIALIZATION_SERIALIZER_H_
#define OPENDAVINCI_CORE_SERIALIZATION_SERIALIZER_H_

#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Serializable.h"

namespace odcore {
    namespace seriaization {

        using namespace std;

        /**
         * This class is the interface for any serializer.
         *
         * @See Serializable
         */
        class OPENDAVINCI_API Serializer {
            public:
                Serializer();

                virtual ~Serializer();

                /**
                 * This method returns the data in serialized format.
                 *
                 * @param o ostream object (for instance a stringstream) to serialize the data into.
                 */
                virtual void getSerializedData(ostream &o) = 0;

            public:
                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const Serializable &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const bool &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const char &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const unsigned char &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const int8_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const int16_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const uint16_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const int32_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const uint32_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const int64_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const uint64_t &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const float &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const double &v) = 0;

                /**
                 * This method serializes the given value using raw encoding for
                 * values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param v Value to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const string &v) = 0;

                /**
                 * This method serializes undefined data of length size using
                 * the raw encoding for values of this Serializer implementation.
                 *
                 * @param o Stream to be used for serialization.
                 * @param data Data to be serialized.
                 * @param size Length of the data to be serialized.
                 * @return Number of bytes written for serialization.
                 */
                virtual uint32_t writeValue(ostream &o, const void *data, const uint32_t &size) = 0;

            public:
                /**
                 * This method serializes a Serializable.
                 *
                 * @param id Identifier for the s to be serialized.
                 * @param s Serializable to be serialized.
                 */
                virtual void write(const uint32_t &id, const Serializable &s) = 0;

                /**
                 * This method serializes a bool.
                 *
                 * @param id Identifier for the b to be serialized.
                 * @param b Bool to be serialized.
                 */
                virtual void write(const uint32_t &id, const bool &b) = 0;

                /**
                 * This method serializes a char.
                 *
                 * @param id Identifier for the c to be serialized.
                 * @param c Char to be serialized.
                 */
                virtual void write(const uint32_t &id, const char &c) = 0;

                /**
                 * This method serializes an unsigned char.
                 *
                 * @param id Identifier for the uc to be serialized.
                 * @param uc Unsigned char to be serialized.
                 */
                virtual void write(const uint32_t &id, const unsigned char &uc) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the i to be serialized.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const int8_t &i) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the i to be serialized.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const int16_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the ui to be serialized.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const uint16_t &ui) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the i to be serialized.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const int32_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the ui to be serialized.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const uint32_t &ui) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the i to be serialized.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const int64_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the ui to be serialized.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const uint64_t &ui) = 0;

                /**
                 * This method serializes a float.
                 *
                 * @param id Identifier for the f to be serialized.
                 * @param f Float to be serialized.
                 */
                virtual void write(const uint32_t &id, const float &f) = 0;

                /**
                 * This method serializes a double.
                 *
                 * @param id Identifier for the d to be serialized.
                 * @param d Double to be serialized.
                 */
                virtual void write(const uint32_t &id, const double &d) = 0;

                /**
                 * This method serializes a string.
                 *
                 * @param id Identifier for the s to be serialized.
                 * @param s String to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &s) = 0;

                /**
                 * This method serializes undefined data of length size.
                 *
                 * @param id Identifier for the data to be serialized.
                 * @param data Data to be serialized.
                 * @param size Length of the data to be serialized.
                 */
                virtual void write(const uint32_t &id, const void *data, const uint32_t &size) = 0;

            public:
                /**
                 * This method serializes a Serializable.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param s Serializable to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const Serializable &s) = 0;

                /**
                 * This method serializes a bool.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param b Bool to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const bool &b) = 0;

                /**
                 * This method serializes a char.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param c Char to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const char &c) = 0;

                /**
                 * This method serializes an unsigned char.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param uc Unsigned char to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const unsigned char &uc) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int8_t &i) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int16_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint16_t &ui) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int32_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint32_t &ui) = 0;

                /**
                 * This method serializes an int.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param i Int to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const int64_t &i) = 0;

                /**
                 * This method serializes an uint32_t.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param ui Unsigned int32_t to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const uint64_t &ui) = 0;

                /**
                 * This method serializes a float.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param f Float to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const float &f) = 0;

                /**
                 * This method serializes a double.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param d Double to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const double &d) = 0;

                /**
                 * This method serializes a string.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param s String to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const string &s) = 0;

                /**
                 * This method serializes undefined data of length size.
                 *
                 * @param id Identifier for the value to be serialized.
                 * @param longName Long string name of the field.
                 * @param shortName Short string name of the field.
                 * @param data Data to be serialized.
                 * @param size Length of the data to be serialized.
                 */
                virtual void write(const uint32_t &id, const string &longName, const string &shortName, const void *data, const uint32_t &size) = 0;

            public:
                /**
                 * This method converts a float from
                 * host byte order to network byte order.
                 *
                 * @param f float to be converted.
                 * @return f in NBO.
                 */
                static float htonf(float f);

                /**
                 * This method converts a double from
                 * host byte order to network byte order.
                 *
                 * @param d double to be converted.
                 * @return d in NBO.
                 */
                static double htond(double d);

                /**
                 * This method converts a uint64_t from
                 * host byte order to network byte order.
                 *
                 * @param ui uint64_t to be converted.
                 * @return ui in NBO.
                 */
                static uint64_t __htonll(uint64_t ui);

                /**
                 * This method converts an int64_t from
                 * host byte order to network byte order.
                 *
                 * @param i int64_t to be converted.
                 * @return i in NBO.
                 */
                static int64_t __htonll(int64_t i);
        };

    }
} // odcore::base

#endif /*OPENDAVINCI_CORE_SERIALIZATION_SERIALIZER_H_*/
