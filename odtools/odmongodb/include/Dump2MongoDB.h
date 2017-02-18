/**
 * odmongodb - Tool for dumping received containers after message resolving into a MongoDB.
 * Copyright (C) 2017 Christian Berger
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

#ifndef DUMP2MONGODB_H_
#define DUMP2MONGODB_H_

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/reflection/MessageResolver.h>
#include <opendavinci/odcore/base/module/DataTriggeredConferenceClientModule.h>

namespace odmongodb {

    using namespace std;

    /**
     * This class dumps successfully mapped containers to MongoDB.
     */
    class Dump2MongoDB : public odcore::base::module::DataTriggeredConferenceClientModule {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            Dump2MongoDB(const Dump2MongoDB &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            Dump2MongoDB& operator=(const Dump2MongoDB &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             */
            Dump2MongoDB(const int32_t &argc, char **argv);

            virtual ~Dump2MongoDB();

            virtual void nextContainer(odcore::data::Container &c);

        private:
            virtual void setUp();

            virtual void tearDown();

        private:
            odcore::reflection::MessageResolver m_messageResolver;
    };

} // odmongodb

#endif /*DUMP2MONGODB_H_*/
