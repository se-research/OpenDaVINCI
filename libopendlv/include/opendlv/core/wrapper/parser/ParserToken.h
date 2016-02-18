/**
 * OpenDLV - Simulation environment
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

#ifndef HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKEN_H_
#define HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKEN_H_

#include <string>

#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace wrapper {
        namespace parser {

class ParserTokenExtendedData;

            using namespace std;

            class OPENDAVINCI_API ParserToken {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    ParserToken(const ParserToken &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    ParserToken& operator=(const ParserToken &);

                public:
                    /**
                     * Constructor.
                     *
                     * @param value The value of the token.
                     * @param data Extended data for a token.
                     */
                    ParserToken(const string &value, const ParserTokenExtendedData &data);

                    virtual ~ParserToken();

                    /**
                     * This method returns the value of the token.
                     *
                     * @return Value.
                     */
                    const string getValue() const;

                    /**
                     * This method returns the extended data.
                     *
                     * @return Extended data.
                     */
                    const ParserTokenExtendedData& getExtendedData() const;

                private:
                    const string m_value;
                    const ParserTokenExtendedData &m_data;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKEN_H_*/
