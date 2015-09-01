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

#include "core/macros.h"

#include "QtIncludes.h"
#include "ContainerObserver.h"
#include "plugins/environmentviewer/EnvironmentViewerPlugIn.h"

namespace cockpit {
    namespace plugins {
        namespace environmentviewer {

            using namespace core::base;

            EnvironmentViewerPlugIn::EnvironmentViewerPlugIn(const string &name, const KeyValueConfiguration &kvc, QWidget* prnt) :
                    PlugIn(name, kvc, prnt),
                    m_widget(NULL) {
                setDescription("This plugin shows the entire environment in 3D.");
            }

            EnvironmentViewerPlugIn::~EnvironmentViewerPlugIn() {
            }

            void EnvironmentViewerPlugIn::setupPlugin() {
                m_widget = new EnvironmentViewerWidget(*this, getParentQWidget());

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_widget);
                }
            }

            void EnvironmentViewerPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_widget);
                }
            }

            QWidget* EnvironmentViewerPlugIn::getQWidget() const {
                return m_widget;
            }
        }
    }
} // plugins::scnxviewer

