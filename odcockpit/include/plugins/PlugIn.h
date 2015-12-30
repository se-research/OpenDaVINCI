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

#ifndef COCKPIT_PLUGINS_PLUGIN_H_
#define COCKPIT_PLUGINS_PLUGIN_H_

#include <string>

#include "core/base/KeyValueConfiguration.h"
#include "core/base/Mutex.h"

class QWidget;
namespace cockpit { class ContainerObserver; }

namespace cockpit {

    namespace plugins {

        using namespace std;

        /**
         * This class is the main class for all plugins.
         */
        class PlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                PlugIn(const PlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                PlugIn& operator=(const PlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this plugin.
                 * @param prnt Pointer to the containing super window.
                 */
                PlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget* prnt);

                virtual ~PlugIn();

                /**
                 * This method must be overridden in subclasses to setup
                 * this plugin, i.e. construct all necessary GUI elements.
                 */
                virtual void setupPlugin() = 0;

                /**
                 * This method must be overridden in subclasses to stop
                 * this plugin right before destruction.
                 */
                virtual void stopPlugin() = 0;

                /**
                 * This method returns the widget on which all content is drawn.
                 *
                 * @return Widget on which all content is drawn.
                 */
                virtual QWidget* getQWidget() const = 0;

                /**
                 * This method returns the container observer or NULL.
                 *
                 * @return ContainerObserver to be used.
                 */
                cockpit::ContainerObserver* getContainerObserver() const;

                /**
                 * This method sets the container observer to be used.
                 *
                 * @param containerObserver ContainerObserver to be used.
                 */
                void setContainerObserver(cockpit::ContainerObserver *containerObserver);

                /**
                 * This method returns the name of this plugin.
                 *
                 * @return Name of this plugin.
                 */
                const string getName() const;

                /**
                 * This method sets the description of the plugin.
                 *
                 * @param description Description.
                 */
                void setDescription(const string &description);

                /**
                 * This method returns a simple description for the
                 * plugin.
                 *
                 * @return Description of this plugin.
                 */
                const string getDescription() const;

                /**
                 * This method returns the parental widget.
                 *
                 * @return Parental widget.
                 */
                QWidget* getParentQWidget();

                /**
                 * This method returns the configuration for this widget.
                 *
                 * @return KeyValueConfiguration.
                 */
                const core::base::KeyValueConfiguration getKeyValueConfiguration() const;

            private:
                QWidget *m_parent;
                const string m_name;
                string m_description;
                const core::base::KeyValueConfiguration &m_kvc;
                mutable core::base::Mutex m_containerObserverMutex;
                cockpit::ContainerObserver *m_containerObserver;
        };

    } // plugins

} // cockpit

#endif /*COCKPIT_PLUGINS_PLUGIN_H_*/

