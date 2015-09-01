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

#ifndef COCKPIT_PLUGINS_PLUGINPROVIDER_H_
#define COCKPIT_PLUGINS_PLUGINPROVIDER_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include <string>
#include <vector>
#include <map>

#include "QtIncludes.h"

// native.h must be included as first header file for definition of _WIN32_WINNT.
#include "core/native.h"

#include "core/SharedPointer.h"
#include "core/base/KeyValueConfiguration.h"
#include "core/base/Mutex.h"
#include "core/base/DataStoreManager.h"
#include "core/io/conference/ContainerConference.h"

#include "plugins/PlugIn.h"

namespace cockpit {

    namespace plugins {

        using namespace std;

        /**
         * This class provides all available plugins.
         */
        class PlugInProvider : public QObject {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                PlugInProvider(const PlugInProvider &);
                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                PlugInProvider& operator=(const PlugInProvider &);

            private:
                /**
                 * Constructor.
                 *
                 * @param kvc KeyValueConfiguration for this GL-based widget.
                 * @param dsm DataStoreManager to be used for adding DataStores.
                 * @param conf Container conference to send data to.
                 * @param prnt Pointer to the container super window.
                 */
                PlugInProvider(const core::base::KeyValueConfiguration &kvc, core::base::DataStoreManager &dsm, core::io::conference::ContainerConference &conf, QWidget *prnt);

            public:
                virtual ~PlugInProvider();

                /**
                 * This method returns a static instance for this factory.
                 *
                 * @param kvc KeyValueConfiguration for this widget.
                 * @param dsm DataStoreManager to be used for adding DataStores.
                 * @param conf Container conference to send data to.
                 * @param prnt Pointer to the container super window.
                 * @return Instance of this factory.
                 */
                static PlugInProvider& getInstance(const core::base::KeyValueConfiguration &kvc, core::base::DataStoreManager &dsm, core::io::conference::ContainerConference &conf, QWidget *prnt);

                /**
                 * This method returns the list of available plugins.
                 *
                 * @return List of available plugins.
                 */
                const vector<string> getListOfAvailablePlugIns() const;

                /**
                 * This method returns the list of available master plugins.
                 *
                 * @return List of available master plugins.
                 */
                const vector<string> getListOfAvailableMasterPlugIns() const;

                /**
                 * This method returns the description for the given Plugin.
                 *
                 * @param pluginName Name of the Plugin.
                 * @return Description.
                 */
                string getDescriptionForPlugin(const string &pluginName);

                /**
                 * This method returns the plugin for the given name.
                 *
                 * @param name Name of the plugin.
                 * @return Plugin.
                 */
                core::SharedPointer<PlugIn> getPlugIn(const string &name);

            private:
                static core::base::Mutex m_singletonMutex;
                static PlugInProvider* m_singleton;

                vector<string> m_listOfAvailablePlugIns;
                map<string,string> m_listOfDescriptions;
                core::base::KeyValueConfiguration m_kvc;
                core::base::DataStoreManager &m_dataStoreManager;
                core::io::conference::ContainerConference &m_conference;
                QWidget *m_parent;

                /**
                 * This method creates a new instance for the given name.
                 *
                 * @param name Name of the plugin.
                 * @return New instance.
                 */
                core::SharedPointer<PlugIn> createPlugIn(const string &name);
        };

    } // plugins

} // cockpit

#endif /*COCKPIT_PLUGINS_PLUGINPROVIDER_H_*/

