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

#ifdef PANDABOARD
#include <stdc-predef.h>
#endif

#include "plugins/player/PlayerPlugIn.h"

namespace cockpit {

    namespace plugins {

        namespace player {

            using namespace std;

            PlayerPlugIn::PlayerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, core::io::conference::ContainerConference &conf, QWidget *prnt) :
                ControlPlugIn(name, kvc, conf, prnt),
                m_kvc(kvc),
                m_playerWidget(NULL) {
                setDescription("This plugin replays previously recorded files.");
            }

            PlayerPlugIn::~PlayerPlugIn() {}

            void PlayerPlugIn::setupPlugin() {
                m_playerWidget = new PlayerWidget(*this, m_kvc, getConference(), getParentQWidget());
            }

            void PlayerPlugIn::stopPlugin() {}

            QWidget* PlayerPlugIn::getQWidget() const {
                return m_playerWidget;
            }
        }
    }
}
