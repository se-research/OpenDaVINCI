/**
 * odsplit - Tool for splitting recorded data
 * Copyright (C) 2015 Christian Berger
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
#include <vector>

#include "core/strings/StringToolbox.h"
#include "core/data/Container.h"
#include "core/io/URL.h"
#include "core/base/CommandLineParser.h"

#include "GeneratedHeaders_CoreData.h"

#include "tools/player/Player.h"
#include "tools/recorder/Recorder.h"
#include "tools/splitter/Splitter.h"

#include "Split.h"

namespace odsplit {

    using namespace std;
    using namespace core::base;
    using namespace core::data;
    using namespace core::io;
    using namespace tools::player;
    using namespace tools::recorder;
    using namespace tools::splitter;

    Split::Split(const int32_t &argc, char **argv) :
        TimeTriggeredConferenceClientModule(argc, argv, "odsplit"),
        m_source(),
        m_range() {
        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);
    }

    Split::~Split() {}

    void Split::setUp() {}

    void Split::tearDown() {}

    void Split::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("source");
        cmdParser.addCommandLineArgument("range");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentSOURCE = cmdParser.getCommandLineArgument("source");
        CommandLineArgument cmdArgumentRANGE = cmdParser.getCommandLineArgument("range");

        if (cmdArgumentSOURCE.isSet()) {
            m_source = cmdArgumentSOURCE.getValue<string>();
            core::strings::StringToolbox::trim(m_source);
        }

        if (cmdArgumentRANGE.isSet()) {
            m_range = cmdArgumentRANGE.getValue<string>();
            core::strings::StringToolbox::trim(m_range);
        }
    }

    coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode Split::body() {
        coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode retVal = coredata::dmcp::ModuleExitCodeMessage::OKAY;

        // Size of the memory buffer.
        const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");

        // Split the range parameter.
        vector<string> rangeTokens = core::strings::StringToolbox::split(m_range, '-');

        if (rangeTokens.size() == 2) {
            uint32_t start = 0, end = 0;
            stringstream s_start;
            s_start << rangeTokens.at(0);
            s_start >> start;

            stringstream s_end;
            s_end << rangeTokens.at(1);
            s_end >> end;

            if (start < end) {
                Splitter s;
                s.process(m_source, MEMORY_SEGMENT_SIZE, start, end);
            }
            else {
                retVal = coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;
            }
        }

        return retVal;
    }

} // odsplit

