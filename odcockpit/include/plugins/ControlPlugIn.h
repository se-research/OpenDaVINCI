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

#ifndef COCKPIT_PLUGINS_CONTROLPLUGIN_H_
#define COCKPIT_PLUGINS_CONTROLPLUGIN_H_

#include "core/io/conference/ContainerConference.h"
#include "plugins/PlugIn.h"

namespace cockpit {

    namespace plugins {

        using namespace std;

        /**
         * This class is the main class for all plugins that are able to send data.
         */
        class ControlPlugIn : public PlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ControlPlugIn(const ControlPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ControlPlugIn& operator=(const ControlPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this plugin.
                 * @param conf client conference to send data to.
                 * @param prnt Pointer to the containing super window.
                 */
                ControlPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, core::io::conference::ContainerConference &conf, QWidget* prnt);

                virtual ~ControlPlugIn();

                /**
                 * This method returns the container conference for this widget.
                 *
                 * @return ContainerConference.
                 */
                core::io::conference::ContainerConference& getConference() const;

            private:
                core::io::conference::ContainerConference &m_conference;
        };

    } // plugins

} // cockpit

#endif /*COCKPIT_PLUGINS_CONTROLPLUGIN_H_*/

