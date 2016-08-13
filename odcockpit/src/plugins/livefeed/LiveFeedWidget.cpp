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

            LiveFeedWidget::LiveFeedWidget(const PlugIn &/*plugIn*/, QWidget *prnt) :
                QWidget(prnt),
                m_dataViewMutex(),
                m_dataView(),
                m_dataToType(),
                m_dynamicObjectHandle(NULL),
                m_helper(NULL) {
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

#ifdef HAS_DL
cout << "Opening libodvdcommaai.so...\n";
m_dynamicObjectHandle = dlopen("libodvdcommaai.so", RTLD_LAZY);

if (!m_dynamicObjectHandle) {
    cerr << "Cannot open library: " << dlerror() << '\n';
}
else {
    typedef odcore::reflection::Helper *createHelper_t();

    // reset errors
    dlerror();
    createHelper_t* getHelper = (createHelper_t*) dlsym(m_dynamicObjectHandle, "newHelper");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'mapper': " << dlsym_error << endl;
        dlclose(m_dynamicObjectHandle);
    }
    else {
        // Get pointer to external message handling.
        m_helper = getHelper();
    }
}
#endif
            }

            LiveFeedWidget::~LiveFeedWidget() {
#ifdef HAS_DL
if (m_dynamicObjectHandle && m_helper) {
    typedef void deleteHelper_t(odcore::reflection::Helper *);

    // reset errors
    dlerror();
    deleteHelper_t* delHelper = (deleteHelper_t*) dlsym(m_dynamicObjectHandle, "deleteHelper");
    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        cerr << "Cannot load symbol 'mapper': " << dlsym_error << endl;
        dlclose(m_dynamicObjectHandle);
    }
    delHelper(m_helper);
    dlclose(m_dynamicObjectHandle);
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
                if (!successfullyMapped && (m_helper != NULL)) {
                    msg = m_helper->map(container, successfullyMapped);
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
