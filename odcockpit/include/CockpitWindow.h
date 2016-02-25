/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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

#ifndef COCKPITWINDOW_H_
#define COCKPITWINDOW_H_

#include <Qt/qmainwindow.h>
#include <qobjectdefs.h>

#include <vector>

#include "opendavinci/odcore/SharedPointer.h"
#include "opendavinci/odcore/base/KeyValueConfiguration.h"

class QListWidget;
class QListWidgetItem;
class QMdiArea;
class QMenu;
namespace odcore { namespace base { class DataStoreManager; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

class FIFOMultiplexer;
namespace plugins { class PlugIn; }
namespace plugins { class PlugInProvider; }

    using namespace std;

    class CockpitWindow: public QMainWindow {

            Q_OBJECT

        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             */
            CockpitWindow(const CockpitWindow &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             */
            CockpitWindow& operator=(const CockpitWindow &/*obj*/);

        public:
            /**
             * Constructor.
             *
             * @param kvc KeyValueConfiguration.
             * @param dsm DataStoreManager to be used for adding DataStores.
             * @param conf Container conference to send data to.
             */
            CockpitWindow(const odcore::base::KeyValueConfiguration &kvc, odcore::base::DataStoreManager &dsm, odcore::io::conference::ContainerConference &conf);

            virtual ~CockpitWindow();

        public slots:
            void close();
            void maximizeActiveSubWindow();
            void minimizeActiveSubWindow();
            void resetActiveSubWindow();
            void showPlugIn(QListWidgetItem *item);

        private:
            void constructLayout();

        private:
            odcore::base::KeyValueConfiguration m_kvc;
            odcore::base::DataStoreManager &m_dataStoreManager;
            FIFOMultiplexer *m_multiplexer;
            cockpit::plugins::PlugInProvider &m_plugInProvider;
            vector<odcore::SharedPointer<cockpit::plugins::PlugIn> > m_listOfPlugIns;

            QMdiArea *m_cockpitArea;
            QMenu *m_fileMenu;
            QMenu *m_windowMenu;
            QListWidget *m_availablePlugInsList;
    };
}

#endif /* COCKPITWINDOW_H_ */
