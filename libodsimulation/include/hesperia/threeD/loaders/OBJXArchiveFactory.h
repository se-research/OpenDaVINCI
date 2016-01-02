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

#ifndef HESPERIA_CORE_THREED_LOADERS_OBJXARCHIVEFACTORY_H_
#define HESPERIA_CORE_THREED_LOADERS_OBJXARCHIVEFACTORY_H_

#include <iostream>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/opendavinci.h"
#include "core/base/Mutex.h"
#include "core/exceptions/Exceptions.h"

#include "hesperia/threeD/loaders/OBJXArchive.h"

namespace hesperia {
    namespace threeD {
        namespace loaders {

            using namespace std;

            /**
             * This class produces an instance for accessing the contents
             * of an OBJXArchive (.objx) from a given input stream.
             */
            class OPENDAVINCI_API OBJXArchiveFactory {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OBJXArchiveFactory(const OBJXArchiveFactory &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OBJXArchiveFactory& operator=(const OBJXArchiveFactory &);

                private:
                    OBJXArchiveFactory();

                public:
                    virtual ~OBJXArchiveFactory();

                    /**
                     * This method returns a static instance for this factory.
                     *
                     * @return Instance of this factory.
                     */
                    static OBJXArchiveFactory& getInstance();

                    /**
                     * This method returns the OBJXArchive data structure for a simple obj file without material and textures.
                     *
                     * @param in Input stream containing a plain obj file.
                     * @return OBJXArchive.
                     * @throws InvalidArgumentException if the URL could not be used to create the data structure.
                     */
                    OBJXArchive* getOBJXArchiveFromPlainOBJFile(istream &in) throw (core::exceptions::InvalidArgumentException);

                    /**
                     * This method returns the OBJXArchive data structure.
                     *
                     * @param in Input stream to be used for building the OBJX archive file.
                     * @return OBJXArchive.
                     * @throws InvalidArgumentException if the URL could not be used to create the data structure.
                     */
                    OBJXArchive* getOBJXArchive(istream &in) throw (core::exceptions::InvalidArgumentException);

                private:
                    static core::base::Mutex m_singletonMutex;
                    static OBJXArchiveFactory* m_singleton;
            };

        }
    }
} // hesperia::threeD::loaders

#endif /*HESPERIA_CORE_THREED_LOADERS_OBJXARCHIVEFACTORY_H_*/
