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

#ifndef HESPERIA_CORE_WRAPPER_LIBRARIES_H_
#define HESPERIA_CORE_WRAPPER_LIBRARIES_H_

namespace core {
    namespace wrapper {

        /**
         * Enumeration of supported, but mutual excluded parser libraries.
         */
        enum PARSER_LIBRARIES {
            BOOST_SPIRIT_LIBRARIES
        };

        /**
         * Which parser library has to be used?
         *
         * To add a new library, simply change const to static,
         * try to compile libnative, fix all compiling errors
         * and re-change it back to const!
         */
        const PARSER_LIBRARIES USEPARSERLIBRARY = BOOST_SPIRIT_LIBRARIES;

        /**
         * Enumeration of supported, but mutual excluded imaging libraries.
         */
        enum IMAGING_LIBRARIES {
            OPENCV_LIBRARIES
        };

        /**
         * Which imaging library has to be used?
         *
         * To add a new library, simply change const to static,
         * try to compile libnative, fix all compiling errors
         * and re-change it back to const!
         */
        const IMAGING_LIBRARIES USEIMAGINGLIBRARY = OPENCV_LIBRARIES;


        /**
         * Enumeration of supported, but mutual excluded matrix libraries.
         */
        enum MATRIX_LIBRARIES {
            MATRIX_OPENCV_LIBRARIES
        };

        /**
         * Which matrix library has to be used?
         *
         * To add a new library, simply change const to static,
         * try to compile libnative, fix all compiling errors
         * and re-change it back to const!
         */
        const MATRIX_LIBRARIES USEMATRIXLIBRARY = MATRIX_OPENCV_LIBRARIES;
    }
} // core::wrapper

#endif /*HESPERIA_CORE_WRAPPER_LIBRARIES_H_*/
