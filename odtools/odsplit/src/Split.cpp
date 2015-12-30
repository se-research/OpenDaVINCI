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

#include "core/base/CommandLineParser.h"
#include "core/strings/StringToolbox.h"
#include "core/data/Container.h"
#include "core/io/URL.h"

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

    Split::Split() :
        m_source(),
        m_range(),
        m_memorySegmentSize(0) {}

    Split::~Split() {}

    void Split::parseAdditionalCommandLineParameters(const int &argc, char **argv) {
        CommandLineParser cmdParser;
        cmdParser.addCommandLineArgument("source");
        cmdParser.addCommandLineArgument("range");
        cmdParser.addCommandLineArgument("memorysegmentsize");

        cmdParser.parse(argc, argv);

        CommandLineArgument cmdArgumentSOURCE = cmdParser.getCommandLineArgument("source");
        CommandLineArgument cmdArgumentRANGE = cmdParser.getCommandLineArgument("range");
        CommandLineArgument cmdArgumentMEMORYSEGMENTSIZE = cmdParser.getCommandLineArgument("memorysegmentsize");

        if (cmdArgumentSOURCE.isSet()) {
            m_source = cmdArgumentSOURCE.getValue<string>();
            core::strings::StringToolbox::trim(m_source);
        }

        if (cmdArgumentRANGE.isSet()) {
            m_range = cmdArgumentRANGE.getValue<string>();
            core::strings::StringToolbox::trim(m_range);
        }

        if (cmdArgumentMEMORYSEGMENTSIZE.isSet()) {
            m_memorySegmentSize = cmdArgumentMEMORYSEGMENTSIZE.getValue<int32_t>();
        }

        const int32_t MINIMUM_MEMORY_SEGMENT_SIZE = 640*480*1;
        if (m_memorySegmentSize < MINIMUM_MEMORY_SEGMENT_SIZE) {
            cerr << "[odsplit] Specified memorySegmentSize is too small, using " << MINIMUM_MEMORY_SEGMENT_SIZE << " bytes." << endl;
            m_memorySegmentSize = MINIMUM_MEMORY_SEGMENT_SIZE;
        }
    }

    int32_t Split::run(const int32_t &argc, char **argv) {
        enum RETURN_CODE { CORRECT = 0,
                           END_SMALLER_THAN_START = 1 };

        RETURN_CODE retVal = CORRECT;

        // Parse command line arguments.
        parseAdditionalCommandLineParameters(argc, argv);

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
                s.process(m_source, m_memorySegmentSize, start, end);
            }
            else {
                retVal = END_SMALLER_THAN_START;
            }
        }

        return retVal;
    }

} // odsplit

