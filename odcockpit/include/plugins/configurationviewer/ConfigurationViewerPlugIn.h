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

#ifndef CONFIGURATIONVIEWER_H_
#define CONFIGURATIONVIEWER_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include "plugins/PlugIn.h"
#include "plugins/configurationviewer/ConfigurationViewerWidget.h"

namespace cockpit {

    namespace plugins {

        namespace configurationviewer {

          class ConfigurationViewerPlugIn : public PlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ConfigurationViewerPlugIn(const ConfigurationViewerPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ConfigurationViewerPlugIn& operator=(const ConfigurationViewerPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this based widget.
                 * @param prnt Pointer to the containing super window.
                 */
                ConfigurationViewerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget *prnt);

                virtual ~ConfigurationViewerPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                ConfigurationViewerWidget *m_viewerWidget;
            };

        }
    }
}

#endif /*CONFIGURATIONVIEWER_H_*/

