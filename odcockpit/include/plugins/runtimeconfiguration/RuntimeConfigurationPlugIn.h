/**
 * cockpit - Visualization environment
 * Copyright (C) 2017 Christian Berger
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

#ifndef RUNTIMECONFIGURATION_H_
#define RUNTIMECONFIGURATION_H_

#include <string>

#include "plugins/ControlPlugIn.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace runtimeconfiguration {

class RuntimeConfigurationWidget;

          class RuntimeConfigurationPlugIn : public ControlPlugIn {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 */
                RuntimeConfigurationPlugIn(const RuntimeConfigurationPlugIn &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 */
                RuntimeConfigurationPlugIn& operator=(const RuntimeConfigurationPlugIn &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param name Name of this plugin.
                 * @param kvc KeyValueConfiguration for this based widget.
                 * @param conf Client conference to send data to.
                 * @param prnt Pointer to the containing super window.
                 */
                RuntimeConfigurationPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt);

                virtual ~RuntimeConfigurationPlugIn();

                virtual QWidget* getQWidget() const;

                virtual void setupPlugin();

                virtual void stopPlugin();

            private:
                RuntimeConfigurationWidget *m_runtimeConfigurationWidget;
            };

        }
    }
}

#endif /*RUNTIMECONFIGURATION_H_*/

