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

#include <iostream>
#include <string>
#include <vector>

#include <memory>
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/wrapper/CompressionFactory.h"
#include "opendavinci/odcore/wrapper/DecompressedData.h"
#include "opendlv/core/wrapper/ImageFactory.h"
#include "opendlv/threeD/loaders/OBJXArchive.h"
#include "opendlv/threeD/loaders/OBJXArchiveFactory.h"

namespace core { namespace wrapper { class Image; } }

namespace opendlv {
    namespace threeD {
        namespace loaders {

            using namespace std;
            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::exceptions;

            // Initialize singleton instance.
            Mutex OBJXArchiveFactory::m_singletonMutex;
            OBJXArchiveFactory* OBJXArchiveFactory::m_singleton = NULL;

            OBJXArchiveFactory::OBJXArchiveFactory() {}

            OBJXArchiveFactory::~OBJXArchiveFactory() {}

            OBJXArchiveFactory& OBJXArchiveFactory::getInstance() {
                {
                    Lock l(OBJXArchiveFactory::m_singletonMutex);
                    if (OBJXArchiveFactory::m_singleton == NULL) {
                        OBJXArchiveFactory::m_singleton = new OBJXArchiveFactory();
                    }
                }

                return (*OBJXArchiveFactory::m_singleton);
            }

            OBJXArchive* OBJXArchiveFactory::getOBJXArchiveFromPlainOBJFile(istream &in) throw (InvalidArgumentException) {
                if (!(in.good())) {
                    // Try to rewind the stream.
                    clog << "Trying to rewind the stream." << endl;
                    in.clear();
                    in.seekg(ios::beg);

                    if (!(in.good())) {
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Given inputstream is invalid.");
                    }
                }

                OBJXArchive *objxArchive = new OBJXArchive();

                char c;
                stringstream s;
                while (in.good()) {
                    in.get(c);
                    s << c;
                }
                objxArchive->setContentsOfObjFile(s.str());

                return objxArchive;
            }

            OBJXArchive* OBJXArchiveFactory::getOBJXArchive(istream &in) throw (InvalidArgumentException) {
                if (!(in.good())) {
                    // Try to rewind the stream.
                    clog << "Trying to rewind the stream." << endl;
                    in.clear();
                    in.seekg(ios::beg);

                    if (!(in.good())) {
                        OPENDAVINCI_CORE_THROW_EXCEPTION(InvalidArgumentException, "Given inputstream is invalid.");
                    }
                }

                OBJXArchive *objxArchive = NULL;

                // Use CompressionFactory to read the contents of the OBJXArchive.
                std::shared_ptr<odcore::wrapper::DecompressedData> data = odcore::wrapper::CompressionFactory::getContents(in);

                if (data.get()) {
                    // Create OBJXArchive.
                    objxArchive = new OBJXArchive();

                    vector<string> listOfEntries = data->getListOfEntries();
                    vector<string>::iterator it = listOfEntries.begin();

                    while (it != listOfEntries.end()) {
                        string entry = (*it++);

                        if (entry.find(".obj") != string::npos) {
                            // Set object file.
                            std::shared_ptr<istream> stream = data->getInputStreamFor(entry);
                            if (stream.get()) {
                                char c;
                                stringstream s;
                                while (stream->good()) {
                                    stream->get(c);
                                    s << c;
                                }
                                objxArchive->setContentsOfObjFile(s.str());
                            }
                        } else if (entry.find(".mtl") != string::npos) {
                            // Set material file.
                            std::shared_ptr<istream> stream = data->getInputStreamFor(entry);
                            if (stream.get()) {
                                char c;
                                stringstream s;
                                while (stream->good()) {
                                    stream->get(c);
                                    s << c;
                                }
                                objxArchive->setContentsOfMtlFile(s.str());
                            }
                        } else {
                            // Try to load an image.
                            std::shared_ptr<istream> stream = data->getInputStreamFor(entry);

                            if (stream.get()) {
                                core::wrapper::Image *image = core::wrapper::ImageFactory::getInstance().getImage(*stream);

                                if (image != NULL) {
                                    // TODO: Check where origin lies.
                                    image->rotate(static_cast<float>(cartesian::Constants::PI));

                                    // Remove any directory prefixes from the entry.
                                    string name = entry;
                                    if (name.rfind('/') != string::npos) {
                                        name = name.substr(name.rfind('/') + 1);
                                    }

                                    objxArchive->addImage(name, image);
                                }
                            }
                        }

                    }
                }

                return objxArchive;
            }

        }
    }
} // opendlv::threeD::loaders
