/**
 * example-boxparker - This test suite demonstrates how to
 *                     compose a simulation including an SCNX
 *                     scenario.
 * Copyright (C) 2012 - 2016 Christian Berger
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

#ifndef EXAMPLEDRIVERSIMULATION_H_
#define EXAMPLEDRIVERSIMULATION_H_

#include "core/opendavinci.h"

namespace simulation {
    class ExampleDriverSimulation {
        public:
            /**
             * This method executes the simulation and returns true
             * if everything ran as expected.
             *
             * @return true if everything ran as expected.
             */
            bool run();
    };
}

#endif // EXAMPLEDRIVERSIMULATION_H_
