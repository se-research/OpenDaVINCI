/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2016 Christian Berger
 * Copyright (C) 2008 - 2011 (as monitor component) Christian Berger, Bernhard Rumpe
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

#ifdef HAS_DL
    #include <dlfcn.h>
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
#include "opendavinci/odcore/reflection/Message.h"

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

            ///////////////////////////////////////////////////////////////////

            LiveFeedWidget::LiveFeedWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataViewMutex(),
                m_dataView(),
                m_dataToType(),
                m_listOfHelpers() {
                // Set size.
                setMinimumSize(640, 480);

                // Layout manager.
                QGridLayout* mainBox = new QGridLayout(this);

                //ListView and header construction
                m_dataView = unique_ptr<QTreeWidget>(new QTreeWidget(this));
                m_dataView->setColumnCount(2);
                QStringList headerLabel;
                headerLabel << tr("Message") << tr("Value");
                m_dataView->setColumnWidth(0, 200);
                m_dataView->setColumnWidth(1, 200);
                m_dataView->setHeaderLabels(headerLabel);

                //add to Layout
                mainBox->addWidget(m_dataView.get(), 0, 0);

                // Set layout manager.
                setLayout(mainBox);

                findAndLoadSharedLibraries();
            }

            LiveFeedWidget::~LiveFeedWidget() {
                unloadSharedLibraries();
            }

            void LiveFeedWidget::findAndLoadSharedLibraries() {
#ifdef HAS_DL
                HelperEntry e;

                cout << "[odcockpit/livefeed] Opening libodvdcommaai.so...\n";
                e.m_dynamicObjectHandle = dlopen("libodvdcommaai.so", RTLD_LAZY);

                if (!e.m_dynamicObjectHandle) {
                    cerr << "[odcockpit/livefeed] Cannot open library: " << dlerror() << '\n';
                }
                else {
                    typedef odcore::reflection::Helper *createHelper_t();

                    // reset errors
                    dlerror();
                    createHelper_t* getHelper = (createHelper_t*) dlsym(e.m_dynamicObjectHandle, "newHelper");
                    const char *dlsym_error = dlerror();
                    if (dlsym_error) {
                        cerr << "[odcockpit/livefeed] Cannot load symbol 'newHelper': " << dlsym_error << endl;
                        dlclose(e.m_dynamicObjectHandle);
                    }
                    else {
                        // Get pointer to external message handling.
                        e.m_helper = getHelper();

                        m_listOfHelpers.push_back(e);
                    }
                }
#endif
            }

            void LiveFeedWidget::unloadSharedLibraries() {
#ifdef HAS_DL
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
                        dlclose(e.m_dynamicObjectHandle);
                    }
                    delHelper(e.m_helper);
                    dlclose(e.m_dynamicObjectHandle);

                    it++;
                }
#endif
            }

            void LiveFeedWidget::nextContainer(Container &container) {
                Lock l(m_dataViewMutex);
                transformContainerToTree(container);
            }

            void LiveFeedWidget::transformContainerToTree(Container &container) {
                // Map attributes from message to the entries.
                bool successfullyMapped = false;
                Message msg;

                // Try AutomotiveData first.
                if (!successfullyMapped) {
                    msg = GeneratedHeaders_AutomotiveData_Helper::__map(container, successfullyMapped);
                }

                // If failed, try regular OpenDaVINCI messages.
                if (!successfullyMapped) {
                    msg = GeneratedHeaders_OpenDaVINCI_Helper::__map(container, successfullyMapped);
                }

                // Try dynamic shared object as last.
                if (!successfullyMapped && (m_listOfHelpers.size() > 0)) {
                    auto it = m_listOfHelpers.begin();
                    while ( (!successfullyMapped) && (it != m_listOfHelpers.end())) {
                        HelperEntry e = *it;
                        msg = e.m_helper->map(container, successfullyMapped);
                        it++;
                    }
                }

                if (successfullyMapped) {
                    vector<pair<string, string> > entries;
                    entries.push_back(make_pair("Sent", container.getSentTimeStamp().getYYYYMMDD_HHMMSSms()));
                    entries.push_back(make_pair("Received", container.getReceivedTimeStamp().getYYYYMMDD_HHMMSSms()));

                    MessageToTupleVisitor mttv(entries);
                    msg.accept(mttv);

                    //create new Header if needed
                    if (m_dataToType.find(msg.getLongName()) == m_dataToType.end()) {
                        QTreeWidgetItem *newHeader = new QTreeWidgetItem(m_dataView.get());
                        newHeader->setText(0, msg.getLongName().c_str());
                        m_dataToType[msg.getLongName()] = newHeader;
                    }

                    QTreeWidgetItem *entry = m_dataToType[msg.getLongName()];
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
