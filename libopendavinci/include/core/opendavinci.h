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

#ifndef OPENDAVINCI_CORE_PLATFORM_H_
#define OPENDAVINCI_CORE_PLATFORM_H_

/**
 * The following defines are needed for building a dynamic library using
 * the Microsoft C++ compiler or the GNU compiler collection.
 */
#ifdef _WIN32
    // Disable warning "__declspec(nothrow)..."
    #pragma warning( disable : 4290 )
    // Disable warning "Possible loss of precision"
    #pragma warning( disable : 4244 )
    // Disable warning "DLL interface..."
    #pragma warning( disable : 4251 )
    // Disable warning "this pointer during initialization..."
    #pragma warning( disable : 4355 )
    // Disable warning "'dynamic_cast' for polymorphic type..."
    #pragma warning( disable : 4541 )
    // Disable warning "Not all control paths..."
    #pragma warning( disable : 4715 )
    // Disable warning "C++ exceptio specification ignored..."
    #pragma warning( disable : 4290 )
    // Disable warning "Missing dllimport for std::exception..."
    #pragma warning( disable : 4275 )
    // Disable warning "new behavior: elements of array will be default initialized..."
    #pragma warning( disable : 4351 )

    // Link to ws2_32.lib to get symbol "htonl and ntohl".
    #pragma comment(lib, "ws2_32.lib")

    // Define Windows 7.
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT 0x0601
    #endif
    #define WIN32_LEAN_AND_MEAN

    #ifdef OPENDAVINCI_SHARED
        #ifdef OPENDAVINCI_EXPORTS
            #define OPENDAVINCI_API __declspec(dllexport)
        #else
            #define OPENDAVINCI_API __declspec(dllimport)
        #endif
    #else
        // In the case of static linking:
        #define OPENDAVINCI_API
    #endif
#else // Not _WIN32 (i.e. LINUX or something else)
    #define OPENDAVINCI_API
#endif // _WIN32

#include "platform/PortableEndian.h"

/**************************************************************************************/

#ifndef WIN32
    #include <arpa/inet.h>  // for htonl etc
    #include <stddef.h>     // for NULL
    #include <stdint.h>     // for uint32_t etc
    #include <unistd.h>     // for unlink

    // Use regular unlink.
    #define UNLINK unlink
#elif WIN32
    // Unlink causes an error under Windows.
    #define UNLINK _unlink
    
    #include "core/platform/win/inttypes.h"
    #include <basetsd.h>
    #include <Winsock2.h>
    #include <ws2tcpip.h>
#endif

/**************************************************************************************/

// Basic header for OpenDaVINCI macros.
#include "core/opendavinci.h"

// Type convention software-wide.
namespace core {
    enum TYPE_ {
        BOOL_=0,
        INTEGERS_START,
        UINT8_T,  // same as unsigned char
        INT8_T,
        UINT16_T, // same as unsigned short
        INT16_T,  // same as short
        UINT32_T,
        INT32_T,
        UINT64_T, // same as unsigned long
        INT64_T,  // same as long
        INTEGERS_END,
        CHAR_,
        UCHAR_,
        FLOAT_,
        DOUBLE_,
        /////////////////////////
        // non-primitive types //
        /////////////////////////
        NON_PRIMITIVE_START=50,
        STRING_,
        DATA_,
        SERIALIZABLE_,
        NON_PRIMITIVE_END,
        //////////////////
        // delta values //
        //////////////////
        RESERVED_=127,
        UINT8_T_R,
        INT8_T_R,
        UINT16_T_R,
        INT16_T_R,
        UINT32_T_R,
        INT32_T_R,
        UINT64_T_R,
        INT64_T_R,
        ///////////////////
        UINT8_UINT16=150,
        UINT8_UINT16_R,
        UINT8_INT16,
        UINT8_INT16_R,
        UINT8_UINT32,
        UINT8_UINT32_R,
        UINT8_INT32,
        UINT8_INT32_R,
        UINT8_UINT64,
        UINT8_UINT64_R,
        UINT8_INT64,
        UINT8_INT64_R,
        UINT8_FLOAT,
        UINT8_FLOAT_R,
        UINT8_DOUBLE,
        UINT8_DOUBLE_R,
        ////
        INT8_INT16,
        INT8_INT16_R,
        INT8_INT32,
        INT8_INT32_R,
        INT8_INT64,
        INT8_INT64_R,
        INT8_FLOAT,
        INT8_FLOAT_R,
        INT8_DOUBLE,
        INT8_DOUBLE_R,
        ////
        UINT16_UINT32,
        UINT16_UINT32_R,
        UINT16_INT32,
        UINT16_INT32_R,
        UINT16_UINT64,
        UINT16_UINT64_R,
        UINT16_INT64,
        UINT16_INT64_R,
        UINT16_FLOAT,
        UINT16_FLOAT_R,
        UINT16_DOUBLE,
        UINT16_DOUBLE_R,
        ////
        INT16_INT32,
        INT16_INT32_R,
        INT16_INT64,
        INT16_INT64_R,
        INT16_FLOAT,
        INT16_FLOAT_R,
        INT16_DOUBLE,
        INT16_DOUBLE_R,
        ////
        UINT32_UINT64,
        UINT32_UINT64_R,
        UINT32_INT64,
        UINT32_INT64_R,
        UINT32_DOUBLE,
        UINT32_DOUBLE_R,
        ////
        INT32_INT64,
        INT32_INT64_R,
        INT32_DOUBLE,
        INT32_DOUBLE_R,
        ////
        FLOAT_DOUBLE,
        FLOAT_DOUBLE_R,
        ////
        BOOL_FALSE,
        BOOL_TRUE,
        ////
        NO_OP=255
    };
}

/* This macro eases the declaration of exceptions. */
#define OPENDAVINCI_CORE_DECLARE_EXCEPTION(ExceptionName) class OPENDAVINCI_API ExceptionName : public Exceptions { public: ExceptionName(const string &exceptionMessage, const string &fileName, const uint32_t &lineNumber) : Exceptions(exceptionMessage, fileName, lineNumber) {}; const string getExceptionName() const { return "" #ExceptionName ""; } };

/* This macro eases the usage of exceptions. */
#define OPENDAVINCI_CORE_THROW_EXCEPTION(ExceptionClass, ExceptionMessage) do { throw core::exceptions::ExceptionClass(ExceptionMessage, "", 0); } while (false)

/* This macro eases the usage of freeing a pointer. */
#define OPENDAVINCI_CORE_FREE_POINTER(ptr) do { if (ptr != NULL) { free(ptr); }; ptr = NULL; } while (false)

/* This macro eases the usage of deleting a pointer. */
#define OPENDAVINCI_CORE_DELETE_POINTER(ptr) do { if (ptr != NULL) { delete(ptr); }; ptr = NULL; } while (false)

/* This macro eases the usage of deleting an array. */
#define OPENDAVINCI_CORE_DELETE_ARRAY(ptr) do { if (ptr != NULL) { delete [] (ptr); }; ptr = NULL; } while (false)

/* This macro eases the usage of logging. */
#define CLOG if (core::base::module::AbstractCIDModule::isVerbose()) std::clog
#define CLOG1 if (core::base::module::AbstractCIDModule::getVerbosity() == 1) std::clog
#define CLOG2 if ((core::base::module::AbstractCIDModule::getVerbosity() <= 2) && (core::base::module::AbstractCIDModule::getVerbosity() >= 1)) std::clog
#define CLOG3 if ((core::base::module::AbstractCIDModule::getVerbosity() <= 3) && (core::base::module::AbstractCIDModule::getVerbosity() >= 1)) std::clog

#endif // OPENDAVINCI_CORE_PLATFORM_H_
