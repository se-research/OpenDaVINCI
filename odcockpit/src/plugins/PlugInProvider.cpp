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

#include <qobjectdefs.h>
#include <qstring.h>
#include <qwidget.h>

#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "plugins/PlugInProvider.h"
#include "plugins/birdseyemap/BirdsEyeMapPlugIn.h"
#include "plugins/configurationviewer/ConfigurationViewerPlugIn.h"
#include "plugins/controller/ControllerPlugIn.h"
#include "plugins/environmentviewer/EnvironmentViewerPlugIn.h"
#include "plugins/iruscharts/IrUsChartsPlugIn.h"
#include "plugins/irusmap/IrUsMapPlugIn.h"
#include "plugins/livefeed/LiveFeedPlugIn.h"
#include "plugins/logmessage/LogMessagePlugIn.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerPlugIn.h"
#include "plugins/objxviewer/OBJXViewerPlugIn.h"
#include "plugins/player/PlayerPlugIn.h"
#include "plugins/scnxviewer/SCNXViewerPlugIn.h"
#include "plugins/sharedimageviewer/SharedImageViewerPlugIn.h"
#include "plugins/spy/SpyPlugIn.h"
#include "plugins/streetmapviewer/StreetMapPlugIn.h"

namespace odcore { namespace base { class DataStoreManager; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

class PlugIn;

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::io::conference;

        // Initialize singleton instance.
        Mutex PlugInProvider::m_singletonMutex;
        PlugInProvider* PlugInProvider::m_singleton = NULL;

        PlugInProvider::PlugInProvider(const KeyValueConfiguration &kvc, DataStoreManager &dsm, ContainerConference &conf, QWidget *prnt) :
            QObject(prnt),
            m_listOfAvailablePlugIns(),
            m_listOfDescriptions(),
            m_kvc(kvc),
            m_dataStoreManager(dsm),
            m_conference(conf),
            m_parent(prnt) {
            // TODO: Read available plugins from .so-files.
            m_listOfAvailablePlugIns.push_back("ConfigurationViewer");
            m_listOfAvailablePlugIns.push_back("Controller");
            m_listOfAvailablePlugIns.push_back("BirdsEyeMap");
            m_listOfAvailablePlugIns.push_back("EnvironmentViewer");
            m_listOfAvailablePlugIns.push_back("IrUsCharts");
            m_listOfAvailablePlugIns.push_back("ModuleStatisticsViewer");
            m_listOfAvailablePlugIns.push_back("OBJXViewer");
            m_listOfAvailablePlugIns.push_back("SCNXViewer");
            m_listOfAvailablePlugIns.push_back("IrUsMap");
            m_listOfAvailablePlugIns.push_back("LiveFeed");
            m_listOfAvailablePlugIns.push_back("LogMessage");
            m_listOfAvailablePlugIns.push_back("Player");
            m_listOfAvailablePlugIns.push_back("SharedImageViewer");
            m_listOfAvailablePlugIns.push_back("Spy");
            m_listOfAvailablePlugIns.push_back("StreetMap");

            m_listOfDescriptions["ConfigurationViewer"] = tr("This plugin displays the current configuration.").toStdString();
            m_listOfDescriptions["Controller"] = tr("This plugin allows the control of the vehicle by the arrow keys.").toStdString();
            m_listOfDescriptions["BirdsEyeMap"] = tr("This plugin shows the entire environment in 2D.").toStdString();
            m_listOfDescriptions["EnvironmentViewer"] = tr("This plugin shows the entire environment in 3D.").toStdString();
            m_listOfDescriptions["IrUsCharts"] = tr("This plugin displays the values of SensorBoardData over time.").toStdString();
            m_listOfDescriptions["ModuleStatisticsViewer"] = tr("This plugin shows module statistics.").toStdString();
            m_listOfDescriptions["OBJXViewer"] = tr("This plugin shows .objx files.").toStdString();
            m_listOfDescriptions["SCNXViewer"] = tr("This plugin shows .scnx files.").toStdString();
            m_listOfDescriptions["IrUsMap"] = tr("This plugin displays the current irus readings.").toStdString();
            m_listOfDescriptions["LiveFeed"] = tr("This plugin displays all distributed visitable messages.").toStdString();
            m_listOfDescriptions["LogMessage"] = tr("This plugin displays log messages from components.").toStdString();
            m_listOfDescriptions["Player"] = tr("This plugin replays previously recorded files.").toStdString();
            m_listOfDescriptions["SharedImageViewer"] = tr("This plugin displays shared images.").toStdString();
            m_listOfDescriptions["Spy"] = tr("This plugin displays all distributed containers.").toStdString();
            m_listOfDescriptions["StreetMap"] = tr("This plugin visualizes the environment data using a map tile provider.").toStdString();
        }

        PlugInProvider::~PlugInProvider() {
            PlugInProvider::m_singleton = NULL;
        }

        PlugInProvider& PlugInProvider::getInstance(const KeyValueConfiguration &kvc, DataStoreManager &dsm, ContainerConference &conf, QWidget *prnt) {
            {
                Lock l(PlugInProvider::m_singletonMutex);
                if (PlugInProvider::m_singleton == NULL) {
                    PlugInProvider::m_singleton = new PlugInProvider(kvc, dsm, conf, prnt);
                }
            }

            return (*PlugInProvider::m_singleton);
        }

        const vector<string> PlugInProvider::getListOfAvailablePlugIns() const {
            return m_listOfAvailablePlugIns;
        }

        string PlugInProvider::getDescriptionForPlugin(const string &pluginName) {
          return m_listOfDescriptions[pluginName];
        }

        odcore::SharedPointer<PlugIn> PlugInProvider::createPlugIn(const string &name) {
            odcore::SharedPointer<PlugIn> plugIn;

            if (name == "ConfigurationViewer") {
                cerr << "Creating ConfigurationViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new configurationviewer::ConfigurationViewerPlugIn("ConfigurationViewer", m_kvc, m_parent));
            } else if (name == "Controller") {
                cerr << "Creating Controller" << endl;
                plugIn = odcore::SharedPointer<PlugIn>((PlugIn*)(new controller::ControllerPlugIn("Controller", m_kvc, m_conference, m_parent)));
            }
            else if (name == "BirdsEyeMap") {
                cerr << "Creating BirdsEyeMap" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new birdseyemap::BirdsEyeMapPlugIn("BirdsEyeMap", m_kvc, m_parent));
            }
            else if (name == "EnvironmentViewer") {
                cerr << "Creating EnvironmentViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new environmentviewer::EnvironmentViewerPlugIn("EnvironmentViewer", m_kvc, m_parent));
            }
            else if (name == "IrUsCharts") {
                cerr << "Creating IrUsCharts" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new iruscharts::IrUsChartsPlugIn("IrUsCharts", m_kvc, m_parent));
            }
            else if (name == "ModuleStatisticsViewer") {
                cerr << "Creating ModuleStatisticsViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new modulestatisticsviewer::ModuleStatisticsViewerPlugIn("ModuleStatisticsViewer", m_kvc, m_parent));
            }
            else if (name == "OBJXViewer") {
                cerr << "Creating OBJXViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new objxviewer::OBJXViewerPlugIn("OBJXViewer", m_kvc, m_parent));
            }
            else if (name == "SCNXViewer") {
                cerr << "Creating SCNXViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new scnxviewer::SCNXViewerPlugIn("SCNXViewer", m_kvc, m_parent));
            }
            else if (name == "IrUsMap") {
                cerr << "Creating IrUsMap" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new irusmap::IrUsMapPlugIn("IrUsMap", m_kvc, m_parent));
            } else if (name == "LiveFeed") {
                cerr << "Creating LiveFeed" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new livefeed::LiveFeedPlugIn("LiveFeed", m_kvc, m_parent));
            } else if (name == "LogMessage") {
                cerr << "Creating LogMessage" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new logmessage::LogMessagePlugIn("LogMessage", m_kvc, m_parent));
            } else if (name == "Player") {
                cerr << "Creating Player" << endl;
                plugIn = odcore::SharedPointer<PlugIn>((PlugIn*)(new player::PlayerPlugIn("Player", m_kvc, m_conference, m_parent)));
            } else if (name == "SharedImageViewer") {
                cerr << "Creating SharedImageViewer" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new sharedimageviewer::SharedImageViewerPlugIn("SharedImageViewer", m_kvc, m_parent));
            } else if (name == "Spy") {
                cerr << "Creating Spy" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new spy::SpyPlugIn("Spy", m_kvc, m_parent));
            } else if (name == "StreetMap") {
                cerr << "Creating StreetMap" << endl;
                plugIn = odcore::SharedPointer<PlugIn>(new streetmap::StreetMapPlugIn("StreetMap", m_kvc, m_parent));
            }

            return plugIn;
        }

        odcore::SharedPointer<PlugIn> PlugInProvider::getPlugIn(const string &name) {
            odcore::SharedPointer<PlugIn> plugIn;

            // Check if the plugin exists.
            vector<string>::const_iterator it = m_listOfAvailablePlugIns.begin();
            while (it != m_listOfAvailablePlugIns.end()) {
                if ((*it) == name) {
                    break;
                }
                it++;
            }

            if (it != m_listOfAvailablePlugIns.end()) {
                plugIn = createPlugIn(*it);
            }

            return plugIn;
        }
    }
}

