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

#include <ctype.h>

#include <algorithm>
#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Lock.h"
#include "plugins/PlugInProvider.h"
#include "plugins/birdseyemap/BirdsEyeMapPlugIn.h"
#include "plugins/configurationviewer/ConfigurationViewerPlugIn.h"
#include "plugins/controller/ControllerPlugIn.h"
#include "plugins/environmentviewer/EnvironmentViewerPlugIn.h"
#include "plugins/healthstatusviewer/HealthStatusViewerPlugIn.h"
#include "plugins/irusmap/IrUsMapPlugIn.h"
#include "plugins/livefeed/LiveFeedPlugIn.h"
#include "plugins/logmessage/LogMessagePlugIn.h"
#ifdef HAVE_QWT5QT4
    #include "plugins/iruscharts/IrUsChartsPlugIn.h"
    #include "plugins/modulestatisticsviewer/ModuleStatisticsViewerPlugIn.h"
#endif
#include "plugins/objxviewer/OBJXViewerPlugIn.h"
#include "plugins/player/PlayerPlugIn.h"
#include "plugins/player2/Player2PlugIn.h"
#include "plugins/scnxviewer/SCNXViewerPlugIn.h"
#include "plugins/sessionviewer/SessionViewerPlugIn.h"
#include "plugins/sharedimageviewer/SharedImageViewerPlugIn.h"
#include "plugins/streetmapviewer/StreetMapPlugIn.h"
#include "plugins/startstop/StartStopPlugIn.h"
#include "plugins/truckmap/TruckMapPlugIn.h"

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

            // Read list of allowed plugins to show.
            string listOfPlugins;
            try {
                listOfPlugins = m_kvc.getValue<string>("odcockpit.plugins");
                std::transform(listOfPlugins.begin(), listOfPlugins.end(), listOfPlugins.begin(), ::tolower);
                cout << "[odcockpit] Showing plugins: " << listOfPlugins << endl;
            }
            catch(...){}

            // TODO: Read available plugins from .so-files.
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("birdseyemap") != string::npos) )
                m_listOfAvailablePlugIns.push_back("BirdsEyeMap");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("configurationviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("ConfigurationViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("controller") != string::npos) )
                m_listOfAvailablePlugIns.push_back("Controller");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("environmentviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("EnvironmentViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("healthstatusviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("HealthStatusViewer");
#ifdef HAVE_QWT5QT4
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("iruscharts") != string::npos) )
                m_listOfAvailablePlugIns.push_back("IrUsCharts");
#endif
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("irusmaps") != string::npos) )
                m_listOfAvailablePlugIns.push_back("IrUsMap");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("livefeed") != string::npos) )
                m_listOfAvailablePlugIns.push_back("LiveFeed");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("logmessage") != string::npos) )
                m_listOfAvailablePlugIns.push_back("LogMessage");
#ifdef HAVE_QWT5QT4
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("modulestatisticsviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("ModuleStatisticsViewer");
#endif
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("objxviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("OBJXViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("player") != string::npos) )
                m_listOfAvailablePlugIns.push_back("Player");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("player2") != string::npos) )
                m_listOfAvailablePlugIns.push_back("Player2");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("scnxviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("SCNXViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("sessionviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("SessionViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("sharedimageviewer") != string::npos) )
                m_listOfAvailablePlugIns.push_back("SharedImageViewer");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("startstop") != string::npos) )
                m_listOfAvailablePlugIns.push_back("StartStop");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("streetmap") != string::npos) )
                m_listOfAvailablePlugIns.push_back("StreetMap");
            if ( (listOfPlugins.size() == 0) || (listOfPlugins.find("truckmap") != string::npos) )
                m_listOfAvailablePlugIns.push_back("TruckMap");


            m_listOfDescriptions["ConfigurationViewer"] = tr("This plugin displays the current configuration.").toStdString();
            m_listOfDescriptions["Controller"] = tr("This plugin allows the control of the vehicle by the arrow keys.").toStdString();
            m_listOfDescriptions["BirdsEyeMap"] = tr("This plugin shows the entire environment in 2D.").toStdString();
            m_listOfDescriptions["EnvironmentViewer"] = tr("This plugin shows the entire environment in 3D.").toStdString();
            m_listOfDescriptions["HealthStatusViewer"] = tr("This plugin displays the system's health.").toStdString();
#ifdef HAVE_QWT5QT4
            m_listOfDescriptions["IrUsCharts"] = tr("This plugin displays the values of SensorBoardData over time.").toStdString();
            m_listOfDescriptions["ModuleStatisticsViewer"] = tr("This plugin shows module statistics.").toStdString();
#endif
            m_listOfDescriptions["OBJXViewer"] = tr("This plugin shows .objx files.").toStdString();
            m_listOfDescriptions["SCNXViewer"] = tr("This plugin shows .scnx files.").toStdString();
            m_listOfDescriptions["IrUsMap"] = tr("This plugin displays the current irus readings.").toStdString();
            m_listOfDescriptions["LiveFeed"] = tr("This plugin displays all distributed visitable messages.").toStdString();
            m_listOfDescriptions["LogMessage"] = tr("This plugin displays log messages from components.").toStdString();
            m_listOfDescriptions["Player"] = tr("This plugin replays previously recorded files.").toStdString();
            m_listOfDescriptions["Player2"] = tr("This plugin replays previously recorded files.").toStdString();
            m_listOfDescriptions["SessionViewer"] = tr("This plugin displays currently running modules.").toStdString();
            m_listOfDescriptions["SharedImageViewer"] = tr("This plugin displays shared images.").toStdString();
            m_listOfDescriptions["StartStop"] = tr("This plugin allows to activate/deactivate autonomous control of the vehicle.").toStdString();
            m_listOfDescriptions["StreetMap"] = tr("This plugin visualizes the environment data using a map tile provider.").toStdString();
            m_listOfDescriptions["TruckMap"] = tr("This plugin visualizes the environment data for the truck.").toStdString();
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

        std::shared_ptr<PlugIn> PlugInProvider::createPlugIn(const string &name) {
            std::shared_ptr<PlugIn> plugIn;

            if (name == "ConfigurationViewer") {
                cerr << "[odcockpit] Creating plugin: ConfigurationViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new configurationviewer::ConfigurationViewerPlugIn("ConfigurationViewer", m_kvc, m_parent));
            } else if (name == "Controller") {
                cerr << "[odcockpit] Creating plugin: Controller" << endl;
                plugIn = std::shared_ptr<PlugIn>((PlugIn*)(new controller::ControllerPlugIn("Controller", m_kvc, m_conference, m_parent)));
            } else if (name == "StartStop") {
                cerr << "[odcockpit] Creating plugin: StartStop" << endl;
                plugIn = std::shared_ptr<PlugIn>((PlugIn*)(new startstop::StartStopPlugIn("StartStop", m_kvc, m_conference, m_parent)));
            }
            else if (name == "BirdsEyeMap") {
                cerr << "[odcockpit] Creating plugin: BirdsEyeMap" << endl;
                plugIn = std::shared_ptr<PlugIn>(new birdseyemap::BirdsEyeMapPlugIn("BirdsEyeMap", m_kvc, m_parent));
            }
            else if (name == "EnvironmentViewer") {
                cerr << "[odcockpit] Creating plugin: EnvironmentViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new environmentviewer::EnvironmentViewerPlugIn("EnvironmentViewer", m_kvc, m_parent));
            }
#ifdef HAVE_QWT5QT4
            else if (name == "IrUsCharts") {
                cerr << "[odcockpit] Creating plugin: IrUsCharts" << endl;
                plugIn = std::shared_ptr<PlugIn>(new iruscharts::IrUsChartsPlugIn("IrUsCharts", m_kvc, m_parent));
            }
            else if (name == "ModuleStatisticsViewer") {
                cerr << "[odcockpit] Creating plugin: ModuleStatisticsViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new modulestatisticsviewer::ModuleStatisticsViewerPlugIn("ModuleStatisticsViewer", m_kvc, m_parent));
            }
#endif
            else if (name == "OBJXViewer") {
                cerr << "[odcockpit] Creating plugin: OBJXViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new objxviewer::OBJXViewerPlugIn("OBJXViewer", m_kvc, m_parent));
            }
            else if (name == "SCNXViewer") {
                cerr << "[odcockpit] Creating plugin: SCNXViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new scnxviewer::SCNXViewerPlugIn("SCNXViewer", m_kvc, m_parent));
            } else if (name == "HealthStatusViewer") {
                cerr << "[odcockpit] Creating plugin: HealthStatusViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new healthstatusviewer::HealthStatusViewerPlugIn("HealthStatusViewer", m_kvc, m_parent));
            }
            else if (name == "IrUsMap") {
                cerr << "[odcockpit] Creating plugin: IrUsMap" << endl;
                plugIn = std::shared_ptr<PlugIn>(new irusmap::IrUsMapPlugIn("IrUsMap", m_kvc, m_parent));
            }
            else if (name == "TruckMap") {
                cerr << "[odcockpit] Creating plugin: TruckMap" << endl;
                plugIn = std::shared_ptr<PlugIn>(new truckmap::TruckMapPlugIn("TruckMap", m_kvc, m_parent));
            } else if (name == "LiveFeed") {
                cerr << "[odcockpit] Creating plugin: LiveFeed" << endl;
                plugIn = std::shared_ptr<PlugIn>(new livefeed::LiveFeedPlugIn("LiveFeed", m_kvc, m_parent));
            } else if (name == "LogMessage") {
                cerr << "[odcockpit] Creating plugin: LogMessage" << endl;
                plugIn = std::shared_ptr<PlugIn>(new logmessage::LogMessagePlugIn("LogMessage", m_kvc, m_parent));
            } else if (name == "Player") {
                cerr << "[odcockpit] Creating plugin: Player" << endl;
                plugIn = std::shared_ptr<PlugIn>((PlugIn*)(new player::PlayerPlugIn("Player", m_kvc, m_conference, m_parent)));
            } else if (name == "Player2") {
                cerr << "[odcockpit] Creating plugin: Player2" << endl;
                plugIn = std::shared_ptr<PlugIn>((PlugIn*)(new player2::Player2PlugIn("Player2", m_kvc, m_conference, m_parent)));
            } else if (name == "SessionViewer") {
                cerr << "[odcockpit] Creating plugin: SessionViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new sessionviewer::SessionViewerPlugIn("SessionViewer", m_kvc, m_parent));
            } else if (name == "SharedImageViewer") {
                cerr << "[odcockpit] Creating plugin: SharedImageViewer" << endl;
                plugIn = std::shared_ptr<PlugIn>(new sharedimageviewer::SharedImageViewerPlugIn("SharedImageViewer", m_kvc, m_parent));
            } else if (name == "StreetMap") {
                cerr << "[odcockpit] Creating plugin: StreetMap" << endl;
                plugIn = std::shared_ptr<PlugIn>(new streetmap::StreetMapPlugIn("StreetMap", m_kvc, m_parent));
            }

            return plugIn;
        }

        std::shared_ptr<PlugIn> PlugInProvider::getPlugIn(const string &name) {
            std::shared_ptr<PlugIn> plugIn;

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

