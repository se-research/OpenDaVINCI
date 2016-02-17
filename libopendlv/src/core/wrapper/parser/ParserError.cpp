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

#include "hesperia/core/wrapper/parser/ParserError.h"

namespace core {
    namespace wrapper {
        namespace parser {

class ParserErrorExtendedData;

            ParserError::ParserError(const string &context, const ParserErrorExtendedData &peed) :
                    m_context(context),
                    m_data(peed) {}

            ParserError::~ParserError() {}

            const string ParserError::getContext() const {
                return m_context;
            }

            const ParserErrorExtendedData& ParserError::getExtendedData() const {
                return m_data;
            }

        }
    }
} // core::wrapper::parser
