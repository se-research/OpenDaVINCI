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

#ifndef STARTSTOP_H_
#define STARTSTOP_H_

#include <string>

#include "plugins/ControlPlugIn.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace startstop {

class StartStopWidget;

          class StartStopPlugIn : public ControlPlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                StartStopPlugIn(const StartStopPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                StartStopPlugIn& operator=(const StartStopPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this based widget.
                 * @param conf Client conference to send data to.
                 * @param prnt Pointer to the containing super window.
                 */
                StartStopPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt);

                virtual ~StartStopPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                StartStopWidget *m_startStopWidget;
            };

        }
    }
}

#endif /*STARTSTOP_H_*/

