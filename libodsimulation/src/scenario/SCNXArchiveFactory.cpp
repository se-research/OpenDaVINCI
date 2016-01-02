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

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "core/platform.h"
#include "core/SharedPointer.h"
#include "core/base/Lock.h"
#include "core/base/Mutex.h"
#include "core/exceptions/Exceptions.h"
#include "core/io/URL.h"
#include "core/opendavinci.h"
#include "core/strings/StringComparator.h"
#include "core/wrapper/CompressionFactory.h"
#include "core/wrapper/DecompressedData.h"
#include "hesperia/data/scenario/Scenario.h"
#include "hesperia/scenario/SCNXArchive.h"
#include "hesperia/scenario/SCNXArchiveFactory.h"
#include "hesperia/scenario/ScenarioFactory.h"

namespace hesperia {
    namespace scenario {

        using namespace std;
        using namespace core;
        using namespace core::base;
        using namespace core::exceptions;
        using namespace core::io;

        using namespace data::scenario;

        // Initialize singleton instance.
        Mutex SCNXArchiveFactory::m_singletonMutex;
        SCNXArchiveFactory* SCNXArchiveFactory::m_singleton = NULL;

        SCNXArchiveFactory::SCNXArchiveFactory() :
            m_mapOfSCNXArchives() {}

        SCNXArchiveFactory::~SCNXArchiveFactory() {
            map<string, SCNXArchive*, core::strings::StringComparator>::iterator it = m_mapOfSCNXArchives.begin();
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
            map<string, SCNXArchive*, core::strings::StringComparator>::iterator it = m_mapOfSCNXArchives.find(url.toString());
            if (it != m_mapOfSCNXArchives.end()) {
            	clog << "Found already constructed data structure." << endl;
                scnxArchive = it->second;
            }

            if (scnxArchive == NULL) {
                clog << "Creating new SCNXArchive from " << url.toString() << endl;

                string fileName = url.getResource();
                fstream fin(fileName.c_str(), ios::binary | ios::in);
                core::SharedPointer<core::wrapper::DecompressedData> data = core::wrapper::CompressionFactory::getContents(fin);
                fin.close();

                if (data.isValid()) {
                    Scenario scenario;
                    SharedPointer<istream> stream = data->getInputStreamFor("scenario.scn");
                    if (stream.isValid()) {
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
} // hesperia::scenario
