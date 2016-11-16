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
#include "ContainerObserver.h"
#include "plugins/performancemonitor/PerformanceMonitorPlugIn.h"
#include "plugins/performancemonitor/PerformanceMonitorWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace performancemonitor {

            PerformanceMonitorPlugIn::PerformanceMonitorPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(name, kvc, prnt),
                m_viewerWidget(NULL),
                m_cpu_history(3),
                m_mem_history(3) {
                setDescription("This plugin displays cpu and memory usage statistics of components.");
                bool found=false;
                string s = kvc.getOptionalValue<string>("odcockpit.performancemonitor.history.cpu",found);
                if(found)
                    m_cpu_history=std::stoi(s);
                found=false;
                s = kvc.getOptionalValue<string>("odcockpit.performancemonitor.history.mem",found);
                if(found)
                    m_mem_history=std::stoi(s);
            }

            PerformanceMonitorPlugIn::~PerformanceMonitorPlugIn() {}

            void PerformanceMonitorPlugIn::setupPlugin() {
                m_viewerWidget = new PerformanceMonitorWidget(*this, getParentQWidget(), m_cpu_history, m_mem_history);

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_viewerWidget);
                }
            }

            void PerformanceMonitorPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_viewerWidget);
                }
            }

            QWidget* PerformanceMonitorPlugIn::getQWidget() const {
                return m_viewerWidget;
            }
        }
    }
}
