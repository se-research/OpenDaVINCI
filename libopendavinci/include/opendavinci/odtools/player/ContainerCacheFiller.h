/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2017 Christian Berger
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

#ifndef OPENDAVINCI_TOOLS_PLAYER_CONTAINERCACHEFILLER_H_
#define OPENDAVINCI_TOOLS_PLAYER_CONTAINERCACHEFILLER_H_

#include <opendavinci/odcore/opendavinci.h>
#include <opendavinci/odcore/base/Service.h>

namespace odtools {
    namespace player {

        using namespace std;

        class OPENDAVINCI_API ContainerCacheFiller : public odcore::base::Service {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                ContainerCacheFiller(const ContainerCacheFiller &/*obj*/) = delete;

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                ContainerCacheFiller& operator=(const ContainerCacheFiller &/*obj*/) = delete;

            public:
                /**
                 * Constructor.
                 */
                ContainerCacheFiller();

                virtual ~ContainerCacheFiller();

            public:
                virtual void beforeStop();

                virtual void run();
        };

    } // player
} // tools

#endif /*OPENDAVINCI_TOOLS_PLAYER_CONTAINERCACHEFILLER_H_*/
