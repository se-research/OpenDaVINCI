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

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/io/URL.h"
#include "opendavinci/odcore/strings/StringComparator.h"
#include "opendavinci/odcore/wrapper/CompressionFactory.h"
#include "opendavinci/odcore/wrapper/DecompressedData.h"
#include "opendlv/data/scenario/Scenario.h"
#include "opendlv/scenario/SCNXArchive.h"
#include "opendlv/scenario/SCNXArchiveFactory.h"
#include "opendlv/scenario/ScenarioFactory.h"

namespace opendlv {
    namespace scenario {

        using namespace std;
        using namespace odcore;
        using namespace odcore::base;
        using namespace odcore::exceptions;
        using namespace odcore::io;

        using namespace data::scenario;

        // Initialize singleton instance.
        Mutex SCNXArchiveFactory::m_singletonMutex;
        SCNXArchiveFactory* SCNXArchiveFactory::m_singleton = NULL;

        SCNXArchiveFactory::SCNXArchiveFactory() :
            m_mapOfSCNXArchives() {}

        SCNXArchiveFactory::~SCNXArchiveFactory() {
            map<string, SCNXArchive*, odcore::strings::StringComparator>::iterator it = m_mapOfSCNXArchives.begin();
            while (it != m_mapOfSCNXArchives.end()) {
                SCNXArchive *s = it->second;
                OPENDAVINCI_CORE_DELETE_POINTER(s);
            }
            m_mapOfSCNXArchives.clear();

            clog << "SCNXArchiveFactory destroyed." << endl;
        }

        SCNXArchiveFactory& SCNXArchiveFactory::getInstance() {
            {
                Lock l(SCNXArchiveFactory::m_singletonMutex);
                if (SCNXArchiveFactory::m_singleton == NULL) {
                    SCNXArchiveFactory::m_singleton = new SCNXArchiveFactory();
                }
            }

            return (*SCNXArchiveFactory::m_singleton);
        }

        SCNXArchive& SCNXArchiveFactory::getSCNXArchive(const URL &url) throw (InvalidArgumentException) {
            if (!(url.isValid())) {
                OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "URL is invalid.");
            }

            SCNXArchive *scnxArchive = NULL;

            // Try to find an existing SCNXArchive in the map using the URL as key.
            map<string, SCNXArchive*, odcore::strings::StringComparator>::iterator it = m_mapOfSCNXArchives.find(url.toString());
            if (it != m_mapOfSCNXArchives.end()) {
            	clog << "Found already constructed data structure." << endl;
                scnxArchive = it->second;
            }

            if (scnxArchive == NULL) {
                clog << "Creating new SCNXArchive from " << url.toString() << endl;

                string fileName = url.getResource();
                fstream fin(fileName.c_str(), ios::binary | ios::in);
                std::shared_ptr<odcore::wrapper::DecompressedData> data = odcore::wrapper::CompressionFactory::getContents(fin);
                fin.close();

                if (data.get()) {
                    Scenario scenario;
                    std::shared_ptr<istream> stream = data->getInputStreamFor("scenario.scn");
                    if (stream.get()) {
                        stringstream s;
                        char c;
                        while (stream->good()) {
                            stream->get(c);
                            s << c;
                        }

                        // Trying to parse the input.
                        scenario = ScenarioFactory::getInstance().getScenario(s.str());
                    } else {
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Archive from the given URL does not contain a valid SCN file.");
                    }

                    // Create SCNXArchive.
                    scnxArchive = new SCNXArchive(scenario, data);

                    // Store SCNXArchive for further usage.
                    // Somehow, there seems to be a bug because the data structure got corrupt...
//                    m_mapOfSCNXArchives[url.toString()] = scnxArchive;
                }
                else {
                    OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "URL could not be used to read input data.");
                }
            }

            return *scnxArchive;
        }

    }
} // opendlv::scenario
