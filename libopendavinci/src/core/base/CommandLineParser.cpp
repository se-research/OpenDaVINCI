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

#include <cassert>
#include <cerrno>
#include <algorithm>
#include <sstream>

#include "core/base/CommandLineParser.h"
#include "core/exceptions/Exceptions.h"
#include "core/opendavinci.h"

namespace core {
    namespace base {
        using namespace std;
        using namespace core::exceptions;

        CommandLineParser::CommandLineParser() :
            m_listOfArgumentsToParse(),
            m_values() {}

        CommandLineParser::~CommandLineParser() {}

        void CommandLineParser::addCommandLineArgument(const string& argument) {
            m_listOfArgumentsToParse.push_back(argument);
        }

        const CommandLineArgument CommandLineParser::getCommandLineArgument(const string &argument) throw (CommandLineParserException) {
            vector<string>::iterator it = find(m_listOfArgumentsToParse.begin(), m_listOfArgumentsToParse.end(), argument);
            if (it == m_listOfArgumentsToParse.end()) {
                errno = 0;
                OPENDAVINCI_CORE_THROW_EXCEPTION(CommandLineParserException, "Argument " + argument + " unknown to command line parser.");
            }

            CommandLineArgument cla(argument, "", false);
            if (m_values[argument].size() > 0) {
                cla = *(m_values[argument].begin());
            }
            return cla;
        }

        const vector<CommandLineArgument> CommandLineParser::getCommandLineArguments(const string& argument) {
            return m_values[argument];
        }

        void CommandLineParser::parse(const int32_t &argc, char **argv) {
            assert(argc > 1);
            vector<string>::iterator it;
            const string argStart("--");

            for (int32_t i = 1; i < argc; i++) {
                string cmdLineValue(argv[i]);
                for (it = m_listOfArgumentsToParse.begin(); it != m_listOfArgumentsToParse.end(); ++it) {
                    const string argument = (*it);
                    string cmdLineArgument = argStart + argument + "=";

                    if ( (cmdLineValue.length() > cmdLineArgument.length()) &&
                            (cmdLineValue.substr(0, cmdLineArgument.length()) == cmdLineArgument) ) {
                        m_values[argument].push_back(CommandLineArgument(argument, cmdLineValue.substr(cmdLineArgument.length()), true));
                        break;
                    }
                }
            }
        }
    }
} // core::base
