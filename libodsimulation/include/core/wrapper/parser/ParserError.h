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

#ifndef HESPERIA_CORE_WRAPPER_PARSER_PARSERERROR_H_
#define HESPERIA_CORE_WRAPPER_PARSER_PARSERERROR_H_

#include <string>

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

namespace core {
    namespace wrapper {
        namespace parser {

class ParserErrorExtendedData;

            using namespace std;

            /**
             * This class encapsulates a parser error.
             */
            class OPENDAVINCI_API ParserError {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ParserError(const ParserError &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ParserError& operator=(const ParserError &);

                public:
                    /**
                     * Constructor.
                     *
                     * @param context The context where the error occurred.
                     * @param peed Extended data for this parser error.
                     */
                    ParserError(const string &context, const ParserErrorExtendedData &peed);

                    virtual ~ParserError();

                    /**
                     * This method returns the context where the error occurred.
                     *
                     * @return context.
                     */
                    const string getContext() const;

                    /**
                     * This method returns the extended data for the parser error.
                     *
                     * @return Extended data for the occurred error.
                     */
                    const ParserErrorExtendedData& getExtendedData() const;

                private:
                    const string m_context;
                    const ParserErrorExtendedData &m_data;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_CORE_WRAPPER_PARSER_PARSERERROR_H_*/
