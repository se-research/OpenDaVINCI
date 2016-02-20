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

#include "opendavinci/odcore/opendavinci.h"
#include "plugins/configurationviewer/ConfigurationViewerPlugIn.h"
#include "plugins/configurationviewer/ConfigurationViewerWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace configurationviewer {

            ConfigurationViewerPlugIn::ConfigurationViewerPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(name, kvc, prnt),
                m_viewerWidget(NULL) {
                setDescription("This plugin displays the current configuration.");
            }

            ConfigurationViewerPlugIn::~ConfigurationViewerPlugIn() {}

            void ConfigurationViewerPlugIn::setupPlugin() {
                m_viewerWidget = new ConfigurationViewerWidget(*this, getKeyValueConfiguration(), getParentQWidget());
            }

            void ConfigurationViewerPlugIn::stopPlugin() {}

            QWidget* ConfigurationViewerPlugIn::getQWidget() const {
                return m_viewerWidget;
            }
        }
    }
}

