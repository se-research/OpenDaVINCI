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

#include "opendavinci/odcore/opendavinci.h"
#include "plugins/runtimeconfiguration/RuntimeConfigurationPlugIn.h"
#include "plugins/runtimeconfiguration/RuntimeConfigurationWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace runtimeconfiguration {

            using namespace odcore::io::conference;

            RuntimeConfigurationPlugIn::RuntimeConfigurationPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt) :
                ControlPlugIn(name, kvc, conf, multiplexer, prnt),
                m_runtimeConfigurationWidget(NULL) {
                setDescription("This plugin allows to interactively provide configuration parameters to the running software modules.");
            }

            RuntimeConfigurationPlugIn::~RuntimeConfigurationPlugIn() {}

            void RuntimeConfigurationPlugIn::setupPlugin() {
                m_runtimeConfigurationWidget = new RuntimeConfigurationWidget(*this, getKeyValueConfiguration(), getConference(), getParentQWidget());
            }

            void RuntimeConfigurationPlugIn::stopPlugin() {}

            QWidget* RuntimeConfigurationPlugIn::getQWidget() const {
                return m_runtimeConfigurationWidget;
            }
        }
    }
}

