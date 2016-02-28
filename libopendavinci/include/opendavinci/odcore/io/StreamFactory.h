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

#ifndef OPENDAVINCI_CORE_IO_STREAMFACTORY_H_
#define OPENDAVINCI_CORE_IO_STREAMFACTORY_H_

#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/io/URL.h"

namespace odcore {
    namespace io {

        using namespace std;

        /**
         * This class provides input and output streams.
         */
        class OPENDAVINCI_API StreamFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                StreamFactory(const StreamFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                StreamFactory& operator=(const StreamFactory &);

            private:
                StreamFactory();

            public:
                virtual ~StreamFactory();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @return Instance of this factory.
                 */
                static StreamFactory& getInstance();

                /**
                 * This method returns a new input stream based on a given URL.
                 *
                 * @param url URL for the input stream
                 * @return input stream based on the given URL.
                 * @throws InvalidArgumentException in case of an invalid URL.
                 */
                std::shared_ptr<istream> getInputStream(const URL &url) throw (odcore::exceptions::InvalidArgumentException);

                /**
                 * This method returns a new output stream based on a given URL.
                 *
                 * @param url URL for the output stream
                 * @return output stream based on the given URL.
                 * @throws InvalidArgumentException in case of an invalid URL.
                 */
                std::shared_ptr<ostream> getOutputStream(const URL &url) throw (odcore::exceptions::InvalidArgumentException);

            private:
                static base::Mutex m_singletonMutex;
                static StreamFactory* m_singleton;

                vector<std::shared_ptr<istream> > m_listOfInputStreams;
                vector<std::shared_ptr<ostream> > m_listOfOutputStreams;
        };

    }
} // odcore::io

#endif /*OPENDAVINCI_CORE_IO_STREAMFACTORY_H_*/
