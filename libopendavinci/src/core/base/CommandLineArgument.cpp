/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#include "opendavinci/core/base/CommandLineArgument.h"

namespace core {
    namespace base {

        CommandLineArgument::CommandLineArgument() :
                m_argument(""),
                m_value(""),
                m_set(false) {}

        CommandLineArgument::CommandLineArgument(const string& argument, const string& value, const bool &set) :
                m_argument(argument),
                m_value(value),
                m_set(set) {}

        CommandLineArgument::~CommandLineArgument() {}

        bool CommandLineArgument::isSet() const {
            return m_set;
        }

        const std::string CommandLineArgument::getArgument() const {
            return m_argument;
        }
    }
} // core::base
