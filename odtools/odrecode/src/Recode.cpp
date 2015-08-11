/**
 * odrecode - Tool for recoding existing recordings
 * Copyright (C) 2014 - 2015 Christian Berger
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

#include <iostream>

#include "core/base/CommandLineParser.h"
#include "core/strings/StringToolbox.h"

#include "tools/splitter/Splitter.h"

#include "Recode.h"

namespace recode {

    using namespace std;
    using namespace core::base;
    using namespace tools::splitter;

    Recode::Recode(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "recode"),
        m_source(),
        m_destination() {
        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);
    }

    Recode::~Recode() {}

    void Recode::setUp() {}

    void Recode::tearDown() {}

    void Recode::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("source");
        cmdParser.addCommandLineArgument("destination");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentSOURCE = cmdParser.getCommandLineArgument("source");
        CommandLineArgument cmdArgumentDESTINATION = cmdParser.getCommandLineArgument("destination");

        if (cmdArgumentSOURCE.isSet()) {
            m_source = cmdArgumentSOURCE.getValue<string>();
            core::strings::StringToolbox::trim(m_source);
        }

        if (cmdArgumentDESTINATION.isSet()) {
            m_destination = cmdArgumentDESTINATION.getValue<string>();
            core::strings::StringToolbox::trim(m_destination);
        }
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode Recode::body() {
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode retVal = coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;

        // Size of the memory buffer.
        const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");

        if (m_source.size() > 0) {
            if (m_destination.size() > 0) {
                Splitter s;
                s.process(m_source, m_destination, MEMORY_SEGMENT_SIZE);
                retVal = coredata::dmcp::ModuleExitCodeMessage::OKAY;
            }
            else {
                cerr << "destination file not set, use parameter --destination=" << endl;
            }
        }
        else {
            cerr << "source file not set, use parameter --source=" << endl;
        }

        return retVal;
    }

} // recode
