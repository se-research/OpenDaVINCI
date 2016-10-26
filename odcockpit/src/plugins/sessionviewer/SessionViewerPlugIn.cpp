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
#include "opendavinci/odcore/strings/StringToolbox.h"
#include "ContainerObserver.h"
#include "plugins/sessionviewer/SessionViewerPlugIn.h"
#include "plugins/sessionviewer/SessionViewerWidget.h"

class QWidget;
namespace odcore { namespace base { class KeyValueConfiguration; } }

namespace cockpit {

    namespace plugins {

        namespace sessionviewer {

            SessionViewerPlugIn::SessionViewerPlugIn(const string &name, const odcore::base::KeyValueConfiguration &kvc, QWidget *prnt) :
                PlugIn(name, kvc, prnt),
                m_viewerWidget(NULL),
                m_listOfExpectedModulesToParticipate() {
                setDescription("This plugin displays currently running modules.");
                try {
                    string s = kvc.getValue<string>("global.session.expectedModules");
                    m_listOfExpectedModulesToParticipate = odcore::strings::StringToolbox::split(s, ',');
                }
                catch(...) {}
            }

            SessionViewerPlugIn::~SessionViewerPlugIn() {}

            void SessionViewerPlugIn::setupPlugin() {
                m_viewerWidget = new SessionViewerWidget(*this, getParentQWidget(), m_listOfExpectedModulesToParticipate);

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_viewerWidget);
                }
            }

            void SessionViewerPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_viewerWidget);
                }
            }

            QWidget* SessionViewerPlugIn::getQWidget() const {
                return m_viewerWidget;
            }
        }
    }
}
