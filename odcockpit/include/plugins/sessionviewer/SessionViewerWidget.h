/**
 * cockpit - Visualization environment
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

#ifndef COCKPIT_PLUGINS_SESSIONVIEWERWIDGET_H_
#define COCKPIT_PLUGINS_SESSIONVIEWERWIDGET_H_

#include <QtCore>
#include <QtGui>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "opendavinci/odcore/io/conference/ContainerListener.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/generated/odcore/data/dmcp/ModuleStatistic.h"

class QTreeWidget;
class QTreeWidgetItem;
namespace cockpit { namespace plugins { class PlugIn; } }
namespace odcore { namespace base { class Visitable; } }
namespace odcore { namespace data { class Container; } }

namespace cockpit {

    namespace plugins {

        namespace sessionviewer {

            using namespace std;
            using namespace odcore::data;

            /**
             * This class is the container for the session viewer widget.
             */
            class SessionViewerWidget : public QWidget, public odcore::io::conference::ContainerListener {

                    Q_OBJECT

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    SessionViewerWidget(const SessionViewerWidget &/*obj*/);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    SessionViewerWidget&
                    operator=(const SessionViewerWidget &/*obj*/);

                public:
                    /**
                     * Constructor.
                     *
                     * @param plugIn Reference to the plugin to which this widget belongs.
                     * @param prnt Pointer to the parental widget.
                     * @param listOfExpectedModules List of modules expected to participate in the session.
                     */
                    SessionViewerWidget(const PlugIn &plugIn, QWidget *prnt, const vector<string> &listOfExpectedModules);

                    virtual ~SessionViewerWidget();

                    virtual void nextContainer(Container &c);

                private:
                    odcore::base::Mutex m_participatingModulesViewMutex;
                    unique_ptr<QListWidget> m_expectedModulesToParticipateView;
                    unique_ptr<QTreeWidget> m_participatingModulesView;
                    vector<string> m_listOfExpectedModulesToParticipate;
                    map<string, QTreeWidgetItem* > m_participatingModules;
                    unique_ptr<QLabel> m_expectedModulesToParticipateViewLabel;
                    unique_ptr<QLabel> m_participatingModulesViewLabel;

                    void addLogMessageToTree(const string &module, const odcore::data::dmcp::ModuleStatistic &ms);
            };

        }
    }
}

#endif /* COCKPIT_PLUGINS_SESSIONVIEWERWIDGET_H_ */
