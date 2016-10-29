/**
 * cockpit - Visualization environment
 * Copyright (C) 2012 - 2015 Christian Berger
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
#include "plugins/livefeed/LiveFeedPlugIn.h"
#include "plugins/livefeed/LiveFeedWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace livefeed {

            LiveFeedPlugIn::LiveFeedPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(name, kvc, prnt),
                m_kvc(kvc),
                m_viewerWidget(NULL) {
                setDescription("This plugin displays all distributed containers.");
            }

            LiveFeedPlugIn::~LiveFeedPlugIn() {}

            void LiveFeedPlugIn::setupPlugin() {
                m_viewerWidget = new LiveFeedWidget(m_kvc, *this, getParentQWidget());

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_viewerWidget);
                }
            }

            void LiveFeedPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_viewerWidget);
                }
            }

            QWidget* LiveFeedPlugIn::getQWidget() const {
                return m_viewerWidget;
            }
        }
    }
}
