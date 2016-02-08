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

#ifndef HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKENLISTENER_H_
#define HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKENLISTENER_H_

#include "opendavinci/core/opendavinci.h"

namespace core {
    namespace wrapper {
        namespace parser {

            // Forward declaration.
            class ParserToken;

            /**
             * This interface encapsulates all data for a token listener.
             */
            class OPENDAVINCI_API ParserTokenListener {
                public:
                    virtual ~ParserTokenListener();

                    /**
                     * This method is called to process the next token from the grammar.
                     *
                     * @param token Token to be processed.
                     */
                    virtual void nextToken(const ParserToken &token) = 0;
            };

        }
    }
} // core::wrapper::parser

#endif /*HESPERIA_CORE_WRAPPER_PARSER_PARSERTOKENLISTENER_H_*/
