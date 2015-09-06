/**
 * canproxymapper - Tool combining canproxy and canmapper
 * Copyright (C) 2015 Christian Berger
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

#ifndef CANPROXYMAPPER_H_
#define CANPROXYMAPPER_H_

#include "CanProxy.h"
#include "DataMapper.h"

namespace automotive {

    using namespace std;

    /**
     * This class can be used to map GenericCANMessages to high-level C++ messages.
     */
    class CanProxyMapper : public CanProxy {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            CanProxyMapper(const CanProxyMapper &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            CanProxyMapper& operator=(const CanProxyMapper &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            CanProxyMapper(const int32_t &argc, char **argv);

            virtual ~CanProxyMapper();

            virtual void nextGenericCANMessage(const GenericCANMessage &gcm);

        private:
            DataMapper m_dataMapper;

    };

} // automotive

#endif /*CANPROXYMAPPER_H_*/
