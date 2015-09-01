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

#include "ContainerObserver.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerPlugIn.h"
#include "plugins/modulestatisticsviewer/ModuleStatisticsViewerWidget.h"

namespace cockpit {
    namespace plugins {
        namespace modulestatisticsviewer {

            ModuleStatisticsViewerPlugIn::ModuleStatisticsViewerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                    PlugIn(name, kvc, prnt),
                    m_modulestatisticsViewerWidget(NULL) {
                setDescription("This plugin shows module statistics.");
            }

            ModuleStatisticsViewerPlugIn::~ModuleStatisticsViewerPlugIn() {
                // The widget m_modulestatisticsViewerWidget will be destroyed by Qt.
            }

            void ModuleStatisticsViewerPlugIn::setupPlugin() {
                m_modulestatisticsViewerWidget = new ModuleStatisticsViewerWidget(*this, getParentQWidget());

                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_modulestatisticsViewerWidget);
                }
            }

            void ModuleStatisticsViewerPlugIn::stopPlugin() {
                cockpit::ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->removeContainerListener(m_modulestatisticsViewerWidget);
                }
            }

            QWidget* ModuleStatisticsViewerPlugIn::getQWidget() const {
                return m_modulestatisticsViewerWidget;
            }
        }
    }
} // cockpit::plugins::modulestatistics
