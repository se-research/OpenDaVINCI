/**
 * odredirector - Tool for dumping data to stdout or reading back from stdin
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

#ifndef STDOUT_PUMP_H_
#define STDOUT_PUMP_H_

#include "core/platform.h"
#include "core/base/AbstractDataStore.h"

namespace core { namespace data { class Container; } }

namespace odredirector {

    /**
     * Data store ("sink") to pump received containers to stdout.
     */
    class StdoutPump : public core::base::AbstractDataStore {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            StdoutPump(const StdoutPump &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            StdoutPump& operator=(const StdoutPump &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param jpegQuality Compression quality for SharedImages.
             */
            StdoutPump(const int32_t &jpegQuality);

            virtual ~StdoutPump();

            virtual void add(const core::data::Container &container);

            virtual void clear();

            virtual uint32_t getSize() const;

            virtual bool isEmpty() const;

        private:
            int32_t m_jpegQuality;
    };

} // odredirector

#endif /*STDOUT_PUMP_H_*/
