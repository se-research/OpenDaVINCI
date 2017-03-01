/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef COCKPIT_PLUGINS_LIVEFEEDWIDGET_H_
#define COCKPIT_PLUGINS_LIVEFEEDWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/reflection/Helper.h"
#include "opendavinci/odcore/reflection/Message.h"

class QTreeWidget;
class QTreeWidgetItem;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class Visitable; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            using namespace std;
            using namespace odcore::data;

            class HelperEntry {
                public:
                    HelperEntry(const HelperEntry &/*obj*/);
                    HelperEntry& operator=(const HelperEntry &/*obj*/);

                public:
                    HelperEntry();
                    virtual ~HelperEntry();

                public:
                    string m_library;
                    void *m_dynamicObjectHandle;
                    odcore::reflection::Helper *m_helper;
            };

            /**
             * This class is the container for the livefeed widget.
             */
            class LiveFeedWidget : public QWidget, public odcore::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    LiveFeedWidget(const LiveFeedWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    LiveFeedWidget&
                    operator=(const LiveFeedWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param kvc KeyValueConfiguration for this widget.
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     */
                    LiveFeedWidget(const odcore::base::KeyValueConfiguration &kvc, const PlugIn &plugIn, QWidget *prnt);

                    virtual ~LiveFeedWidget();

                    virtual void nextContainer(Container &c);

                public slots:
                    void treeItemChanged(QTreeWidgetItem*, int);

                private:
                    void findAndLoadSharedLibraries();
                    void unloadSharedLibraries();
                    vector<string> getListOfLibrariesToLoad(const vector<string> &paths);

                    void transformContainerToTree(Container &container);

                    odcore::reflection::Message resolve(odcore::data::Container &c, bool &successfullyMapped);

                private:
                    odcore::base::Mutex m_dataViewMutex;
                    QLabel *m_lastContainerSampleTime;
                    QTreeWidget *m_dataView;
                    map<int32_t, string> m_containerTypeToName;
                    odcore::base::Mutex m_containerTypeResolvingMutex;
                    map<string, bool> m_containerTypeResolving;
                    map<string, QTreeWidgetItem*> m_dataToType;

                    vector<string> m_listOfLibrariesToLoad;
                    vector<HelperEntry> m_listOfHelpers;
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_LIVEFEEDWIDGET_H_ */
