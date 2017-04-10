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

#include "opendavinci/odcore/opendavinci.h"
#include "ContainerObserver.h"
#include "plugins/startstop/StartStopPlugIn.h"
#include "plugins/startstop/StartStopWidget.h"

class QWidget;
namespace cockpit { class ContainerObserver; }
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace startstop {

            using namespace odcore::io::conference;

            StartStopPlugIn::StartStopPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, ContainerConference &conf, FIFOMultiplexer &multiplexer, QWidget *prnt) :
                ControlPlugIn(name, kvc, conf, multiplexer, prnt),
                m_startStopWidget(NULL) {
                setDescription("This plugin allows to activate/deactivate autonomous control of the vehicle.");
            }

            StartStopPlugIn::~StartStopPlugIn() {}

            void StartStopPlugIn::setupPlugin() {
                m_startStopWidget = new StartStopWidget(*this, getKeyValueConfiguration(), getConference(), getParentQWidget());

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_startStopWidget);
                }

            }

            void StartStopPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_startStopWidget);
                }
            }

            QWidget* StartStopPlugIn::getQWidget() const {
                return m_startStopWidget;
            }
        }
    }
}

