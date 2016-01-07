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

#include "core/opendavinci.h"
#include "ContainerObserver.h"
#include "plugins/controller/ControllerPlugIn.h"
#include "plugins/controller/ControllerWidget.h"

class QWidget;
namespace cockpit { class ContainerObserver; }
namespace core { namespace base { class KeyValueConfiguration; } }
namespace core { namespace io { namespace conference { class ContainerConference; } } }

namespace cockpit {

    namespace plugins {

        namespace controller {

            using namespace core::io::conference;

            ControllerPlugIn::ControllerPlugIn(const string &name, const core::base::KeyValueConfiguration &kvc, ContainerConference &conf, QWidget *prnt) :
                ControlPlugIn(name, kvc, conf, prnt),
                m_controllerWidget(NULL) {
                setDescription("This plugin allows the control of the vehicle by the arrow keys.");
            }

            ControllerPlugIn::~ControllerPlugIn() {}

            void ControllerPlugIn::setupPlugin() {
                m_controllerWidget = new ControllerWidget(*this, getKeyValueConfiguration(), getConference(), getParentQWidget());

                ContainerObserver *co = getContainerObserver();
                if (co != NULL) {
                    co->addContainerListener(m_controllerWidget);
                }

            }

            void ControllerPlugIn::stopPlugin() {
                ContainerObserver *co = getContainerObserver();

                if (co != NULL) {
                    co->removeContainerListener(m_controllerWidget);
                }
            }

            QWidget* ControllerPlugIn::getQWidget() const {
                return m_controllerWidget;
            }
        }
    }
}

