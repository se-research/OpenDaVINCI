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

#include "opendlv/core/wrapper/parser/ParserErrorExtendedData.h"

namespace core {
    namespace wrapper {
        namespace parser {

            ParserErrorExtendedData::ParserErrorExtendedData() :
                    m_line(0) {}

            ParserErrorExtendedData::~ParserErrorExtendedData() {}

            void ParserErrorExtendedData::setLine(const uint32_t &line) {
                m_line = line;
            }

            uint32_t ParserErrorExtendedData::getLine() const {
                return m_line;
            }

        }
    }
} // core::wrapper::parser
