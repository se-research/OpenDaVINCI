/**
 * hesperia - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef HESPERIA_SCENARIO_SCNXARCHIVEFACTORY_H_
#define HESPERIA_SCENARIO_SCNXARCHIVEFACTORY_H_

#include <map>
#include <string>

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/base/Mutex.h"
#include "opendavinci/core/exceptions/Exceptions.h"
#include "opendavinci/core/io/URL.h"
#include "opendavinci/core/strings/StringComparator.h"

#include "hesperia/scenario/SCNXArchive.h"

namespace hesperia {
    namespace scenario {

        using namespace std;

        /**
         * This class produces an instance for accessing the contents
         * as well as the parsed scenario data structure of an
         * SCNXArchive.
         */
        class OPENDAVINCI_API SCNXArchiveFactory {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                SCNXArchiveFactory(const SCNXArchiveFactory &);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                SCNXArchiveFactory& operator=(const SCNXArchiveFactory &);

            private:
                SCNXArchiveFactory();

            public:
                virtual ~SCNXArchiveFactory();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @return Instance of this factory.
                 */
                static SCNXArchiveFactory& getInstance();

                /**
                 * This method returns the SCNXArchive data structure.
                 *
                 * @param u URL describing the source of the SCNX archive file.
                 * @return SCNXArchive.
                 * @throws InvalidArgumentException if the URL could not be used to create the data structure.
                 */
                SCNXArchive& getSCNXArchive(const core::io::URL &u) throw (core::exceptions::InvalidArgumentException);

            private:
                static core::base::Mutex m_singletonMutex;
                static SCNXArchiveFactory* m_singleton;

                map<string, SCNXArchive*, core::strings::StringComparator> m_mapOfSCNXArchives;
        };

    }
} // hesperia::scenario

#endif /*HESPERIA_SCENARIO_SCNXARCHIVEFACTORY_H_*/
