/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
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

#ifdef HAVE_DL
    #include <dlfcn.h>
    #include <experimental/filesystem>
#endif

#include <QtCore>
#include <QtGui>

#include <cstring>
#include <iostream>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/data/TimeStamp.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "plugins/livefeed/LiveFeedWidget.h"
#include "plugins/livefeed/MessageToTupleVisitor.h"

#include "opendavinci/GeneratedHeaders_OpenDaVINCI_Helper.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData_Helper.h"

namespace cockpit { namespace plugins { class PlugIn; } }

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::reflection;

            HelperEntry::HelperEntry() : 
                 m_library(""),
                 m_dynamicObjectHandle(NULL),
                 m_helper(NULL)
            {}

            HelperEntry::HelperEntry(const HelperEntry &obj) :
                m_library(obj.m_library),
                m_dynamicObjectHandle(obj.m_dynamicObjectHandle),
                m_helper(obj.m_helper)
            {}

            HelperEntry& HelperEntry::operator=(const HelperEntry &obj) {
                m_library = obj.m_library;
                m_dynamicObjectHandle = obj.m_dynamicObjectHandle;
                m_helper = obj.m_helper;
                return *this;
            }

            HelperEntry::~HelperEntry() {}

            ///////////////////////////////////////////////////////////////////

            LiveFeedWidget::LiveFeedWidget(const odcore::base::KeyValueConfiguration &kvc, const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataViewMutex(),
                m_dataView(),
                m_containerTypeToName(),
                m_containerTypeResolvingMutex(),
                m_containerTypeResolving(),
                m_dataToType(),
                m_listOfLibrariesToLoad(),
                m_listOfHelpers() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = new QTreeWidget(this);
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("Message") << tr("Value");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                connect(m_dataView, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(treeItemChanged(QTreeWidgetItem*, int)));

                //add to Layout
                mainBox->addWidget(m_dataView, 0, 0);

                // Set layout manager.
                setLayout(mainBox);

                // Try to load shared libaries.
                const string SEARCH_PATH = kvc.getValue<string>("odcockpit.directoriesForSharedLibaries");
                cout << "[odcockpit/livefeed] Trying to find libodvd*.so files in: " << SEARCH_PATH << endl;

                const vector<string> paths = odcore::strings::StringToolbox::split(SEARCH_PATH, ',');
                m_listOfLibrariesToLoad = getListOfLibrariesToLoad(paths);

                findAndLoadSharedLibraries();
            }

            LiveFeedWidget::~LiveFeedWidget() {
                unloadSharedLibraries();
            }

            vector<string> LiveFeedWidget::getListOfLibrariesToLoad(const vector<string> &paths) {
                vector<string> librariesToLoad;
#ifndef HAVE_DL
                (void)paths;
#endif

#ifdef HAVE_DL
                for(auto pathToSearch : paths) {
                    try {
                        for(auto &pathElement : std::experimental::filesystem::recursive_directory_iterator(pathToSearch)) {
                            stringstream sstr;
                            sstr << pathElement;
                            string entry = sstr.str();
                            if (entry.find("libodvd") != string::npos) {
                                if (entry.find(".so") != string::npos) {
                                    vector<string> path = odcore::strings::StringToolbox::split(entry, '/');
                                    if (path.size() > 0) {
                                        string lib = path[path.size()-1];
                                        if (lib.size() > 0) {
                                            lib = lib.substr(0, lib.size()-1);
                                            librariesToLoad.push_back(lib);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    catch(...) {}
                }
#endif
                return librariesToLoad;
            }

            void LiveFeedWidget::findAndLoadSharedLibraries() {
#ifdef HAVE_DL
                auto it = m_listOfLibrariesToLoad.begin();
                while (it != m_listOfLibrariesToLoad.end()) {
                    const string libraryToLoad = *it;

                    {
                        HelperEntry e;

                        cout << "[odcockpit/livefeed] Opening '" + libraryToLoad + "'..." << endl;
                        e.m_dynamicObjectHandle = dlopen(libraryToLoad.c_str(), RTLD_LAZY);

                        if (!e.m_dynamicObjectHandle) {
                            cerr << "[odcockpit/livefeed] Cannot open library '" + libraryToLoad + "': " << dlerror() << endl;
                        }
                        else {
                            typedef odcore::reflection::Helper *createHelper_t();

                            // reset errors
                            dlerror();
                            createHelper_t* getHelper = (createHelper_t*) dlsym(e.m_dynamicObjectHandle, "newHelper");
                            const char *dlsym_error = dlerror();
                            if (dlsym_error) {
                                cerr << "[odcockpit/livefeed] Cannot load symbol 'newHelper' from '" + libraryToLoad + "': " << dlsym_error << endl;
                                dlclose(e.m_dynamicObjectHandle);
                            }
                            else {
                                // Get pointer to external message handling.
                                e.m_helper = getHelper();
                                e.m_library = libraryToLoad;
                                m_listOfHelpers.push_back(e);
                            }
                        }
                    }

                    it++;
                }
#endif
            }

            void LiveFeedWidget::unloadSharedLibraries() {
#ifdef HAVE_DL
                auto it = m_listOfHelpers.begin();
                while (it != m_listOfHelpers.end()) {
                    HelperEntry e = *it;

                    // Type to refer to the destroy method inside the shared library.
                    typedef void deleteHelper_t(odcore::reflection::Helper *);

                    // Reset error messages from dynamically loading shared object.
                    dlerror();
                    deleteHelper_t* delHelper = (deleteHelper_t*) dlsym(e.m_dynamicObjectHandle, "deleteHelper");
                    const char *dlsym_error = dlerror();
                    if (dlsym_error) {
                        cerr << "[odcockpit/livefeed] Cannot load symbol 'deleteHelper': " << dlsym_error << endl;
                    }
                    else {
                        cout << "[odcockpit/livefeed] Closing link to '" + e.m_library + "'" << endl;
                        delHelper(e.m_helper);
                    }
                    dlclose(e.m_dynamicObjectHandle);

                    it++;
                }
#endif
            }

            void LiveFeedWidget::nextContainer(Container &container) {
                Lock l(m_dataViewMutex);
                if (container.getDataType() == odcore::data::player::PlayerStatus::ID()) {
                    odcore::data::player::PlayerStatus ps = container.getData<odcore::data::player::PlayerStatus>();
                    if (ps.getStatus() == odcore::data::player::PlayerStatus::NEW_FILE_LOADED) {
                        // Clear current entries.
                        for (auto it = m_dataToType.begin(); it != m_dataToType.end(); it++) {
                            QTreeWidgetItem *entry = it->second;
                            entry->takeChildren();
                        }
                        m_dataToType.clear();
                        m_dataView->clear();
                    }
                }
                else {
                    transformContainerToTree(container);
                }
            }

            void LiveFeedWidget::treeItemChanged(QTreeWidgetItem *twi, int col) {
                if ( (NULL != twi) && (0 == col) ) {
                    Lock l(m_containerTypeResolvingMutex);
                    m_containerTypeResolving[twi->text(col).toStdString()] = (twi->checkState(col) == Qt::Checked);
                }
            }

            odcore::reflection::Message LiveFeedWidget::resolve(odcore::data::Container &c, bool &successfullyMapped) {
                Message msg;

                // Try AutomotiveData first.
                if (!successfullyMapped) {
                    msg = GeneratedHeaders_AutomotiveData_Helper::__map(c, successfullyMapped);
                }

                // If failed, try regular OpenDaVINCI messages.
                if (!successfullyMapped) {
                    msg = GeneratedHeaders_OpenDaVINCI_Helper::__map(c, successfullyMapped);
                }

                // Try dynamic shared object as last.
                if (!successfullyMapped && (m_listOfHelpers.size() > 0)) {
                    auto it = m_listOfHelpers.begin();
                    while ( (!successfullyMapped) && (it != m_listOfHelpers.end())) {
                        HelperEntry e = *it;
                        msg = e.m_helper->map(c, successfullyMapped);
                        it++;
                    }
                }

                return msg;
            }


            void LiveFeedWidget::transformContainerToTree(Container &container) {
                // Map attributes from message to the entries.
                bool successfullyMapped = false;
                Message msg;

                if (0 == (m_containerTypeToName.count(container.getDataType()))) {
                    msg = resolve(container, successfullyMapped);
                    if (successfullyMapped) {
                        m_containerTypeToName[container.getDataType()] = msg.getLongName();

                        Lock l(m_containerTypeResolvingMutex);
                        stringstream sstr;
                        sstr << m_containerTypeToName[container.getDataType()] << "/" << container.getSenderStamp();
                        m_containerTypeResolving[sstr.str()] = false;
                    }
                }
                else {
                    vector<pair<string, string> > entries;
                    {
                        stringstream sstr;
                        sstr << container.getDataType();
                        const string str = sstr.str();
                        entries.push_back(make_pair("type", str));
                    }
                    {
                        stringstream sstr;
                        sstr << container.getSenderStamp();
                        const string str = sstr.str();
                        entries.push_back(make_pair("sender stamp", str));
                    }
                    entries.push_back(make_pair("sent", container.getSentTimeStamp().getYYYYMMDD_HHMMSSms()));
                    entries.push_back(make_pair("received", container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()));
                    entries.push_back(make_pair("sample time", container.getSampleTimeStamp().getYYYYMMDD_HHMMSSms()));

                    // Create new Header if needed.
                    stringstream sstr_entryName;
                    sstr_entryName << m_containerTypeToName[container.getDataType()] << "/" << container.getSenderStamp();
                    const string entryName = sstr_entryName.str();

                    {
                        Lock l(m_containerTypeResolvingMutex);
                        if (m_containerTypeResolving[entryName]) {
                            msg = resolve(container, successfullyMapped);
                            if (successfullyMapped) {
                                MessageToTupleVisitor mttv(entries);
                                msg.accept(mttv);
                            }
                        }
                    }

                    if (m_dataToType.find(entryName) == m_dataToType.end()) {
                        QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView);
                        newHeader->setText(0, entryName.c_str());
                        m_dataToType[entryName] = newHeader;

                        newHeader->setFlags(newHeader->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable);
                        newHeader->setCheckState(0, Qt::Unchecked);
                    }

                    QTreeWidgetItem *entry = m_dataToType[entryName];
                    if (static_cast<uint32_t>(entry->childCount()) != entries.size()) {
                        entry->takeChildren();

                        for (uint32_t i = 0; i < entries.size(); i++) {
                            QTreeWidgetItem *sent = new QTreeWidgetItem();
                            entry->insertChild(i, sent);
                        }
                    }

                    // Map tuples of <string, string> to the tree.
                    for (uint32_t i = 0; i < entries.size(); i++) {
                        QTreeWidgetItem *child = entry->child(i);
                        child->setText(0, entries.at(i).first.c_str());
                        child->setText(1, entries.at(i).second.c_str());
                    }
                }
            }
        }
    }
}
