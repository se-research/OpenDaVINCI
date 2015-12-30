/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2014 - 2015 Christian Berger
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

#ifndef OPENDAVINCI_TOOLS_RECORDER_SHAREDDATAWRITER_H_
#define OPENDAVINCI_TOOLS_RECORDER_SHAREDDATAWRITER_H_

#include <iosfwd>
#include <map>

// platform.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/platform.h"
#include "core/SharedPointer.h"
#include "core/base/Service.h"

namespace core { namespace base { class FIFOQueue; } }

namespace tools {

    namespace recorder {

        using namespace std;

        /**
         * This class writes the FIFO of MemorySegments to an outstream.
         */
        class SharedDataWriter : public core::base::Service {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                SharedDataWriter(const SharedDataWriter &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                SharedDataWriter& operator=(const SharedDataWriter &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param out Output stream to write to.
                 */
                SharedDataWriter(core::SharedPointer<ostream> out, map<uint32_t, char*> &mapOfMemories, core::base::FIFOQueue &bufferIn, core::base::FIFOQueue &bufferOut);

                virtual ~SharedDataWriter();

                void recordEntries();

            private:
                virtual void beforeStop();

                virtual void run();

            private:
                core::SharedPointer<ostream> m_out;

                map<uint32_t, char*> &m_mapOfMemories;

                core::base::FIFOQueue &m_bufferIn;
                core::base::FIFOQueue &m_bufferOut;
        };

    } // recorder
} // tools

#endif /*OPENDAVINCI_TOOLS_RECORDER_SHAREDDATAWRITER_H_*/
