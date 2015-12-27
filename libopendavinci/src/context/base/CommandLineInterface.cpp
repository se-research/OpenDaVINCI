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

#include <ctype.h>
#include <algorithm>
#include <fstream>
#include <functional>
#include <sstream>

#include "context/base/CommandLineInterface.h"
#include "core/base/CommandLineArgument.h"
#include "core/base/CommandLineParser.h"

namespace context {
    namespace base {

        using namespace std;
        using namespace core::base;

        CommandLineInterface::CommandLineInterface() :
            m_configuration(),
            m_multicastGroup(),
            m_CID(),
			m_isVerbose(false),
			m_isSupercomponent(false) {}

        CommandLineInterface::~CommandLineInterface() {}

        bool CommandLineInterface::parse(const int32_t &argc, char **argv) {
            bool retVal = true;

            CommandLineParser cmdParser;
            cmdParser.addCommandLineArgument("cid");
            cmdParser.addCommandLineArgument("configuration");
            cmdParser.addCommandLineArgument("verbose");
            cmdParser.addCommandLineArgument("supercomponent");

            cmdParser.parse(argc, argv);

            CommandLineArgument cmdArgumentCID = cmdParser.getCommandLineArgument("cid");
            CommandLineArgument cmdArgumentCONFIGURATION = cmdParser.getCommandLineArgument("configuration");
            CommandLineArgument cmdArgumentVERBOSE = cmdParser.getCommandLineArgument("verbose");
            CommandLineArgument cmdArgumentSUPERCOMPONENT = cmdParser.getCommandLineArgument("supercomponent");

            if (cmdArgumentCID.isSet()) {
                m_multicastGroup = "225.0.0." + cmdArgumentCID.getValue<string>();
                m_CID = cmdArgumentCID.getValue<uint32_t>();
            }
            else {
                retVal &= false;
            }

            if (cmdArgumentCONFIGURATION.isSet()) {
                string fileName = cmdArgumentCONFIGURATION.getValue<string>();
                ifstream configStream(fileName.c_str(), ios::in);
                if (configStream.good()) {
                    m_configuration.readFrom(configStream);
                }
                else {
                    retVal &= false;
                }
            }
            else {
                retVal &= false;
            }

            if (cmdArgumentVERBOSE.isSet()) {
            	string value = cmdArgumentVERBOSE.getValue<string>();
                transform(value.begin(), value.end(), value.begin(), ptr_fun(::tolower));

            	m_isVerbose = (value == "true");
            }

            if (cmdArgumentSUPERCOMPONENT.isSet()) {
            	string value = cmdArgumentSUPERCOMPONENT.getValue<string>();
                transform(value.begin(), value.end(), value.begin(), ptr_fun(::tolower));

            	m_isSupercomponent = (value == "true");
            }

            return retVal;
        }

        const KeyValueConfiguration CommandLineInterface::getConfiguration() const {
            return m_configuration;
        }

        const string CommandLineInterface::getMulticastGroup() const {
            return m_multicastGroup;
        }

        uint32_t CommandLineInterface::getCID() const {
            return m_CID;
        }

        bool CommandLineInterface::isVerbose() const {
        	return m_isVerbose;
        }

        bool CommandLineInterface::isSupercomponent() const {
        	return m_isSupercomponent;
        }

    }
} // context::base
