/**
 * odrec2fuse - Mounting .rec files via Fuse into a directory.
 * Copyright (C) 2016 Christian Berger
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

#define FUSE_USE_VERSION 26
#include <fuse.h>

#include <cstring>
#include <cerrno>

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/odcore/reflection/Field.h>
#include <opendavinci/odcore/reflection/Message.h>
#include <opendavinci/odcore/reflection/CSVFromVisitableVisitor.h>
#include <opendavinci/odcore/strings/StringToolbox.h>

#include <opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h>
#include <opendavinci/generated/odcore/data/reflection/AbstractField.h>

#include "Rec2Fuse.h"

////////////////////////////////////////////////////////////////////////////////

/*
Docker call (example): Make sure that the output directory on the host is existing.

docker run --rm -ti -v ~/HOST/COPPLAR.Recordings/2017-05-04_Umea:/opt/input -v ~/fuse:/opt/output:shared --cap-add SYS_ADMIN --cap-add MKNOD --security-opt apparmor:unconfined --device=/dev/fuse -u `id -u $USER` seresearch/opendavinci-on-base-with-fuse:latest /opt/od4/bin/odrec2fuse /opt/input/CID-189-odrecorderh264_2017-05-04_120016.rec -f /opt/output

Binary call in the image:
/opt/od4/bin/odrec2fuse /opt/input/CID-251-odrecorderh264_2016-11-08_10\:27\:05.rec -f /opt/output

Required configuration changes (not necessary with Docker 17.06+ ??):
http://unix.stackexchange.com/questions/292999/mounting-a-nfs-directory-into-host-volume-that-is-shared-with-docker

If Docker was installed through a package manager or install script for systemd, you may need to adjust the MountFlags daemon argument. To do that, locate the docker.service file:

$ sudo find /etc -name "docker.service"
In my case on Ubuntu 16.04, it was located at /etc/systemd/system/multi-user.target.wants/docker.service. Edit this file with vi or nano, and ensure that the MountFlags option reads:

MountFlags=shared
Save the file, reload the daemon args, and restart docker:

$ sudo systemctl daemon-reload
$ sudo systemctl restart docker
*/

// Maps of container-ID & sender-stamp.
std::map<std::string, std::string> mapOfFilenames;
std::map<std::string, std::string> mapOfEntries;
std::map<std::string, uint32_t> mapOfEntrySizes;

static int getattr_callback(const char *path, struct stat *stbuf) {
    memset(stbuf, 0, sizeof(struct stat));

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
        return 0;
    }

    for (auto entry : mapOfEntries) {
        std::stringstream sstr;
        sstr << "/" << mapOfFilenames[entry.first] << ".csv";
        const std::string FQDN = sstr.str();
        if (strcmp(path, FQDN.c_str()) == 0) {
            stbuf->st_mode = S_IFREG | 0444;
            stbuf->st_nlink = 1;
            stbuf->st_size = mapOfEntrySizes[entry.first];
            return 0;
        }
    }

    return -ENOENT;
}

static int readdir_callback(const char */*path*/, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);

    for (auto entry : mapOfEntries) {
        std::stringstream sstr;
        sstr << "/" << mapOfFilenames[entry.first] << ".csv";
        const std::string FQDN = sstr.str();
        filler(buf, FQDN.c_str()+1, NULL, 0); // Omit leading '/'
    }

    return 0;
}

static int open_callback(const char */*path*/, struct fuse_file_info */*fi*/) {
    return 0;
}

static int read_callback(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info */*fi*/) {
    for (auto entry : mapOfEntries) {
        std::stringstream sstr;
        sstr << "/" << mapOfFilenames[entry.first] << ".csv";
        const std::string FQDN = sstr.str();

        if (strcmp(path, FQDN.c_str()) == 0) {
            size_t len = mapOfEntrySizes[entry.first];
            if (offset >= static_cast<int32_t>(len)) {
                return 0;
            }

            const std::string filecontent = mapOfEntries[entry.first];

            if (offset + size > len) {
                memcpy(buf, filecontent.c_str() + offset, len - offset);
                return len - offset;
            }

            memcpy(buf, filecontent.c_str() + offset, size);
            return size;
        }
    }

    return -ENOENT;
}


static struct fuse_operations rec2fuse_operations;

////////////////////////////////////////////////////////////////////////////////

namespace odrec2fuse {

    using namespace std;
    using namespace odcore;
    using namespace odcore::base;
    using namespace odcore::data;
    using namespace odcore::reflection;

    ////////////////////////////////////////////////////////////////////////////

    Rec2Fuse::Rec2Fuse() :
        m_messageResolver() {
        const string SEARCH_PATH = "/opt";
        const vector<string> paths = odcore::strings::StringToolbox::split(SEARCH_PATH, ',');
        m_messageResolver = unique_ptr<MessageResolver>(new MessageResolver(paths, "libodvd", ".so"));
    }

    Rec2Fuse::~Rec2Fuse() {}

    int32_t Rec2Fuse::run(const int32_t &argc, char **argv) {
        uint32_t mappedContainers = 0;

        ::mapOfFilenames.clear();
        ::mapOfEntrySizes.clear();
        ::mapOfEntries.clear();

        if (argc > 1) {
            const string FILENAME(argv[1]);
            fstream fin;
            fin.open(FILENAME.c_str(), ios_base::in|ios_base::binary);

            if (fin.good()) {
                // Determine file size.
                fin.seekg(0, fin.end);
                int32_t length = fin.tellg();
                fin.seekg(0, fin.beg);

                int32_t oldPercentage = -1;

                while (fin.good()) {
                    Container c;
                    fin >> c;

                    if (fin.gcount() > 0) {
                        int32_t currPos = fin.tellg();
                        float percentage = (float)(currPos*100.0)/(float)length;

                        if ( ((int32_t)percentage % 5 == 0) && ((int32_t)percentage != oldPercentage) ) {
                            cout << "[Rec2Fuse]: " << (int32_t)percentage << "% (" << currPos << "/" << length << " bytes processed)." << endl;
                            oldPercentage = (int32_t)percentage;
                        }

                        bool successfullyMapped = false;

                        // First, try to decode a regular OpenDaVINCI message.
                        odcore::reflection::Message msg = GeneratedHeaders_OpenDaVINCI_Helper::__map(c, successfullyMapped);

                        // Try dynamically loaded libraries next.
                        if (!successfullyMapped) {
                            msg = m_messageResolver->resolve(c, successfullyMapped);
                        }

                        if (successfullyMapped) {
                            // Insert time stamps.
                            {
                                shared_ptr<Field<double> > f1 = shared_ptr<Field<double> >(new Field<double>());
                                f1->setFieldIdentifier(1002);
                                f1->setLongFieldName("ReceivedTimeStamp");
                                f1->setShortFieldName("ReceivedTimeStamp");
                                f1->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
                                const double v = c.getReceivedTimeStamp().getSeconds() + c.getReceivedTimeStamp().getMicroseconds()/(1000.0*1000.0);
                                f1->setValue(v);
                                f1->setSize(sizeof(double));
                                msg.insertField(f1);
                            }
                            {
                                shared_ptr<Field<double> > f2 = shared_ptr<Field<double> >(new Field<double>());
                                f2->setFieldIdentifier(1001);
                                f2->setLongFieldName("SentTimeStamp");
                                f2->setShortFieldName("SentTimeStamp");
                                f2->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
                                const double v = c.getSentTimeStamp().getSeconds() + c.getSentTimeStamp().getMicroseconds()/(1000.0*1000.0);
                                f2->setValue(v);
                                f2->setSize(sizeof(double));
                                msg.insertField(f2);
                            }
                            {
                                shared_ptr<Field<double> > f3 = shared_ptr<Field<double> >(new Field<double>());
                                f3->setFieldIdentifier(1003);
                                f3->setLongFieldName("SampleTimeStamp");
                                f3->setShortFieldName("SampleTimeStamp");
                                f3->setFieldDataType(odcore::data::reflection::AbstractField::DOUBLE_T);
                                const double v = c.getSampleTimeStamp().getSeconds() + c.getSampleTimeStamp().getMicroseconds()/(1000.0*1000.0);
                                f3->setValue(v);
                                f3->setSize(sizeof(double));
                                msg.insertField(f3);
                            }

                            mappedContainers++;

                            stringstream sstrKey;
                            sstrKey << c.getDataType() << "/" << c.getSenderStamp();
                            const string KEY = sstrKey.str();

                            stringstream sstrCSVData;
                            const bool ADD_HEADER = (mapOfEntries.count(KEY) == 0);
                            const char DELIMITER = ';';
                            CSVFromVisitableVisitor csv(sstrCSVData, ADD_HEADER, DELIMITER);
                            msg.accept(csv);

                            stringstream sstrFilename;
                            sstrFilename << msg.getLongName() << "-" << c.getSenderStamp();
                            const string _FILENAME = sstrFilename.str();

                            mapOfFilenames[KEY] = _FILENAME;
                            mapOfEntries[KEY] +=  sstrCSVData.str();
                            mapOfEntrySizes[KEY] = mapOfEntries[KEY].size();
                        }

                    }
                }
            }

            cout << "[Rec2Fuse] Mapped " << mappedContainers << " containers in total into " << mapOfEntries.size() << " files." << endl;

            rec2fuse_operations.getattr = getattr_callback;
            rec2fuse_operations.open = open_callback;
            rec2fuse_operations.read = read_callback;
            rec2fuse_operations.readdir = readdir_callback;

            // Remove .rec filename from list of args before calling FUSE.
            vector<string> args;
            for (int32_t i = 0; i < argc; i++) {
                if (i != 1) {
                    args.push_back(string(argv[i]));
                }
            }

            char **argv2 = new char*[args.size()];
            for (uint32_t i = 0; i < args.size(); i++) {
                argv2[i] = const_cast<char*>(args[i].c_str());
            }

            return fuse_main(argc-1, argv2, &rec2fuse_operations, NULL);
        }

        return -1;
    }

} // odrec2fuse

