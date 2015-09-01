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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include "plugins/ControlPlugIn.h"
#include "plugins/controller/ControllerWidget.h"

namespace cockpit {

    namespace plugins {

        namespace controller {

          class ControllerPlugIn : public ControlPlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                ControllerPlugIn(const ControllerPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                ControllerPlugIn& operator=(const ControllerPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this based widget.
                 * @param conf Client conference to send data to.
                 * @param prnt Pointer to the containing super window.
                 */
                ControllerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, core::io::conference::ContainerConference &conf, QWidget *prnt);

                virtual ~ControllerPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                ControllerWidget *m_controllerWidget;
            };

        }
    }
}

#endif /*CONTROLLER_H_*/

