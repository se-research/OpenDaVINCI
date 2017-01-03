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
#include "plugins/player2/Player2PlugIn.h"
#include "plugins/player2/Player2Widget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }
namespace odcore { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace player2 {

            using namespace std;

            Player2PlugIn::Player2PlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, odcore::io::conference::ContainerConference &conf, QWidget *prnt) :
                ControlPlugIn(name, kvc, conf, prnt),
                m_kvc(kvc),
                m_player2Widget(NULL) {
                setDescription("This plugin replays previously recorded files.");
            }

            Player2PlugIn::~Player2PlugIn() {}

            void Player2PlugIn::setupPlugin() {
                m_player2Widget = new Player2Widget(*this, m_kvc, getConference(), getParentQWidget());
            }

            void Player2PlugIn::stopPlugin() {}

            QWidget* Player2PlugIn::getQWidget() const {
                return m_player2Widget;
            }
        }
    }
}
