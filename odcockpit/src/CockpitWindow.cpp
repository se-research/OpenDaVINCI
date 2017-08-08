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

#include <QtCore>
#include <QtGui>

#include <iostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/strings/StringToolbox.h"

#include "CockpitWindow.h"
#include "FIFOMultiplexer.h"
#include "MdiPlugIn.h"

#include "plugins/PlugIn.h"
#include "plugins/PlugInProvider.h"
#include "plugins/chartviewer/ChartPlugIn.h"

namespace odcore { namespace base { class DataStoreManager; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    using namespace std;
    using namespace odcore::base;
    using namespace odcore::io::conference;

    string CockpitWindow::m_startupDirectory = ".";

    CockpitWindow *CockpitWindow::m_instance = NULL;

    CockpitWindow& CockpitWindow::getInstance() {
        return *m_instance;
    }

    CockpitWindow::CockpitWindow(const KeyValueConfiguration &kvc, DataStoreManager &dsm, ContainerConference &conf) :
        m_kvc(kvc),
        m_dataStoreManager(dsm),
        m_multiplexer(new FIFOMultiplexer(dsm)),
        m_plugInProvider(cockpit::plugins::PlugInProvider::getInstance(kvc, dsm, conf, *m_multiplexer, this)),
        m_listOfPlugIns(),
        m_cockpitArea(NULL),
        m_fileMenu(NULL),
        m_windowMenu(NULL),
        m_availablePlugInsList(NULL) {
        getStartupDirectory();
        constructLayout();
        m_instance = this;
    }

    CockpitWindow::~CockpitWindow() {
        m_multiplexer->stop();
        OPENDAVINCI_CORE_DELETE_POINTER(m_multiplexer);
    }

    string CockpitWindow::getStartupDirectory() {
        if (CockpitWindow::m_startupDirectory.at(0) == '.') {
            CockpitWindow::m_startupDirectory = QDir::current().absolutePath().toStdString() + "/";
            cout << "[odcockpit] Startup directory: '" << CockpitWindow::m_startupDirectory << "'" << endl;
        }
        return CockpitWindow::m_startupDirectory;
    }

    void CockpitWindow::watchSignalUsingChartPlugIn(const string &title, const int32_t &dataType, const uint32_t &senderStamp, const string &fieldName) {
        cout << "Watching " << dataType << "/" << senderStamp << ", field = " << fieldName << endl;

        std::shared_ptr<plugins::PlugIn> plugIn = std::shared_ptr<plugins::PlugIn>(new plugins::chartviewer::ChartPlugIn(title, dataType, senderStamp, fieldName, m_kvc, this));
        setupPlugIn(plugIn);
    }

    void CockpitWindow::constructLayout() {
        // Setup an MDI application.
        m_cockpitArea = new QMdiArea(this);

        // Query PlugInProvider for available plugins.
        vector<string> listOfAvailablePlugins = m_plugInProvider.getListOfAvailablePlugIns();

        // Check for odcockpit.autostartPlugins.
        string listOfPluginsToStart;
        try {
            listOfPluginsToStart = m_kvc.getValue<string>("odcockpit.autostartplugins");
        }
        catch(...) {}

        if (listOfPluginsToStart.size() > 0) {
            showMaximized();

            QDesktopWidget desktop;
            const int32_t maxWidth = desktop.width();
            //const int32_t maxHeight = desktop.height();

            vector<string> pluginsToStart = odcore::strings::StringToolbox::split(listOfPluginsToStart, ',');
            for(auto it = pluginsToStart.begin(); it != pluginsToStart.end(); it++) {
                cout << "Trying to auto-start plugin '" << *it << "'" << endl;
                loadPlugIn(*it);
            }

            // Try to improve layout.
            if (!m_cockpitArea->subWindowList().isEmpty()) {
                uint32_t _height = 10;
                QPoint position(10, 10);
                for(auto it = m_cockpitArea->subWindowList().begin(); it != m_cockpitArea->subWindowList().end(); it++) {
                    QMdiSubWindow *_window = *it;
                    if ((position.x() + _window->width()) > maxWidth) {
                        position.setX(10);
                        position.setY(_height);
                        _height = 0;
                    }
                    _window->move(position);
                    _height = std::max<int32_t>(_height, _window->height());
                    position.setX(position.x() + _window->width());
                }
            }

        }
        else {
            m_fileMenu = menuBar()->addMenu(tr("&File"));
            m_fileMenu->addSeparator();
            QAction *closeAction = new QAction(tr("&Close"), this);
            closeAction->setShortcut(tr("Ctrl+Q"));
            closeAction->setToolTip("Close the application.");
            connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
            m_fileMenu->addAction(closeAction);

            m_windowMenu = menuBar()->addMenu(tr("&Window"));
            QAction* cascadeSWAct = new QAction(tr("C&ascade"), this);
            cascadeSWAct->setShortcut(tr("Ctrl+F9"));
            cascadeSWAct->setToolTip(tr("Cascade all open monitors."));
            connect(cascadeSWAct, SIGNAL(triggered()), m_cockpitArea, SLOT(cascadeSubWindows()));
            m_windowMenu->addAction(cascadeSWAct);

            QAction* tileSWAct = new QAction(tr("&Tile"), this);
            tileSWAct->setShortcut(tr("Ctrl+F10"));
            tileSWAct->setToolTip(tr("Tile all open monitors."));
            connect(tileSWAct, SIGNAL(triggered()), m_cockpitArea, SLOT(tileSubWindows()));

            m_windowMenu->addAction(tileSWAct);
            m_windowMenu->addSeparator();
            QAction* maxSWAction = new QAction(tr("Ma&ximize"), this);
            maxSWAction->setShortcut(tr("Ctrl+F11"));
            maxSWAction->setToolTip(tr("Maximize current monitor."));
            connect(maxSWAction, SIGNAL(triggered()), SLOT(maximizeActiveSubWindow()));

            m_windowMenu->addAction(maxSWAction);
            QAction* minSWAction = new QAction(tr("M&inimize"), this);
            minSWAction->setShortcut(tr("Ctrl+F12"));
            minSWAction->setToolTip(tr("Minimize current monitor."));
            connect(minSWAction, SIGNAL(triggered()), SLOT(minimizeActiveSubWindow()));

            m_windowMenu->addAction(minSWAction);
            QAction* resetSWAction = new QAction(tr("&Reset"), this);
            resetSWAction->setShortcut(tr("Ctrl+Shift+F12"));
            resetSWAction->setToolTip(tr("Reset current monitor."));
            connect(resetSWAction, SIGNAL(triggered()), SLOT(resetActiveSubWindow()));

            m_windowMenu->addAction(resetSWAction);
            QAction* closeSWAction = new QAction(tr("&Close"), this);
            closeSWAction->setShortcut(tr("Ctrl+C"));
            closeSWAction->setToolTip(tr("Close current monitor."));
            connect(closeSWAction, SIGNAL(triggered()), m_cockpitArea , SLOT(closeActiveSubWindow()));

            m_windowMenu->addAction(closeSWAction);
            QAction* closeAllSWAction = new QAction(tr("Close &all"), this);
            closeAllSWAction->setShortcut(tr("Ctrl+Shift+C"));
            closeAllSWAction->setToolTip(tr("Close all monitors."));
            connect(closeAllSWAction, SIGNAL(triggered()), m_cockpitArea, SLOT(closeAllSubWindows()));
            m_windowMenu->addAction(closeAllSWAction);

            // Load available plugins.
            m_availablePlugInsList = new QListWidget(this);
            m_availablePlugInsList->setMaximumWidth(200);
            m_availablePlugInsList->setMinimumWidth(200);
            connect(m_availablePlugInsList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), SLOT(showPlugIn(QListWidgetItem*)));

            // Add available plugins.
            vector<string>::iterator it = listOfAvailablePlugins.begin();
            while (it != listOfAvailablePlugins.end()) {
                QListWidgetItem *item = new QListWidgetItem(m_availablePlugInsList);
                item->setText((*it).c_str());
                item->setToolTip(m_plugInProvider.getDescriptionForPlugin((*it)).c_str());

                it++;
            }

            QDockWidget *dockWidget = new QDockWidget(tr("Plugins"), this);
            dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea |
                                        Qt::RightDockWidgetArea);
            dockWidget->setWidget(m_availablePlugInsList);
            addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
        }
        setCentralWidget(m_cockpitArea);

        m_multiplexer->start();
    }

    void CockpitWindow::maximizeActiveSubWindow() {
        if (m_cockpitArea->activeSubWindow() != 0) {
            m_cockpitArea->activeSubWindow()->showMaximized();
        }
    }

    void CockpitWindow::minimizeActiveSubWindow() {
        if (m_cockpitArea->activeSubWindow() != 0) {
            m_cockpitArea->activeSubWindow()->showMinimized();
        }
    }

    void CockpitWindow::resetActiveSubWindow() {
        if (m_cockpitArea->activeSubWindow() != 0) {
            m_cockpitArea->activeSubWindow()->showNormal();
        }
    }

    void CockpitWindow::close() {
        m_multiplexer->stop();

        if (m_cockpitArea != NULL) {
            if (m_cockpitArea->subWindowList().size() > 0) {
                m_cockpitArea->closeAllSubWindows();
            }
        }
        qApp->exit();
    }

    void CockpitWindow::showPlugIn(QListWidgetItem *item) {
        loadPlugIn(item->text().toStdString());
    }

    void CockpitWindow::loadPlugIn(const string &s) {
        std::shared_ptr<plugins::PlugIn> plugIn = m_plugInProvider.getPlugIn(s);
        setupPlugIn(plugIn);
    }

    void CockpitWindow::setupPlugIn(std::shared_ptr<plugins::PlugIn> plugIn) {
        if (plugIn.get()) {
            m_listOfPlugIns.push_back(plugIn);

            // Set container observer.
            plugIn->setContainerObserver(m_multiplexer);

            // Setup plugin.
            plugIn->setupPlugin();

            // Show plugin within an MDI window.
            if (plugIn->getQWidget() != NULL) {
                MdiPlugIn* subWindow = new MdiPlugIn(*plugIn, m_cockpitArea);
                subWindow->setAttribute(Qt::WA_DeleteOnClose);
                subWindow->setObjectName(plugIn->getName().c_str());
                subWindow->setWindowTitle(plugIn->getName().c_str());
                subWindow->setWidget(plugIn->getQWidget());

                m_cockpitArea->addSubWindow(subWindow);

                subWindow->show();
            }
        }
    }

}
