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

#ifndef OPENDAVINCI_CORE_IO_STRINGOBSERVER_H_
#define OPENDAVINCI_CORE_IO_STRINGOBSERVER_H_

// platform.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"

namespace core {
    namespace io {

class StringListener;

        /**
         * This class provides an interface for registering
         * as a string listener at a string observer.
         */
        class OPENDAVINCI_API StringObserver {
            public:
                virtual ~StringObserver();

                /**
                 * This method sets or unsets a string listener.
                 *
                 * @param sl StringListener to be set. If set to NULL, observing is suspended.
                 */
                virtual void setStringListener(StringListener *sl) = 0;
        };

    }
} // core::io

#endif /*OPENDAVINCI_CORE_IO_STRINGOBSERVER_H_*/
