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

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/Service.h"

namespace odcore { namespace base { class FIFOQueue; } }

namespace odtools {

    namespace recorder {

        using namespace std;

        /**
         * This class writes the FIFO of MemorySegments to an outstream.
         */
        class SharedDataWriter : public odcore::base::Service {
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
                SharedDataWriter(odcore::SharedPointer<ostream> out, map<uint32_t, char*> &mapOfMemories, odcore::base::FIFOQueue &bufferIn, odcore::base::FIFOQueue &bufferOut);

                virtual ~SharedDataWriter();

                void recordEntries();

            private:
                virtual void beforeStop();

                virtual void run();

            private:
                odcore::SharedPointer<ostream> m_out;

                map<uint32_t, char*> &m_mapOfMemories;

                odcore::base::FIFOQueue &m_bufferIn;
                odcore::base::FIFOQueue &m_bufferOut;
        };

    } // recorder
} // tools

#endif /*OPENDAVINCI_TOOLS_RECORDER_SHAREDDATAWRITER_H_*/
